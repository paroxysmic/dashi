import time, math
pg = int(input("how many pages?"))
currpg = 0
tottime = 0
def format(num):
    if(num < 60):
        return f"{round(num, 2)}s"
    elif(num < 3600):
        return f"{math.floor(num / 60)}m {format(num % 60)}"
    else:
        return f"{math.floor(num / 3600)}h {format(num % 3600)}"
while(currpg < pg):
    ct = time.time()
    npt = input("press any key to advance by a page!")
    if npt == "quit":
        print("bye!")
        break
    currpg += 1
    tottime += time.time() - ct
    avgpgt = tottime / currpg
    print(f"pages left to go: {pg - currpg}\navg time per page: {format(avgpgt)}\nest time left: {format(avgpgt * (pg - currpg))}")

