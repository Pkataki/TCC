#include<iostream>
#include<cmath>
#include "greedy.hpp"
using std::cout;
using std::endl;

double f(double c, vector<int> x)
{   
    return pow(c,1/3) / log(x.size() * x.size());
    return c / x.size(); 
}

int main(int argc, char *argv[])
{
    auto k = Reader::read(argv[1]);
    SCP_greedy x = SCP_greedy(k, f);
    auto ins = x.run();
    cout << "value: "<< ins << endl;
    cout << "solution: " << x.objects_solution.size() << endl;
    return 0;
}