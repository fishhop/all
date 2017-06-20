#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "pthread.h"

/*注意:编译时加上选项:  -pthread 
pthread 库不是 Linux 系统默认的库，连接时需要使用库 libpthread.a，
所以在编译中要加 -lpthread参数。*/

void *t1(void * arg)
{
	printf("%d: %d,  %d, %d \n",__LINE__, getpid(), pthread_self());
	while(1)
	{
		sleep(1);
	}
}

int main(int argc, char** argv)
{
	pthread_t t[3];
	pid_t p;
	p = fork();
	
	printf("line: tgid() \t ppid() \t pgrp() \t gettgid(),\n");
	
	if(p == 0)
	{
		pthread_create(&t[0], NULL, t1, NULL);
		pthread_create(&t[1], NULL, t1, NULL);
		
		printf("getpid() \t ppid() \t pgrp() \t gettgid(), %d \n", __LINE__);
        printf("%d \t %d \t %d \t %d \n", getpid(),getppid(),getpgrp(),gettgid());

		if(fork() == 0)
		{
		printf("getpid() \t ppid() \t pgrp() \t gettgid(), %d \n", __LINE__);
        printf("%d \t %d \t %d \t %d \n", getpid(),getppid(),getpgrp(),gettgid());	
		}
		else
		{
		printf("getpid() \t ppid() \t pgrp() \t gettgid(), %d \n", __LINE__);
        printf("%d \t %d \t %d \t %d \n", getpid(),getppid(),getpgrp(),gettgid());	
		}

		pthread_join(t[0], NULL);	
		pthread_join(t[1], NULL);
	}
	else
	{
		pthread_create(&t[0], NULL, t1, NULL);
		pthread_create(&t[1], NULL, t1, NULL);
		
		printf("getpid() \t ppid() \t pgrp() \t gettgid(), %d \n", __LINE__);
        printf("%d \t %d \t %d \t %d \n", getpid(),getppid(),getpgrp(),gettgid());

		pthread_join(t[0], NULL);	
		pthread_join(t[1], NULL);	

	}

	return 0;
}
