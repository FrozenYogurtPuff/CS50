#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_non_negative_float(void);

int main(void)
{
    int total_coin = 0;
    const int denominations[4] = {25, 10, 5, 1};
    float dollar = get_non_negative_float();
    int penny = round(dollar * 100);
    for (int i = 0; i < 4; i++)
    {
        total_coin += (penny / denominations[i]);
        penny = penny % denominations[i];
    }
    printf("%d\n", total_coin);
    return 0;
}

float get_non_negative_float()
{
    float ans;
    do
    {
        ans = get_float("Change owed: ");
    } while (ans < 0);
    return ans;
}
