//
//  parts.hpp
//  p4
//
//  Created by Connor Turco on 6/17/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#ifndef parts_hpp
#define parts_hpp

#include <stdio.h>
#include <vector>
#include <limits>

const int LAND = 0;
const int COASTLINE = 1;
const int SEA = 2;

const int MST = 0;
const int FASTTSP = 1;
const int OPTTST = 2;

const int NULL_PARENT = -1;

struct Coordinate {
    int x;
    int y;
    int terrain;
    
    Coordinate(int x_in, int y_in, bool part_a) : x(x_in), y(y_in) {
        //If MST
        if(part_a) {
            if(y == 0 && x <= 0) {
                terrain = COASTLINE;
            }
            else if (x == 0 && y <= 0) {
                terrain = COASTLINE;
            }
            else if (x < 0 && y < 0) {
                terrain = SEA;
            }
            else {
                terrain = LAND;
            }
        }

    }
};

// =============================== Part A ================================== //
struct Prim {
    bool visited;
    double weight;
    int parent;
    
    Prim() : visited(false), weight(std::numeric_limits<double>::infinity()) {}
    
    Prim(int mode) :
    visited(false), weight(std::numeric_limits<double>::infinity()) {
        if(mode == OPTTST) {
            visited = true;
        }
    }
    
};
class PartA {
    PartA(std::vector<Coordinate> &vec) : all_coordinates(vec) {
        table.resize(all_coordinates.size());
    }
    void prims_algorithm(int start_index = 0);
    
    
private:
    std::vector<Coordinate> &all_coordinates;
    std::vector<Prim> table;
    
};


// =============================== Part B ================================== //

// =============================== Part C ================================== //


#endif /* parts_hpp */
