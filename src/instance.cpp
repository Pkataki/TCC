#include "instance.hpp"
#include <iostream>
void Instance::print_matrix_form()
{
    std::vector<std::vector<bool> >matrix;
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