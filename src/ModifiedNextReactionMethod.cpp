#include "../include/ModifiedNextReactionMethod.hpp"

void ModifiedNextReactionMethod::initialization(string filename, double simulTime)
{
    model = new Model();
    ut = new Utils();
    this->simulTime = simulTime;
    for (int i = 0; i < filename.size(); i++)
    {
        if (filename[i] == '.')
        {
            methodOutName += "_NRMANDERSON_output";
            break;
        }
        else
            methodOutName += filename[i];
    }
    model->loadModel(filename);
    if (model->isModelLoaded())
    {
        specQuantity = new int[model->getSpecNumber()];
        propArray = new double[model->getReacNumber()];
        queue = new IndexedPrioQueue(model->getReacNumber());
        //
        P = new double[model->getReacNumber()];
        T = new double[model->getReacNumber()];
        for (int i = 0; i < model->getSpecNumber(); i++)
        {
            specQuantity[i] = model->getInitialQuantity()[i];
        }
    }
}
void ModifiedNextReactionMethod::reacTimeGeneration()
{
    double u, t1;
    for (int i = 0; i < model->getReacNumber(); i++)
    {

        u = ut->getRandomNumber();
        P[i] = (-1.0 * ut->ln(u));
        T[i] = 0.0;
        t1 = (P[i] - T[i]) / propArray[i];
        queue->insertKey(i, t1);
    }
    //queue->sort();
}
void ModifiedNextReactionMethod::reacSelection()
{
    selectedNode = queue->getMin();
    currentTime = currentTime + selectedNode->getTime();
}
void ModifiedNextReactionMethod::reacExecution()
{
    double u;  //random number
    double nt; //new time
    int index;
    int sIndex = selectedNode->getIndex();
    //updates the species quantities
    for (int i = 0; i < model->getSpecNumber(); i++)
    {
        specQuantity[i] = specQuantity[i] + model->getStoiMatrix()[sIndex][i];
    }

    for (int i = 0; i < model->getReacNumber(); i++)
    {
        T[i] = T[i] + propArray[i] * selectedNode->getTime();
    }
    u = ut->getRandomNumber();
    P[sIndex] = P[sIndex] + (-1.0 * ut->ln(u));
    for (int i = 0; i < model->getReacNumber(); i++)
    {
        calcPropOne(i);
        cout << P[i] << " : " << T[i] << " : " << propArray[i] << endl;
        nt = (P[i] - T[i]) / propArray[i];
        cout << i << ": " << nt << endl;
        queue->update(i, nt);
    }
}
void ModifiedNextReactionMethod::perform(string filename, double simulTime, double beginTime)
{
    cout << "NEXT REACTION METHOD Anderson" << endl;
    initialization(filename, simulTime);
    if (!model->isModelLoaded())
    {
        cout << "Error! Invalid model." << endl;
        return;
    }
    double beg = ut->getCurrentTime();
    currentTime = beginTime;
    int *xArray;
    x.clear();
    calcPropensity();
    //reacTimeGeneration comes before the while because you can calculate it only once and then
    //update inside the while
    reacTimeGeneration();
    //saves the species quantities on beginTime
    reacSelection();
    if (currentTime != inf)
    {
        currentTime = beginTime;
        //currentTime = beginTime;
        while (currentTime <= simulTime)
        {
            xArray = new int[model->getSpecNumber()];
            for (int i = 0; i < model->getSpecNumber(); i++)
            {
                xArray[i] = specQuantity[i];
            }
            x.insert(make_pair(currentTime, xArray));
            reacSelection();
            reacExecution();
        }
    }
    double en = ut->getCurrentTime(); //end
    cout << "\nSimulation finished with " << en - beg << " seconds." << endl;
    saveToFile();
}
ModifiedNextReactionMethod::~ModifiedNextReactionMethod()
{
    delete dg;
    delete model;
    delete ut;
    delete[] specQuantity;
    delete[] propArray;
    delete[] T;
    delete[] P;
    delete queue;
    delete selectedNode;
}
