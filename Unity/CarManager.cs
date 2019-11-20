using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CarManager : MonoBehaviour
{
    public float timeframe;
    public int population;
    public GameObject carPrefab;

    public int[] parameters = { 3, 5, 1 };

    public float Gamespeed = 1f;
    public float mutationChance = 0.5f;
    public float mutationStrength = 0.5f;

    public List<NN> networks;
    private List<CarController> cars;

    private void Start()
    {
        if(population % 2 != 0)
        {
            //Vid ojämnt antal adderar 1 till storleken av befolkningen
            population++;
        }

        InitNetworks();
        InvokeRepeating("CreateCars", 0.1f, timeframe);
    }

    void InitNetworks()
    {
        networks = new List<NN>();
        for (int i = 0; i < population; i++)
        {
            NN net = new NN(parameters);
            net.Load("Assets/Trained.txt");
            networks.Add(net);
        }
    }

    public void CreateCars()
    {
        Time.timeScale = Gamespeed;
        if(cars != null)
        {
            for (int i = 0; i < cars.Count; i++)
            {
                cars[i].UpdateFitness();
                GameObject.Destroy(cars[i].gameObject);
            }
            SortNetworks();
        }

        cars = new List<CarController>();
        for (int i = 0; i < population; i++)
        {
            CarController car = (Instantiate(carPrefab)).GetComponent<CarController>();
            car.network = networks[i];
            cars.Add(car);
        }
    }

    public void SortNetworks()
    {
        networks.Sort();
        networks[population - 1].Save("Assets/Save.txt");
        //Botten hälften av nätverken muteras
        for (int i = 0; i < population/2; i++)
        {
            networks[i] = networks[i + population/2].copy(new NN(parameters));
            networks[i].Mutate((int)(1 / mutationChance), mutationStrength);
        }
    }
}
