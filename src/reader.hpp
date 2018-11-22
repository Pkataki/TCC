#ifndef READER_H
#define READER_H

#include<vector>
#include <string>
#include "instance.hpp"
using std::vector;
using std::string;
class Reader
{
    public: 
    static Instance read(string path);
};

#endif