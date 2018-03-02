#ifndef SPECIE_H
#define SPECIE_H

#include <iostream>
#include <string>

using namespace std;
class Specie
{
  private:
    string name;
    long int number;

  public:
    Specie();
    ~Specie();
    void setName(string n);
    void setNumber(long int num);
    string getName();
    long int getNumber();
};
#endif
