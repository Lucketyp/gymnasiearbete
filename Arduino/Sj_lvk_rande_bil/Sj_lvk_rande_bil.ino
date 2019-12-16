//Självkörande bil
//Skapad av Lucas Johnson

#define sensor1 A3 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
#define sensor2 A4
#define sensor3 A5

//Biblotek
#include <NN.h>
#include <Sensorer.h>
#include <Styrning.h>

//Nätverksvärden
//======================================================================
double a = -0.102183610200882; 
double b = 0.604229182004929; 
double c = 1.36135351657867; 
double d = 0.480410560965538; 
double e = 1.94524163007736; 
double f = 1.36344069242477; 
double g = 0.146766483783722; 
double h = -0.195690214633942; 
double i = -2.47424174845219; 
double j = -0.101662278175354; 
double k = 1.07618692517281; 
double l = -1.12541967630386; 
double m = -0.80472506582737; 
double n = 1.79264281690121; 
double o = -0.719811275601387; 
double p = -1.30845177173615; 
double q = 0.902448296546936; 
double r = -0.33608503639698; 
double s = -1.72986131906509; 
double t = 0.890344500541687; 
double u = 0.600034445524216; 
double v = 1.19118444621563; 
double w = -1.54627247154713; 
double x = -1.13746644556522; 
double y = -0.0987199693918228; 
double z = -0.0319940000772476; 

double network [26] = {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z};
//Biblotek deklarering
//======================================================================
NN net = NN(network);
      //=> kan nätverk laddas här redan?

byte sensors[] = {sensor1, sensor2, sensor3};
Sensorer sens = Sensorer(sensors);

Styrning styr = Styrning();
//======================================================================

double steerValue = 0;
float sensValues[3];

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//Innan setup globala variablar och konstanter
void setup() {
Serial.begin(115200);
}

void loop() {
  //Sensor läsning
  sens.readSensors();
  //Processa sensorer
  steerValue = net.process(sens.inputDis);
  Serial.println(steerValue - 0.5f);
  //Styrning
  styr.steer(steerValue);
}
