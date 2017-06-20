#include "stdio.h"
int main()
{
	FILE *fp;
	char buf[200] = {0};
	if((fp=popen("cat test", "r"))==NULL)
	{
		perror("Fail to popen \n");
		exit(1);
	}
	printf("popen returned!\n");
	while(fgets(buf, 200, fp) != NULL)//popen可通过此fp获得命令（如:ls）的打印结果
	{
		printf("%s", buf);
	}
	pclose(fp);
	return 0;
}
