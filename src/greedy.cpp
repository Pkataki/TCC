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
    if(v.size() == 0)
        return -1;
    int idx;
    while(v.size())
    {
        idx = v.back().second;
        v.pop_back();
        if(used_columns[idx] == 1)
            continue;
        bool ok = 0;
        for(auto &x: ins.columns[idx])
        {
            if(elements_in_solution.count(x) == 0)
            {
                ok = 1;
            }
        }
        if(ok)
            break;
    }
    v.pop_back();
    return idx;
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
    
    cout << ins.lines.size() << endl;
    while(elements_in_solution.size() < ins.lines.size())
    {
        

        double progress = 1;
        int barWidth = 70;
        progress = double(ins.lines.size() - elements_in_solution.size()) / ins.lines.size();
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
            used[w] = 1;
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
        used[best_choice] = 1;
        cout << best_choice << ": ";
        for(auto &w: ins.columns[best_choice])
        {
            cout << w << ' '; 
            elements_in_solution.insert(w);
        }
        cout << endl;

    }

    elements_in_solution.clear();
    for(int i = 0; i < used_columns.size(); i++)
    {
        if(used[i] == 1)
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
    cout << used_columns.size() << endl;
    v.clear();
    vector<int>a;
    for(int i = 0; i < ins.columns.size(); i++)
    {
        cout << function_of_choice(ins.costs[i], ins.columns[i]) << endl;
        v.push_back({function_of_choice(ins.costs[i], ins.columns[i]), i});
    }
    sort(v.begin(),v.end(),greater<pair<double,int> >());
    cout << ins.lines.size() << endl;
    while(elements_in_solution.size() < ins.lines.size())
    {

        int best_choice = choose_best_object();
        if(best_choice == -1)
            break;

        used_columns[best_choice] = 1;
        a.push_back(best_choice);
       // cout << best_choice << ": ";
        for(auto &w: ins.columns[best_choice])
        {
        //    cout << w << ' ';

            elements_in_solution.insert(w);
        }
        //cout << endl;

    }
    greedy_cost = 0;
    cout << a.size() << endl;
    for(auto &x : a)
    {
        objects_solution.push_back(x+1);
       // cout << ins.costs[x] << endl;
        greedy_cost += ins.costs[x];
    }
    return greedy_cost;
}
