#include <cs50.h>
#include <stdio.h>
// It's kindo messy, but CS50 require the Allman style.

int get_range_int(int a, int b);

int main(void)
{
    const int lower = 1, upper = 8;
    int height = get_range_int(lower, upper);
    for (int i = 1; i <= height; i++)
    {
        for (int left = 0; left < height; left++)
        {
            if (left < height - i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");
        for (int right = 0; right < height; right++)
        {
            if (right < i)
            {
                printf("#");
            }
            else
            {
                // printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}

int get_range_int(int a, int b)
{
    int ans;
    do
    {
        ans = get_int("Height: ");
    }
    while (ans < a || ans > b);
    return ans;
}
