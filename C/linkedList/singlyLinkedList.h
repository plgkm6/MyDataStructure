#pragma once

#include <malloc.h>
#include <stdio.h>
#include "emptyStdin.h"

#ifndef SLLTYPE
#define SLLTYPE char //链表节点的数据类型
#endif

#ifndef SLLTYPEPTR
#define SLLTYPEPTR SLLTYPE* //链表节点的数据类型的指针类型
#endif

//遍历函数
typedef int(*ErgodicFuncSLL)(SLLTYPEPTR pData, int i);
//遍历输入函数
typedef int(*InputFuncSLL)(SLLTYPEPTR pData);
//遍历判断相等函数，参数1为链表节点值，参数2为用户查找值
typedef int(*ComparisonFuncSLL)(SLLTYPEPTR pData, SLLTYPEPTR pUserInputData);
//释放SLLTYPEPTR
typedef void(*freeFuncSLL)(SLLTYPEPTR pDataPtr);

//链表节点结构体
typedef struct _singlyLinkedListNode
{
	struct _singlyLinkedListNode *pNext;
	SLLTYPE data;
} SLLNode, *pSLLNode;

/**
 * 销毁一个单向链表
 * @param pHead 单向链表头指针
 * @param pFun 释放链表节数据
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
 * 创建一个含有n个数据的链表（n不含表头）
 * @param n 节点数量（不含表头）
 * @param pFun 用来输入数据的函数
 * @param pFun2 释放链表节数据
 * @return 单向链表头指针
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
 * 遍历链表
 * @param pHead 单向链表头指针
 * @param pFun 遍历的链表的链表数据的地址会传入pFun，可用来读写（如输出）
 * @param pFun 释放链表节数据
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
 * 删除第@where的节点
 * @param pHead 单向链表头指针
 * @param where 目标下标（从1开始）
 * @param pFun 释放链表节数据
 * @return 找到并删除返回1，否则返回0
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
 * 删除节点数据为@equalValue的节点
 * @param pHead 单向链表头指针
 * @param equalValue 查找的值
 * @param pFun 比较函数
 * @param pFun2 释放链表节数据
 * @return 找到并删除返回1，否则返回0
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
 * 在@after之后插入数据（包括0位置）
 * @param pHead 单向链表头指针
 * @param after 插入位置（之前）
 * @param value 新值
 * @return 找到并插入成功返回1，否则（未找到或插入失败）返回0
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