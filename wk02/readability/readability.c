#include <cs50.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string textSample = get_string("Text: ");
    // string is already an accessible array type
    // use %c char type
    // printf("%c\n", textSample[1]);

    int letters = count_letters(textSample);
    int words = count_words(textSample);
    int sentences = count_sentences(textSample);

    // deal with Coleman-Liau index
    // remember to promote int to float
    float l = (float)letters / (float)words * 100.00;
    float s = (float)sentences / (float)words * 100.00;
    float index = 0.0588 * l - 0.296 * s - 15.8;

    // print out grade result
    if (index < 1.0)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16.0)
    {
        printf("Grade 16+\n");
    }
    else
    {
        // round float up
        printf("Grade %1.0f\n", index);
    }

}

int count_letters(string text)
{
    // count characters
    int stringLength = strlen(text);
    // count spaces
    int spacesCount = 0;
    // count punctuation
    int punctCount = 0;
    for (int i = 0, n = stringLength; i < n ; i++)
    {
        if (text[i] == ' ')
        {
            spacesCount++;
        }
        // check for punctuation
        if (text[i] == ',' ||
            text[i] == '.' ||
            text[i] == '!' ||
            text[i] == '?' ||
            text[i] == ';' ||
            text[i] == ':' ||
            text[i] == '\'' ||
            text[i] == '\"' ||
            text[i] == '\\' ||
            text[i] == '/' ||
            text[i] == '-')
        {
            punctCount++;
        }
    }
    // printf("Number of spaces: %i\n", spacesCount);
    // printf("Number of punctuation marks: %i\n", punctCount);
    // subtract spaces from stringLength
    stringLength -= spacesCount + punctCount;
    // output letters count
    // printf("Number of letters: %i\n", stringLength);
    // printf("%i letters\n", stringLength);
    return stringLength;
}

int count_words(string text)
{
    // count characters
    int stringLength = strlen(text);
    // count words
    int wordCount = 0;
    for (int i = 0, n = stringLength; i < n ; i++)
    {
        if (text[i] == ' ')
        {
            wordCount++;
        }
    }
    // add one more word to indicate last word in the string.
    wordCount++;
    // "Assume that a sentence will not start or end with a space,
    // and assume that a sentence will not have multiple spaces in a row"
    // https://cs50.harvard.edu/x/2022/psets/2/readability/
    // printf("%i words\n", wordCount);
    return wordCount;
}

int count_sentences(string text)
{
    // count characters
    int stringLength = strlen(text);
    int sentenceCount = 0;
    for (int i = 0, n = stringLength; i < n ; i++)
    {
        // check for punctuation that ends sentences
        if (text[i] == '.' ||
            text[i] == '!' ||
            text[i] == '?')
        {
            sentenceCount++;
        }
    }
    // In practice, sentence boundary detection needs to be
    // a little more intelligent to handle these cases,
    // but we’ll not worry about that for now.
    // https://cs50.harvard.edu/x/2022/psets/2/readability/

    // printf("%i sentences\n", sentenceCount);
    return sentenceCount;
}