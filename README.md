# Project B: CSV Mini Database & Query Engine

## Overview

This project implements a lightweight CSV-based mini database system in C++.
It demonstrates key concepts in database systems, including:

* CSV parsing
* In-memory data storage
* Query processing
* Indexing optimization
* Performance comparison

The system reads data from a CSV file, stores it in memory, and allows users to execute simple queries via a command-line interface.

---

## Features

* Read and parse CSV files
* Store structured data using a custom table model
* Support `SELECT *` query
* Support `WHERE column = value` filtering
* Build index on `city` column using `unordered_map`
* Compare performance:

  * Full table scan
  * Indexed search
* Interactive user input for queries

---

## System Architecture

### 1. CSV Parser

* Reads file line-by-line
* Splits values using comma delimiter
* Converts raw data into structured format

### 2. Table Structure

```cpp
struct Table {
    vector<string> headers;
    vector<vector<string>> rows;
    unordered_map<string, vector<int>> cityIndex;
};
```

* `headers`: column names
* `rows`: data records
* `cityIndex`: index for fast lookup

---

### 3. Query Processing

* `selectAll()` → display entire table
* `selectWhere()` → full scan filtering
* `selectWhereCityIndexed()` → indexed filtering

---

### 4. Indexing

* Built on `city` column
* Uses hash map (`unordered_map`)
* Maps value → row indices

Example:

```
"Hanoi" → [0, 2, 4]
```

---

### 5. Performance Measurement

* Uses `chrono` library
* Compares:

  * Full scan time
  * Indexed query time

---

## Example Usage

### Compile

```bash
g++ main.cpp -o app.exe
```

### Run

```bash
./app.exe
```
---

### Sample Output

```
SELECT *:
id  name    age city    dept
1   Alice   21  Hanoi   IT
...

Enter column: city
Enter value: Hanoi

WHERE city = Hanoi (full scan):
...

WHERE city = Hanoi (indexed):
...

Scan time: 2776200 ns
Index time: 1747300 ns
```

---

## How to Use

1. Prepare a CSV file (e.g., `sample.csv`)
2. Compile the program
3. Run the executable
4. Enter:

   * Column name (e.g., `city`)
   * Value (e.g., `Hanoi`)

⚠️ Note:

* Input is **case-sensitive**
* Column name must match exactly

---

## Limitations

* Only supports `SELECT *`
* Only supports single `WHERE` condition
* No JOIN operations
* No UPDATE / DELETE
* CSV parser does not fully support quoted fields

---

## Future Improvements

* Support multiple conditions (AND / OR)
* Implement full SQL-like grammar
* Add INSERT / UPDATE / DELETE
* Improve CSV parsing (quoted fields, edge cases)
* Index multiple columns
* Optimize memory usage

---

## Author

* Name: Kassie (陳寶林)
* Student ID: 1113540
* GitHub: https://github.com/Baaotraan0407

---

## .gitignore

```gitignore
app.exe

```
