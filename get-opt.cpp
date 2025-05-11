// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <iostream>

#include "getopt.h"
#include "silly.h"

void Silly::get_options(int argc, char** argv) {
    int option_index = 0, option = 0;

    opterr = false;

    struct option longOpts[] = {
        { "help", no_argument, nullptr,  'h'},
        {"quiet", no_argument, nullptr,  'q'},
        {nullptr,           0, nullptr, '\0'}
    };

    while ((option = getopt_long(argc, argv, "hq", longOpts, &option_index)) != -1) {
        switch (option) {
        case 'q':
            quiet_mode = true;
            break;

        case 'h':
            cout << "This program allows a user to create, manipulate, and analyze datasets using a set of commands\n";
            exit(0);

        case '?':
            cerr << "Unknown command line option\n";
            exit(1);
        }
    }
}
