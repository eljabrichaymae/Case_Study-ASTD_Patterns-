#include <iostream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <fstream>
#include "../../nlohmann/json.hpp"
#include "kde.h"
#include <Python.h>
#include <sstream>
#include <iomanip>
#include <ctime>

//#include "numpy/arrayobject.h"
using json = nlohmann::json;
using namespace std;


kde::kde(){
    this->data_post_training={};
    this->alerts={};
    //this->threshold=0.000001;
};
kde::kde(double threshold){
    this->data_post_training={};
    this->alerts={};
    this->threshold=threshold;
};
void kde::setData_post_training(std::vector<double> data_post_training){
    this->data_post_training = data_post_training;
};
void kde::setThreshold(double threshold){
    this->threshold =threshold;
};
void kde::setKDEObject(PyObject* pKDE){
    this->pKDE= pKDE ;
};
std::vector<double> kde::getData_post_training(){
    return this->data_post_training;
};
std::vector<std::string> kde::getAlerts(){
    return this->alerts;
};
double kde::getThreshold(){
    return this->threshold;
};
PyObject* kde::getKDEObject(){
    return pKDE;
};

void kde::training(PyObject* result){
       

        //appeler la fonction avec les argument nécessaires
        PyObject *pName1, *pModule, *pFunc, *pArgs, *pValue,*pKDE;
        pName1 = PyUnicode_FromString((char*)"vonMises");
        pModule = PyImport_Import(pName1);
        if (pModule == nullptr)
        {
            PyErr_Print();
            std::exit(1);
        }
        pFunc = PyObject_GetAttrString(pModule, (char*)"circular_kde");
         pArgs = PyTuple_Pack(1, result);
        pValue = PyObject_CallObject(pFunc, pArgs);
        Py_DECREF(pArgs);

        if (pValue != nullptr && PyTuple_Size(pValue) == 3) {
            pKDE = PyTuple_GetItem(pValue, 0); // Keep a reference to the KDE object
            Py_INCREF(pKDE); // Increment the reference count

            PyObject* kde_values_obj = PyTuple_GetItem(pValue, 1);
            PyObject* threshold_obj = PyTuple_GetItem(pValue, 2);

            if (PyList_Check(kde_values_obj) && PyFloat_Check(threshold_obj)) {
                int kde_values_len = PyList_Size(kde_values_obj);
                std::vector<double> kde_values;
                kde_values.reserve(kde_values_len);

                for (int i = 0; i < kde_values_len; ++i) {
                    PyObject* item = PyList_GetItem(kde_values_obj, i);
                    if (PyFloat_Check(item)) {
                        kde_values.push_back(PyFloat_AsDouble(item));
                    } else {
                        PyErr_SetString(PyExc_TypeError, "Expected a list of floats");
                       
                    }
                }
                setData_post_training(kde_values);
                threshold = PyFloat_AsDouble(threshold_obj);
                setThreshold(threshold);
        
                setKDEObject(pKDE);

            } else {
                PyErr_SetString(PyExc_TypeError, "Unexpected return types from circular_kde");
                
            }
        } else {
            PyErr_Print();
            
        }       
       
};
void kde::detection(std::string eventDate, std::string eventId, std::vector<int>& labels){

    if(getKDEObject()){
    std::tm tm = {};
    // Utiliser std::istringstream pour lire la chaîne de caractères
    std::istringstream ss(eventDate);
    ss >> std::get_time(&tm, "%d/%m/%Y %H:%M:%S");
    std::time_t time = std::mktime(&tm);    
    int X = tm.tm_hour;

    // Importer le module Python (assurez-vous que le chemin d'accès est correct)
    PyObject *pName = PyUnicode_FromString((char*)"vonMises");
    PyObject *pModule = PyImport_Import(pName);
    //Py_DECREF(pName);
    if (pModule != nullptr) {
        // Récupérer la fonction 'detection' du module
        PyObject *pFunc = PyObject_GetAttrString(pModule, "detection");
        if (pFunc) {
            // Convertir X en Python float
            PyObject *pX = PyFloat_FromDouble(X);  

            // Convertir threshold en Python float
            PyObject *pThreshold = PyFloat_FromDouble(getThreshold());

            // Construire les arguments pour l'appel de la fonction Python
            PyObject *pArgs = PyTuple_New(3);
            PyTuple_SetItem(pArgs, 0, pX);
            PyTuple_SetItem(pArgs, 1, getKDEObject());
            PyTuple_SetItem(pArgs, 2, pThreshold);

            // Appeler la fonction Python
            PyObject *pResult = PyObject_CallObject(pFunc, pArgs);
            if (pResult != nullptr) {
                // Récupérer le label retourné par la fonction Python
                int label = PyLong_AsLong(pResult);
                labels.push_back(label);
                //Py_DECREF(pResult);
            } else {
                PyErr_Print();
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            std::cerr << "Impossible de trouver la fonction 'detection'." << std::endl;
        }
    } else {
        PyErr_Print();
        std::cerr << "Impossible d'importer le module Python." << std::endl;
    }
    }

};

kde::~kde(){};
