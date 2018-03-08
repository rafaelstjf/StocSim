#ifndef DIRECTMETHOD_H
#define DIRECTMETHOD_H

#include <iostream>
#include "SSA.h"

using namespace std;

class DirectMethod : public SSA
{
public:

    void perform(string filename);
    virtual ~DirectMethod();

private:
    void initialize(string filename); //read the model and initialize data structures
    void calcPropensity(); //calculate the propensity function for each reaction
    void genReactionTime(); //estimate the occurrence time for the next reaction
    void selectReaction(); //select which reaction will occur next

};

#endif // DIRECTMETHOD_H
