#include "cs50.h"
#include "cs50.c"
#include <stdio.h>
#include <string.h>

double count_letters(string text);
double count_words(string text);
double count_sentences(string text);

int main(void) 
{
    string text = get_string(NULL, "Text: ");

    // user input sentence data vars
    double letters = count_letters(text);
    double sentences = count_sentences(text);
    double words = count_words(text);

    printf("letters: %lf \n", letters);
    printf("sentences: %lf \n", sentences);
    printf("words: %lf \n", words);

    // average number of letters per 100 words
    float L = round(((letters / words) * 100) * 100) / 100; 

    // average number of sentences per 100 words
    float S = round(((sentences / words) * 100) * 100) / 100; 

    float raw_index = 0.0588 * L - 0.296 * S - 15.8;
    int index = round(raw_index);

    if (index < 1)
        printf("Before Grade 1");
    else if (index >= 16)
        printf("Grade 16+");
    else
        printf("Grade %i \n", index);

    return 0;
}

double count_words (string text)
{
    int words = 1;
    int text_length = strlen(text);
    for (int i = 0; i < text_length; i++)
    {
        if (isspace(text[i]) == 1)
            words++;
    }

    return words;
}

double count_letters(string text)
{
    int letters = 0;
    int text_length = strlen(text);
    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]) == 1)
            letters++;
    }
    return letters;
}

double count_sentences(string text)
{
    int sentences = 0;
    int text_length = strlen(text);
    for (int i = 0; i < text_length; i++)
    {
        if (text[i] == '?' || text[i] == '!' || text[i] == '.' )
            sentences++;
    }
    return sentences;
}