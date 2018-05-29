#ifndef NEXTREACTIONMETHOD_HPP
#define NEXTREACTIONMETHOD_HPP
#define inf INT_MAX
#include <iostream>
#include "../include/SSA.hpp"
#include "../include/HeapNode.hpp"
#include "../include/IndexedPrioQueue.hpp"
#include "../include/List.hpp"
#include "../include/DependencyGraphNRM.hpp"

using namespace std;

class NextReactionMethod : public SSA
{
public:
  virtual void perform(string filename, double simulTime, double beginTime);
  virtual ~NextReactionMethod();

protected:
  virtual void initialization(string filename, double simulTime);
  virtual void calcPropensity();
  virtual void calcPropOne(int index);
  virtual void reacTimeGeneration();
  virtual void reacSelection();
  virtual void reacExecution();
  List* queue; //priority queue used to store the absolute time of each reaction
  double* RNArray;
  HeapNode* selectedNode; //used to store the selected reaction index and time

};
#endif
