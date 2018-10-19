#include<bits/stdc++.h>
#include "reader.hpp"
using std::vector;

class SCP_solver
{
    vector<vector<double> > matrix;
    vector<bool>deleted_columns,delete_lines;
    vector<int>are_in_solution;

    int factibility()
    {
        for(int i = 1; i < matrix.size(); i++)
        {
            bool only_zeros = 1;
            for(int j = 1; j < matrix[0].size(); j++)
            {
                only_zeros &= (matri[i][j] == 0);
            }
            if(only_zeros)
                return 0;
        }
        return 1;
    }

    void dominated_cost_column()
    {
        vector<int>d(matrix.size(), DBL_MAX);
        for(int i = 1; i < matrix.size(); i++)
        {
            for(int j = 1 ; j < matrix[0].size(); j++)
            {
                if(matrix[i][j])
                    d[i] = min(d[i],matrix[0][j]);
            }
        }
        for(int i = 1; i < matrix[0].size(); i++)
        {
            int sum_d = 0;
            for(int j = 1; j < matrix.size(); j++)
            {
                if(matrix[j][i])
                    sum_d += d[j];
            }
            if(matrix[0][i] > sum_d)
                deleted_columns[i] = 1;
        }
    }

    bool is_subset(int a, int b)// check if a is a 
    {
        bool subset = 1;
        for(int j = 1; j < matrix[b].size(); j++)
        {
            if(matrix[b][j])
            {
                is_subset &= matrix[a][j];
            }
        }
        return subset;
    }

    void line_dominance()
    {

    }

    void pre_fixed_variables()
    {
        for(int i = 1; i < matrix.size(); i++)
        {
            int count = 0;
            int idxc = 0;
            for(int j = 1; j < matrix[0].size(); j++)
            {
                count += matrix[i][j];
                if(count == 1)
                {
                    idxc = j;
                }
                if(count > 1)
                    break;
            }
            if(count == 1)
            {
                deleted_columns[idxc] = 1;
                delete_lines[i] = 1;
                are_in_solution.push_back(idxc);
            }
        }
    }

public:
    SCP_solver(vector<vector<double> > instance)
    {
        matrix = instance;
        delete_lines.resize(matrix.size());
        deleted_columns.resize(matrix[0].size());
    }


}

int main()
{
    auto matrix = Reader::read("/home/kataki/TCC/instancias/stein.9.in");
    
    return 0;
}