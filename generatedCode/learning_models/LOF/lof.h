#ifndef LOF_H
#define LOF_H

#include <vector>
#include <map>
#include "../model.h"
#include <Python.h>

using namespace std;
class lof : public model{
    
    private:
        PyObject* pyModel;
        PyObject* pScaler;
        double meanScores;
        double sdScores;
        double threshold;
        int numNeighbors;
        std::vector<std::string> alerts;
    public:
        
        lof();
        lof(int);
        PyObject* getPyModel();
        void setPyModel(PyObject*);
        void setPScaler(PyObject*);
        PyObject* getPScaler();
        double getMeanScores();
        void setMeanScores(double);
        double getSdScores();
        void setSdScores(double);
        double getThreshold();
        void setThreshold(double);
        int getNumNeighbors();
        void setNumNeighbors(int);
        std::vector<std::string> getAlerts();
        void setAlerts(std::vector<std::string>);
        void training(PyObject* result);
        void detection(std::string,std::string,std::vector<int>&); 

};


#endif