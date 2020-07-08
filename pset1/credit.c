#include <stdio.h>
#include <cs50.h>

bool luhn(long n);
char check(long number);

int main(void)
{
    long card_number = get_long("Number: ");
    if (luhn(card_number))
        switch(check(card_number))
        {
            case 'i': printf("INVALID\n");   break;
            case 'a': printf("AMEX\n");   break;
            case 'm': printf("MASTERCARD\n");   break;
            case 'v': printf("VISA\n");   break;
        }
    else
        printf("INVALID\n");
    return 0;
}

bool luhn(long n)
{
    int sum = 0;
    bool odd = false;
    while (n != 0)
    {
        odd = !odd;
        if (odd)
            sum += (n % 10);
        else
            sum += (2 * (n % 10)) / 10 + (2 * (n % 10)) % 10;
        n /= 10;
    }
    if (sum % 10 == 0)
        return true;
    else
        return false;
}

char check(long number)
{
    if (number >= 4000000000000000 && number < 5000000000000000)
        return 'v';
    else if (number >= 4000000000000 && number < 5000000000000)
        return 'v';
    else if (number >= 340000000000000 && number < 350000000000000)
        return 'a';
    else if (number >= 370000000000000 && number < 380000000000000)
        return 'a';
    else if (number >= 5100000000000000 && number < 5600000000000000)
        return 'm';
    else
        return 'i';
}
