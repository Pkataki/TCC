#ifndef GREEDY_H
#define GREEDY_H
#include<vector>
#include<limits>
#include<set>
#include<utility>
#include<functional>
#include "reader.hpp"
using std::vector;
using std::set;
using std::function;
using std::pair;


class SCP_greedy
{

    Instance ins;
    
    double greedy_cost;
    function<double (double, vector<int>)> function_of_choice;
public:
    vector<bool>used_columns;

    vector<pair<double,int> >v;
    vector<int>objects_solution;
    set<int>elements_in_solution;
    SCP_greedy(Instance ins, function<double (double, vector<int>)> function_of_choice ) : ins(ins), 
    function_of_choice(function_of_choice)
    {
        elements_in_solution.clear();
        greedy_cost = 0;
        used_columns.resize(ins.columns.size());
    }

    int choose_best_object();
    double run_reduction();
    double run();
    
};

#endif