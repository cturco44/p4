//
//  main.cpp
//  p4
//
//  Created by Connor Turco on 6/17/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include <iostream>
#include <vector>
#include "xcode_redirect.hpp"
#include "parts.hpp"
#include <iomanip>
#include <getopt.h>
#include <string>
#include <cassert>

using namespace std;



int read_args(int argc, char* argv[]) {
    int mode_int = 3;
    int gotopt;
    int option_index = 0;
    option long_opts[] = {
        { "mode", required_argument, nullptr, 'm' },
        { "help", no_argument      , nullptr, 'h' },
        {nullptr, 0                , nullptr, '\0'},
        
    };
    while((gotopt = getopt_long(argc, argv, "m:h", long_opts, &option_index)) != -1) {
        switch(gotopt) {
            case 'm': {
                string mode = string(optarg);
                if(mode == "MST") {
                    mode_int = MST;
                }
                else if(mode == "FASTTSP") {
                    mode_int = FASTTSP;
                }
                else if(mode  == "OPTTSP") {
                    mode_int = OPTTST;
                }
                else {
                    cerr << "Mistyped m argument\n";
                    exit(0);
                }
                break;
            }
            case 'h': {
                cout << "-m, --mode <MODE>\n";
                exit(0);
                break;
            }
            default: {
                cout << "Flag not recognized\n";
                exit(0);
                break;
            }
        }
    } //while
    return mode_int;
}
void read_in(vector<Coordinate> &all_coordinates, int mode) {
    int vector_size;
    cin >> vector_size;
    all_coordinates.reserve(vector_size);
    
    bool part_a = false;
    if (mode == MST) {
        part_a = true;
    }
    
    int x;
    int y;
    while(cin >> x) {
        cin >> y;
        all_coordinates.emplace_back(x, y, part_a);
    }
}

int main(int argc, char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    cout << std::setprecision(2);
    cout << std::fixed;
    xcode_redirect(argc, argv);
    
    int mode = read_args(argc, argv);
    assert(mode >= 0 && mode <= 2);
    
    vector<Coordinate> all_coordinates;
    read_in(all_coordinates, mode);
    
    if(mode == MST) {
        PartA mist (all_coordinates, mode);
        mist.prims_algorithm();
    }
    else if(mode == FASTTSP) {
        PartB b(all_coordinates, mode);
        b.find_fast();
    }
    
    
    return 0;
}
