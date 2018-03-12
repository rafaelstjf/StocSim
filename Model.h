#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <strstream>
#include <fstream>
#include "Model/TReact.h"
#include "Model/Reaction.h"

using namespace std;

class Model {
public:
    Model();
    ~Model();
    void loadModel(string filename);
    int** getReactants();
    int** getProducts();
    double* getReacRateArray();
    double** getDelaysValue();
    double** getDelaysVariation();
    int* getInitialQuantity();
    int getSpecNumber();
    int getReacNumber();
    vector<string> getModelRepresentation();
    bool isModelLoaded();
    map<string, long int> getSpecNameNumber();
private:
    int** reactants; //reactants matrix
    int** products; //products matrix
    double** delaysValue; //delay value matrix
    double** delaysVariation; //delay variation matrix
    int specNumber; //number of species in the model
    int reacNumber; //number of reactions in the model
    double* reacRate; //array with the rate used in each reaction
    bool modelLoaded; //boolean to show if the model is loaded or not
    int* initialQuantity;//array with the species' initial quantities
    map<string, long int>specNameNumber; //associative container with the species' name and number
    vector<string> modelRepresentation;
};


#endif
