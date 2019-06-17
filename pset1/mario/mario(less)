#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    
    // Prompt user for height only between 1 and 8
    do
    {
        height = get_int("Enter height between 1 and 8:");
    }
    while (height < 1 || height > 8);
    
    // Draws right aligned pyramid with hashes according to the given height
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - i - 1; j++)
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
