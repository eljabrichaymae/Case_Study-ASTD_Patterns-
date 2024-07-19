#ifndef KDE_H
#define KDE_H

#include <iostream>
#include <vector>
#include "../model.h"
#include <Python.h>

using namespace std;
class kde : public model {
    private:
        PyObject* pKDE;
        std::vector<double> data_post_training;
        std::vector<std::string> alerts;
        double threshold;
    public:
        kde();
        kde(double);
        void setData_post_training(std::vector<double> data_post_training);
        void setThreshold(double threshold);
        void setKDEObject(PyObject* pKDE);
        std::vector<double> getData_post_training();
        int getBins();
        double getThreshold();
        PyObject* getKDEObject();
        std::vector<std::string> getAlerts();
        void training(PyObject* result);
        void detection(std::string,std::string,std::vector<int>&);
        ~kde();
};



#endif