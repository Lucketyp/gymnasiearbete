using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NN : IComparable<NN>
{
    public float fitness = 0;

    private int[] parameters;

    private int numInputs;
    private int numHidden;
    private int numOutputs;

    double[] inputLayer;
    double[] hiddenLayer;
    double[] outputLayer;

    double[] hiddenBiases;
    double[] outputBiases;

    double[,] hiddenWeights;
    double[,] outputWeights;

    void InitVariables()
    {
        numInputs = parameters[0];
        numHidden = parameters[1];
        numOutputs = parameters[2];

        inputLayer = new double[numInputs];
        hiddenLayer = new double[numHidden];
        outputLayer = new double[numOutputs];

        hiddenBiases = new double[numHidden];
        outputBiases = new double[numOutputs];

        hiddenWeights = new double[numInputs, numHidden];
        outputWeights = new double[numHidden, numOutputs];
    }

    public NN(int[] _parameters)
    {
        parameters = _parameters;
        InitVariables();
        InitBiases();
        InitWeights();
    }
    
    public void Mutate(int chance, float val)
    {
        for (int i = 0; i < numHidden; i++)
        {
            hiddenBiases[i] = (UnityEngine.Random.Range(0f, chance) <= 5) ? hiddenBiases[i] += UnityEngine.Random.Range(-val, val) : hiddenBiases[i];
        }

        for (int i = 0; i < numOutputs; i++)
        {
            outputBiases[i] = (UnityEngine.Random.Range(0f, chance) <= 5) ? outputBiases[i] += UnityEngine.Random.Range(-val, val) : outputBiases[i];
        }

        for (int i = 0; i < numHidden; i++)
        {
            for (int j = 0; j < numInputs; j++)
            {
                hiddenWeights[j, i] = (UnityEngine.Random.Range(0f, chance) <= 5) ? hiddenWeights[j,i] += UnityEngine.Random.Range(-val, val) : hiddenWeights[j, i];
            }
        }

        for (int i = 0; i < numOutputs; i++)
        {
            for (int j = 0; j < numHidden; j++)
            {
                outputWeights[j, i] = (UnityEngine.Random.Range(0f, chance) <= 5) ? outputWeights[j, i] += UnityEngine.Random.Range(-val, val) : outputWeights[j, i];
            }
        }
    }

    void InitBiases()
    {
        for (int i = 0; i < numHidden; i++)
        {
            hiddenBiases[i] = getRandom();
        }

        for (int i = 0; i < numOutputs; i++)
        {
            outputBiases[i] = getRandom();
        }
    }

    void InitWeights()
    {
        for (int i = 0; i < numHidden; i++)
        {
            for (int j = 0; j < numInputs; j++)
            {
                hiddenWeights[j, i] = getRandom();
            }
        }

        for (int i = 0; i < numOutputs; i++)
        {
            for (int j = 0; j < numHidden; j++)
            {
                outputWeights[j, i] = getRandom();
            }
        }
    }

    public double[] Process(double[] inputs)
    {
        double[] outputs = new double[1];

        for (int i = 0; i < numHidden; i++)
        {
            double activation = hiddenBiases[i];
            for (int j = 0; j < numInputs; j++)
            {
                activation += inputs[j] * hiddenWeights[j, i];
            }
            hiddenLayer[i] = sigmoid(activation);
        }

        for (int i = 0; i < numOutputs; i++)
        {
            double activation = outputBiases[i];
            for (int j = 0; j < numHidden; j++)
            {
                activation += hiddenLayer[j] * outputWeights[j, i];
            }
            outputs[i] = sigmoid(activation);
        }
        return outputs;
    }

    double getRandom()
    {
        return UnityEngine.Random.Range(-1.0f, 1.0f);
    }

    double sigmoid(double In)
    {
        return 1.0 / (1.0 + Mathf.Exp((float)-In));
    }

    public int CompareTo(NN other)
    {
        if (other == null) return 1;

        if (fitness > other.fitness)
            return 1;
        else if (fitness < other.fitness)
            return -1;
        else
            return 0;
    }

    public NN copy(NN nn)
    {
        for (int i = 0; i < numHidden; i++)
        {
            nn.hiddenBiases[i] = hiddenBiases[i];
        }

        for (int i = 0; i < numOutputs; i++)
        {
            nn.outputBiases[i] = outputBiases[i];
        }

        for (int i = 0; i < numHidden; i++)
        {
            for (int j = 0; j < numInputs; j++)
            {
                nn.hiddenWeights[j, i] = hiddenWeights[j, i];
            }
        }

        for (int i = 0; i < numOutputs; i++)
        {
            for (int j = 0; j < numHidden; j++)
            {
                nn.outputWeights[j, i] = outputWeights[j, i];
            }
        }

        return nn;
    }

    public void Load(string path)
    {
        TextReader tr = new StreamReader(path);
        int NumberOfLines = (int)new FileInfo(path).Length;
        string[] ListLines = new string[NumberOfLines];
        int index = 1;

        for (int i = 0; i < NumberOfLines; i++)
        {
            ListLines[i] = tr.ReadLine();
        }
        tr.Close();

        if(new FileInfo(path).Length > 0)
        {
            for (int i = 0; i < hiddenBiases.Length; i++)
            {
                hiddenBiases[i] = float.Parse(ListLines[index]);
                index++;
            }

            for (int i = 0; i < outputBiases.Length; i++)
            {
                outputBiases[i] = float.Parse(ListLines[index]);
                index++;
            }

            for (int i = 0; i < numInputs; i++)
            {
                for (int j = 0; j < numHidden; j++)
                {
                    hiddenWeights[i, j] = float.Parse(ListLines[index]);
                    index++;                   
                }
            }

            for (int i = 0; i < numHidden; i++)
            {
                for (int j = 0; j < numOutputs; j++)
                {
                    outputWeights[i, j] = float.Parse(ListLines[index]);
                    index++;
                }
            }
        }
    }

    public void Save(string path)
    {
        File.Create(path).Close();
        StreamWriter writer = new StreamWriter(path, true);

        for (int i = 0; i < hiddenBiases.Length; i++)
        {
            writer.WriteLine(hiddenBiases[i]);
        }

        for (int i = 0; i < outputBiases.Length; i++)
        {
            writer.WriteLine(outputBiases[i]);
        }

        for (int i = 0; i < numInputs; i++)
        {
            for (int j = 0; j < numHidden; j++)
            {
                writer.WriteLine(hiddenWeights[i, j]);                
            }
        }

        for (int i = 0; i < numHidden; i++)
        {
            for (int j = 0; j < numOutputs; j++)
            {
                writer.WriteLine(outputWeights[i, j]);
            }
        }
        writer.Close();
    }

    //Save och load metoder
}
