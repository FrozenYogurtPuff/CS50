// Implements a dictionary's functionality
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 181081;
unsigned int total = 0;

// Hash table
node *table[N];

bool strcasecmp(char * a, const char * b)
{
    char A[LENGTH + 1];
    char B[LENGTH + 1];
    strcpy(A, a);
    strcpy(B, b);
    int aLen = strlen(A);
    int bLen = strlen(B);
    for (int i = 0; i < aLen; i++)
    {
        A[i] = tolower(A[i]);
    }
    for (int i = 0; i < bLen; i++)
    {
        B[i] = tolower(B[i]);
    }
    return strcmp(A, B);
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int hashCode = hash(word);
    node * key = table[hashCode];
    while (key != NULL)
    {
        if (!strcasecmp(key->word, word))
            return true;
        key = key->next;
    }
        return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int len = strlen(word);
    unsigned int hashCode = 1;
    for (int i = 0; i < len; i++)
    {
        hashCode = (hashCode * (unsigned int) tolower(word[i]));
        if (hashCode > N)
            hashCode = hashCode % N;
    }
    return hashCode;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE * dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open dictionary.\n");
        return false;
    }
    while (fscanf(dict, "%s", word) != EOF)
    {
        if (check(word))
            continue;
        unsigned int hashCode = hash(word);
        node * insert = malloc(sizeof(node));
        strcpy(insert->word, word);
        node * key = table[hashCode];
        if (key != NULL)
            insert->next = key;
        else
            insert->next = NULL;
        table[hashCode] = insert;
        total++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return total;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (unsigned int i = 0; i < N; i++)
    {
        node * temp1 = table[i];
        node * temp2 = temp1;
        while (temp1 != NULL && temp2 != NULL)
        {
            temp1 = temp1->next;
            free(temp2);
            temp2 = temp1;
        }
    }
    total = 0;
    return true;
}
