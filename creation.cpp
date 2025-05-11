// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "silly.h"

void Silly::generate() {
    size_t distinctKeys = 0;
    string junk;
    string tableName;
    string indexType;
    string colName;
    cin >> junk >> tableName >> indexType >> junk >> junk >> colName;
    auto iter = tables.find(tableName);
    if (iter == tables.end()) {
        cout << "Error during GENERATE: " << tableName << " does not name a table in the database\n";
        getline(cin, junk);
        return;
    }
    if (indexType == "hash") {
        auto colIter = iter->second.colNames.find(colName);
        if (colIter == iter->second.colNames.end()) {
            cout << "Error during GENERATE: " << colName << " does not name a column in " << tableName << "\n";
            getline(cin, junk);
            return;
        }
        iter->second.colHashed = colIter->second;
        iter->second.hashIndex.clear();
        iter->second.bstIndex.clear();
        for (size_t i = 0; i < iter->second.table.size(); ++i) {
            auto insertIter = iter->second.hashIndex.find(iter->second.table[i][iter->second.colHashed]);
            if (insertIter == iter->second.hashIndex.end()) {
                vector<size_t> indexes;
                indexes.push_back(i);
                iter->second.hashIndex.insert(make_pair(iter->second.table[i][iter->second.colHashed], indexes));
            } else {
                insertIter->second.push_back(i);
            }
        }
        distinctKeys = iter->second.hashIndex.size();
    } else {
        auto colIter = iter->second.colNames.find(colName);
        if (colIter == iter->second.colNames.end()) {
            cout << "Error during GENERATE: " << colName << " does not name a column in " << tableName << "\n";
            getline(cin, junk);
            return;
        }
        iter->second.colHashed = colIter->second;
        iter->second.hashIndex.clear();
        iter->second.bstIndex.clear();
        for (size_t i = 0; i < iter->second.table.size(); ++i) {
            auto insertIter = iter->second.bstIndex.find(iter->second.table[i][iter->second.colHashed]);
            if (insertIter == iter->second.bstIndex.end()) {
                vector<size_t> indexes;
                indexes.push_back(i);
                iter->second.bstIndex.insert(make_pair(iter->second.table[i][iter->second.colHashed], indexes));
            } else {
                insertIter->second.push_back(i);
            }
        }
        distinctKeys = iter->second.bstIndex.size();
    }
    cout << "Created " << indexType << " index for table " << tableName << " on column " << colName << ", with "
         << distinctKeys << " distinct keys\n";
}

void Silly::regenerate(string tableName) {
    auto iter = tables.find(tableName);
    if (!iter->second.hashIndex.empty()) {
        iter->second.hashIndex.clear();
        for (size_t i = 0; i < iter->second.table.size(); ++i) {
            auto insertIter = iter->second.hashIndex.find(iter->second.table[i][iter->second.colHashed]);
            if (insertIter == iter->second.hashIndex.end()) {
                vector<size_t> indexes;
                indexes.push_back(i);
                iter->second.hashIndex.insert(make_pair(iter->second.table[i][iter->second.colHashed], indexes));
            } else {
                insertIter->second.push_back(i);
            }
        }
    } else {
        iter->second.bstIndex.clear();
        auto iter = tables.find(tableName);
        for (size_t i = 0; i < iter->second.table.size(); ++i) {
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
}

void Silly::temporary_generate(string& tableIn, string& colIn) {
    auto iter = tables.find(tableIn);
    auto colIter = iter->second.colNames.find(colIn);
    iter->second.tempHashed = colIter->second;
    for (size_t i = 0; i < iter->second.table.size(); ++i) {
        auto insertIter = iter->second.tempHash.find(iter->second.table[i][iter->second.tempHashed]);
        if (insertIter == iter->second.tempHash.end()) {
            vector<size_t> indexes;
            indexes.push_back(i);
            iter->second.tempHash.insert(make_pair(iter->second.table[i][iter->second.tempHashed], indexes));
        } else {
            insertIter->second.push_back(i);
        }
    }
}


void Silly::join() {
    vector<int> tableToPrintFrom;
    string junk;
    string table1;
    string table2;
    cin >> table1 >> junk >> table2 >> junk;
    auto firstIter = tables.find(table1);
    auto secondIter = tables.find(table2);
    if (firstIter == tables.end()) {
        cout << "Error during JOIN: " << table1 << " does not name a table in the database\n";
        getline(cin, junk);
        return;
    }
    if (secondIter == tables.end()) {
        cout << "Error during JOIN: " << table2 << " does not name a table in the database\n";
        getline(cin, junk);
        return;
    }
    string col1;
    string col2;
    char compToUse = '0';
    cin >> col1 >> compToUse >> col2 >> junk >> junk >> numColsIn;
    auto colOneIter = firstIter->second.colNames.find(col1);
    auto colTwoIter = secondIter->second.colNames.find(col2);
    if (colOneIter == firstIter->second.colNames.end()) {
        cout << "Error during JOIN: " << col1 << " does not name a column in " << table1 << "\n";
        getline(cin, junk);
        return;
    }
    if (colTwoIter == secondIter->second.colNames.end()) {
        cout << "Error during JOIN: " << col2 << " does not name a column in " << table2 << "\n";
        getline(cin, junk);
        return;
    }
    string newCol;
    int tableIndicator = 0;
    for (size_t i = 0; i < numColsIn; ++i) {
        cin >> newCol;
        cin >> tableIndicator;
        if (tableIndicator == 1) {
            auto it = firstIter->second.colNames.find(newCol);
            if (it == firstIter->second.colNames.end()) {
                cout << "Error during JOIN: " << newCol << " does not name a column in " << table1 << "\n";
                getline(cin, junk);
                return;
            }
        } else {
            auto it = secondIter->second.colNames.find(newCol);
            if (it == secondIter->second.colNames.end()) {
                cout << "Error during JOIN: " << newCol << " does not name a column in " << table2 << "\n";
                getline(cin, junk);
                return;
            }
        }
        colToPrint.push_back(newCol);
        tableToPrintFrom.push_back(tableIndicator);
    }
    if (!quiet_mode) {
        for (size_t i = 0; i < numColsIn; ++i) {
            cout << colToPrint[i] << " ";
        }
        cout << "\n";
    }

    int count = 0;
    size_t firstColIdx = colOneIter->second;
    size_t secondColIdx = colTwoIter->second;
    if (secondIter->second.hashIndex.empty() || secondColIdx != secondIter->second.colHashed) {
        temporary_generate(table2, col2);
    }
    if (!secondIter->second.hashIndex.empty() && secondColIdx == secondIter->second.colHashed) {
        for (size_t i = 0; i < firstIter->second.table.size(); ++i) {
            TableEntry valueOne(firstIter->second.table[i][firstColIdx]);
            auto equalIter = secondIter->second.hashIndex.find(valueOne);
            if (equalIter != secondIter->second.hashIndex.end()) {
                vector<size_t> rowsToPrint = equalIter->second;
                for (size_t j = 0; j < rowsToPrint.size(); ++j) {
                    if (!quiet_mode) {
                        for (size_t k = 0; k < numColsIn; ++k) {
                            if (tableToPrintFrom[k] == 1) {
                                cout
                                  << firstIter->second.table[i][firstIter->second.colNames.find(colToPrint[k])->second]
                                  << " ";
                            } else {
                                cout
                                  << secondIter->second
                                       .table[rowsToPrint[j]][secondIter->second.colNames.find(colToPrint[k])->second]
                                  << " ";
                            }
                        }
                        cout << "\n";
                    }
                    ++count;
                }
            }
        }
    } else {
        for (size_t i = 0; i < firstIter->second.table.size(); ++i) {
            TableEntry valueOne(firstIter->second.table[i][firstColIdx]);
            auto equalIter = secondIter->second.tempHash.find(valueOne);
            if (equalIter != secondIter->second.tempHash.end()) {
                vector<size_t> rowsToPrint = equalIter->second;
                for (size_t j = 0; j < rowsToPrint.size(); ++j) {
                    if (!quiet_mode) {
                        for (size_t k = 0; k < numColsIn; ++k) {
                            if (tableToPrintFrom[k] == 1) {
                                cout
                                  << firstIter->second.table[i][firstIter->second.colNames.find(colToPrint[k])->second]
                                  << " ";
                            } else {
                                cout
                                  << secondIter->second
                                       .table[rowsToPrint[j]][secondIter->second.colNames.find(colToPrint[k])->second]
                                  << " ";
                            }
                        }
                        cout << "\n";
                    }
                    ++count;
                }
            }
        }
        secondIter->second.tempHash.clear();
    }
    colToPrint.clear();
    cout << "Printed " << count << " rows from joining " << table1 << " to " << table2 << "\n";
}
