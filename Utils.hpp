#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <math.h>
#include <random>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#define E 2.71828182845904523536
using namespace std;



class Utils
{
  public:
  Utils();
  double getRandomNumber();
  double binomialCoefficient(int k, int n);
  double ln(double n);
  double log10(double n);
  double getCurrentTime();
  double getMinDouble(double* array, int size);
  void saveToCSV(string buffer, string filename);
  void saveToTXT(string buffer, string filename);
  ~Utils();
  private:
  int calcFactorial(int n);
  int fat[11];
};
#endif