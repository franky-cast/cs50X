// Implements a dictionary's functionality

#include <strings.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 46;

// Hash table
node *table[N];

// global vars
unsigned int word_count = 0;
unsigned int hash_index;

// Returns true if word is in dictionary (hash table)
// (is it spelled correctly... else false)
bool check(const char *word)
{
    hash_index = hash(word);
    for (node *ptr = table[hash_index]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
            return true;
    }
    return false;
}

// Hashes word to a number (returns number that represents N in table[N])
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int count = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        count++;
    }
    return count;
}

// Loads dictionary into memory (hash table), returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Failed to open dictionary");
        fclose(dict);
        return false;
    }

    char *word = malloc(LENGTH + 1);

    // read each word from file and create a node
    while (fscanf(dict, "%s", word) != EOF)
    {
        // create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Failed to allocate memory for node");
            free(word);
            fclose(dict);
            return 1;
        }

        strcpy(n->word, word);
        n->next = NULL;

        // update word count
        word_count++;

        // insert node into hash table at that location
        hash_index = hash(word);
        n->next = table[hash_index];
        table[hash_index] = n;
    }
    free(word);
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count > 0 ? word_count : 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // iterate over hash table linked lists and free each node
    for (int i = 0; i < N; i++)
    {
        for (node *ptr = table[i]; ptr != NULL; ptr = ptr->next)
        {
            node *temp = ptr;
            free(temp);
        }
    }

    return true;
}