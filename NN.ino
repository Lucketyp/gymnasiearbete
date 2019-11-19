  //Antalet neuroner i varje lager
  static const int numInputs = 3;
  static const int numHidden = 5;
  static const int numOutputs = 1;

  double inputLayer[numInputs];
  double hiddenLayer[numHidden];
  double outputLayer[numOutputs];

  double hiddenBiases[numHidden];
  double outputBiases[numOutputs];

  double hiddenWeights[numInputs][numHidden];
  double outputWeights[numHidden][numOutputs];

void setup() {
  
}

void loop() {
  //Behöver få inputs från sensorerna
  Activation();
  //Behöver skicka outputs till svägning
}

void Activation() {
  HiddenActivation();
  OutputActivation();
}

//Från lager 1 till 2
void HiddenActivation() {
  for(int i=0; i < numHidden; i++) {
    double activation = hiddenBiases[i];
    for (int j=0; j<numInputs; j++) {
      activation += inputLayer[j] * hiddenWeights[j][i];
    }
    hiddenLayer[i] = sigmoid(activation);
  }
}

//Från lager 2 till 3
void OutputActivation() {
  for(int i=0; i < numOutputs; i++) {
    double activation = outputBiases[i];
    for (int j=0; j<numHidden; j++) {
      activation += hiddenLayer[j] * outputWeights[j][i];
    }
    hiddenLayer[i] = sigmoid(activation);
  }
}


double sigmoid(double In) {
  return 1.0/(1.0 + exp(-In));
}
