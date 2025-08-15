bmag = open("bbits.txt", "r")
print([(int(line[:-1])) for line in bmag.readlines()])