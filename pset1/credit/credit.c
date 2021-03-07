#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //declare the variabbles:

    long number, a;
    int sum = 0, mult_digit, other_digit, len = 0;

    //First, let's get the card number input from the user
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);

    // a is like a dummy variable with the number info in it.
    a = number;

    //First, let's try to multiple every other digit by 2, starting with the second to last:
    while (a > 0)
    {
        //first line calculates the number, second line removes two last digits from the number, third line adds numbers to the sum
        mult_digit = a % 100 / 10 * 2;
        a = a / 100;
        if (mult_digit < 10)
        {
            sum = sum + mult_digit;
        }
        else
        {
            sum = sum + (mult_digit % 10) + mult_digit / 10;
        }
    }
    //second loop is for adding other number without multipling
    a = number;
    while (a > 0)
    {
        other_digit = a % 10;
        sum = sum + other_digit;
        a = a / 100;
    }

    //Now let's test which card is it:
    // For all cards we need the lenght of number:

    a = number;
    while (a > 0)
    {
        a = a / 10;
        len++;
    }
    //printf("%d\n", len);
    // let's find first and last digits:
    a = number;
    long n1 = a, n2 = a; // n2 will hold the first two digits, n1 is the first digit

    while (a)
    {
        n2 = n1;
        n1 = a;
        a /= 10;
    }
    //Check if it is AMEX:
    if (((sum % 10) == 0) && ((n2 == 34) || (n2 == 37)) && (len == 15))
    {
        printf("AMEX\n");
        return 0;
    }
    //Check if it is VISA:
    else if (((sum % 10) == 0) && (n1 == 4) && ((len == 13) || (len == 16)))
    {
        printf("VISA\n");
        return 0;
    }
    //Check if it is MasterCard:
    else if (((sum % 10) == 0) && ((n2 == 51) || (n2 == 52) || (n2 == 53) || (n2 == 54) || (n2 == 55)) && (len == 16))
    {
        printf("MASTERCARD\n");
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}
