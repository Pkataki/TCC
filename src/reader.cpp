#include "reader.hpp"
#include<fstream>
using std::ifstream;
vector<vector<double> > Reader::read(string path)
{
    vector<vector<double > >matrix;
    ifstream File;
    File.open(path);

    int n,m;
    File >> n;
    File >> m;
    
    matrix.resize(n+1, vector<double>(m+1));

    for(int i = 1; i <= m; i++)
    {
        File >> matrix[0][i];
        int number_elements;
        File >> number_elements;
        for(int j = 0; j < number_elements; j++)
        {
            int index;
            File >> index;
            matrix[index][i] = 1;
        }
    }
    return matrix;
}