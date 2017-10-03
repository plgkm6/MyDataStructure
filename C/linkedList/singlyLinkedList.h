#pragma once

#include <malloc.h>
#include <stdio.h>
#include "emptyStdin.h"

#ifndef SLLTYPE
#define SLLTYPE char //����ڵ����������
#endif

#ifndef SLLTYPEPTR
#define SLLTYPEPTR SLLTYPE* //����ڵ���������͵�ָ������
#endif

//��������
typedef int(*ErgodicFuncSLL)(SLLTYPEPTR pData, int i);
//�������뺯��
typedef int(*InputFuncSLL)(SLLTYPEPTR pData);
//�����ж���Ⱥ���������1Ϊ����ڵ�ֵ������2Ϊ�û�����ֵ
typedef int(*ComparisonFuncSLL)(SLLTYPEPTR pData, SLLTYPEPTR pUserInputData);
//�ͷ�SLLTYPEPTR
typedef void(*freeFuncSLL)(SLLTYPEPTR pDataPtr);

//����ڵ�ṹ��
typedef struct _singlyLinkedListNode
{
	struct _singlyLinkedListNode *pNext;
	SLLTYPE data;
} SLLNode, *pSLLNode;

/**
 * ����һ����������
 * @param pHead ��������ͷָ��
 * @param pFun �ͷ����������
 */
void destorySLL(pSLLNode pHead, freeFuncSLL pFun)
{
	if (pHead == NULL)return;
	pSLLNode pCursor = pHead, pDestory;
	while(pCursor->pNext != NULL)
	{
		pDestory = pCursor;
		pCursor = pCursor->pNext;
		if (pFun != NULL)
			pFun(&(pDestory->data));
		free(pDestory);
	}
	free(pCursor);
}

/**
 * ����һ������n�����ݵ�����n������ͷ��
 * @param n �ڵ�������������ͷ��
 * @param pFun �����������ݵĺ���
 * @param pFun2 �ͷ����������
 * @return ��������ͷָ��
 */
pSLLNode createSLL(int n, InputFuncSLL pFun, freeFuncSLL pFun2)
{
	pSLLNode pHead = (pSLLNode)malloc(sizeof(SLLNode));
	if (pHead == NULL)
	{
		puts("Create singly linked list header failed.");
		return NULL;
	}
	pHead->pNext = NULL;
	emptyStdin();
	pSLLNode pCursor = pHead;
	for(int i = 0; i < n; i++)
	{
		pCursor->pNext = (pSLLNode)malloc(sizeof(SLLNode));
		if (pCursor->pNext == NULL)
		{
			printf("Create singly linked list failed in Number %d\n.", i);
			destorySLL(pHead, pFun2);
			return NULL;
		}
		pCursor = pCursor->pNext;
		pCursor->pNext = NULL;
		if(pFun(&(pCursor->data)) != 1)
		{
			printf("Create singly linked list stop by input data in Number %d\n", i);
			break;
		}
	}
	emptyStdin();
	return pHead;
}

/**
 * ��������
 * @param pHead ��������ͷָ��
 * @param pFun ������������������ݵĵ�ַ�ᴫ��pFun����������д���������
 * @param pFun �ͷ����������
 */
void ergodicSLL(pSLLNode pHead, ErgodicFuncSLL pFun)
{
	if (pHead == NULL)
	{
		puts("Ergodic this singly linked list is empty.");
		return;
	}
	pSLLNode p = pHead;
	int i = 1;
	while(p->pNext != NULL)
	{
		p = p->pNext;
		if (pFun(&(p->data), i++) != 1)
			return;
	}
}

/**
 * ɾ����@where�Ľڵ�
 * @param pHead ��������ͷָ��
 * @param where Ŀ���±꣨��1��ʼ��
 * @param pFun �ͷ����������
 * @return �ҵ���ɾ������1�����򷵻�0
 */
int deleteInSLL(pSLLNode pHead, int where, freeFuncSLL pFun)
{
	if (pHead == NULL)
	{
		puts("Delete this singly linked list is empty.");
		return 0;
	}
	if (where < 0)
		return 0;
	pSLLNode pDelete = pHead, pBefore = pDelete;
	int i = 0, found = 0;
	while(pDelete->pNext != NULL)
	{
		pBefore = pDelete;
		pDelete = pDelete->pNext;
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
	pDelete = pDelete->pNext;
	if (pFun != NULL)
		pFun(&(pBefore->pNext->data));
	free(pBefore->pNext);
	pBefore->pNext = pDelete;
	return 1;
}

/**
 * ɾ���ڵ�����Ϊ@equalValue�Ľڵ�
 * @param pHead ��������ͷָ��
 * @param equalValue ���ҵ�ֵ
 * @param pFun �ȽϺ���
 * @param pFun2 �ͷ����������
 * @return �ҵ���ɾ������1�����򷵻�0
 */
int deleteWhatSLL(pSLLNode pHead, SLLTYPEPTR equalValue, ComparisonFuncSLL pFun, freeFuncSLL pFun2)
{
	if (pHead == NULL)
	{
		puts("Delete this singly linked list is empty.");
		return 0;
	}
	pSLLNode pDelete = pHead, pBefore = pDelete;
	int found = 0;
	while (pDelete->pNext != NULL)
	{
		pBefore = pDelete;
		pDelete = pDelete->pNext;
		if (pFun(&(pDelete->data), equalValue) == 1)
		{
			found = 1;
			break;
		}
	}
	if (found == 0)
		return 0;
	pDelete = pDelete->pNext;
	if (pFun2 != NULL)
		pFun2(&(pBefore->pNext->data));
	free(pBefore->pNext);
	pBefore->pNext = pDelete;
	return 1;
}

/**
 * ��@after֮��������ݣ�����0λ�ã�
 * @param pHead ��������ͷָ��
 * @param after ����λ�ã�֮ǰ��
 * @param value ��ֵ
 * @return �ҵ�������ɹ�����1������δ�ҵ������ʧ�ܣ�����0
 */
int insertInSLL(pSLLNode pHead, int after, SLLTYPE value)
{
	if (pHead == NULL)
	{
		puts("Delete this singly linked list is empty.");
		return 0;
	}
	if (after < 0)
		return 0;
	pSLLNode pCursor = pHead, pAfter = NULL;
	int i = 0, found = 0;
	if (after == 0)
		found = 1;
	while(pCursor->pNext != NULL && found == 0)
	{
		pCursor = pCursor->pNext;
		i++;
		if(i == after)
		{
			found = 1;
			break;
		}
		/*if (i > where)
		return 0;*/
	}
	if (found == 0)
		return 0;
	pAfter = pCursor->pNext;
	pSLLNode pInsert = (pSLLNode)malloc(sizeof(SLLNode));
	if (pInsert == NULL)
		return 0;
	pInsert->data = value;
	pCursor->pNext = pInsert;
	pInsert->pNext = pAfter;
	return 1;
}