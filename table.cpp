// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "silly.h"

void Silly::insert() {
    string junk;
    string tableName;
    cin >> junk >> tableName;
    auto iter = tables.find(tableName);
    if (iter == tables.end()) {
        cout << "Error during INSERT: " << tableName << " does not name a table in the database\n";
        getline(cin, junk);
        return;
    }
    size_t newRowCount = 0;
    cin >> newRowCount >> junk;
    // Resize Vector
    size_t currentSize = iter->second.table.size();
    iter->second.table.resize(iter->second.table.size() + newRowCount);
    for (size_t i = 0; i < newRowCount; ++i) {
        iter->second.table[i].reserve(iter->second.types.size());
    }
    string stringOption;
    int intOption = 0;
    string boolOption;
    double doubleOption = 0;
    for (size_t i = currentSize; i < currentSize + newRowCount; ++i) {
        for (size_t j = 0; j < iter->second.types.size(); ++j) {
            EntryType option = iter->second.types[j];
            switch (option) {
            case EntryType::Int:
                cin >> intOption;
                iter->second.table[i].emplace_back(intOption);
                break;
            case EntryType::String:
                cin >> stringOption;
                iter->second.table[i].emplace_back(stringOption);
                break;
            case EntryType::Bool:
                cin >> boolOption;
                if (boolOption == "true") {
                    iter->second.table[i].emplace_back(true);
                } else {
                    iter->second.table[i].emplace_back(false);
                }
                break;
            case EntryType::Double:
                cin >> doubleOption;
                iter->second.table[i].emplace_back(doubleOption);
                break;
            }
        }
        if (!iter->second.hashIndex.empty()) {
            auto insertIter = iter->second.hashIndex.find(iter->second.table[i][iter->second.colHashed]);
            if (insertIter == iter->second.hashIndex.end()) {
                vector<size_t> indexes;
                indexes.push_back(i);
                iter->second.hashIndex.insert(make_pair(iter->second.table[i][iter->second.colHashed], indexes));
            } else {
                insertIter->second.push_back(i);
            }
        } else if (!iter->second.bstIndex.empty()) {
            auto insertIter = iter->second.bstIndex.find(iter->second.table[i][iter->second.colHashed]);
            if (insertIter == iter->second.bstIndex.end()) {
                vector<size_t> indexes;
                indexes.push_back(i);
                iter->second.bstIndex.insert(make_pair(iter->second.table[i][iter->second.colHashed], indexes));
            } else {
                insertIter->second.push_back(i);
            }
        }
    }
    cout << "Added " << newRowCount << " rows to " << tableName << " from position " << currentSize << " to "
         << iter->second.table.size() - 1 << "\n";
}

void Silly::print() {
    string junk;
    string tableName;
    cin >> junk >> tableName;
    auto iter = tables.find(tableName);
    if (iter == tables.end()) {
        cout << "Error during PRINT: " << tableName << " does not name a table in the database\n";
        getline(cin, junk);
        return;
    }
    cin >> numColsIn;
    string colInput;
    colToPrint.clear();
    for (size_t i = 0; i < numColsIn; ++i) {
        cin >> colInput;
        auto columnIter = iter->second.colNames.find(colInput);
        if (columnIter == iter->second.colNames.end()) {
            cout << "Error during PRINT: " << colInput << " does not name a column in " << tableName << "\n";
            getline(cin, junk);
            return;
        }
        colToPrint.push_back(colInput);
    }
    cin >> junk;
    if (junk == "ALL") {
        if (!quiet_mode) {
            for (size_t i = 0; i < numColsIn; ++i) {
                cout << colToPrint[i] << " ";
            }
            cout << "\n";
        }
        print_all(tableName);
    } else {
        print_where(tableName);
    }
}

void Silly::print_all(string tableIn) {
    auto iter = tables.find(tableIn);
    if (!quiet_mode) {
        for (size_t i = 0; i < iter->second.table.size(); ++i) {
            for (size_t j = 0; j < numColsIn; ++j) {
                size_t colIdx = iter->second.colNames.find(colToPrint[j])->second;
                cout << iter->second.table[i][colIdx] << " ";
            }
            cout << "\n";
        }
    }
    colToPrint.clear();
    cout << "Printed " << iter->second.table.size() << " matching rows from " << tableIn << "\n";
}

void Silly::print_where(const string tableIn) {
    auto iter = tables.find(tableIn);
    cin >> colToCheck >> compToUse;
    string stringOption;
    int intOption = 0;
    bool boolOption = false;
    double doubleOption = 0;
    auto colIter = iter->second.colNames.find(colToCheck);
    if (colIter == iter->second.colNames.end()) {
        cout << "Error during PRINT: " << colToCheck << " does not name a column in " << tableIn << "\n";
        string junk;
        getline(cin, junk);
        return;
    }
    if (!quiet_mode) {
        for (size_t i = 0; i < numColsIn; ++i) {
            cout << colToPrint[i] << " ";
        }
        cout << "\n";
    }
    size_t colIdx = colIter->second;
    EntryType option = iter->second.types[colIdx];
    switch (option) {
    case EntryType::Int: {
        cin >> intOption;
        TableEntry value(intOption);
        print_where_helper(value, tableIn, colIdx);
        break;
    }
    case EntryType::String: {
        cin >> stringOption;
        TableEntry value(stringOption);
        print_where_helper(value, tableIn, colIdx);
        break;
    }
    case EntryType::Bool: {
        cin >> std::boolalpha >> boolOption;
        TableEntry value(boolOption);
        print_where_helper(value, tableIn, colIdx);
        break;
    }
    case EntryType::Double: {
        cin >> doubleOption;
        TableEntry value(doubleOption);
        print_where_helper(value, tableIn, colIdx);
        break;
    }
    }
    colToPrint.clear();
}

void Silly::print_where_helper(TableEntry valueIn, string tableNameIn, size_t currentCol) {
    int count = 0;
    auto iter = tables.find(tableNameIn);
    if (!iter->second.bstIndex.empty() && currentCol == iter->second.colHashed) {
        if (compToUse == '=') {
            auto equalIter = iter->second.bstIndex.find(valueIn);
            if (equalIter == iter->second.bstIndex.end()) {
                cout << "Printed 0 matching rows from " << tableNameIn << "\n";
                return;
            }
            vector<size_t> rowsToPrint = equalIter->second;
            for (size_t i = 0; i < rowsToPrint.size(); ++i) {
                if (!quiet_mode) {
                    for (size_t j = 0; j < numColsIn; ++j) {
                        cout << iter->second.table[rowsToPrint[i]][iter->second.colNames.find(colToPrint[j])->second]
                             << " ";
                    }
                    cout << "\n";
                }
                ++count;
            }
        } else if (compToUse == '<') {
            auto it = iter->second.bstIndex.lower_bound(valueIn);
            auto track = iter->second.bstIndex.begin();
            while (track != it) {
                vector<size_t> rowsToPrint = track->second;
                for (size_t i = 0; i < rowsToPrint.size(); ++i) {
                    if (!quiet_mode) {
                        for (size_t j = 0; j < numColsIn; ++j) {
                            cout
                              << iter->second.table[rowsToPrint[i]][iter->second.colNames.find(colToPrint[j])->second]
                              << " ";
                        }
                        cout << "\n";
                    }
                    ++count;
                }
                ++track;
            }
        } else {
            auto it = iter->second.bstIndex.upper_bound(valueIn);
            while (it != iter->second.bstIndex.end()) {
                vector<size_t> rowsToPrint = it->second;
                for (size_t i = 0; i < rowsToPrint.size(); ++i) {
                    if (!quiet_mode) {
                        for (size_t j = 0; j < numColsIn; ++j) {
                            cout
                              << iter->second.table[rowsToPrint[i]][iter->second.colNames.find(colToPrint[j])->second]
                              << " ";
                        }
                        cout << "\n";
                    }
                    ++count;
                }
                ++it;
            }
        }
    } else {
        for (size_t i = 0; i < iter->second.table.size(); ++i) {
            bool printed = false;
            for (size_t j = 0; j < numColsIn; ++j) {
                size_t colIdx = iter->second.colNames.find(colToPrint[j])->second;
                if (compToUse == '<') {
                    lessFunctor less(currentCol, valueIn);
                    if (less.operator()(iter->second.table[i][currentCol])) {
                        if (!quiet_mode) {
                            cout << iter->second.table[i][colIdx] << " ";
                        }
                        printed = true;
                    } else {
                        break;
                    }
                } else if (compToUse == '=') {
                    equalFunctor equal(currentCol, valueIn);
                    if (equal.operator()(iter->second.table[i][currentCol])) {
                        if (!quiet_mode) {
                            cout << iter->second.table[i][colIdx] << " ";
                        }
                        printed = true;
                    } else {
                        break;
                    }
                } else if (compToUse == '>') {
                    moreFunctor more(currentCol, valueIn);
                    if (more.operator()(iter->second.table[i][currentCol])) {
                        if (!quiet_mode) {
                            cout << iter->second.table[i][colIdx] << " ";
                        }
                        printed = true;
                    } else {
                        break;
                    }
                }
            }
            if (printed) {
                if (!quiet_mode) {
                    cout << "\n";
                }
                ++count;
            }
        }
    }
    cout << "Printed " << count << " matching rows from " << tableNameIn << "\n";
}
