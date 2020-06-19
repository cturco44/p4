// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
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

double PartA::distance(int a, int b) const {
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
double PartB::distance(int a, int b) const {
    double a_x = (double)all_coordinates[a].x;
    double a_y = (double)all_coordinates[a].y;
    double b_x = (double)all_coordinates[b].x;
    double b_y = (double)all_coordinates[b].y;
    return sqrt(((b_x - a_x) * (b_x - a_x)) + ((b_y - a_y) * (b_y - a_y)));
}
void PartB::find_fast() {
    //First element of table
    table.emplace_back(0,0);
    in_path[0] = true;
    
    //Find second element of table
    int smallest_index = 0;
    double smallest = numeric_limits<double>::infinity();
    for (int i = 1; i < (int)all_coordinates.size(); ++i) {
        double dist_temp = distance(0, i);
        if(dist_temp < smallest) {
            smallest_index = i;
            smallest = dist_temp;
        }
    }
    table[0].next_index = 1;
    table.emplace_back(smallest_index, 0);
    in_path[smallest_index] = true;
    total += 2*smallest;
    
    // Coordinate 0 and smallest index are currently in path
    for(int j = 0; j < (int)all_coordinates.size(); ++j) {
        
        //J is a unique location not added to path
        if(in_path[j] == false) {
            find_and_add_min_edge(j);
            in_path[j] = true;
        }
    }
    if(mode == FASTTSP) {
        print();
    }
}

void PartB::find_and_add_min_edge(int k) {
    
    int smallest_index = 0;
    double smallest = numeric_limits<double>::infinity();
    for(int z = 0; z < (int)table.size(); ++z) {
        int i = table[z].coord_index;
        int j = table[table[z].next_index].coord_index;
        double temp_dist = distance(i, k) + distance(k, j) - distance(i, j);
        
        if(temp_dist < smallest) {
            smallest = temp_dist;
            smallest_index = z;
        }
    }
    
    put_after(smallest_index, k);
    total += smallest;
}
void PartB::put_after(int first_index, int k) {
    int second_index = table[first_index].next_index;
    int insertion_index = (int)table.size();
    
    table[first_index].next_index = insertion_index;
    table.emplace_back(k, second_index);
    
}
void PartB::print() const {
    cout << total << "\n";
    int index  = 0;
    
    do {
        cout << table[index].coord_index << " ";
        index = table[index].next_index;
    } while (index != 0);
    cout << "\n";
}
// =============================== Part C ================================== //
void PartC::genPerms(size_t permLength) {
    if (permLength == path.size()) {
      // Do something with the path
      return;
    } // if
    if (!promising(permLength))
      return;
    for (size_t i = permLength; i < path.size(); ++i) {
      swap(path[permLength], path[i]);
      genPerms(permLength + 1);
      swap(path[permLength], path[i]);
    } // for
}
bool PartC::promising(size_t permLength) {
    if(path.size() - permLength < 6) {
        return true;
    }
    return lowerbound(permLength) < path_dist;
}
double PartC::lowerbound(size_t permLength) {
    PartA a(all_coordinates, OPTTST);
    
    
    return 2;
}
