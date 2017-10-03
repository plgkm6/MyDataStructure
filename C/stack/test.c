#include "stack.h"
#include <stdio.h>

int f(char* pData, as_uint n)
{
	printf("%d: %c\n", n, *pData);
	return 1;
}

int main()
{
	pStack pS = StackInit(10);
	printf("Length: %d, isEmpty: %c\n", StackLength(pS), StackIsEmpty(pS) ? 'Y' : 'N');
	StackPush(pS, 'a');
	StackPush(pS, 'b');
	StackPush(pS, 'c');
	StackPush(pS, 'd');
	StackPush(pS, 'e');
	StackPush(pS, 'f');
	StackPush(pS, 'g');
	StackPush(pS, 'h');
	StackPush(pS, 'i');
	StackPush(pS, 'j');
	StackPush(pS, 'k');
	StackTraversal(pS, f);
	printf("Last Error: %d\n", StackGetLatestError(pS));
	printf("Last Error: %d\n", StackGetLatestError(pS));

	char t = StackPop(pS);
	printf("Pop: %c\n", t);
	StackTraversal(pS, f);

	t = StackGetTop(pS);
	printf("GetTop: %c\n", t);
	StackTraversal(pS, f);

	printf("Length: %d, isEmpty: %c\n", StackLength(pS), StackIsEmpty(pS) ? 'Y' : 'N');

	StackResize(pS, 20);
	StackPush(pS, 'k');
	printf("Last Error: %d\n", StackGetLatestError(pS));
	StackTraversal(pS, f);

	StackReinit(pS, 10);
	printf("Length: %d, isEmpty: %c\n", StackLength(pS), StackIsEmpty(pS) ? 'Y' : 'N');

	StackDestory(pS);

	return 0;
}