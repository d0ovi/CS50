#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int size;
    //first, let's ask user for the piramid number
    do
    {
        size = get_int("Height: ");
    }
    //the number should be less than 8 and more than 1 (included both numbers)
    while (size > 8 || size < 1);

    // in the loops we need to count spaces - 1 from the piramid size
    //and hashes from 1 to size in next lines
    for (int i = 0; i < size; i++)
    {
        for (int s = 0; s < size - (i + 1); s++)
        {
            printf(" ");
        }

        for (int j = 0; j < i + 1; j++)
        {

            printf("#");

        }
        printf("\n");
    }
}
