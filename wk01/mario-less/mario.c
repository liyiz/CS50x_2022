#include <cs50.h>
#include <stdio.h>

int n;

int main(void)
{
    // do while loop
    // check if the input int is at least 1 or more
    //

    // prompt user for input of height int
    do
    {
        // provide a note about what is a valid input
        if (n < 1 || n > 8)
        {
            printf("Note: We can only proceed with a height of 1 to 8 inclusive.\n");
        }
        // assign variable n with the height int
        n = get_int("Please input a height: ");
        // show user input
        // printf("Height: %i\n", n);
    }
    // check if n value is between 1 and 8 inclusive
    while (n < 1 || n > 8);

    // if n is within inclusive range of 1 to 8
    if (n > 0 && n < 9)
    {

        // for loop on col. Note, discard the first iteration because it's just empty space
        for (int i = 1; i <= n; i++)
        {
            //for loop on spacing
            for (int k = n; k > i; k--)
            {
                // add a space to push hastag forward
                printf(" ");
            }
            // for loop on row
            for (int j = 0; j < i; j++)
            {
                printf("#");
            }
            printf("\n");
        }

    }
}