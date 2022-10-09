#define _CRT_SECURE_NO_WARNINGS

#include "card.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	EN_cardError_t ret_car= WRONG_NAME;


	char arr[30] = { '\0' };
	printf("please enter your card hold name: ");
	fflush(stdin);
	scanf("%[^\n]%*c", arr);
	

	int i = 0;
	while (arr[i] != '\0')
	{
		i++;
	}
	for (int i = 0; i < 25; i++)
	{
		cardData->cardHolderName[i] = arr[i];
	}
	if ((i >= 20) && (i <= 24) && (i != 0))
	{
		ret_car= OK_card;
	}
	else
	{
		ret_car= WRONG_NAME;
	}
	return ret_car;
}



EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	EN_cardError_t ret_car = WRONG_PAN;
		int i = 0;
		char arr[30] = { '\0' };

		printf("plese enter PAN number: ");
		fflush(stdin);
		scanf("%[^\n]%*c", arr);
		while (arr[i] != '\0')
		{
			i++;
		}
		for (int j = 0; j < 20;j++)
		{
			cardData->primaryAccountNumber[j] = arr[j];
		}
		if ((i >= 16) && (i <= 24) && (i != 0))
		{
			printf("your pan is: %s\n", arr);
			ret_car = OK_card;
		}
		else
		{
			ret_car =  WRONG_PAN;
		}
	
		return ret_car;

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	EN_cardError_t ret_car = WRONG_EXP_DATE;
	int month = 0, year = 0;

	int i;

	for (i = 0; i < 6; i++)
	{
		cardData->cardExpirationDate[i] = '\0';
	}

	printf("Enter expiry date [MM/YY]: ");
	fflush(stdin);

	scanf("%[^\n]%*c", cardData->cardExpirationDate);

	month = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');

	year = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
	

	if ((cardData->cardExpirationDate[5] != '\0') || (cardData->cardExpirationDate[2] != '/'))
	{
		ret_car = WRONG_EXP_DATE;
	}
	else if ((month >= 1 && month <= 12) && (year < 99 && year > 0))
	{

		printf(" expiry date: %s\n", cardData->cardExpirationDate);
		ret_car = OK_card;
	}
	else
	{


		ret_car  = WRONG_EXP_DATE;
	}
	return ret_car;
}


