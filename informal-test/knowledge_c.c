
#include <stdlib.h>  
#include <stdio.h>  

void change_const_by_ptr()
{
	const int a = 10;
	int *p = &a;
	*p = 20;
	printf("%d %d", a, *p);

}
//20 20

int main()
{

	change_const_by_ptr();
	return 0;
}
