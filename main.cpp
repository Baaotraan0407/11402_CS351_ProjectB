#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <chrono>


using namespace std;

vector<string> split(const string& line) {
    vector<string> result;
    stringstream ss(line);
    string item;

    while (getline(ss, item, ',')) {
        result.push_back(item);
    }

    return result;
}

struct Table {
    vector<string> headers;
    vector<vector<string>> rows;
    unordered_map<string, vector<int>> cityIndex;
};

void selectAll(const Table& table) {
    for (auto h : table.headers) cout << h << "\t";
    cout << endl;

    for (auto row : table.rows) {
        for (auto val : row) cout << val << "\t";
        cout << endl;
    }
}

void selectWhere(const Table& table, string column, string value) {
    int colIndex = -1;

    for (int i = 0; i < (int)table.headers.size(); i++) {
        if (table.headers[i] == column) {
            colIndex = i;
            break;
        }
    }

    if (colIndex == -1) {
        cout << "Column not found\n";
        return;
    }

    for (auto h : table.headers) cout << h << "\t";
    cout << endl;

    for (auto row : table.rows) {
        if (row[colIndex] == value) {
            for (auto val : row) cout << val << "\t";
            cout << endl;
        }
    }
}

void buildCityIndex(Table& table) {
    int cityCol = -1;

    for (int i = 0; i < (int)table.headers.size(); i++) {
        if (table.headers[i] == "city") {
            cityCol = i;
            break;
        }
    }

    if (cityCol == -1) {
        cout << "City column not found\n";
        return;
    }

    for (int i = 0; i < (int)table.rows.size(); i++) {
        table.cityIndex[table.rows[i][cityCol]].push_back(i);
    }
}

void selectWhereCityIndexed(const Table& table, string city) {
    for (auto h : table.headers) cout << h << "\t";
    cout << endl;

    auto it = table.cityIndex.find(city);

    if (it == table.cityIndex.end()) {
        cout << "No matching rows\n";
        return;
    }

    for (int rowIndex : it->second) {
        for (auto val : table.rows[rowIndex]) {
            cout << val << "\t";
        }
        cout << endl;
    }
}

int main() {
    ifstream file("sample.csv");

    if (!file.is_open()) {
        cout << "Cannot open file\n";
        return 1;
    }

    string line;
    Table table;
    bool isHeader = true;

    while (getline(file, line)) {
        vector<string> row = split(line);

        if (isHeader) {
            table.headers = row;
            isHeader = false;
        } else {
            table.rows.push_back(row);
        }
    }

    buildCityIndex(table);

    cout << "SELECT *:\n";
    selectAll(table);

    cout << "\nAvailable columns:\n";
    for (auto h : table.headers) {
        cout << "- " << h << endl;
    }

    cout << "\nExample:\n";
    cout << "column: city\n";
    cout << "value: Hanoi\n";

    string column, value;

    cout << "\nEnter column: ";
    cin >> column;

    cout << "Enter value: ";
    cin >> value;

    cout << "\nWHERE " << column << " = " << value << " (full scan):\n";
    auto start1 = chrono::high_resolution_clock::now();
    selectWhere(table, column, value);
    auto end1 = chrono::high_resolution_clock::now();

    if (column == "city") {
        cout << "\nWHERE city = " << value << " (indexed):\n";
        auto start2 = chrono::high_resolution_clock::now();
        selectWhereCityIndexed(table, value);
        auto end2 = chrono::high_resolution_clock::now();

        cout << "\nScan time: "
             << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count()
             << " ns\n";

        cout << "Index time: "
             << chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count()
             << " ns\n";
    }

    return 0;
}