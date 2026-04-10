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

int main() {
    ifstream file("sample.csv");

    if (!file.is_open()) {
        cout << "Cannot open file\n";
        return 1;
    }

    string line;

    cout << "Reading CSV by columns:\n";

    while (getline(file, line)) {
        vector<string> row = split(line);

        for (string val : row) {
            cout << val << " | ";
        }
        cout << endl;
    }

    return 0;
}