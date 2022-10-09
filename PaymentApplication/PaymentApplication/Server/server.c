#define _CRT_SECURE_NO_WARNINGS


#include "server.h"
#include <stdio.h>

int index = -1;

ST_accountsDB_t AccountDB[255] = {
	{1118.000000 ,"6228710870023450848"},
	{1263.000000 ,"2154156582386382610"},
	{2000.000000 ,"12345678912345678952"},
	{3000.000000 ,"09874563214567895214"},
	{3500.000000 ,"09874563987167895214"},
	{1318.000000 ,"62287108714723450848"},
	{1363.000000 ,"21541565110386382610"},
	{2000.000000 ,"12345678912345678952"},
	{3080.000000 ,"09874563244457895214"},
	{3588.000000 ,"85274563987167895214"}
};

ST_transaction_t transactionsdata[255] ;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_transState_t ret_serv;
	

	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND)
	{
		transData->transState = DECLINED_STOLEN_CARD;
		ret_serv=DECLINED_STOLEN_CARD;
	}
	else if(isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		ret_serv = DECLINED_INSUFFECIENT_FUND;
	}
	else if(saveTransaction(transData) == SAVING_FAILED)
	{
		ret_serv = INTERNAL_SERVER_ERROR;
	}
	else
	{

		transData->transState = APPROVED;
		ret_serv = APPROVED;

		AccountDB[index].balance -= transData->terminalData.transAmount;
	}
	
	return ret_serv ;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{

	int flag = 0;
	int i, j;
	uint8_t* PAN = cardData->primaryAccountNumber;


	for (i = 0; i < 255; i++)
	{
		if (AccountDB[i].primaryAccountNumber[0] != '\0')
		{
			int equal = 1;
			for (j = 0; j < 20; j++)
			{
				if (AccountDB[i].primaryAccountNumber[j] != PAN[j])
				{
					equal = 0;
					break;
				}
			}
			if (equal == 1)
			{
				flag = 1;
				index = i;
				break;
			}
		}
		else
		{
			break;
		}
	}
	if (flag == 0)
	{
		return ACCOUNT_NOT_FOUND;
	}
	else
	{
		return OK;
	}
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{

	
	EN_serverError_t ret_serv;
	if ((AccountDB[index].balance) < (termData->transAmount))
	{
		ret_serv = LOW_BALANCE;
	}
	else 
	{
		ret_serv = OK;

	}

	return ret_serv;
}


EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	EN_serverError_t ret_serv;

	if (transData->transState == DECLINED_INSUFFECIENT_FUND)
	{
		ret_serv = SAVING_FAILED;
	}
	else if (transData->transState == DECLINED_STOLEN_CARD)
	{
		ret_serv = SAVING_FAILED;

	}
	else
	{
		static int i = 0;
		 transData->transactionSequenceNumber = i;
		
		transactionsdata[i].cardHolderData = transData->cardHolderData;
		transactionsdata[i].transactionSequenceNumber = transData->transactionSequenceNumber;
		transactionsdata[i].terminalData = transData->terminalData;
		transactionsdata[i].transState = transData->transState;
		i++;
		ret_serv = OK;

	}

	return ret_serv;
}


