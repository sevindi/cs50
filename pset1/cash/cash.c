#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int coins;
    
    // Prompt user for change as dollars and turn it into cents.
    do
    {
        float d = get_float("Change in dollars: ");
        coins = round(d * 100);
    }
    while (coins <= 0);
    
    //Calculate modulus for 25, 10 and 5 consecutively
    int quarters = coins / 25;
    int dimes = (coins % 25) / 10;
    int nickels = ((coins % 25) % 10) / 5;
    int pennies = (((coins % 25) % 10) % 5); 
    
    printf("%d\n", quarters + dimes + nickels + pennies);
}
