#include "cs50.h"
#include "cs50.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// cs50
// ------------------------------
// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET "\e[0;39m"
// ------------------------------

// user-defined function prototypes
string get_guess(int word_size);
int check_word(string guess, int word_size, int status[], string choice);
void print_word(string guess, int status[]);
int validate_command(int argc, string argv[]);

int word_size;

int main(int argc, string argv[])
{

    // ensures user input is valid
    int response = validate_command(argc, argv);
    if (response == 1)
        return 1;

    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", word_size);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][word_size + 1];

    for (int i = 0; i < LISTSIZE; i++)
        fscanf(wordlist, "%s", options[i]);

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    int guesses = word_size + 1;
    bool won = false;

    printf(GREEN "This is WORDLE50" RESET "\n \n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of \n", guesses, word_size);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        string guess = get_guess(word_size);

        if (strcmp(guess, "quit") == 0)
            break;

        int status[word_size];
        for (int i; i < word_size; i++)
            status[i] = 0;

        // check_word(guess, word_size, status, choice);
        int score = check_word(guess, word_size, status, choice);

        printf("Guess %i: ", i + 1);
        print_word(guess, status);
        printf("\n");

        if (score == 2 * word_size)
        {
            won = true;
            break;
        }

    }

    if (won)
        printf("Winner! \n Secret word: %s \n", choice);
    else 
        printf("Out of guesses! \n Secret word: %s \n", choice);

    return 0;
}

// prompts user for a word
string get_guess(int word_size)
{
    string guess = "";

    do
    {
        guess = get_string(NULL, "Enter a %i-letter word or 'quit': ", word_size);
        if (strcmp(guess, "quit") == 0 ) break;
    }
    while (strlen(guess) != word_size);

    return guess;
}

// iterates through each char of guess word and assigns score
// stores score in status[i] ... i == index of char being scored
int check_word(string guess, int word_size, int status[], string choice)
{
    int score = 0;
    char secret_letter;
    char current_letter;

    for (int i = 0; i < word_size; i++)
    {
        current_letter = guess[i];
        for(int z = 0; z < word_size; z++)
        {
            secret_letter = choice[z];
            if (current_letter == secret_letter)
            {
                if (i == z)
                {
                    score += 2;
                    status[i] = 2;
                    break;
                }
                else 
                {
                    score++;
                    status[i] += 1;
                }
            }
            else
                status[i] = 0;
        }
    }

    return score;
}

// prints guess word with color
void print_word(string guess, int status[])
{
    int guess_word_length = strlen(guess);
    for (int i = 0; i < guess_word_length; i++)
    {
        switch (status[i])
        {
            case 0:
                printf("%c", guess[i]);
                break;
            case 1:
                printf(YELLOW"%c"RESET, guess[i]);
                break;
            case 2:
                printf(GREEN"%c"RESET, guess[i]);
                break;
            default:
                printf("Error switch case");
        }
    }
}

// validates initial user input upon invoking main()
int validate_command(int argc, string argv[]) 
{
    // Validates command. Assigns word_size if command valid or not present
    if (argc > 2)
    {
        printf("Error: must only enter two arguments: ./wordle && word size \n");
        return 1;
    }

    if (argc == 2)
    {
        // ensure user input is valid
        int initial_word_size = atoi(argv[1]);
        word_size = initial_word_size;
        switch (initial_word_size)
        {
            case 5:
                word_size = 5;
                break;
            case 6:
                word_size = 6;
                break;
            case 7:
                word_size = 7;
                break;
            case 8:
                word_size = 8;
                break;
            default:
                printf("Error: word size must be 5, 6, 7, or 8. \n");
                return 1;
        }
        printf("\n");
        return 0;
    }
    else
    {
        // default word size if no user input
        word_size = 5;
        printf("Default word size: %i \n \n", word_size);
        return 0;
    }
}