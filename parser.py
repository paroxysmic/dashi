file = open("unformattedrays.txt", "r")
for line in file.readlines():
    print(eval(line[:-1]))
