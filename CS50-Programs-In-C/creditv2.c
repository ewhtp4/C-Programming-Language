/**
  *Program name: credit
  *Aouthor: Slavko Mihajlvic
  *Course name: CS50
  *Year: 2020
  **/

#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    //Getting user input
    long cardnumber = 0;
    do
    {
        cardnumber = get_long("whats the card number?: ");
    }
    while (cardnumber < 0);

    int totalDigits = 0;
    long digits = cardnumber;
    while (digits > 0)
    {
        digits = digits / 10;
        totalDigits++;
    }
    //Eliminating numbers whic are not 13,15 or 16 digits long
    if ((totalDigits != 13) && (totalDigits != 15) && (totalDigits != 16))
    {
        printf("INVALID\n");
    }
    //Checking the vadility with Luhn's algorithm.
    // Extracting digits from the card number,
    //by moulding the number by 10 then deviding by 10 to get the next digit.
    int digit[totalDigits];

    for (int i = 0; i < totalDigits; i++)
    {
        digit[i] = cardnumber % 10;
        cardnumber = cardnumber / 10;
    }
    //Separating every other digit starting second to last
    //And doing the fist step of the Luhn Algorithm
    int originalNumber[totalDigits];
    for (int i = 1; i < totalDigits; i++)
    {
        originalNumber[i] = digit[i];
    }
    for (int i = 1; i < totalDigits; i += 2)
    {
        digit[i] = digit[i] * 2;
    } 
    //Validating as per number of digits
    // and checking that the las digit is 0
    int valid = 0;
    int temp;
   
    if (totalDigits == 13)
    {
        for (int i = 0; i < totalDigits; i++)
        {
            temp = (digit[i] % 10) + (digit[i] / 10 % 10);
            valid = valid + temp;
        }
        // Visa cards star with 4
        if (originalNumber[12] == 4 && valid % 10 == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    if (totalDigits == 15)
    {
        for (int i = 0; i < totalDigits; i++)
        {
            temp = (digit[i] % 10) + (digit[i] / 10 % 10);
            valid = valid + temp;
        }
        //American Express starts with 3
        if (originalNumber[14] == 3 && valid % 10 == 0 && (originalNumber[13] == 4 || originalNumber[13] == 7))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }  
    if (totalDigits == 16)
    {
        for (int i = 0; i < totalDigits; i++)
        {
            temp = (digit[i] % 10) + (digit[i] / 10 % 10);
            valid = valid + temp;
        }
        //Visa cards start with 4 start with 4
        if (originalNumber[15] == 4 && valid % 10 == 0)
        {
            printf("VISA\n");
        }
        //Mastercards can start with : 1,2,3,4 or 5
        else if (originalNumber[15] == 5 && valid % 10 == 0 && (originalNumber[14] == 1 || 
                 originalNumber[14] == 2 || originalNumber[14] == 3 || originalNumber[14] == 4 || 
                 originalNumber[14] == 5))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    } 
    return 0;
}