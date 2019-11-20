#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include<SoftwareSerial.h>

ESP8266WebServer server;
SoftwareSerial s(3, 1);

int example = 1;

char* ssid = "COMHEM_5f6a42";
char* password = "ud4qdn2e";

char webpage[] PROGMEM = R"=====(
<html> 
<head> 
</head> 

<body>

</body>

<script>

  function clicking(letter) {
    var xhr = new XMLHttpRequest();
    var clickurlw = "/clickstatew";
    var clickurla = "/clickstatea";
    var clickurls = "/clickstates";
    var clickurld = "/clickstated";

    xhr.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        console.log("FEFEFE");
      }
    };

    if (letter == 1) {
      xhr.open("GET", clickurlw, true);
    } else if (letter == 2) {
      xhr.open("GET", clickurla, true);
    } else if (letter == 3) {
      xhr.open("GET", clickurls, true);
    } else if (letter == 4) {
      xhr.open("GET", clickurld, true);
    } 
    xhr.send();
  }
  
  window.addEventListener("keydown", checkKeyPress, false);

 
 
// this function checks to see if the letter 'a' key has been pressed
  function checkKeyPress(key) {
    if (key.keyCode == "87") {
      clicking(1);
    } else if (key.keyCode == "65") {
      clicking(2);
    } else if (key.keyCode == "83") {
      clicking(3);
    } else if (key.keyCode == "68") {
      clicking(4);
    }
  }


</script>
</html>
)=====";

void setup() 
{
  // put your setup code here, to run once: 
  
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println(" ");
  Serial.println("Connection succesful");
  Serial.print("Ip address: ");
  Serial.print(WiFi.localIP());

  server.on("/",[](){server.send_P(200,"text/html",webpage);});
  server.on("/clickstatew", addOnClickw);
  server.on("/clickstatea", addOnClicka);
  server.on("/clickstates", addOnClicks);
  server.on("/clickstated", addOnClickd);
  server.begin();
}

void loop() 
{
  server.handleClient();
  
}

void addOnClickw() {
  server.send(204,"");
  Serial.println("w");
  s.write(1);
}

void addOnClicka() {
  server.send(204,"");
  Serial.println("a");
  s.write(2);
}

void addOnClicks() {
  server.send(204,"");
  Serial.println("s");
  s.write(3);
}

void addOnClickd() {
  server.send(204,"");
  Serial.println("d");
  s.write(4);
}
