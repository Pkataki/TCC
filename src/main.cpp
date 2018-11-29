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
    cout << " ******** GREEDY *********\n";
    auto ins = x.run();

    cout  << std::fixed << std::setprecision(10) << "Value Solution: "<< ins << endl;
    double a = 0, b = 0;
    cout << "qt of objects: " << x.objects_solution.size() << endl;
    

    cout << "\n\n\n******** GREEDY RANDOM *********\n";

    { 
        auto v = x.objects_solution;
        double ma = DBL_MAX;
        int qt = 0;
        int ans = 0;
        for(int it = 0; it < 100; it++)
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

        cout <<"Value of Solution: " << ma << " qt of objects: " << ans << endl;
        a = ma;
        cout << "diff: " << ins - ma << endl;
    }

    cout << "\n\n\n********* RANDOM *********\n";
    {
        auto v = k.columns;
        auto costs = k.costs;
        vector<int>p(v.size());
        for(int i = 0; i < v.size(); i++)
            p[i] = i;

        double ma = DBL_MAX;
        int qt = 0;
        int ans = 0;
        for(int it = 0; it < 100; it++)
        {
            std::shuffle(p.begin(), p.end(), rng);
            set<int>s;
            double val = 0;
            qt = 0;
            for(int i = 0; i < p.size() && s.size() < k.lines.size(); i++)
            {
                qt++;
                val += costs[p[i]];
                for(auto &x: v[p[i]])
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

        cout <<"Value of Solution: " << ma << " qt of objects: " << ans << endl;
        b = ma;
        cout << "diff: " << ins - ma << endl;
    }
    cout << "\n#############################################\n";
    if(a < b)
        cout << "Greedy random is better\n";
    else if(a > b)
        cout << "Random is better\n";
    else
        cout << "Any of them\n";
    return 0;
}