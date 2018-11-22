#include<bits/stdc++.h>
#include "greedy.hpp"
using namespace std;

double f(double c, vector<int> x)
{   
    return pow(c,1/2) / log(x.size() * x.size());
}

int main(int argc, char *argv[])
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
    
    Instance k = Reader::read(argv[1]);
    SCP_greedy x = SCP_greedy(k, f);
    auto ins = x.run();

    cout  << std::fixed << std::setprecision(10) << "value: "<< ins << endl;
    cout << "solution: " << x.objects_solution.size() << endl;
    auto v = x.objects_solution;
    double ma = DBL_MAX;
    int qt = 0;
    int ans = 0;
    for(int it = 0; it < 10000; it++)
    {
        std::shuffle(v.begin(), v.end(), rng);
        set<int>s;
        double val = 0;
        qt = 0;
        for(int i = 0; i < v.size() && s.size() < x.elements_in_solution.size(); i++)
        {
            qt++;
            val += k.costs[v[i]-1];
            for(auto &x: k.columns[v[i]-1])
            {
                s.insert(x);
            }
        }
        if(val < ma)
        {
            ma = val;
            ans = qt;
        }
    }

    cout << ma << " --> " << ans << endl;
    cout << "diff: " << ins - ma << endl;



    return 0;
}