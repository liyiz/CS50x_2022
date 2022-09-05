#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();
    // printf("%i\n",cents);

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // printf("Cents left: %i\n", cents);

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // temp holding variable
    int n;
    // reprompt if inappropriate input
    do
    {
        n = get_int("How much change do we need to check? ");
    }
    while (n < 1);
    return n;
}

int calculate_quarters(int cents)
{
    // figure out how many 25s go into the input value
    int r = cents % 25;
    int quarters = (cents - r) / 25;
    printf("calculate_quarters = %i\n", quarters);

    return quarters;
}

int calculate_dimes(int cents)
{
    int r = cents % 10;
    int dimes = (cents - r) / 10;
    printf("calculate_dimes = %i\n", dimes);
    return dimes;
}

int calculate_nickels(int cents)
{
    int r = cents % 5;
    int nickels = (cents - r) / 5;
    printf("calculate_nickels = %i\n", nickels);
    return nickels;
}

int calculate_pennies(int cents)
{
    int r = cents % 1;
    int pennies = (cents - r);
    printf("calculate_pennies = %i\n", pennies);
    return pennies;
}
