#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//Takes char* where leftmost char represents most significant value. char* contains number in base 2-36.
//Changes array to replace numbers with their character representations.
//Not sane for bases higher than 36 or negative numbers
void convertBaseToReadable(char* outputArray)
{
  for (size_t i = 0; i < 64; i++)
  {
    if (outputArray[i] < 10){outputArray[i] = outputArray[i] + '0';}
    else {outputArray[i] =  outputArray[i] + 'A' - 10;}
  }
}

//Takes an unsigned int for a value and a base to represent it in.
//Returns an array containing NUMERIC representations of the values digits in that base, leftmost char being most significant
//Not sane for bases higher than 36 or negative numbers
char* calculateValueInBase(unsigned int value, unsigned int base)
{
  unsigned int index = 0;
  char* outputArray = (char* )(malloc(sizeof(char) * 64));
  for (size_t i = 0; i < 64; i++)
  {
    outputArray[i] = 0;
  }
  while (value != 0)
  {
    outputArray[63-index] = value % base;
    value = value / base;
    index++;
  }
  return outputArray;
}

//Takes a character array and the size of the array
//Prints the array while ignoring leading 0's
void printWithoutLeadingZeroes(char* str, unsigned int sizeOfStr)
{
  int i = 0;
  while (str[i]=='0') { i++; }

  for (; i < 64; i++)
  {
    printf("%c", str[i]);
  }
}
//Takes a unsigned integer represented in base 10 in a string and a pointer to an error flag
//returns the equivelent unsigned int or sets error flag to 1
unsigned int convertStringToUnsignedInt(char* value, char* errorFlag)
{
  char *endPointer;
  unsigned int returnVal = strtoul (value, &endPointer, 10);
  if ((endPointer == value) || (*endPointer != '\0'))
  {
      *errorFlag = 1;
      return 0;
  }
  return returnVal;
}
//Takes value then base as unsigned integers.
//Prints a representation of the value within the base.
int main(int n, char *args[])
{
  if (n==3)
  {
    char errorFlag = 0;
    unsigned int value = convertStringToUnsignedInt(args[1], &errorFlag);
    unsigned int base = convertStringToUnsignedInt(args[2], &errorFlag);
    if (errorFlag)
    {
      printf("Error, input could not be parsed\n");
      return 1;
    }
    if (!((base > 1)&&(base < 37))){printf("Error, base must be between 2 and 36\n");}

    char* valueInBase = calculateValueInBase(value, base);
    convertBaseToReadable(valueInBase);

    printf("%d in base %d is: ", value, base);
    printWithoutLeadingZeroes(valueInBase,64);
    printf("\n");
    free(valueInBase);
    return 0;
  }
}
