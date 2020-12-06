/**
  *Program name: credit.c
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
    //Getting the numer of digit in the card number.
    long cardnumber = get_long("what is the card number?: ");
    int totalDigits = floor(log10(labs(cardnumber))) + 1;
    while (totalDigits < 13 || totalDigits > 16)
    {
        cardnumber = get_long("The card number has to be 13-16 digits long: ");
        totalDigits = floor(log10(labs(cardnumber))) + 1;

    
    //Eliminating numbers which are not 13,15 or 16 digits long
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
    int originalNumber[totalDigits];
    
    for (int i = 1; i < totalDigits; i++)
    {
        originalNumber[i] = digit[i];
    }
    //Multiplying every other digit by 2 (First step of the Luhn algorithm)
    for (int i = 1; i < totalDigits; i += 2)
    {
        digit[i] = digit[i] * 2;
    } 
    
    //Validation
    int valid = 0;
    int temp;
   
    if (totalDigits == 13)
    {
      for (int i = 0; i < totalDigits; i++)
      {
        temp = (digit[i] % 10) + (digit[i] / 10 % 10);
        valid = valid + temp;
      }
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
      if (originalNumber[15] == 4 && valid % 10 == 0)
      {
        printf("VISA\n");
      }
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




