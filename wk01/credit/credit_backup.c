#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long cnum = 0;
    long temp_cnum = 0;

    int checksum1 = 0; // value for Luhn step one
    int checksum2 = 0; // value for Luhn step two

    int digitLength = 0;

    int semanticDigits = 0;
    int semanticDigit1 = 0;
    int semanticDigit2 = 0;

    do
    {
        cnum = get_long("Please enter your card number: ");
        temp_cnum = cnum; // used to get digit length
        // printf("cnum: %li\n",cnum);
        // printf("temp_cnum: %li\n",temp_cnum);
        digitLength = 0; // reset counter if repeated
        do
        {
            temp_cnum = temp_cnum / 10;
            digitLength++;
            // printf("digitLength: %i\n",digitLength);
        }
        while (temp_cnum > 0);
        // printf("digitLength: %i\n",digitLength);
    }
    while (digitLength < 13 || digitLength > 16);


    // printf("length: %i\n",digitLength);

    // the digitLength+1 is to compensate an extra ten
    // so modulo gives us the digit we want first
    // from Right to Left
    for (int i = 1; i < digitLength+1; i++)
    {
        // gets us the modulo factor to get the desired digit
        long factor = 1;
        for (int j = 0; j < i; j++)
        {
            factor *= 10;
        }
        // printf("interval factor: %li\n", factor);

        // modulo cnum to get the digit we're looking at
        long digit = cnum % factor;
        // take digit away from cnum to clear it
        cnum -= digit;
        // printf("digit raw: %li\n", digit);
        // divide by factor to give us digit without zeros
        if (digit >= 10)
        {
            digit = digit / (factor/10);
        }
        // printf("digit want: %li\n", digit);

        // store last two iteration values
        if (i == digitLength - 1)
        {
            semanticDigit2 = digit;
        }
        if (i == digitLength)
        {
            semanticDigit1 = digit;
            semanticDigits = (digit * 10) + semanticDigit2;
        }

        // if odd or even interval, save to appropriate checksum value
        if (i % 2 == 0)
        {
            // save to checksum1

            // multiply the chosen digit by 2
            digit *= 2;

            int digit1 = 0;
            int digit2 = 0;
            // check if digit var is a double digit number
            // because we want to sum the digits,
            // not the product itself!
            if (digit > 9)
            {
                // e.g. 12
                // digit2 = 2
                digit2 = digit % 10;
                // digit1 = 12 - 2
                digit1 = digit - digit2;
                // digit1 = 1
                digit1 = digit1 / 10;
                // printf("digit1: %i\n",digit1);
                // printf("digit2: %i\n",digit2);
                // 1 + 2
                checksum1 += digit1 + digit2;
            } else {
                checksum1 += digit;
            }
            // checksum1 += digit*2;
            // printf("checksum1: %i\n",checksum1);
        } else {
            // save to checksum2
            checksum2 += digit;
            // printf("checksum2: %i\n",checksum2);
        }

    }

    // printf("checksum1 total: %i\n",checksum1);
    // printf("checksum2 total: %i\n",checksum2);

    int checksumTotal = checksum1 + checksum2;
    // printf("checksum final total: %i\n",checksumTotal);

    if (checksumTotal % 10 == 0) {
        // printf("Input number is valid!\n");
        // printf("Semantic digits to check: %i%i\n", semanticDigit1, semanticDigit2);
        if (digitLength == 16) {
            // MASTERCARD or VISA
            if (semanticDigits >= 51 && semanticDigits <= 55)
            {
                printf("MASTERCARD\n");
            }
            if (semanticDigit1 == 4)
            {
                printf("VISA\n");
            }
        }
        if (digitLength == 15) {
            // AMEX
            if (semanticDigits == 34 || semanticDigits == 37)
            {
                printf("AMEX\n");
            }
        }
        if (digitLength == 13) {
            // VISA
            if (semanticDigit1 == 4)
            {
                printf("VISA\n");
            }
        }
    } else {
        printf("INVALID\n");
    }
}