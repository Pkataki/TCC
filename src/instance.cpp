#include "instance.hpp"
#include <iostream>
void Instance::print_matrix_form()
{
    std::vector<std::vector<bool> >matrix;
    std:: cout << "MATRIX FORM: " << std::endl;
    matrix.resize(lines.size(),vector<bool>(columns.size()));
    for(int i = 0 ; i < lines.size(); i++)
    {
        for(auto &c : lines[i])
            matrix[i][c] = 1;
    }
    for(int i = 0; i < matrix.size(); i++)
    {
        for(int j = 0; j < matrix[0].size(); j++)
        {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void Instance::print_costs()
{
    std:: cout << "OBJECT'S COSTS: " << std::endl;
    for(int i = 0 ; i < columns.size(); i++)
    {
        std::cout << i+1 << " : " << costs[i] << std::endl;
    }
}