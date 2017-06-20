#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

int *_test_ret_local_int()
{
	int i = 5;

	return &i;
}

void test_ret_local_int()
{
	int *p = 0;
	
	p = _test_ret_local_int();

	printf("%d\n", *p);
}

char *_test_ret_local_char()
{
	char *s = "abdce";
	
	return s;
}


void test_ret_local_char()
{
	char *s = NULL;
	
	s = _test_ret_local_char();

	printf("%s\n", s);
}


#endif
