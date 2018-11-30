#include<bits/stdc++.h>
#include "greedy.hpp"
#include<glpk.h>
using namespace std;

double f(double c, vector<int> x)
{   
    return pow(c,1/2) / log(x.size() * x.size());
}

const int maxn = 10000000;

int ia[maxn],ja[maxn];
double ar[maxn];

int main(int argc, char *argv[])
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    Instance k = Reader::read(argv[1]);
    SCP_greedy x = SCP_greedy(k, f);
    double w = x.run_reduction();
    cout << fixed << setprecision(5)  << "With reduction: " << w << endl;
    //cout << fixed << setprecision(5) << "Without reduction: " << x.run() << endl;

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
        glp_set_col_kind(mip, i+1, GLP_CV);   
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
    
    cout << "Z = " << z << endl;

    for(int i = 0; i < k.columns.size(); i++)
    {
        double x = glp_mip_col_val(mip, i+1);
        if(x > 0.0)
            cout  << "x["<< i+1 << "] = " << x << endl;
    }

    glp_delete_prob(mip);

    cout << "gap: " << ((w - z) / w) * 100 << endl; 

    return 0;
}