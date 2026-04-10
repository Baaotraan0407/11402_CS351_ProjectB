#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

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

    for (int i = 0; i < table.headers.size(); i++) {
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

    cout << "SELECT *:\n";
    selectAll(table);

    cout << "\nWHERE city = Hanoi:\n";
    selectWhere(table, "city", "Hanoi");

    return 0;
}
