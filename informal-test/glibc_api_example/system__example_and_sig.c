#include <stdlib.h>
int main()
{
	system("ping 192.168.0.1 > /dev/null -t");
	system("echo 'bye'");
	return 0;
}