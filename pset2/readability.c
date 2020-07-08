#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);

int main(void)
{
    string str = get_string("Text: ");
    int l = count_letters(str);
    int w = count_words(str);
    int s = count_sentences(str);
    double L = (double) l / (double) w * 100.0;
    double S = (double) s / (double) w * 100.0;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
        printf("Before Grade 1\n");
    else if (index >= 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", index);
    return 0;
}

int count_letters(string s)
{
    int len = strlen(s);
    int letter = 0;
    for (int i = 0; i < len; i++)
        if (isalpha(s[i]))
            letter++;
    return letter;
}

int count_words(string s)
{
    int len = strlen(s);
    int word = 1;
    for (int i = 0; i < len; i++)
        if (s[i] == ' ')
            word++;
    return word;
}

int count_sentences(string s)
{
    int len = strlen(s);
    int sentence = 0;
    for (int i = 0; i < len; i++)
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
            sentence++;
    return sentence;
}
