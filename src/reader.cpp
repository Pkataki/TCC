#include "reader.hpp"
#include<fstream>
#include<algorithm>
using std::ifstream;
// Instance Reader::read(string path)
// {
//     ifstream File;
//     File.open(path);
//     int n,m;
//     File >> n;
//     File >> m;
//     Instance x = Instance(n,m);
//     for(int i = 0; i < m; i++)
//     {
//        File >> x.costs[i]; 
//     }
//     for(int i = 0; i < n; i++)
//     {
//         int number_elements;
//         File >> number_elements;
//         for(int j = 0; j < number_elements; j++)
//         {
//             int index;
//             File >> index;
//             index--;
//             x.lines[i].push_back(index);
//         }
//         for(auto &l : x.lines[i])
//         {
//             x.columns[l].push_back(i);
//         }
//     }
//     for(auto &l : x.lines)
//     {
//         std::sort(l.begin(), l.end());
//     }

//     for(auto &c : x.columns)
//     {
//         std::sort(c.begin(), c.end());
//     }

//     return x;
// }

Instance Reader::read(string path)
{
    ifstream File;
    File.open(path);
    int n,m;
    File >> n;
    File >> m;
    Instance x = Instance(n,m);
    for(int i = 0; i < m; i++)
    {
        File >> x.costs[i];
        int number_elements;
        File >> number_elements;
        for(int j = 0; j < number_elements; j++)
        {
            int index;
            File >> index;
            index--;
            x.columns[i].push_back(index);
        }
        for(auto &l : x.columns[i])
        {
            x.lines[l].push_back(i);
        }
    }
    for(auto &l : x.lines)
    {
        std::sort(l.begin(), l.end());
    }

    for(auto &c : x.columns)
    {
        std::sort(c.begin(), c.end());
    }

    return x;
}