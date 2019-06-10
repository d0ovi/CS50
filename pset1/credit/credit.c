#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long cc_number, c, cc;
    int last, s2_last;
    int sum1 = 0, sum2 = 0, sum;
    long amex =   10000000000000;
    long master = 100000000000000;
    long visa16 = 1000000000000000;
    long visa13 = 10000000000000;
    int len;

    // get CC number
    do
    {
        cc_number = get_long("cc nr:");
    }
    while (cc_number <= 0);
    c = cc_number;
    cc = cc_number;
    //calculate sums
    while (cc_number > 0)
    {
        // second to last digit * 2:
        s2_last = ((cc_number % 100) / 10) * 2;
        // last digit:
        last = cc_number % 10;
        // if second to last *2 is two digits, need to calculate to one digit:
        if (s2_last > 9)
        {
            sum1 = (s2_last % 10) + ((s2_last % 100) / 10) + sum1;
        }
        else 
        {
            sum1 = sum1 + s2_last;
        }

        // last digits sum:
        sum2 = sum2 + last;

        // remove two last digits from the cc number and calculate others digits sums in the loop:
        cc_number = cc_number / 100;
    }
    
    // sum of all the digits:
    sum = sum1 + sum2;

    // count the length of the CC number
    for (len = 0; c > 0; len++)
    {
        c = c / 10;
    }
    // conditions for the bank
    // amex starts with 37 or 34; 15
    // master 51, 52, 53, 54, 55; 16
    // visa 4; 13 or 16
    if (len == 15 && (sum % 10) == 0 && (cc / (amex) == 34 || cc / (amex) == 37))
    {
        printf("AMEX\n");
    }
    else if (sum % 10 == 0 && len == 16 && (cc / master > 50 && cc / master < 56))
    {
        printf("MASTERCARD\n");
    }
    else if (((sum % 10) == 0 && len == 16 && (cc / visa16 == 4)) || (sum % 10 == 0 && len == 13 && cc / visa13 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
