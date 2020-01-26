#include "Arduino.h"
#include "NN.h"

NN::NN(double network[]) 
{
  load(network);
}

double NN::process(float input[3]) 
{
   double output;
  //Från lager 1 till 2
  for(int i=0; i < numHidden; i++) {
    double activation = hiddenBiases[i];
    for (int j=0; j<numInputs; j++) {
      activation += input[j] * hiddenWeights[j][i];
    }
    hiddenLayer[i] = sigmoid(activation);
  }
  //Från lager 2 till 3
  for(int i=0; i < numOutputs; i++) {
    double activation = outputBiases[i];
    for (int j=0; j<numHidden; j++) {
      activation += hiddenLayer[j] * outputWeights[j][i];
    }
    output = sigmoid(activation);
  }
  return output;
}

void NN::load(double network[]) 
{
  int index = 0;
  
  for(int i=0; i < numHidden;i++) {
    hiddenBiases[i] = network[index];
    index++;
  }

  for(int i=0; i < numOutputs; i++) {
    outputBiases[i] = network[index];
    index++;
  }

  for (int i = 0; i < numInputs; i++)
  {
      for (int j = 0; j < numHidden; j++)
      {
          hiddenWeights[i][j] = network[index];
          index++;                   
      }
  }

  for (int i = 0; i < numHidden; i++)
  {
      for (int j = 0; j < numOutputs; j++)
      {
          outputWeights[i][j] = network[index];
          index++;
      }
  }
}

double NN::sigmoid(double In)
{
  return 1.0/(1.0 + exp(-In));
}