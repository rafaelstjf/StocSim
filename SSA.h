#ifndef SSA_H
#define SSA_H

#include<string>
#include <iostream>

using namespace std;
class SSA
{
public:
    SSA();
    void perform(string filename);
    virtual ~SSA();
protected:
    typedef struct Reactions
    {
        // each reaction has 2 matrix(products and reactants)
        int** reactants;
        int** products;
        int numReactions;
        int numElements;

    } Reactions;

    Reactions* reactions; //reactions of the model
    int* k; //reaction rate constant
    float* a0; //propensity array
private:

    virtual void initialize(string filename) = 0; //read the model and initialize data structures
    virtual void calcPropensity() = 0; //calculate the propensity function for each reaction
    virtual void genReactionTime() = 0; //estimate the occurrence time for the next reaction
    virtual void selectReaction() = 0; //select which reaction will occur next



};

#endif // SSA_H
