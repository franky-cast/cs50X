#include "cs50.h"
#include "cs50.c"
#include <stdio.h>
#include <string.h>

string substitution(string key, string plain_text);

int main(int argc, string argv[])
{
    // key validation
    // ------------------------------
    if (argc != 2)
    {
        printf("Error: Enter ONE key for the cypher \n Usage: ./substitution key \n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Error: Key for the cypher must be 26 characters long \n");
        return 1;
    }
    else
    {
        for (int i = 0; i < 26; i++)
        {
            char letter = argv[1][i];
            if (!isalpha(letter))
            {
                printf("Error: Only supports alphabet letters as key \n");
                return 1;
            }
        }
    }
    // ------------------------------

    string key = argv[1];
    string plain_text = get_string(NULL, "Enter plaintext: ");
    string cipher_text = substitution(key, plain_text);

    printf("ciphertext: %s \n", cipher_text);

    return 0;
}

string substitution(string key, string plain_text)
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int length_plain_text = (int) strlen(plain_text);
    string cipher_text = (string) malloc(length_plain_text + 1);

    for (int i = 0; i < length_plain_text; i++)
    {
        char character = plain_text[i];
        if (!isalpha(character))
            cipher_text[i] = character;
        else
        {
            int current_index;

            if (isupper(character) == 1)
            {
                char lcChar = tolower(character);
                for (int z = 0; z < 26; z++)
                {
                    if (lcChar == alphabet[z])
                    {
                        current_index = z;
                        cipher_text[i] = toupper(key[current_index]);
                        break;
                    }
                }
            }
            else
            {
                for (int z = 0; z < 26; z++)
                {
                    if (character == alphabet[z])
                    {
                        current_index = z;
                        cipher_text[i] = tolower(key[current_index]);
                        break;
                    }
                }
            }
        }
    }

    return cipher_text;
}