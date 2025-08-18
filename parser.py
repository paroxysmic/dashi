file = open("prettyrays.txt", "r")
arr2 = [(''.join([char for char in line if char not in "{}"])).split(',') for line in file.readlines()]
for line in arr2:
    buf = ''
    for i in range(64):
        buf += line[i]
        if i % 8 == 7:
            print(buf)
            buf = ''
    
    
