nums = []
for i in range(64):
    pos = 1 << i
    wleft = (((pos << 15) | (pos >> 17)) & ~(0x8080808080808080)) & ((1 << 64) - 1)
    wright = (((pos >> 15) | (pos << 17)) & ~(0x0101010101010101)) & ((1 << 64) - 1)
    sleft = (((pos << 6) | (pos >> 10)) & ~(0xC0C0C0C0C0C0C0C0)) & ((1 << 64) - 1)
    sright = (((pos >> 6) | (pos << 10)) & ~(0x0303030303030303)) & ((1 << 64) - 1)
    atk = wleft + wright + sleft + sright
    nums.append(atk)
buf = ''
def ppr(num):
    for i in range(8):
        buf = ''
        for j in range(8):
            ind = j + (i * 8)
            bit = "1 " if ((num >> ind) & 1) == 1 else ". "
            buf += bit
        print(buf)
for i in range(64):
    number = hex(nums[i])[2:]
    buf += f"0x{'0' * (16 - len(number))}{number}ULL, "
    if(i % 8 == 7):
        print(buf)
        buf = ''