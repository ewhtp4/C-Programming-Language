/**
Author : Slavko Mihajlovic
Course name : CS50
Year : 2020
**/
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void) 
{
    int coins = 0;
    
    // User input validation
    float change = get_float("What is a change amount?: ");
    if (change <= 0)
    {
       do
       {
            change = get_float("Change amount must be a positive number and smaller then a dollar:");
       }
       while (change <= 0);   
    }
    
    int cents = round(change * 100);
    
    // Determine number of coins
    //Quaters
    while(cents >= 25)
    {
        cents -= 25;
        coins++;
    }
    
    //Dimes
    while (cents >= 10)
    {
        cents -= 10;
        coins++;
    }
    
    //Nickles
    while (cents >= 5)
    {
        cents -= 5;
        coins++;
    }
    //Pennies
    while (cents >= 1)
    {
        cents -= 1;
        coins++;
   }
   //Print number of coins
   printf("%i\n", coins);
}
