from cs50 import get_int

def main():
    table = {
        'i': "INVALID",
        'a': "AMEX",
        'm': "MASTERCARD",
        'v': "VISA"
    }

    card_number = get_int("Number: ")
    if luhn(card_number):
        print(table[check(card_number)])
    else:
        print("INVALID")

def check(number):
    if number >= 4000000000000000 and number < 5000000000000000:
        return 'v'
    elif number >= 4000000000000 and number < 5000000000000:
        return 'v'
    elif number >= 340000000000000 and number < 350000000000000:
        return 'a'
    elif number >= 370000000000000 and number < 380000000000000:
        return 'a'
    elif number >= 5100000000000000 and number < 5600000000000000:
        return 'm'
    else:
        return 'i'

def luhn(n):
    s = str(n)[::-1]
    sum = 0
    for i in range(len(s)):
        if i % 2 == 0:
            sum += int(s[i])
        else:
            sum += int((int(s[i]) * 2) / 10) + (int(s[i]) * 2) % 10
    if sum % 10 == 0:
        return True
    else:
        return False

main()
