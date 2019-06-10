#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    int rounds, coins = 0;
    
    do
    {
        change = get_float("Change to give:");
    }
    while (change < 0);
           
    // change -> rounds
    change = round(change * 100);

    //quarters
    while (change - 25 >= 0)
    {
        change -= 25;
        coins += 1;
    }

    // dimes
    while (change - 10 >= 0)
    {
        change -= 10;
        coins += 1;
    }

    //nickels
    while (change - 5 >= 0)
    {
        change -= 5;
        coins += 1;
    }

    //pennies
    while (change - 1 >= 0)
    {
        change -= 1;
        coins += 1;
    }

    for(int i = 0, int i < change, i++)
    {
        
    }
    //print min amount of coins
    printf("%i\n", coins);
}
