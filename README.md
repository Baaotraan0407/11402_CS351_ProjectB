# Project B: CSV Mini Database & Query Engine

## Overview

This project implements a lightweight CSV-based mini database system in C++.
It demonstrates fundamental concepts of data storage, querying, indexing, and performance comparison.

The system loads data from a CSV file, stores it in memory, and supports basic query operations through a simple interactive interface.

---

## Features

- Read data from a CSV file
- Store data using an in-memory table structure
- Support `SELECT *`
- Support `WHERE column = value`
- Build an index for the `city` column using `unordered_map`
- Compare full scan and indexed query performance using timing
- Accept simple user input for query execution

---

## System Architecture

- **CSV Parser**
  - Reads data line by line
  - Splits fields using comma delimiter

- **Table Structure**
  - Stores column names in `headers`
  - Stores records in `rows`
  - Stores city index in `cityIndex`

- **Query Functions**
  - `selectAll()` → display all rows
  - `selectWhere()` → perform full scan query
  - `selectWhereCityIndexed()` → perform indexed lookup

- **Indexing**
  - Hash-based index for the `city` column
  - Maps city name to matching row indices

---

## Example Usage

### Compile

```bash
g++ main.cpp -o app.exe

---

```markdown
## Author

- Name: Kassie (陳寶林)
- Student ID: 1113540
- GitHub: https://github.com/Baaotraan0407