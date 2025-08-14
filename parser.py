bm = open("rays.txt", "r")
hexes = []
for line in bm.readlines():
    hexlin = []
    for num in line.split(","):
        hexed = hex(int(num))[2:]
        hexlin.append("0x" + ('0' * (16 - len(hexed))) + hexed)
    hexes.append(hexlin)
for hex in hexes:
    buf = '{'
    for i in range(64):
        buf += hex[i] + ' '
        if(i % 8 == 7):
            print(buf)
            buf = '{'
