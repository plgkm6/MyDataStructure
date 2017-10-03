#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

pStack StackInit(as_uint max)
{
	pStack pS = (pStack)malloc(sizeof(Stack));
	if (pS == NULL)
	{
		printf("Stack Error: Initialize stack failed.\n");
		return NULL;
	}
	//pS->m_pStack = (DATA_TYPE_POINTER)calloc(max, sizeof(DATA_TYPE));
	pS->m_pStack = (DATA_TYPE_POINTER)malloc(max * sizeof(DATA_TYPE));
	//memset(pS->m_pStack, 0, max * sizeof(DATA_TYPE));
	if (pS->m_pStack == NULL)
	{
		printf("Stack Error: Not enough space to calloc for stack.\n");
		return NULL;
	}
	pS->m_uiMax = max;
	pS->m_uiCount = 0;
	pS->m_iErrorCode = Stack_STACK_NOERROR;
	return pS;
}

as_uint StackLength(pStack pS)
{
	if (pS == NULL)
	{
		printf("Stack Error: Parameter for StackLength() is NULL.\n");
		return;
	}
	return pS->m_uiCount;
}

int StackIsEmpty(pStack pS)
{
	if (pS == NULL)
	{
		printf("Stack Error: Parameter for StackIsEmpty() is NULL.\n");
		return;
	}
	return (pS->m_uiCount == 0) ? 1 : 0;
}

int StackGetLatestError(pStack pS)
{
	if (pS == NULL)
	{
		printf("Stack Error: Parameter for StackGetLatestError() is NULL.\n");
		return 0;
	}
	int temp = pS->m_iErrorCode;
	pS->m_iErrorCode = Stack_STACK_NOERROR;
	return temp;
}

int StackPush(pStack pS, DATA_TYPE data)
{
	if (pS == NULL)
	{
		printf("Stack Error: Parameter for StackPush() is NULL.\n");
		return -1;
	}
	if (pS->m_uiCount == pS->m_uiMax)
	{
		pS->m_iErrorCode = Stack_STACK_FULL;
		return -2;
	}
	pS->m_pStack[pS->m_uiCount++] = data;
	return 1;
}

DATA_TYPE StackPop(pStack pS)
{
	if (pS == NULL)
	{
		printf("Stack Error: Parameter for StackPop() is NULL.\n");
		return;
	}
	if (StackIsEmpty(pS))
	{
		printf("Stack Error: StackPop is empty.\n");
		pS->m_iErrorCode = Stack_STACK_EMPTY;
		return;
	}
	pS->m_uiCount--;
	return pS->m_pStack[pS->m_uiCount];
}

DATA_TYPE StackGetTop(pStack pS)
{
	if (pS == NULL)
	{
		printf("Stack Error: Parameter for StackGetTop() is NULL.\n");
		return;
	}
	if (StackIsEmpty(pS))
	{
		printf("Stack Error: StackPop is empty.\n");
		pS->m_iErrorCode = Stack_STACK_EMPTY;
		return;
	}
	return pS->m_pStack[pS->m_uiCount - 1];
}

void StackTraversal(pStack pS, int (*f)(DATA_TYPE_POINTER pData, as_uint n))
{
	if (pS == NULL)
	{
		printf("Stack Error: Parameter for StackTraversal() is NULL.\n");
		return;
	}
	if (StackIsEmpty(pS))
	{
		printf("Stack Error: StackPop is empty.\n");
		pS->m_iErrorCode = Stack_STACK_EMPTY;
		return;
	}

	for(long long i = pS->m_uiCount - 1; i >= 0; i--)
	{
		int r = f(&(pS->m_pStack[i]), i);
		if (r == 1)
			continue;
		else if (r == 0)
			break;
		else if (r < 0)
			i -= r;
		else
			i += r;
		printf("f1\n");
	}
}

void StackDestory(pStack pS)
{
	if (pS == NULL)
		return;
	free(pS->m_pStack);
	free(pS);
}

int StackResize(pStack pS, as_uint addNums)
{
	if (pS == NULL)
	{
		printf("Stack Error: Parameter for StackResize() is NULL.\n");
		return -1;
	}
	pS->m_pStack = realloc(pS->m_pStack, (pS->m_uiMax + addNums) * sizeof(DATA_TYPE));
	if (pS->m_pStack == NULL)
		exit(-1);
	return 0;
}

int StackCleanup(pStack pS)
{
	if (pS == NULL)
	{
		printf("Stack Error: Parameter for StackResize() is NULL.\n");
		return -1;
	}
	memset(pS->m_pStack, 0, pS->m_uiMax * sizeof(DATA_TYPE));
	pS->m_uiCount = 0;
	pS->m_iErrorCode = Stack_STACK_NOERROR;
	return 1;
}

int StackReinit(pStack pS, as_uint max)
{
	if (pS == NULL)
	{
		printf("Stack Error: Parameter for StackResize() is NULL.\n");
		return -1;
	}

	if (pS->m_pStack != NULL)
		free(pS->m_pStack);

	//pS->m_pStack = (DATA_TYPE_POINTER)calloc(max, sizeof(DATA_TYPE));
	pS->m_pStack = (DATA_TYPE_POINTER)malloc(max * sizeof(DATA_TYPE));
	//memset(pS->m_pStack, 0, max * sizeof(DATA_TYPE));
	if (pS->m_pStack == NULL)
	{
		printf("Stack Error: Not enough space to calloc for stack.\n");
		return -2;
	}
	pS->m_uiMax = max;
	pS->m_uiCount = 0;
	pS->m_iErrorCode = Stack_STACK_NOERROR;
	return 1;
}
