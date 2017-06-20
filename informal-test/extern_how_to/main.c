#include <stdio.h>
#include "main.h"


int main(int argc, char **argv)
{
	extern int val;
	printf("%d\n", val);
	//test_ret_local_char();
	//test_ret_local_int();

	return 0;
}

int test_convert_ptr()
{
	int p = 2;
	float *p2 = (float *)&p;
	printf("%x",p);
	return 0;
}
