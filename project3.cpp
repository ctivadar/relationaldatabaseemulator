// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <iostream>
using namespace std;

#include "silly.h"


int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    cin >> std::boolalpha;
    cout << std::boolalpha;
    Silly silly;
    silly.get_options(argc, argv);
    silly.run();
    return 0;
}
