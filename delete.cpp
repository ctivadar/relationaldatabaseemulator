// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "silly.h"

void Silly::delete_function() {
    string junk;
    string tableName;
    cin >> junk >> tableName;
    auto iter = tables.find(tableName);
    if (iter == tables.end()) {
        cout << "Error during DELETE: " << tableName << " does not name a table in the database\n";
        getline(cin, junk);
        return;
    }
    cin >> junk;
    string colName;
    cin >> colName;
    auto colIter = iter->second.colNames.find(colName);
    if (colIter == iter->second.colNames.end()) {
        cout << "Error during DELETE: " << colName << " does not name a column in " << tableName << "\n";
        getline(cin, junk);
        return;
    }
    cin >> compToUse;
    string stringOption;
    int intOption = 0;
    bool boolOption = false;
    double doubleOption = 0;
    size_t colIdx = colIter->second;
    EntryType option = iter->second.types[colIdx];
    size_t previousSize = iter->second.table.size();
    switch (option) {
    case EntryType::Int: {
        cin >> intOption;
        TableEntry value(intOption);
        delete_helper(value, tableName, colIdx);
        break;
    }
    case EntryType::String: {
        cin >> stringOption;
        TableEntry value(stringOption);
        delete_helper(value, tableName, colIdx);
        break;
    }
    case EntryType::Bool: {
        cin >> std::boolalpha >> boolOption;
        TableEntry value(boolOption);
        delete_helper(value, tableName, colIdx);
        break;
    }
    case EntryType::Double: {
        cin >> doubleOption;
        TableEntry value(doubleOption);
        delete_helper(value, tableName, colIdx);
        break;
    }
    }
    cout << "Deleted " << previousSize - iter->second.table.size() << " rows from " << tableName << "\n";
    if (!iter->second.hashIndex.empty() || !iter->second.bstIndex.empty()) {
        regenerate(tableName);
    }
}

void Silly::delete_helper(TableEntry valueIn, string tableNameIn, size_t currentCol) {
    auto iter = tables.find(tableNameIn);
    if (compToUse == '<') {
        iter->second.table.erase(
          remove_if(iter->second.table.begin(), iter->second.table.end(), lessFunctor(currentCol, valueIn)),
          iter->second.table.end());
        return;
    }
    if (compToUse == '>') {
        iter->second.table.erase(
          remove_if(iter->second.table.begin(), iter->second.table.end(), moreFunctor(currentCol, valueIn)),
          iter->second.table.end());
        return;
    }
    if (compToUse == '=') {
        iter->second.table.erase(
          remove_if(iter->second.table.begin(), iter->second.table.end(), equalFunctor(currentCol, valueIn)),
          iter->second.table.end());
        return;
    }
}
