//
//  parts.cpp
//  p4
//
//  Created by Connor Turco on 6/17/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include "parts.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;
// =============================== Part A ================================== //

void PartA::prims_algorithm(int start_index) {
    table[start_index].parent = NULL_PARENT;
    table[start_index].weight = 0;
    
    double running_total = 0;
    int old_index = -1;
    for(int out = 0; out < num_true; ++out) {
        int smallest_index = 0;
        double smallest = std::numeric_limits<double>::infinity();
        for(int i = 0; i < (int)table.size(); ++i) {
            if(!table[i].visited) {
                if(table[i].weight < smallest) {
                    smallest = table[i].weight;
                    smallest_index = i;
                    
                }
                
            }
        }
        
        table[smallest_index].visited = true;
        running_total += sqrt(smallest);
        if(smallest_index == old_index) {
            cerr << "Cannot construct MST\n";
            exit(1);
        }
        old_index = smallest_index;
        
        for(int i = 0; i < (int)table.size(); ++i) {
            if(!table[i].visited) {
                double dist = distance(smallest_index, i);
                if(dist < table[i].weight) {
                    table[i].weight = dist;
                    table[i].parent = smallest_index;
                }
            }
        }
    }
    if(mode == MST) {
        cout << running_total << "\n";
        print_edges();
    }
    
}

double PartA::distance(int a, int b) {
    if(mode == MST) {
        if(all_coordinates[a].terrain == SEA && all_coordinates[b].terrain == LAND) {
            return numeric_limits<double>::infinity();
        }
        else if(all_coordinates[b].terrain == SEA && all_coordinates[a].terrain == LAND) {
            return numeric_limits<double>::infinity();
        }
    }

    double a_x = (double)all_coordinates[a].x;
    double a_y = (double)all_coordinates[a].y;
    double b_x = (double)all_coordinates[b].x;
    double b_y = (double)all_coordinates[b].y;
    return ((b_x - a_x) * (b_x - a_x)) + ((b_y - a_y) * (b_y - a_y));
}
void PartA::print_edges() const {
    for(int i = 0; i < (int)table.size(); ++i) {
        if(table[i].parent != NULL_PARENT) {
            cout << min(i, table[i].parent) << " " << max(i, table[i].parent)
            << "\n";
        }
    }
}

// =============================== Part B ================================== //

// =============================== Part C ================================== //
