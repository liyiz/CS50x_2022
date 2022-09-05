#include <cs50.h>
#include <stdio.h>

int n; // variable to keep height

int main(void)
{
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

        // for loop on row. Note, discard the first iteration because it's just empty space
        for (int i = 1; i <= n; i++)
        {
            // for loop on spacing left side
            for (int k = n; k > i; k--)
            {
                // add a space to push hastag forward
                printf(" ");
            }
            // for loop on col left side
            for (int j = 0; j < i; j++)
            {
                printf("#");
            }

            // add a space for the gap
            printf("  ");

            // for loop on col right side
            for (int j = 0; j < i; j++)
            {
                printf("#");
            }

            // for loop on spacing right side
            // for (int k = n; k > i; k--)
            // {
            //     // add a space to push hastag forward
            //     printf(" ");
            // }

            printf("\n");
        }

    }
}