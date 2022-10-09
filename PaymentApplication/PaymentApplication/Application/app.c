#define _CRT_SECURE_NO_WARNINGS

#include "app.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


void appStart(void)
{
	ST_cardData_t cardData;
	ST_cardData_t card_Data;

	ST_terminalData_t termData;
	ST_transaction_t transData;
	EN_terminalError_t ret_term;
	

	
		printf("   ----Read AccountsDB------\n");
		printf("   loaded Accounts DataBase is done \n");

		EN_cardError_t return_card = getCardHolderName(&cardData);
		while (return_card == WRONG_NAME)
		{
			printf("\n            ---WRONG_NAME---     \n");
			printf("\t  enter again:\n");
			return_card = getCardHolderName(&cardData);
		}


		return_card = getCardExpiryDate(&card_Data);


		while (return_card == WRONG_EXP_DATE)
		{
			printf("\n\t-------WRONG_EXP_DATE---------\n");
			printf("\t enter again::\n");
			return_card = getCardExpiryDate(&cardData);
		}



		return_card = getCardPAN(&cardData);

		while (return_card == WRONG_PAN)
		{
			printf("\n-------------WRONG_PAN-------\n");
			printf(" \t enter again : \n");
			return_card = getCardPAN(&cardData);
		}




		ret_term = getTransactionDate(&termData);

		while (ret_term == WRONG_DATE)
		{
			printf("\n\t   WRONG_DATE  \n");
			printf("         enter again: \n");
			ret_term = getTransactionDate(&termData);
		}


		ret_term = isCardExpired(card_Data, termData);

		if (ret_term == EXPIRED_CARD)
		{
			printf("\n\t  EXPIRED_CARD   \n");
			return;
		}


		ret_term = setMaxAmount(&termData);

		while (ret_term == INVALID_AMOUNT)
		{
			printf("\n\t INVALID AMOUNT \n");
			printf(" \n  enter again: \n");
			ret_term = setMaxAmount(&termData);
		}


		ret_term = getTransactionAmount(&termData);


		while (ret_term == INVALID_AMOUNT)
		{
			printf("\n\t   INVALID_AMOUNT\n");
			printf("\n\t   enter again: \n");
			ret_term = getTransactionAmount(&termData);
		}


		ret_term = isBelowMaxAmount(&termData);

		if (ret_term == EXCEED_MAX_AMOUNT)
		{
			printf("\n\t  EXCEED_MAX_AMOUNT   \n");
			return;
		}

		transData.cardHolderData = cardData;
		transData.terminalData = termData;

		EN_transState_t transSt = recieveTransactionData(&transData);


		if (transSt == DECLINED_STOLEN_CARD)
		{
			printf("\n\t         DECLINED STOLEN CARD/INVALID ACCOUNT         \n");
		}
		else if (transSt == DECLINED_INSUFFECIENT_FUND) {
			printf("\n\t          DECLINED_INSUFFECIENT_FUND       \n");
		}
		else if (transSt == APPROVED)
		{
			printf("\n\t............................................APPROVED\n");
			printf("\t.............................................SAVING TRANSACTION is done...\n");
		}

		
}

