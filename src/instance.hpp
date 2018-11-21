#ifndef ADD3
#define ADD3
#include<vector>
using std::vector;
class Instance
{
    public: 
    vector<vector<int> > lines,columns;
    vector<double>costs;
    Instance (){}
    Instance(int num_lines, int num_columns)
    {
        lines.resize(num_lines);
        columns.resize(num_columns);
        costs.resize(num_columns);
    }
    void print_matrix_form();
    void print_costs();
};
#endif