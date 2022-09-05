#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // assign user input to string type variable
    string username = get_string("Tell me your name. ");
    // use username variable and print
    printf("Hello, %s!\n", username);
}