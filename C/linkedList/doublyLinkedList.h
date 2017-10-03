#pragma once

#include <malloc.h>
#include <stdio.h>
#include "emptyStdin.h"

#ifndef DLLTYPE
#define DLLTYPE char
#endif

#ifndef DLLTYPEPTR
#define DLLTYPEPTR DLLTYPE*
#endif

typedef int(*ErgodicFuncDLL)(DLLTYPEPTR pData, int i);
typedef int(*InputFuncDLL)(DLLTYPEPTR pData);
typedef int(*ComparisonFuncDLL)(DLLTYPEPTR pData, DLLTYPEPTR pUserInputData);
typedef void(*freeFuncDLL)(DLLTYPEPTR pDataPtr);

typedef struct _doublyLinkedListNode
{
	struct _doublyLinkedListNode *pPrev;
	struct _doublyLinkedListNode *pNext;
	DLLTYPE data;
} DLLNode, *pDLLNode;

void destoryDLL(pDLLNode pHead, freeFuncDLL pFun)
{
	if (pHead == NULL)return;
	pDLLNode pCursor = pHead, pDestory;
	while (pCursor->pNext != NULL)
	{
		pDestory = pCursor;
		pCursor = pCursor->pNext;
		if (pFun != NULL)
			pFun(&(pDestory->data));
		free(pDestory);
	}
	free(pCursor);
}

pDLLNode createDLL(int n, InputFuncDLL pFun, freeFuncDLL pFun2)
{
	pDLLNode pHead = (pDLLNode)malloc(sizeof(DLLNode));
	if (pHead == NULL)
	{
		puts("Create doubly linked list header failed.");
		return NULL;
	}
	pHead->pPrev = NULL;
	pHead->pNext = NULL;
	emptyStdin();
	pDLLNode pCursor = pHead;
	for (int i = 0; i < n; i++)
	{
		pCursor->pNext = (pDLLNode)malloc(sizeof(DLLNode));
		if (pCursor->pNext == NULL)
		{
			printf("Create doubly linked list failed in Number %d\n.", i);
			destoryDLL(pHead, pFun2);
			return NULL;
		}
		pCursor->pNext->pPrev = pCursor;
		pCursor = pCursor->pNext;
		pCursor->pNext = NULL;
		if (pFun(&(pCursor->data)) != 1)
		{
			printf("Create doubly linked list stop by input data in Number %d\n", i);
			break;
		}
	}
	emptyStdin();
	return pHead;
}

void ergodicDLL(pDLLNode pHead, ErgodicFuncDLL pFun)
{
	if (pHead == NULL)
	{
		puts("Ergodic this doubly linked list is empty.");
		return;
	}
	pDLLNode p = pHead;
	int i = 1;
	while (p->pNext != NULL)
	{
		p = p->pNext;
		if (pFun(&(p->data), i++) != 1)
			return;
	}
}

int deleteInDLL(pDLLNode pHead, int where, freeFuncDLL pFun)
{
	if (pHead == NULL)
	{
		puts("Delete this doubly linked list is empty.");
		return 0;
	}
	if (where < 0)
		return 0;
	pDLLNode pCursor = pHead;
	int i = 0, found = 0;
	while (pCursor->pNext != NULL)
	{
		pCursor = pCursor->pNext;
		i++;
		if (i == where)
		{
			found = 1;
			break;
		}
		/*if (i > where)
		return 0;*/
	}
	if (found == 0)
		return 0;
	pCursor->pPrev->pNext = pCursor->pNext;
	if (pCursor->pNext != NULL)
		pCursor->pNext->pPrev = pCursor->pPrev;
	if (pFun != NULL)
		pFun(&(pCursor->data));
	free(pCursor);
	return 1;
}

int deleteWhatDLL(pDLLNode pHead, DLLTYPEPTR equalValue, ComparisonFuncDLL pFun, freeFuncDLL pFun2)
{
	if (pHead == NULL)
	{
		puts("Delete this doubly linked list is empty.");
		return 0;
	}
	pDLLNode pCursor = pHead;
	int i = 0, found = 0;
	while (pCursor->pNext != NULL)
	{
		pCursor = pCursor->pNext;
		i++;
		if (pFun(&(pCursor->data), equalValue) == 1)
		{
			found = 1;
			break;
		}
	}
	if (found == 0)
		return 0;
	pCursor->pPrev->pNext = pCursor->pNext;
	if (pCursor->pNext != NULL)
		pCursor->pNext->pPrev = pCursor->pPrev;
	if (pFun2 != NULL)
		pFun2(&(pCursor->data));
	free(pCursor);
	return 1;
}

int insertInDLL(pDLLNode pHead, int after, DLLTYPE value)
{
	if (pHead == NULL)
	{
		puts("Delete this singly linked list is empty.");
		return 0;
	}
	if (after < 0)
		return 0;
	pDLLNode pCursor = pHead;
	int i = 0, found = 0;
	if (after == 0)
		found = 1;
	while(pCursor->pNext != NULL && found == 0)
	{
		pCursor = pCursor->pNext;
		i++;
		if (i == after)
		{
			found = 1;
			break;
		}
		/*if (i > where)
		return 0;*/
	}
	if (found == 0)
		return 0;
	pDLLNode pInsert = (pDLLNode)malloc(sizeof(DLLNode));
	if (pInsert == NULL)
		return 0;
	pDLLNode pTemp = pCursor->pNext;
	pCursor->pNext = pInsert;
	pInsert->pPrev = pCursor;
	pInsert->pNext = pTemp;
	if (pTemp != NULL)
		pTemp->pPrev = pInsert;
	pInsert->data = value;
	return 1;
}