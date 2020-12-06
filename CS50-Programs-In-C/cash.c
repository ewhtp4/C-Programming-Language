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
    float quater;
    float dime;
    float nickle;
    float penny;
    
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
    // Determine number of coins
   int coins = 0;
   //Quaters
   for (quater = 1; change >= 0.25; quater++)
   {
       change -= 0.25;
       coins++;
   }
   //Dimes
   for (dime = 1; change >= 0.10; dime++)
   {
       change -= 0.10;
       coins++;
   }
   //Nickles
   for (nickle = 1; change >= 0.05; nickle++)
   {
       change -= 0.05;
       coins++;
   }
   //1cent 
   for (penny = 1; change >= 0.01; penny++)
    {
       change -= 0.01;
       coins++;
   }
   //Print number of coins
   printf("%i\n", coins);
}
