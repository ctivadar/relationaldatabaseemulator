// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

#include "TableEntry.h"

class Silly {
public:
    Silly()
        : quiet_mode { false } {}

    // Read and process command line arguments
    void get_options(int argc, char** argv);

    void run();
    void comment();
    void create();
    void remove();
    void insert();
    void print();
    void print_all(string tableIn);
    void print_where(const string tableIn);
    void print_where_helper(TableEntry typeIn, string tableName, size_t currentCol);
    void delete_function();
    void delete_helper(TableEntry typeIn, string tableName, size_t currentCol);
    void join();
    void generate();
    void regenerate(string tableName);
    void temporary_generate(string& tableIn, string& colIn);

    struct lessFunctor {
        size_t col;
        TableEntry value;
        lessFunctor(size_t colIn, TableEntry& valueIn)
            : col { colIn }
            , value { valueIn } {}
        bool operator()(const vector<TableEntry>& row) const { return row[col] < value; }
        bool operator()(const TableEntry input) const { return input < value; }
    };
    struct moreFunctor {
        size_t col;
        TableEntry value;
        moreFunctor(size_t colIn, TableEntry& valueIn)
            : col { colIn }
            , value { valueIn } {}
        bool operator()(const vector<TableEntry>& row) const { return row[col] > value; }
        bool operator()(const TableEntry input) const { return input > value; }
    };
    struct equalFunctor {
        size_t col;
        TableEntry value;
        equalFunctor(size_t colIn, TableEntry& valueIn)
            : col { colIn }
            , value { valueIn } {}
        bool operator()(const vector<TableEntry>& row) const { return row[col] == value; }
        bool operator()(const TableEntry input) const { return input == value; }
    };

private:
    class TableObject {
    public:
        string tableName;
        unordered_map<string, size_t> colNames;
        vector<EntryType> types;
        vector<vector<TableEntry>> table;
        unordered_map<TableEntry, vector<size_t>> hashIndex;
        map<TableEntry, vector<size_t>> bstIndex;
        unordered_map<TableEntry, vector<size_t>> tempHash;
        size_t colHashed = 0;
        size_t tempHashed = 0;

        TableObject(size_t colsIn, string tableNameIn)
            : tableName { tableNameIn } {
            types.reserve(colsIn);
        }
        TableObject()
            : tableName { " " } {}
    };
    bool quiet_mode = false;

    unordered_map<string, TableObject> tables;
    vector<string> colToPrint;
    char compToUse;
    size_t numColsIn;
    string colToCheck;
};
