#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //first, let's ask user for a piramid size
    int size;
    do
    {
        size = get_int("Height: ");
    }
    while (size > 8 || size < 1);

    // now, the hashes and the spaces in between
    //I think I use some part of the code from the "mario less"

    for (int i = 0; i < size; i++)
    {
        //this two loops are for the first pirammid from "mario less"
        for (int s = 0; s < size - (i + 1); s++)
        {
            printf(" ");
        }

        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        } 
        //then we need two spaces until new piramid
        printf("  ");
        
        //let's try to make new piramid vice versa
        //oh, I didn't need the spaces at all/ I just needed the normal piramid withought any spaces.

        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
