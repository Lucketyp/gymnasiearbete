#ifndef NN_h
#define NN_h 

#include "Arduino.h"

class NN 
{
  public:
    NN(double network[]);
    double process(float input[]);
    
  private:
    void load(double network[]);
    double sigmoid(double In);
  
    static const int numInputs = 3;
    static const int numHidden = 5;
    static const int numOutputs = 1;

    double hiddenLayer[numHidden];
    double outputLayer[numOutputs];

    double hiddenBiases[numHidden];
    double outputBiases[numOutputs];
  
    double hiddenWeights[numInputs][numHidden];
    double outputWeights[numHidden][numOutputs];
};

#endif