#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

string normalize_key(string key);
void substitution(string key, string plain);

int main(int argc, string argv[])
{
    string key;
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    bool check[26] = {0};
    int check_num = 0;
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        char temp = tolower(argv[1][i]);
        if (!isalpha(temp))
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            if (check[temp - 'a'])
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            else
            {
                check[temp - 'a'] = true;
                check_num++;
            }
        }
    }
    if (check_num != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    key = normalize_key(argv[1]);
    string plain = get_string("plaintext:  ");
    substitution(key, plain);
    return 0;
}

string normalize_key(string key)
{
    for (int i = 0; i < 26; i++)
        key[i] = toupper(key[i]);
    return key;
}

void substitution(string key, string plain)
{
    printf("ciphertext: ");
    int length = strlen(plain);
    for (int i = 0; i < length; i++)
    {
        if (isalpha(plain[i]))
        {
            int pos = toupper(plain[i]) - 'A';
            int shifted = toupper(key[pos]) - 'A';
            printf("%c", plain[i] - pos + shifted);
        }
        else
            printf("%c", plain[i]);
    }
    printf("\n");
}
