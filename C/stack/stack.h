#pragma once

#define DATA_TYPE char
#define DATA_TYPE_POINTER char*

#define Stack_STACK_NOERROR 0
#define Stack_STACK_FULL 1
#define Stack_STACK_EMPTY	2

typedef unsigned int as_uint;

typedef struct _Stack
{
	DATA_TYPE_POINTER m_pStack;
	as_uint m_uiMax;
	as_uint m_uiCount;
	int m_iErrorCode;
} Stack, *pStack;

pStack StackInit(as_uint max);

as_uint StackLength(pStack pS);

int StackIsEmpty(pStack pS);

int StackGetLatestError(pStack pS);

int StackPush(pStack pS, DATA_TYPE data);

DATA_TYPE StackPop(pStack pS);

DATA_TYPE StackGetTop(pStack pS);

void StackTraversal(pStack pS, int (*f)(DATA_TYPE_POINTER pData, as_uint n));

void StackDestory(pStack pS);

int StackResize(pStack pS, as_uint addNums);

int StackCleanup(pStack pS);

int StackReinit(pStack pS, as_uint max);