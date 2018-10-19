#include<bits/stdc++.h>
using namespace std;
bitset<500>global_set, set_elements[500];

double cost[500];

bool used[513];

double f_min(int pos)
{
	bitset<500>b = (global_set ^ set_elements[pos]);

	int size_intersection = b.count();

	return (size_intersection == 0 || used[pos]) ? DBL_MAX :  cost[pos] / size_intersection;
}

int choose_best_set(int n, function<double(int)> f)
{
	int idx_min = -1;
	double value_min = DBL_MAX;
	for(int i = 0; i < n ; i++)
	{
		if(f(i) < value_min)
		{
			value_min = f(i);
			idx_min = i;
		}
	}
	return idx_min;
}

int main()
{

	int n, k;
	cin >> k >> n;
	for(int i = 0 ; i < n ; i++)
	{
		int m;
		cin >> cost[i];
		cin >> m;
		for(int j = 0; j < m ; j++)
		{
			int pos;
			cin >> pos;
			pos--;
			set_elements[i].set(pos);
		}
		
	}

	function<double(int)> f = f_min;
	set<int>set_solution;
	double value_solution = 0;

	while(global_set.count() < k)
	{
		int best_set = choose_best_set(n,f);
		if(best_set == -1)
			break;
		global_set |= set_elements[best_set];
		used[best_set] = 1;
		set_solution.insert(best_set);
		value_solution += cost[best_set];
	}
	
	cout << value_solution  << " ** " << endl;

	for(auto element : set_solution)
	{
		cout << element << endl;
	}
	cout << endl;

	return 0;
}