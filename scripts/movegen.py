def lshif(k, shift):
    shifk = k >> shift if (shift >= 0) else rshif(k, -shift)
    return 0 if shifk >= 1 << 64 else shifk
def rshif(k, shift):
    shifk = k << shift if (shift >= 0) else lshif(k, -shift)
    return 0 if shifk >= 1 << 64 else shifk
FILE_A = 0x0101010101010101
FILE_H = 0x8080808080808080
def hexprint(num):
    if(num < 0 or num >= 1 << 64):
        return "NOPE"
    hexstr = hex(num)[2:]
    return f"0x{'0' * (16 - len(hexstr))}{hexstr}ULL"
def sqprint(num):
    for i in range(8):
        buf = ""
        for j in range(8):
            buf += f"{(num >> (j + 8 * i)) & 1} "
        buf += "\n"
    buf += '\n'
    return buf
bpatks  = [lshif(1 << i, 8) | (lshif(1 << i, 7) & ~(FILE_A)) | (lshif(1 << i, 9) & ~(FILE_H)) for i in range(64)]
wpatks  = [rshif(1 << i, 8) | (rshif(1 << i, 9) & ~(FILE_A)) | (rshif(1 << i, 7) & ~(FILE_H)) for i in range(64)]

buf = ''
for i in range(8):
    for j in range(8):
        buf += hexprint(wpatks[j + i * 8]) + ", "
    buf += '\n'
print(buf)