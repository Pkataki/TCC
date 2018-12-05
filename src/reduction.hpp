#ifndef REDUCTION_H
#define REDUCTION_H

#include<vector>
#include<algorithm>
#include<iostream>
#include<limits>
#include<set>
#include "reader.hpp"
using std::vector;
using namespace std;


class SCP_Reduction
{

    vector<bool>deleted_columns,deleted_lines;
    Instance ins;

public:
    set<int>are_in_solution;
    void update_deleted_lines();
    void dominated_cost_column();
    void pre_fixed_variables();
    void subset(int i , int j);
    void line_dominance();
    void remove_lines_and_columns();
    Instance apply();
    SCP_Reduction(Instance x, vector<bool>used_columns)
    {
        are_in_solution.clear();
        deleted_columns = used_columns;
        deleted_lines.resize(x.lines.size(),0);
        ins = x;
    }
};

#endif