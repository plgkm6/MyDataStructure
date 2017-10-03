#pragma once

#include <stdio.h>

void emptyStdin()
{
#ifdef WIN32
	rewind(stdin); //fflush(stdin);
#elif defined(linux)
	setbuf(stdin, NULL);
#endif
}