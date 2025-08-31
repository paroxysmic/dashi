import pygame as py
py.init()
win = py.display.set_mode((700, 700))
playing = True
numbitsarr = [0 for i in range(64)]
currSquare = (-1, -1)
tex = py.font.Font(py.font.get_default_font(), 40)
def binToHex(arr):
    return "0123456789ABCDEF"[8 * arr[3] + 4 * arr[2] + 2 * arr[1] + arr[0]]
while playing:
    events = py.event.get()
    keys = py.key.get_pressed()
    mpos = py.mouse.get_pos()
    for event in events:
        if event.type == py.QUIT:
            playing = False
        if event.type == py.MOUSEBUTTONUP:
            currSquare = (-1, -1)
        if event.type == py.KEYDOWN:
            if keys[py.K_f]:
                for i in range(64):
                    numbitsarr[i] = 1 - numbitsarr[i]
            if keys[py.K_r]:
                for i in range(64):
                    numbitsarr[i] = 0
    if py.mouse.get_pressed()[0]:
        mpx = (mpos[0] - 16)//70
        mpy = (mpos[1] - 16)//70
        ind = mpx + (7 - mpy) * 8
        if(currSquare != (mpx, mpy) and mpx >= 0 and mpy >= 0 and mpx < 8 and mpy < 8):
            currSquare = mpx, mpy
            numbitsarr[ind] = 1 - numbitsarr[ind]
    if keys[py.K_q]:
        playing = False

    win.fill(0x888888)
    buf = ''
    for y in range(8):
        for x in range(8):
            ind = x + (7 - y) * 8
            pos = (16 + (x * 70), 16 + (y * 70))
            py.draw.rect(win, 0xdddddd if numbitsarr[ind] else 0x222222, (pos[0], pos[1], 66, 66))
            win.blit(tex.render(f"{ind}", False, 0x222222 if numbitsarr[ind] else 0xdddddd), pos)
        texind = 8 * (7 - y)
        hexstr = binToHex(numbitsarr[texind + 4: texind + 8]) + binToHex(numbitsarr[texind: texind + 4]) 
        win.blit(tex.render(f"0x{hexstr}", False, 0x222222), (pos[0] + 80, pos[1] + 20))  
        buf += hexstr
    win.blit(tex.render(f"0x{buf}ULL", False, 0x222222), (40, 600))
    py.display.update()
print(f"0x{buf}ULL")