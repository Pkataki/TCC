#include<vector>
#include<algorithm>
#include<iostream>
#include<limits>
#include "reader.hpp"
using std::vector;


class SCP_solver
{

    vector<bool>deleted_columns,delete_lines;
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
            for(auto &col : ins.lines[i])
                d[i] = std::min(d[i], ins.costs[col]);
        }
        for(int i = 0; i < ins.columns.size(); i++)
        {
            double sum_d = 0;
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
            if(ins.lines[i].size() == 1)
            {
                deleted_columns[ins.lines[i][0]] = 1;
                delete_lines[i] = 1;
                are_in_solution.push_back(ins.lines[i][0]);
            }
        }
    }


    SCP_solver(Instance x)
    {
        delete_lines.resize(x.lines.size());
        deleted_columns.resize(x.columns.size());
        ins = x;
    }
};

int main()
{
    auto k = Reader::read("/home/kataki/TCC_SCP/TCC/instancias/stein.9.in");
    // for(int i = 0; i < ins.costs.size(); i++)
    //     std::cout << ins.costs[i] << ' ';
    // std::cout << std::endl;
    // for(int i = 0; i < ins.columns.size(); i++)
    // {
    //     std::cout << i << ": ";
    //     for(auto &x : ins.columns[i])
    //     {
    //         std::cout << x << ' ';
    //     }
    //     std::cout << std::endl;
    // }
    SCP_solver x = Instance(k);
    std::cout << x.factibility() << std::endl;

    return 0;
}