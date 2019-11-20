using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CarController : MonoBehaviour
{
    public float speed = 3;
    public float maxTurnAngle = 180;
    float turnDir;

    private double[] inputs = new double[3];
    public NN network;

    public bool collided;
    public int gates;
    public float time;

    public int sensorLength;
    Vector2 forward;
    Vector2 left;
    Vector2 right;
    LayerMask mask;

    private void Start()
    {
        mask = LayerMask.GetMask("Default");
        //Riktningen av sensorerna
        forward = Vector2.up;
        left = new Vector2(0.5f, 0.866f);
        right = new Vector2(-0.5f, 0.866f);

        time = 0;
    }

    void FixedUpdate()
    {        
        if(!collided)
        {
            time += Time.deltaTime;
            inputs = TestSensors(inputs.Length);
            turnDir = TurnDirFromInputs(inputs);
            
            Turn();
            Move();
        }       
    }

    float TurnDirFromInputs(double[] inputs)
    {
        double[] results = network.Process(inputs);
        float steering = (float)results[0];
        return (steering - 0.5f)*2;
    }

    double[] TestSensors(int length)
    {
        double[] sensors = new double[length];
        sensors[0] = TestSensor(forward);
        sensors[1] = TestSensor(left);
        sensors[2] = TestSensor(right);

        return sensors;
    }

    double TestSensor(Vector2 _dir)
    {
        Vector2 dir = transform.TransformDirection(_dir);
        //Gör om positionen till 2D vector
        Vector2 pos = transform.position;
        //Förskjuter sensorerna till kanten av bilen
        pos += dir;
        //Raycast för sensorn
        RaycastHit2D hit = Physics2D.Raycast(pos, dir, sensorLength, mask);

        //Om sensorn träffar något
        if (hit.collider != null)
        {
            //Gör sensor linjen grön
            Debug.DrawRay(pos, dir * sensorLength, Color.green, 0);
            //Gör så att inputen är mellan 0 => 1
            //Debug.Log("sensor return " + hit.distance);
            return 1f - hit.distance / sensorLength;
        }
        //Gör sensor linjen röd
        Debug.DrawRay(pos, dir * sensorLength, Color.red, 0);
        //Ge inputen 0
        return 0;
    }

    void Turn()
    {
        //Måste ändra input från 0 => 1 istället för -1 => 1 när NN tar över
        float turnAngle = -turnDir * maxTurnAngle;
        transform.Rotate(transform.forward, turnAngle * Time.deltaTime);
    }

    void Move()
    {
        //Åker längst lokala y axeln
        Vector3 target = transform.position + transform.up;
        transform.position = Vector3.MoveTowards(transform.position, target, speed * Time.deltaTime);
    }

    void OnCollisionEnter2D(Collision2D col)
    {
        if (col.collider.tag == "Gate")
        {
            //Om det är en poäng port, ge poäng
            gates++;
        }
        else if(col.collider.tag != "Car")
        {
            //Annars är det en vägg => collision
            collided = true;
        }
    }

    public void UpdateFitness()
    {
        network.fitness = gates*5 + time;
    }
}
