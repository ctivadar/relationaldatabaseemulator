// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "silly.h"

void Silly::comment() {
    string junk;
    getline(cin, junk);
}

void Silly::create() {
    string junk;
    string tableName;
    cin >> tableName;
    if (auto iter = tables.find(tableName); iter != tables.end()) {
        cout << "Error during CREATE: Cannot create already existing table " << tableName << "\n";
        getline(cin, junk);
        return;
    }
    size_t colsCount = 0;
    cin >> colsCount;
    string colType;
    TableObject newTable(colsCount, tableName);
    for (size_t i = 0; i < colsCount; ++i) {
        cin >> colType;
        if (colType == "int") {
            newTable.types.push_back(EntryType::Int);
        } else if (colType == "bool") {
            newTable.types.push_back(EntryType::Bool);
        } else if (colType == "string") {
            newTable.types.push_back(EntryType::String);
        } else {
            newTable.types.push_back(EntryType::Double);
        }
    }
    cout << "New table " << tableName << " with column(s) ";
    string nameIn;
    for (size_t i = 0; i < colsCount; ++i) {
        cin >> nameIn;
        cout << nameIn << " ";
        newTable.colNames[nameIn] = i;
    }
    cout << "created\n";
    tables.insert(make_pair(tableName, newTable));
    /*auto outputIter = newTable.colNames.begin();
    while (outputIter != newTable.colNames.end()) {
        cout << outputIter->first << " ";
        ++outputIter;
    }
    */
}

void Silly::remove() {
    string junk;
    string tableName;
    cin >> tableName;
    auto iter = tables.find(tableName);
    if (iter == tables.end()) {
        cout << "Error during REMOVE: " << tableName << " does not name a table in the database\n";
        getline(cin, junk);
        return;
    }
    tables.erase(iter);
    cout << "Table " << tableName << " removed\n";
}
