variabel_names = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
doubles = []

#Skapar dokumentet att skriva i
f = open("NetworkValues.ino", "w+")
#Namnet på filen med sparat nätverk
g = open("Save.txt", "r")

doubles = g.read().splitlines()

#Loop som skriver alla doubles som separata variablar
for i in range(26):
    f.write("double ")
    f.write(variabel_names[i])
    f.write(" = ")
    f.write(doubles[i])
    f.write(";")
    f.write("\n")
    #Kan skriva ihop write raderna

#Lägger in alla doubles i en array
f.write("\n")
f.write("double network [26] = ")
f.write("[")
for i in range(25):
    f.write(variabel_names[i])
    f.write(", ")

f.write(variabel_names[25])
f.write("];")



f.close()
