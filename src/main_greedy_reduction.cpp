#include<bits/stdc++.h>
#include "greedy.hpp"
#include "CPUTimer.hpp"
#include<glpk.h>
using namespace std;

double f1(double c, vector<int> x)
{   
    return c;
}

double f2(double c, vector<int> x)
{   
    return c / (x.size() * log(x.size()));
}

double f3(double c, vector<int> x)
{   
    return c / log2(x.size());
}

double f4(double c, vector<int> x)
{   
    return c / (x.size() * log2(x.size()));
}

double f5(double c, vector<int> x)
{   
    return c / x.size();
}

double f6(double c, vector<int> x)
{   
    return c / pow(x.size(),2);
}

double f7(double c, vector<int> x)
{   
    return pow(c,1/2) / pow(x.size(),2);
}

double f8(double c, vector<int> x)
{   
    return pow(c,1/3) / log(pow(x.size(),2));
}

const int maxn = 10000000;

int ia[maxn],ja[maxn];
double ar[maxn];


void create_model(Instance k)
{
     glp_prob *mip = glp_create_prob();
    glp_set_prob_name(mip, "SCP");
    glp_set_obj_dir(mip, GLP_MIN);

    glp_add_rows(mip, (int)k.lines.size());
    string s = "";
    for(int i = 0 ; i < k.lines.size(); i++)
    {
        string s = "c" + to_string(i+1);
        glp_set_row_name(mip, i+1, s.c_str());
        glp_set_row_bnds(mip, i+1, GLP_LO, 1.0, 0.0);    
    }
    glp_add_cols(mip, (int)k.columns.size());

    for(int i = 0 ; i < k.costs.size(); i++)
    {
        string s = "x" + to_string(i+1);
        glp_set_col_name(mip, i+1, s.c_str());
        glp_set_col_bnds(mip, i+1, GLP_DB, 0.0, 1.0);
        glp_set_obj_coef(mip, i+1, k.costs[i]); 
        glp_set_col_kind(mip, i+1, GLP_BV);   
    }

    int qt = 1;
    for(int i = 0 ; i < k.lines.size(); i++)
    {
        for(auto &x: k.lines[i])
        {
            ia[qt] = i+1;
            ja[qt] = x+1;
            ar[qt] = 1.0;
            qt++;
        }
    }
    glp_load_matrix(mip, qt-1, ia, ja, ar);

    glp_iocp parm;
    glp_init_iocp(&parm);
    parm.presolve = GLP_ON;
    parm.sr_heur = GLP_ON;
    parm.fp_heur = GLP_ON;
    parm.gmi_cuts = GLP_ON;
    parm.mir_cuts = GLP_ON;
    parm.cov_cuts = GLP_ON;
    parm.clq_cuts = GLP_ON;
    parm.binarize = GLP_ON;
   // glp_write_lp(mip,NULL,"scp.lp");
    
    int err = glp_intopt(mip, &parm);

    double z = glp_mip_obj_val(mip);
    cout << "LP: " << z << endl;
    glp_delete_prob(mip);
}

int main(int argc, char *argv[])
{
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    Instance k = Reader::read(argv[1]);
    int idx = stoi(argv[2]);
    SCP_greedy x;
    switch(idx)
    {
        case 1:
            x = SCP_greedy(k, f1);        
            break;
        case 2:
            x = SCP_greedy(k, f2);        
            break;
        case 3:
            x = SCP_greedy(k, f3);        
            break;
        case 4:
            x = SCP_greedy(k, f4);        
            break;
        case 5:
            x = SCP_greedy(k, f5);        
            break;
        case 6:
            x = SCP_greedy(k, f6);        
            break;
        case 7:
            x = SCP_greedy(k, f7);        
            break;
        case 8:
            x = SCP_greedy(k, f8);        
            break;
        default:
            cout << "invalid number\n";
    }
   
   
    cout << "************** RESULTADOS ***************\n\n";
    
    
    // //cout << fixed << setprecision(5) << "Greedy without reduction: " << x.run() << endl;
    CPUTimer c;
    c.start();
    //create_model(k);
    double w = x.run();
    c.stop();
    cout << fixed << setprecision(5)  << w << "  with " << c.getCPUTotalSecs() << " seconds " << endl;
    
    cout << "\n\n*****************************************\n";


    return 0;
}