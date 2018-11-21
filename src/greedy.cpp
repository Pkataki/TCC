#include<vector>
#include<algorithm>
#include<iostream>
#include<limits>
#include<set>
#include<functional>
#include<cmath>
#include "reader.hpp"
#include "greedy.hpp"
using std::vector;
using std::set;
using std::function;

int SCP_greedy::choose_best_object()
{
    double min_value = std::numeric_limits<double>::max();
    int idx = -1;
    for(int i = 0 ; i < used_columns.size(); i++)
    {
        if(used_columns[i] == 1)
            continue;
        double value = function_of_choice(ins.costs[i], ins.columns[i]);
        if(value < min_value)
        {
            min_value = value;
            idx = i;
        }
    }
    return idx;   
}

double SCP_greedy::run()
{
    while(elements_in_solution.size() < ins.lines.size())
    {
        int best_choice = choose_best_object();
        if(best_choice == -1)
            break;
        objects_solution.push_back(best_choice+1);
        used_columns[best_choice] = 1;
        greedy_cost += ins.costs[best_choice];
        for(auto &x: ins.columns[best_choice])
        {
            elements_in_solution.insert(x);
        }
    }
    return greedy_cost;
}
