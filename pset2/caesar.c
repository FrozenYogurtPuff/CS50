#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int parse_int(string key);
void caesar(int key, string plain);

int main(int argc, string argv[])
{
    int key;
    if (argc != 2 || (key = parse_int(argv[1])) == -1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    string plain = get_string("plaintext:  ");
    caesar(key, plain);
    return 0;
}

int parse_int(string key)
{
    int length = strlen(key);
    int ans = 0;
    bool nanflag = false;
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(key[i]))
            nanflag = true;
        else
            ans = ans * 10 + (key[i] - '0');
    }
    return (nanflag) ? -1 : ans;
}

void caesar(int key, string plain)
{
    printf("ciphertext: ");
    int length = strlen(plain);
    for (int i = 0; i < length; i++)
    {
        if (isalpha(plain[i]))
        {
            int pos = toupper(plain[i]) - 'A';
            int shifted = (pos + key) % 26;
            printf("%c", plain[i] - pos + shifted);
        }
        else
            printf("%c", plain[i]);
    }
    printf("\n");
}
