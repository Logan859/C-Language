#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Factorial
void Factorial(int number)
{
	int factorial = 1;
	while(number > 1)
	{
		factorial *= number;
		number--;
	}
	printf("Factorial of %d number Value : %d\n", number, factorial);
}

void Check_PrimeNumber(int number)
{
	int i, n;
	for(i=2; i < sqrt(number); i++)
	{
		if(number%i == 0)
			break;
	}
	
	if(i > sqrt(number))
	{
		printf("%d is prime number\n", number);
	}
	else
	{
		printf("%d is not prime number\n", number);
	}
}

// Fibbonacci_Serias
void Fibbonacci_Serias(int number)
{
	if(!number) return;
	
	int x = 0, y = 1, z = 0;
	
	for( int i=0; i< number; i++)
	{
		z = x + y;
		printf("%d ", z);
		x = y;
		y = z;
	}
	printf("\n");
}

void Check_Endiness(void)
{
	unsigned int data = 0x12345678;
	char *pData = (char *)&data;
	
	if(*pData == 0x78)
	{
		printf("This machine is little endian \n");
	}
	else
	{
		printf("This machine is big endian \n");
	}
}

void Remove_Special_Characters_from_String(char *str)
{
	int i = 0, j;
	printf("Input: %s\n", str);

    for (i = 0; str[i] != '\0'; ++i)
	{
		while (!(str[i] >= 'a' && str[i] <= 'z') && 
			   !(str[i] >= 'A' && str[i] <= 'Z') && 
			   !(str[i] >= '0' && str[i] <= '9') && 
			   !(str[i] == '\0'))
			{
				for (j = i; str[j] != '\0'; ++j)
				{
					str[j] = str[j + 1];
				}
				str[j] = '\0';
			}
	}
	printf("Output : %s\n", str);
}

void Leap_Year_Check(int year)
{
	if((year % 100 != 0 && year % 4 == 0) || (year % 400 == 0))
	{
		printf("%d is leap year\n", year);
	}
	else
	{
		printf("%d is not leap year\n", year);		
	}
}

void Palindrom_Check(char *str)
{
	int i = 0, j = strlen(str) - 1;
	for(i = 0; i <= j; i++, j--)
	{
		if(str[i] != str[j])
			break;
	}
	if(i>j)
	{
		printf("[%s] is palindrom\n", str);
	}
	else
	{
		printf("[%s] is not palindrom\n", str);
	}
}

int AtoI(char *str)
{
	int finalInt = 0, i, num;
	for(i=0; i<strlen(str); i++)
	{
		num = str[i] - '0';
		finalInt = (finalInt * 10) + num;
	}
	return finalInt;
}

void main(void)
{
	//-- Factorial
	//Factorial(7);
	
	// Prime Number
	//Check_PrimeNumber(13);
	
	//-- Fibbonacci_Serias
	//printf("---------- Fibbonacci_Serias -----------\n");
	//Fibbonacci_Serias(10);
	
	//-- Check_Endiness
	//printf("\n---------- Check_Endiness -----------\n");
	//Check_Endiness();
	
	//-- Remove Special Characters from String
	//printf("\n--Remove Special Characters from String--\n");
	//char data[50] = "I Lo/v)e.M#y  I$nd/ia";
	//Remove_Special_Characters_from_String(data);
	
	//-- Leap Yeat Check
	//Leap_Year_Check(2000);
	
	//-- Palindrom
	//Palindrom_Check("madam");
	
	// AtoI
	printf("-- AtoI : %d\n", AtoI("12345"));
	
}