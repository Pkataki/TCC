#include<vector>
#include<algorithm>
#include<iostream>
#include<limits>
#include "reader.hpp"
using std::vector;
using namespace std;


class SCP_solver
{

    vector<bool>deleted_columns,deleted_lines;
    vector<int>are_in_solution;
    Instance ins;

public:
    
    int factibility()
    {
        for(int i = 0; i < ins.lines.size(); i++)
        {
            if(ins.lines[i].size() == 0)
                return 0;
        }
        return 1;
    }

    void dominated_cost_column()
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


    void pre_fixed_variables()
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

    void subset(int i , int j)
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


    void line_dominance()
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

    void remove_lines_and_columns()
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

    Instance apply()
    {
        factibility();
        pre_fixed_variables();
        dominated_cost_column();
        pre_fixed_variables();
        line_dominance();
        pre_fixed_variables();
        remove_lines_and_columns();
        return ins;
    }

    SCP_solver(Instance x)
    {
        deleted_lines.resize(x.lines.size(),0);
        deleted_columns.resize(x.columns.size(),0);
        ins = x;
    }
};

// int main(int argc, char** argv) 
// {
//     auto k = Reader::read("/home/kataki/TCC_SCP/TCC/instancias/stein.9.in");
//     // for(int i = 0; i < ins.costs.size(); i++)
//     //     std::cout << ins.costs[i] << ' ';
//     // std::cout << std::endl;
//     // for(int i = 0; i < ins.columns.size(); i++)
//     // {
//     //     std::cout << i << ": ";
//     //     for(auto &x : ins.columns[i])
//     //     {
//     //         std::cout << x << ' ';
//     //     }
//     //     std::cout << std::endl;
//     // }
//     SCP_solver x = Instance(k);
//     auto ins = x.apply();
//     for(int i = 0; i < ins.costs.size(); i++)
//         std::cout << ins.costs[i] << ' ';
//     std::cout << std::endl;
//     for(int i = 0; i < ins.lines.size(); i++)
//     {
//         std::cout << i << ": ";
//         for(auto &x : ins.lines[i])
//         {
//             std::cout << x << ' ';
//         }
//         std::cout << std::endl;
//     }

//     cout << " *** " << endl;
//     ins.print_matrix_form();

//     return 0;
// }