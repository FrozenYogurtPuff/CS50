from cs50 import get_float

def get_non_negative_float():
    while True:
        ans = get_float("Change owed: ")
        if ans >= 0:
            return ans

total_coin = 0
denominations = [25, 10, 5, 1]
dollar = get_non_negative_float()
penny = int(dollar * 100)
for i in range(4):
    total_coin += int(penny / denominations[i])
    penny = penny % denominations[i]
print(total_coin)
