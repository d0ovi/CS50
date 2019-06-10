#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int number, space, hash;

    //get input from user
    do
    {
        number = get_int("Height : ");
    }
    while (number <= 0 || number > 8);
    
    for (int i = 0; i < number; i++)
    {
        //counting spaces & ## for all lines
        space = number - (i + 1);
        hash = number - space;

        //printing spaces
        for (int s = 0; s < space; s++)
        {
            printf(" ");
        }

        //printing # piramid
        for (int h = 0; h < hash; h++)
        {
            printf("#");
        }

        printf("\n");
    }
}
