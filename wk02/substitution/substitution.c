#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string validate_key(string userKey, int userKeyLen);
string get_plaintext();
string encipher(string plaintext, string cipher);

int main(int argc, string argv[])
{

    // run checks on user input, vet it first!

    // printf("%i\n", argc);

    // check argc is the number of commandline arguments
    // that exist. 2 is the number we expect for a single
    // user input. Any more or less we need to re-prompt user
    if (argc != 2)
    {
        printf("ERROR: Improper use of program\nCorrect usage: ./substitution key\n");
        return 1;
    }

    // get key and initialise as variables
    string userKey = argv[1];
    int userKeyLen = strlen(userKey);

    // check if argv[1], the user entered key,
    // is more or less than 26. If not exactly 26
    // then re-prompt user.
    if (userKeyLen > 26 || userKeyLen < 26)
    {
        printf("ERROR: Key must contain 26 characters.\n");
        return 1;
    }

    // printf("%s\n", userKey);

    // validate key
    string validatedKey = validate_key(userKey, userKeyLen);
    // printf("%i\n", strcmp(validatedKey, "error"));
    if (strcmp(validatedKey, "error1") == 0)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    else if (strcmp(validatedKey, "error2") == 0)
    {
        printf("Key must not contain repeated alphabetic characters.\n");
        return 1;
    }

    // get plaintext
    string userPlaintext = get_plaintext();

    // encipher the plaintext
    string ciphertext = encipher(userPlaintext, validatedKey);

    // print ciphertext
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

string validate_key(string userKey, int userKeyLen)
{
    // string userKey = get_string("");

    for (int i = 0, l = userKeyLen; i < l; i++)
    {
        // This function returns a non-zero int if c is alphabetical and 0 if c is not alphabetical.
        // if the current character is not an alphabetic character
        // check for numbers, spaces, and punctuation in one go
        if (isalpha(userKey[i]) == 0)
        {
            return "error1";
        }
        else if (islower(userKey[i])) // make the key case-INsensitive
        {
            userKey[i] = toupper(userKey[i]);
            // printf("changed from lower to upper: %c\n", userKey[i]);
        }
        // check for repeated characters
        // check current character against all other characters in the string array
        for (int j = 0; j < l; j++)
        {
            // but skip comparing against itself!
            if (j != i)
            {
                if (userKey[i] == userKey[j])
                {
                    return "error2";
                }
            }
        }

    }
    // printf("New user key string: %s\n", userKey);

    // return validated key (toupper'd)
    return userKey;
}

string get_plaintext()
{
    string userPlaintext = get_string("plaintext: ");
    return userPlaintext;
}

string encipher(string plaintext, string cipher)
{
    // strings can be accessed as arrays
    // printf("plaintext: %c\n", plaintext[0]);
    // printf("cipher: %c\n", cipher[0]);

    int textLen = strlen(plaintext);

    // go through each letter in plaintext
    for (int i = 0, n = textLen; i < n; i++)
    {

        int letter = isalpha(plaintext[i]);
        // printf("%i\n", letter);
        // if it is not a letter
        if (letter != 0)
        {
            // printf("%c\n", plaintext[i]);
            // check where in the alphabet the letter is in
            // for uppercase -65 in ASCII chart to get 0 to use as array index
            // for lowercase -97
            // 91 to 96 in ASCII are non alphabetical chars
            if (plaintext[i] >= 65 && plaintext[i] < 91)
            {
                int alphaUppCaseIndex = plaintext[i] - 65;
                // printf("alphabet index: %i\n", alphaUppCaseIndex);
                plaintext[i] = cipher[alphaUppCaseIndex];
            }
            if (plaintext[i] >= 97 && plaintext[i] < 123)
            {
                int alphaLowCaseIndex = plaintext[i] - 97;
                // printf("alphabet index: %i\n", alphaLowCaseIndex);
                plaintext[i] = cipher[alphaLowCaseIndex] + 32; // add 32 to make value lowercase in ASCII
            }
        }
    }
    // get a value out of 26 of plaintext letter
    // compare against index value of cipher array
    // save letter in cipher array index to the current index of plaintext array



    return plaintext;
}