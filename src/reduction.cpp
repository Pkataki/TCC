#include <functional>
#include "reduction.hpp"
void SCP_Reduction::update_deleted_lines()
{
    for(int i = 0; i < ins.lines.size(); i++)
    {
        if(ins.lines[i].size() == 0)
            deleted_lines[i] = 1;
    }
}

void SCP_Reduction::dominated_cost_column()
{
    int qt = 0;
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
        {
            deleted_columns[i] = 1;
        }
    }

}


void SCP_Reduction::pre_fixed_variables()
{
    int qt = 0;
    for(int i = 0; i < ins.lines.size(); i++)
    {
        if(deleted_lines[i] || ins.lines[i].size() != 1)
            continue;
       // cout << "linha " << i << endl;
        deleted_columns[ins.lines[i][0]] = 1;
        deleted_lines[i] = 1;
        are_in_solution.insert(ins.lines[i][0]);
    }
}

void SCP_Reduction::subset(int i , int j)
{
    int x = 0, y = 0;
    int qt = 0;
    while(x < ins.lines[i].size() && y < ins.lines[j].size() )
    {
        if(ins.lines[i][x] == ins.lines[j][y])
        {
            qt++;
            x++;
            y++;
        }
        else if(ins.lines[i][x] < ins.lines[j][y])
        {
            x++;
        }
        else
        {
            y++;
        }    
    }

    if( qt > 0 && qt == min(ins.lines[i].size(), ins.lines[j].size()) )
    {
        int idx = ins.lines[i].size() < ins.lines[j].size() ? j : i;
        deleted_lines[idx] = 1;
    }

}   


void SCP_Reduction::line_dominance()
{
    for(int i = 0 ; i < ins.lines.size(); i++)
    {
        if(deleted_lines[i])
            continue;
        for(int j = i+1; j < ins.lines.size(); j++)
        {
            if( deleted_lines[j] )
                continue;
            subset(i,j);
        }
    }
}

void SCP_Reduction::remove_lines_and_columns()
{

    vector<int>w;
   
    for(int i = 0; i < ins.lines.size(); i++)
    {
        if(deleted_lines[i] )
            ins.lines[i].clear();
        else
        {
            w.clear();
            for(auto &x: ins.lines[i])
            {
                if(deleted_columns[x])
                    continue;
                else
                    w.push_back(x);
            }
            ins.lines[i] = w;
        }
    }

    for(int i = 0; i < ins.columns.size(); i++)
    {
        if(deleted_columns[i])
            ins.columns[i].clear();
        else
        {
            w.clear();
            for(auto &x: ins.columns[i])
            {
                if(deleted_lines[x])
                    continue;
                else
                    w.push_back(x);
            }
            ins.columns[i] = w;
        }
    }

    fill(deleted_lines.begin(), deleted_lines.end(), 0);
    fill(deleted_columns.begin(), deleted_columns.end(), 0);
}

Instance SCP_Reduction::apply()
{

    update_deleted_lines();
    vector<function<void (const SCP_Reduction)> > permutation;
    permutation.push_back(&SCP_Reduction::line_dominance);
    permutation.push_back(&SCP_Reduction::pre_fixed_variables);
    permutation.push_back(&SCP_Reduction::dominated_cost_column);
    srand(time(NULL));
    random_shuffle(permutation.begin(), permutation.end());
    random_shuffle(permutation.begin(), permutation.end());
    
    remove_lines_and_columns();
    for(int i = 0; i < 3; i++)
    {
        permutation[i](*this);
        remove_lines_and_columns();
        pre_fixed_variables();
        remove_lines_and_columns();
    }
    remove_lines_and_columns(); 
    // remove_lines_and_columns();
    // update_deleted_lines();
    // pre_fixed_variables();
    // remove_lines_and_columns();
    // dominated_cost_column();
    // remove_lines_and_columns();
    // pre_fixed_variables();
    // remove_lines_and_columns();
    // line_dominance();
    // remove_lines_and_columns();
    // pre_fixed_variables();
    // remove_lines_and_columns();
    return ins;
}
