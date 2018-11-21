#ifndef ADD1
#define ADD1
#include<vector>
#include<limits>
#include<set>
#include<functional>
#include "reader.hpp"
using std::vector;
using std::set;
using std::function;


class SCP_greedy
{

    Instance ins;
    int qt_availible;
    vector<bool>used_columns;
    double greedy_cost;
    
    function<double (double, vector<int>)> function_of_choice;
public:
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
    double run();
    
};

#endif