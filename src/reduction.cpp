#include "reduction.hpp"
int SCP_Reduction::factibility()
{
    for(int i = 0; i < ins.lines.size(); i++)
    {
        if(ins.lines[i].size() == 0)
            return 0;
    }
    return 1;
}

void SCP_Reduction::dominated_cost_column()
{
    vector<double>d(ins.lines.size(), std::numeric_limits<double>::max());
    for(int i = 0; i < ins.lines.size(); i++)
    {
        if(deleted_lines[i])
            continue;
        for(auto &col : ins.lines[i])
            d[i] = std::min(d[i], ins.costs[col]);
    }
    for(int i = 0; i < ins.columns.size(); i++)
    {
        double sum_d = 0;
        if(deleted_columns[i])
            continue;
        for(auto &lin : ins.columns[i])
            sum_d += d[lin];
    
        if(ins.costs[i] > sum_d)
            deleted_columns[i] = 1;
    }
}


void SCP_Reduction::pre_fixed_variables()
{
    for(int i = 0; i < ins.lines.size(); i++)
    {
        if(deleted_lines[i])
            continue;
        if(ins.lines[i].size() == 1)
        {
            deleted_columns[ins.lines[i][0]] = 1;
            deleted_lines[i] = 1;
            are_in_solution.push_back(ins.lines[i][0]);
        }
    }
}

void SCP_Reduction::subset(int i , int j)
{
    int x = 0;
    while(x < ins.lines[i].size() && x < ins.lines[j].size() && ins.lines[i][x] == ins.lines[j][x])
    {
        x++;
    }
    if(x == ins.lines[i].size())
    {
        deleted_lines[j] = 1;
    }
    else if(x == ins.lines[j].size())
    {
        deleted_lines[i] = 1;
    }
}


void SCP_Reduction::line_dominance()
{
    for(int i = 0 ; i < ins.lines.size(); i++)
    {
        for(int j = i+1; j < ins.lines.size(); j++)
        {
            if(deleted_lines[i] || deleted_lines[j])
                continue;
            subset(i,j);
        }
    }
}

void SCP_Reduction::remove_lines_and_columns()
{
   
    for(int i = 0; i < ins.lines.size(); i++)
    {
        if(deleted_lines[i] && ins.lines[i].size())
            ins.lines[i].clear();

        else
        {
            for(int j = ins.lines[i].size()-1; j >= 0 ; j--)
            {
                if(deleted_columns[ins.lines[i][j]])
                    ins.lines[i].erase(ins.lines[i].begin() + j);
            }
        }
    }

    for(int i = 0; i < ins.columns.size(); i++)
    {
        if(deleted_columns[i] && ins.columns[i].size())
            ins.columns[i].clear();
        
        else
        {
            for(int j = ins.columns[i].size()-1; j >= 0; j--)
            {
                if(deleted_lines[ins.columns[i][j]])
                {
                    ins.columns[i].erase(ins.columns[i].begin() + j);
                }
            } 
        }
    }
    fill(deleted_lines.begin(), deleted_lines.end(), 0);
    fill(deleted_columns.begin(), deleted_columns.end(), 0);
}

Instance SCP_Reduction:: apply()
{
    //factibility();
    pre_fixed_variables();
    dominated_cost_column();
    pre_fixed_variables();
    line_dominance();
    pre_fixed_variables();
    remove_lines_and_columns();
    return ins;
}
