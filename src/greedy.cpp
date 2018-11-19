#include<vector>
#include<algorithm>
#include<iostream>
#include<limits>
#include<set>
#include<functional>
#include<cmath>
#include "reader.hpp"
using std::vector;
using std::set;
using std::function;
using namespace std;

class SCP_greedy
{

    Instance ins;
    int qt_availible;
    vector<bool>used_columns;
    double greedy_cost;
    set<int>elements_in_solution;
    
    function<double (double, vector<int>)> function_of_choice;
public:
    vector<int>objects_solution;
    SCP_greedy(Instance ins, function<double (double, vector<int>)> function_of_choice ) : ins(ins), 
    function_of_choice(function_of_choice)
    {
        elements_in_solution.clear();
        greedy_cost = 0;
        used_columns.resize(ins.columns.size());
    }

    int choose_best_object()
    {
        double min_value = std::numeric_limits<double>::max();
        int idx = -1;
        for(int i = 0 ; i < used_columns.size(); i++)
        {
            if(used_columns[i] == 1)
                continue;
            double value = function_of_choice(ins.costs[i], ins.columns[i]);
            if(value < min_value)
            {
                min_value = value;
                idx = i;
            }
        }
        return idx;   
    }

    double run()
    {
        while(elements_in_solution.size() < ins.lines.size())
        {
            int best_choice = choose_best_object();
            if(best_choice == -1)
                break;
            objects_solution.push_back(best_choice+1);
            used_columns[best_choice] = 1;
            greedy_cost += ins.costs[best_choice];
            for(auto &x: ins.columns[best_choice])
            {
                elements_in_solution.insert(x);
            }
        }
        return greedy_cost;
    }
    
};

double f(double c, vector<int> x)
{   
    return c / log(x.size());
}

int main()
{
    auto k = Reader::read("/home/kataki/TCC_SCP/TCC/instancias/stein.9.in");

    k.print_matrix_form();

    SCP_greedy x = SCP_greedy(k, f);
    auto ins = x.run();
    cout << "value: "<< ins << endl;
    cout << "solution:\n";

    double s = 0;
    for(auto &y: x.objects_solution)
        cout << y << endl;

    k.print_costs();
    return 0;
}