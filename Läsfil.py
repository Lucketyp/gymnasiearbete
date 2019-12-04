# Denna skit är förmodligen helt felprogrammerad men bör funka, den printar alla karaktärer med - som separator
# Se till att du importerar pyserial och INTE serial
# Välj rätt COM port på arduinoData
# Pröva att Serial.write() på arduinon och sedan avläsa i serial monitor för att titta om du får något

import serial
arduinoData = serial.Serial("com3", 115200) # RÄTT COM PORT

inputs = []
totalsträng = []

def read():
    text_file = open("test.txt", "r")
    lines = text_file.read().splitlines()

    for line in lines:
        inputs.append(float(line))

    for i in range(len(inputs)):
        temp = inputs[i]
        varjetal = str(temp)
        for ch in varjetal:
            totalsträng.append(ch)
        totalsträng.append("-")
    resultat = ""
    resultat = resultat.join(totalsträng)
    sendData(resultat)

    text_file.close()


def sendData(para):
    resultatstr = str(para)
    for ka in resultatstr:
        print(ka)
        arduinoData.write(b"ka") # HÄR SKICKAS DATAN
        #kan annars vara endast write("ka")

read()
