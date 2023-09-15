#include "cs50.h"
#include "cs50.c"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int compute_score(string word);

int main(void)
{   
    // Prompt user for two words
    string word1 = get_string(NULL, "Enter word 1: ");
    string word2 = get_string(NULL, "Enter word 2: ");

    // Compute Scores
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Determine winner
    string winner;
    if (score1 > score2)
        winner = "Player 1 wins!";
    else if (score1 < score2 )
        winner = "Player 2 wins!";
    else
        winner = "Tie!";

    // Print winner
    printf("%s \n", winner);
    return 0;
}

int compute_score(string word)
{
    // arrays because we cannot use dictionaries for this lab
    int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    int score = 0;
    // iterating through each character of the word
    for (int i = 0; i < strlen(word); i++)
    {
        // if char is a letter
        if (isalpha(word[i]))
        {
            // lowercase char
            char lcChar = tolower(word[i]);

            // find index of char
            for (int z = 0; z < 26; z++)
            {
                if (letters[z] == lcChar) score += points[z];
            }
        }
        else score += 0;
    }

    return score;
}