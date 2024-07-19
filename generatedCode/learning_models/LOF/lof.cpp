#include <iostream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "lof.h"
#include "../../nlohmann/json.hpp"
#include <Python.h>
#include <sstream>
#include <iomanip>
#include <ctime>

using json = nlohmann::json;
using namespace std;
    
    lof::lof(){
        this->pyModel=NULL;
        this->numNeighbors = 30;
        this->alerts={};
    };
    lof::lof(int numNeighbors){
        this->pyModel=NULL;
        this->numNeighbors = numNeighbors;
        this->alerts={};
    };
    PyObject* lof::getPyModel(){
        return this->pyModel;
    };
    PyObject* lof::getPScaler(){
        return this->pScaler;
    };
    void lof::setPyModel(PyObject* pyModel){
        this->pyModel = pyModel;
    };
    void lof::setPScaler(PyObject* pScaler){
        this->pScaler = pScaler;
    };
    double lof::getMeanScores(){
        return this->meanScores;
    };
    void lof::setMeanScores(double meanScores){
        this->meanScores = meanScores;
    };
    double lof::getSdScores(){
        return this->sdScores;
    };
    void lof::setSdScores(double sdScores){
        this->sdScores = sdScores;
    };
    double lof::getThreshold(){
        return this->threshold;
    };
    void lof::setThreshold(double threshold){
        this->threshold = threshold;
    };
    int lof::getNumNeighbors(){
        return this->numNeighbors;
    };
    void lof::setNumNeighbors(int numNeighbors){
        this->numNeighbors = numNeighbors;
    };
    std::vector<std::string> lof::getAlerts(){
        return this->alerts;
    };
    void lof::setAlerts(std::vector<std::string> alerts){
        this->alerts = alerts;
    };
   void lof::training(PyObject* result) {
    PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;
    pName = PyUnicode_FromString("LOF");
    if (!pName) {
        PyErr_Print();
        std::exit(1);
    }

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);  // Décrémentez la référence immédiatement après l'importation

    if (!pModule) {
        PyErr_Print();
        std::exit(1);
    }

    pFunc = PyObject_GetAttrString(pModule, "train");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        PyErr_Print();
        Py_XDECREF(pFunc);  // Utilisez Py_XDECREF pour éviter des erreurs si pFunc est nullptr
        Py_DECREF(pModule);
        std::exit(1);
    }

    pArgs = PyTuple_Pack(2, result, PyLong_FromLong(getNumNeighbors()));
    if (!pArgs) {
        PyErr_Print();
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        std::exit(1);
    }

    pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);  // Décrémentez la référence après l'appel de la fonction

    if (!pValue) {
        PyErr_Print();
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        std::exit(1);
    }

    if (PyTuple_Check(pValue) && PyTuple_Size(pValue) == 3) {
        setPyModel(PyTuple_GetItem(pValue, 0));
        setPScaler(PyTuple_GetItem(pValue, 1));
        setThreshold(PyFloat_AsDouble(PyTuple_GetItem(pValue, 2)));
 
    } else {
        PyErr_SetString(PyExc_ValueError, "Expected a tuple of size 3");
        PyErr_Print();
        Py_DECREF(pValue);
        
        std::exit(1);
    }

   
};
void lof::detection(std::string eventDate, std::string eventId, std::vector<int>& labels) {
    if (getPyModel()) {
         std::tm tm = {};

        // Utiliser std::istringstream pour lire la chaîne de caractères
        std::istringstream ss(eventDate);
        ss >> std::get_time(&tm, "%d/%m/%Y %H:%M:%S");
        std::time_t time = std::mktime(&tm);
        int value = tm.tm_hour;
        PyObject *pFunc1, *pArgs1, *pName1, *pModule1, *pValue1;
        pName1 = PyUnicode_FromString("LOF");
        if (!pName1) {
            PyErr_Print();
            std::exit(1);
        }

        pModule1 = PyImport_Import(pName1);
        Py_DECREF(pName1);  // Décrémentez la référence immédiatement après l'importation

        if (!pModule1) {
            PyErr_Print();
            std::exit(1);
        }

        pFunc1 = PyObject_GetAttrString(pModule1, "score");
        if (!pFunc1 || !PyCallable_Check(pFunc1)) {
            PyErr_Print();
            Py_XDECREF(pFunc1);
            Py_DECREF(pModule1);
            std::exit(1);
        }

        pArgs1 = PyTuple_Pack(4, PyLong_FromLong(value), getPyModel(), getPScaler(), PyFloat_FromDouble(getThreshold()));
        if (!pArgs1) {
            PyErr_Print();
            Py_DECREF(pFunc1);
            Py_DECREF(pModule1);
            std::exit(1);
        }

        pValue1 = PyObject_CallObject(pFunc1, pArgs1);
        Py_DECREF(pArgs1);  // Décrémentez la référence après l'appel de la fonction

        if (!pValue1) {
            PyErr_Print();
            Py_DECREF(pFunc1);
            Py_DECREF(pModule1);
            std::exit(1);
        }

        int label = static_cast<int>(PyFloat_AsDouble(pValue1));
        labels.push_back(label);

        Py_DECREF(pValue1);
        Py_DECREF(pFunc1);
        Py_DECREF(pModule1);
    }
}



