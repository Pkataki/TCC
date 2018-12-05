#include<vector>
#include<algorithm>
#include<iostream>
#include<limits>
#include<set>
#include<functional>
#include<cmath>
#include<utility>
#include "reader.hpp"
#include "greedy.hpp"
#include "reduction.hpp"
using std::vector;
using std::set;
using std::function;
using std::pair;

int SCP_greedy::choose_best_object()
{

    int idx;
    while(v.size())
    {
        idx = v.back().second;
        v.pop_back();
        if(used_columns[idx] == 1)
            continue;
        used_columns[idx] = 1;
        bool ok = 0;
        for(auto &x: ins.columns[idx])
        {
            if(elements_in_solution.count(x) == 0)
            {
                return idx;
            }
        }
    }
    return -1;
}

void print(int lines_size, int elements_in_solution_size)
{
    double progress = 1;
    int barWidth = 70;
    progress = double(lines_size - elements_in_solution_size) / lines_size;
    progress = 1 - progress;
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; i++) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
        
}

double SCP_greedy::run_reduction()
{

    elements_in_solution.clear();
    fill(used_columns.begin(), used_columns.end(), 0);
    objects_solution.clear();
    greedy_cost = 0;
    Instance red = ins;
    auto used = used_columns;
    v.clear();
    for(int i = 0; i < ins.columns.size(); i++)
    {
        v.push_back({function_of_choice(ins.costs[i], ins.columns[i]), i});
    }
    sort(v.begin(),v.end(),greater<pair<double,int> >());
    
    set<int>a;
    
    while(elements_in_solution.size() < ins.lines.size())
    {
        print(ins.lines.size(), elements_in_solution.size());
        SCP_Reduction x = SCP_Reduction(red, used_columns);
        red = x.apply();

        for(int i = 0; i < red.lines.size(); i++)
        {
            if(red.lines[i].size() == 0)
            {
                elements_in_solution.insert(i);
            }    
        }


        for(int i = 0; i < red.columns.size(); i++)
        {
            if(red.columns[i].size() == 0)
            {  
                used_columns[i] = 1;
            }
        }
        
        for(auto &w : x.are_in_solution )
        {
            used_columns[w] = 1;
            a.insert(w);
            for(auto &y: ins.columns[w])
            {
                elements_in_solution.insert(y);
            }
        }

        if(elements_in_solution.size() == ins.lines.size())
            break;
        
        int best_choice = choose_best_object();
        if(best_choice == -1)
            break;

        used_columns[best_choice] = 1;
        a.insert(best_choice);
        for(auto &w: ins.columns[best_choice])
        {
            elements_in_solution.insert(w);
        }
    }

    for(auto &x : a)
    {
        objects_solution.push_back(x+1);
        greedy_cost += ins.costs[x];
    }
    return greedy_cost;
}

double SCP_greedy::run()
{
    elements_in_solution.clear();
    fill(used_columns.begin(), used_columns.end(), 0);
    objects_solution.clear();
    greedy_cost = 0;
    v.clear();
    vector<int>a;
    for(int i = 0; i < ins.columns.size(); i++)
    {
        v.push_back({function_of_choice(ins.costs[i], ins.columns[i]), i});
    }
    sort(v.begin(),v.end(),greater<pair<double,int> >());
    while(elements_in_solution.size() < ins.lines.size())
    {

        int best_choice = choose_best_object();
        if(best_choice == -1)
            break;

        used_columns[best_choice] = 1;
        a.push_back(best_choice);
        for(auto &w: ins.columns[best_choice])
        {
            elements_in_solution.insert(w);
        }

    }
    greedy_cost = 0;
    //cout << a.size() << endl;
    sort(a.begin(),a.end());
    for(auto &x : a)
    {
    //   cout << x+1 << ' '; 
        objects_solution.push_back(x+1);
        greedy_cost += ins.costs[x];
    }
    //cout << endl;
    return greedy_cost;
}
