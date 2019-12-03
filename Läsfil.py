inputs = []



def read():
    text_file = open("test.txt", "r")
    lines = text_file.read().splitlines()
    print(lines)
    print (len(lines))
    for line in lines:
        print (float(line))
        inputs.append(float(line))
    print("inputs: ", inputs)
    text_file.close()

read()
