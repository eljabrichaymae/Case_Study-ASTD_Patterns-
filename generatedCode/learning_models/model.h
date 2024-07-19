
#ifndef __MODEL__
#define __MODEL__
#include <iostream>
#include <vector>
#include <Python.h>


using namespace std;

class model {
   public: 
    virtual void training(PyObject* result)=0;
    virtual void detection(std::string,std::string,std::vector<int>&)=0;
    virtual ~model() = default;
};
#endif 