#include <iostream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <fstream>
#include "json.hpp"
#include "kmeans.h"
#include <Python.h>
#include "numpy/arrayobject.h"                  
#include <cmath>
#include "../../nlohmann/json.hpp"
#include <sstream>
#include <iomanip>
#include <ctime>


using json = nlohmann::json;
using namespace std;

kmeans::kmeans(){
    this->risInitialized = 0;
    this->numClusters=0;
    this->threshold = 1.75;
};
kmeans::kmeans(double threshold){
    this->risInitialized = 0;
    this->numClusters=0;
    this->threshold = threshold;
};
void kmeans::setThreshold(double threshold){
    this->threshold = threshold;
};
double kmeans::getThreshold(){
    return this->threshold;
};
std::map<int,vector<double>> kmeans::getClusters(){
    return this->clusters;
};
void kmeans::setClusters(std::map<int,vector<double>> clusters){
    this->clusters = clusters;
};
std::map<int,double> kmeans::getSeuils(){
    return this->seuils;
};
void kmeans::setSeuils(std::map<int,double> seuils){
    this->seuils = seuils;
};
std::vector<double> kmeans::getCenters(){
    return this->centers;
};
void kmeans::setCenters(std::vector<double> centers){
    this->centers = centers;
}; 
std::vector<double> kmeans::getStdvars(){
    return this->stdvars;
};
void kmeans::setStdvars(std::vector<double> stdvars){
    this->stdvars = stdvars;
}; 
int kmeans::getNumClusters(){
    return this->numClusters;
};
void kmeans::setNumClusters(int numClusters){
    this->numClusters = numClusters;
};       
std::vector<std::string> kmeans::getAlerts(){
    return this->alerts;
};
double kmeans::distance(double a, double b){
    if(a<b) return std::min(b-a, a-b+24);
    else return std::min(a-b, b-a+24);
}

void kmeans::training(PyObject* result){
    
    PyObject *pName, *pModule, *pFunc, *pArgs;
    PyObject *pValue;
    pName = PyUnicode_FromString((char*)"pyKmeans");
    pModule = PyImport_Import(pName);
    if (pModule == nullptr)
    {
        PyErr_Print();
        std::exit(1);
    }
    pFunc = PyObject_GetAttrString(pModule, (char*)"training");
    pArgs = PyTuple_Pack(1, result);
    pValue = PyObject_CallObject(pFunc, pArgs);
    //std::cout<<*pValue<<std::endl;
    if (pValue == nullptr)
    {
        PyErr_Print();
        std::exit(1);
    }
    PyObject *first_obj = PyTuple_GetItem(pValue, 0);
    PyObject *second_obj = PyTuple_GetItem(pValue, 1);
    PyArrayObject *first_array = reinterpret_cast<PyArrayObject*>(first_obj);
    PyArrayObject *second_array = reinterpret_cast<PyArrayObject*>(second_obj);
    int first_len = PyArray_SHAPE(first_array)[0];
    int second_len = PyArray_SHAPE(second_array)[0];
    //cout<<first_len<<endl;
    //cout<<second_len<<endl;
    double *first_tab= reinterpret_cast<double*>(PyArray_DATA(first_array));
    double *second_tab= reinterpret_cast<double*>(PyArray_DATA(second_array));
    std::vector<double> pycenters(first_tab,first_tab+first_len);
    //cout<<pycenters.size()<<endl;
    std::vector<double> pyStdvars(second_tab,second_tab+second_len);
    setStdvars(pyStdvars);
    setCenters(pycenters);
    //
    Py_DECREF(pName);
    Py_DECREF(pModule);
    Py_DECREF(pFunc);
    Py_DECREF(pArgs);



       // } catch(std::exception& ex) {
        //std::cerr << "Exception caught: " << ex.what() << std::endl;
        //} catch(...) {
       //std::cerr << "Unknown exception caught" << std::endl;
        //}

};


void kmeans::detection(std::string eventDate, std::string eventId, std::vector<int>& labels) {
     if (getCenters().size() != 0) {
        std::tm tm = {};
        // Utiliser std::istringstream pour lire la chaîne de caractères
        std::istringstream ss(eventDate);
        ss >> std::get_time(&tm, "%d/%m/%Y %H:%M:%S");
        std::time_t time = std::mktime(&tm);    
        int value = tm.tm_hour;// Extract hour part from the eventDate string
        
        std::vector<double> distances;
        for (double c : getCenters()) {
            double dist = distance(c, value);
            
            distances.push_back(dist);
        }
        auto it_score = std::min_element(distances.begin(), distances.end());
        int index_val_cluster = it_score - distances.begin();
        double stdvar = this->stdvars[index_val_cluster];
        if (abs(stdvar) != 0) { 

            double zscore = *it_score / std::abs(stdvar);
            if (std::abs(zscore) >= getThreshold()) {
                labels.push_back(1);
            } else {
                labels.push_back(0);
            }
        } else {
            if(abs(*it_score)>= 1){
                labels.push_back(1);
            }else{
                labels.push_back(0);
            }
                

        }
        
    }
};
kmeans::~kmeans(){

};
