using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TrackBuilder : MonoBehaviour
{
    public GameObject wall;
    public GameObject gate;
    public float width = 4;
    int wallIndex;

    private Vector2 centerPoint;
    private List<Vector2> leftPoints;
    private List<Vector2> rightPoints;

    public float debugRadius = 0.5f;
    bool drawPoints = false;

    //REFACTOR
    //Vägg och rotations metoderna bör beskriva vinkel skapad i namnen

    void Start()
    {
        //Initialiserar
        leftPoints = new List<Vector2>();
        rightPoints = new List<Vector2>();
        wallIndex = 0;
        //Skapar första punkterna
        centerPoint = Vector2.zero;
        AddPoints(centerPoint);
        //Rita gizmos
        drawPoints = true;
    }

    void Update()
    {
        //Om vänsterklick
        if(Input.GetKeyDown(KeyCode.Mouse0))
        {
            Segment();
        }
        if(Input.GetKeyDown(KeyCode.Mouse1))
        {
            LastSegment();
        }
        if(Input.GetKeyDown(KeyCode.Mouse2))
        {
            DeleteSegment();
        }
    }

    //Huvud metoden
    void Segment()
    {  
        Vector2 newCenter = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        BuildGate(centerPoint, newCenter, "pointGate " + wallIndex);
        AddPoints(centerPoint, newCenter);       
        BuildWall(leftPoints, "leftWall " + wallIndex);
        BuildWall(rightPoints, "rightWall " + wallIndex);
        wallIndex++;
    }
    //Sista segmentet, modifierad huvud metod
    void LastSegment()
    {
        BuildLastWall(leftPoints);
        BuildLastWall(rightPoints);
    }
    //Tar bort senaste segmentet
    void DeleteSegment()
    {
        wallIndex--;
        RemovePoints();
        RemoveWall();
        RemoveGate();
        LastCenter();
    }

    //Skapar och placerar vägg objektet
    void BuildWall(List<Vector2> side, string name)
    {
        Vector2[] points = side.ToArray();
        Vector2 firstPoint = points[points.Length - 1];
        Vector2 secondPoint = points[points.Length - 2];
        //Längden väggen ska bli är distansen mellan punkterna
        float wallLength = Vector2.Distance(firstPoint, secondPoint);
        Transform wallTransform = CreateWallTransform(firstPoint, secondPoint);
        //Skapar väggen
        GameObject thisWall = Instantiate(wall, firstPoint, wallTransform.rotation) as GameObject;
        //Döper den
        thisWall.name = name;
        //Gör det rätt längd
        thisWall.gameObject.transform.localScale = new Vector2(1, wallLength);
    }
    //Skapar och placerar poäng portar
    void BuildGate(Vector2 oldCenter, Vector2 newCenter, string name)
    {
        Transform gateTransform = CreatePointTransform(oldCenter, newCenter);
        GameObject thisGate = Instantiate(gate, newCenter, gateTransform.rotation) as GameObject;
        //Döper den
        thisGate.name = name;
        //Gör det rätt längd
        thisGate.gameObject.transform.localScale = new Vector2(0.5f, width * 2);
    }
    //Skapar och placerar sista väggarna
    void BuildLastWall(List<Vector2> side)
    {
        Vector2[] points = side.ToArray();
        Vector2 firstPoint = points[0];
        Vector2 secondPoint = points[points.Length - 1];
        //Längden väggen ska bli är distansen mellan punkterna
        float wallLength = Vector2.Distance(firstPoint, secondPoint);
        Transform wallTransform = CreateWallTransform(firstPoint, secondPoint);
        //Skapar väggen
        GameObject thisWall = Instantiate(wall, firstPoint, wallTransform.rotation) as GameObject;
        //Döper den
        thisWall.name = "last wall";
        //Gör det rätt längd
        thisWall.gameObject.transform.localScale = new Vector2(1, wallLength);
    }
    //Tar bort väggar
    void RemoveWall()
    {
        GameObject wall1 = GameObject.Find("leftWall " + wallIndex);
        GameObject wall2 = GameObject.Find("rightWall " + wallIndex);
        Destroy(wall1);
        Destroy(wall2);
    }
    //Tar bort portar
    void RemoveGate()
    {
        GameObject gate = GameObject.Find("pointGate " + wallIndex);
        Destroy(gate);
    }

    //Lägger till punkter i vänster och höger listorna
    void AddPoints(Vector2 center)
    {
        leftPoints.Add(center - new Vector2(width, 0));
        rightPoints.Add(center + new Vector2(width, 0));
    }
    void AddPoints(Vector2 oldCenter, Vector2 newCenter)
    {
        Transform localOffset = CreatePointTransform(oldCenter, newCenter);

        leftPoints.Add(newCenter + (Vector2)(localOffset.up * width));
        rightPoints.Add(newCenter - (Vector2)(localOffset.up * width));

        centerPoint = newCenter;
    }
    void RemovePoints()
    {
        leftPoints.RemoveAt(wallIndex+1);
        rightPoints.RemoveAt(wallIndex+1);
    }
    //Skapar nytt center från förra punkterna
    void LastCenter()
    {
        Vector2[] lPoints = leftPoints.ToArray();
        Vector2 leftPoint = lPoints[lPoints.Length - 1];
        Vector2[] rPoints = rightPoints.ToArray();
        Vector2 rightPoint = rPoints[rPoints.Length - 1];

        centerPoint = (leftPoint + rightPoint) / 2;
    }
    //Skapar en transform för rotationen av punkterna
    private Transform CreatePointTransform(Vector2 oldCenter, Vector2 newCenter)
    {
        Quaternion angle = PointRotation(oldCenter, newCenter);
        Transform localOffset = transform;
        localOffset.rotation = angle;
        return localOffset;
    }
    //Skapar en transform för rotationen av väggarna
    private Transform CreateWallTransform(Vector2 firstPoint, Vector2 secondPoint)
    {
        Quaternion angle = PointRotation(firstPoint, secondPoint, 90);
        Transform localOffset = transform;
        localOffset.rotation = angle;
        return localOffset;
    }
    //Skapar en rotation utifrån var man klickar i förhållande till tidigare center
    private Quaternion PointRotation(Vector2 oldCenter, Vector2 newCenter)
    {
        Vector2 targetVector = newCenter - oldCenter;
        float turnAngle = Mathf.Atan2(targetVector.y, targetVector.x) * Mathf.Rad2Deg;
        return Quaternion.AngleAxis(turnAngle, Vector3.forward);
    }
    private Quaternion PointRotation(Vector2 oldCenter, Vector2 newCenter, float addAngle)
    {
        Vector2 targetVector = newCenter - oldCenter;
        float turnAngle = Mathf.Atan2(targetVector.y, targetVector.x) * Mathf.Rad2Deg;
        turnAngle -= addAngle;
        return Quaternion.AngleAxis(turnAngle, Vector3.forward);
    }

    //Visar pukterna
    private void OnDrawGizmos()
    {
        if (drawPoints)
        {
            Gizmos.color = Color.cyan;
            Gizmos.DrawWireSphere(centerPoint, debugRadius);
            Gizmos.color = Color.magenta;
            foreach (var point in leftPoints)
            {
                Gizmos.DrawWireSphere(point, debugRadius / 2);
            }
            Gizmos.color = Color.yellow;
            foreach (var point in rightPoints)
            {
                Gizmos.DrawWireSphere(point, debugRadius / 2);
            }
        }
    }
}
