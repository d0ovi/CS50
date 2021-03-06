#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //First, let's ask user to input money owed.

    float change;

    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    //Then, let's convert the money into cents (use math.h for rounding)
    int cents = round(change * 100);

    //Assume that the only coins available are quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢).
    for (int i = 0; i < cents; i++)
    {
        int coins;
        //4 loops for every coin to check.
        // is it possible to make it in less lines?
        while (cents >= 25)
        {
            int coins_25 = cents / 25;
            coins = coins + coins_25;
            cents = cents - (coins * 25);
        }
        while (cents >= 10)
        {
            int coins_10 = cents / 10;
            coins = coins + coins_10;
            cents = cents - (coins_10 * 10);
        }
        while (cents >= 5)
        {
            int coins_5 = cents / 5;
            coins = coins + coins_5;
            cents = cents - (coins_5 * 5);
        }
        while (cents >= 1)
        {
            int coins_1 = cents / 1;
            coins = coins + coins_1;
            cents = cents - (coins_1 * 1);
        }
        printf("%d\n", coins);
    }
}
