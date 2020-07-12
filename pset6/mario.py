from cs50 import get_int

def get_range_int(a, b):
    while True:
        ans = get_int("Height: ")
        if ans >= a and ans <= b:
            return ans

height = get_range_int(1, 8)
for i in range(1, height + 1):
    for left in range(height):
        if left < height - i:
            print(" ", end="")
        else:
            print("#", end="")
    print("  ", end="")
    for right in range(height):
        if right < i:
            print("#", end="")
        else:
            # print(" ", end="")
            pass
    print()
