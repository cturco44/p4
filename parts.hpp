// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0
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
    
    
};
class PartA {
public:
    PartA(std::vector<Coordinate> &vec, int mode_in)
                                        : all_coordinates(vec), mode(mode_in) {
                                            
        table.resize(all_coordinates.size());
        
        num_true = (int)all_coordinates.size();
    }
    PartA(const std::vector<Coordinate> &vec, int mode_in)
                                        : all_coordinates(vec), mode(mode_in) {
                                            
        table.resize(all_coordinates.size());
        
        num_true = (int)all_coordinates.size();
    }
    
    void prims_algorithm(int start_index = 0);
    double prims_algorithm_c(std::vector<int> &path, int start);
    void set_num_true(int num_true_in) {
        num_true = num_true_in;
    }
    
private:
    const std::vector<Coordinate> &all_coordinates;
    std::vector<Prim> table;
    
    int num_true;
    int mode;
    
    
    double distance(int a, int b) const;
    void print_edges() const;
    double distance2(int a, int b) const;
    
};


// =============================== Part B ================================== //
struct Node {
    int coord_index;
    int next_index;
    Node(int coord_in, int next_in)
    : coord_index(coord_in), next_index(next_in) {}
};

class PartB {
public:
    //Constructor
    PartB(std::vector<Coordinate> &vec, int mode_in)
    : all_coordinates(vec), total(0), mode(mode_in) {
        table.reserve(all_coordinates.size());
        in_path.resize(all_coordinates.size());
        std::fill(in_path.begin(), in_path.end(), false);
    }
    PartB(const std::vector<Coordinate> &vec, int mode_in)
    : all_coordinates(vec), total(0), mode(mode_in) {
        table.reserve(all_coordinates.size());
        in_path.resize(all_coordinates.size());
        std::fill(in_path.begin(), in_path.end(), false);
    }
    
    void find_fast();
    void copy_into_vector(std::vector<int> &vec, double &best_dist);

private:
    const std::vector<Coordinate> &all_coordinates;
    std::vector<Node> table;
    std::vector<bool> in_path;
    double total;
    int mode;
    
    
    void put_after(int first_index, int k);
    double distance(int a, int b) const;
    void find_and_add_min_edge(int k);
    void print() const;
};
// =============================== Part C ================================== //
class PartC {
public:
    PartC(std::vector<Coordinate> &vec)
    //Initializer list
    : mst_finder{vec, OPTTST}, dist_matrix{vec.size(),
        std::vector<double>(vec.size(), std::numeric_limits<double>::infinity())},
    all_coordinates(vec), path_dist(0), best_path_dist(0) {
        
        path.reserve(all_coordinates.size());
        best_path.reserve(all_coordinates.size());
        
        PartB b(all_coordinates, OPTTST);
        b.find_fast();
        b.copy_into_vector(best_path, best_path_dist);
        
        path = best_path;
        
    }
    void driver();
    void genPerms(size_t permLength);
    bool promising(size_t permLength);
    double lowerbound(size_t permLength);
private:
    PartA mst_finder;
    std::vector<std::vector<double>> dist_matrix;
    std::vector<int> path;
    std::vector<int> best_path;
    const std::vector<Coordinate> &all_coordinates;
    double path_dist;
    double best_path_dist;
    
    double distance(int a, int b) const;
    double shortest_arm(int a, size_t permLength);
    void push_dist(size_t a, size_t b, double dist);
    double lookup(size_t index1, size_t index2);
    double total_path();
   
    
    
};

#endif /* parts_hpp */
