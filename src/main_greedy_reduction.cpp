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
    cout << fixed << setprecision(5) << x.run_reduction() << "   " << x.run() << endl;

    return 0;
}