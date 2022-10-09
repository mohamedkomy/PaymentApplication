#define _CRT_SECURE_NO_WARNINGS

#include"terminal.h"
#include <time.h>
#include <stdio.h>






EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
		EN_terminalError_t term_return= WRONG_DATE;
		char arr[11] = { '\0' };
		printf("please Enter transaction date [DD/MM/YYYY]: ");
		fflush(stdin);
		scanf("%[^\n]%*c", arr);

		for (int i = 0; i < 11; i++)
		{
			termData->transactionDate[i] = arr[i];
		}
	

		uint32_t day = (((termData->transactionDate[0] - '0') * 10) + (termData->transactionDate[1] - '0'));
		uint32_t month = (((termData->transactionDate[3] - '0') * 10) + (termData->transactionDate[4] - '0'));
		uint32_t year = (((termData->transactionDate[6] - '0') * 1000) + ((termData->transactionDate[7] - '0') * 100) + ((termData->transactionDate[8] - '0') * 10) + ((termData->transactionDate[9] - '0')));
	
		if ((day < 0 || day >31) || (month < 1 || month > 12) || (year < 1900))
		{
			term_return = WRONG_DATE;
		}
		
		else if ((termData->transactionDate[9] == '\0') || (termData->transactionDate[2] != '/') || (termData->transactionDate[5] != '/'))
		{
			term_return = WRONG_DATE;
		}
		else 
		{ 
		
			printf("the Date is: %s\n", arr);
			term_return = OK_term;
		
		}
		
			
		
		return  term_return;


	


}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	EN_terminalError_t term_return;

	int cardmonth = (cardData.cardExpirationDate[0] - '0') * 10 + cardData.cardExpirationDate[1] - '0';
	int cardyear = (cardData.cardExpirationDate[3] - '0') * 10 + (cardData.cardExpirationDate[4] - '0') + 2000;
	int termmonth = (termData.transactionDate[3] - '0') * 10 + termData.transactionDate[4] - '0';
	int termyear = (termData.transactionDate[6] - '0') * 1000 + (termData.transactionDate[7] - '0') * 100 + (termData.transactionDate[8] - '0') * 10 + +termData.transactionDate[9] - '0';
	printf(" expiry in termdate: %s\n", cardData.cardExpirationDate);

	if (termyear > cardyear)
	{
		term_return = EXPIRED_CARD;
	}
	else if (termyear == cardyear && termmonth > cardmonth)
	{
		term_return = EXPIRED_CARD;
	}
	else
	{
		term_return = OK_term;
	}
	return term_return;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t term_return;
	float amount = -1;
	printf("Enter transaction amount: ");
	scanf("%f", &amount);

	if (amount <= 0)
	{
		term_return = INVALID_AMOUNT;
	}
	else
	{
		term_return = OK_term;
	}
	termData->transAmount = amount;

	printf("Enter Amount for a transaction: %f\n", termData->transAmount);

	return term_return;
	
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t term_return;

	if ((termData->transAmount) > (termData->maxTransAmount))
	{
		term_return = EXCEED_MAX_AMOUNT;
	}
	else 
	{
		term_return = OK_term;
	}
	return term_return;
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t term_return;
	float mxamount = -1;

	printf("Enter maxAmount for a transaction: ");

	scanf("%f", &mxamount);

	if (mxamount <= 0)
	{
		term_return = INVALID_MAX_AMOUNT;
	}
	else
	{
		term_return = OK_term;
	}

	termData->maxTransAmount = mxamount;

	printf("Enter maxAmount for a transaction: %f\n", termData->maxTransAmount);
	return term_return;
}