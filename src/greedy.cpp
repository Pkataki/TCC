#include<vector>
#include<algorithm>
#include<iostream>
#include<limits>
#include<set>
#include<functional>
#include<cmath>
#include "reader.hpp"
#include "greedy.hpp"
#include "reduction.hpp"
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

double SCP_greedy::run_reduction()
{

    elements_in_solution.clear();
    fill(used_columns.begin(), used_columns.end(), 0);
    objects_solution.clear();
    greedy_cost = 0;
    Instance red = ins;
    while(elements_in_solution.size() < ins.lines.size())
    {
        SCP_Reduction x = SCP_Reduction(red, used_columns);
        red = x.apply();

        for(int i = 0; i < red.lines.size(); i++)
        {
            if(red.lines[i].size() == 0)
                elements_in_solution.insert(i);
        }

        for(int i = 0; i < red.columns.size(); i++)
        {
            if(red.columns[i].size() == 0)
                used_columns[i] = 1;
        }
        

        cout << x.are_in_solution.size() << "***" << endl;
        for(auto &x : x.are_in_solution )
        {
            used_columns[x] = 1;
            for(auto &x: ins.columns[x])
            {
                elements_in_solution.insert(x);
            }
        }

        int best_choice = choose_best_object();
        if(best_choice == -1)
            break;
        used_columns[best_choice] = 1;


        for(auto &x: ins.columns[best_choice])
        {
            elements_in_solution.insert(x);
        }
    }

    for(int i = 0; i < used_columns.size(); i++)
    {
        if(used_columns[i] == 1)
        {
            objects_solution.push_back(i+1);
            greedy_cost += ins.costs[i];
        }
    }


    return greedy_cost;
}

double SCP_greedy::run()
{
    elements_in_solution.clear();
    fill(used_columns.begin(), used_columns.end(), 0);
    objects_solution.clear();
    greedy_cost = 0;
    while(elements_in_solution.size() < ins.lines.size())
    {
        int best_choice = choose_best_object();
        if(best_choice == -1)
            break;
        used_columns[best_choice] = 1;

        for(auto &x: ins.columns[best_choice])
        {
            elements_in_solution.insert(x);
        }
    }

    for(int i = 0; i < used_columns.size(); i++)
    {
        if(used_columns[i] == 1)
        {
            objects_solution.push_back(i+1);
            greedy_cost += ins.costs[i];
        }
    }

    return greedy_cost;
}
