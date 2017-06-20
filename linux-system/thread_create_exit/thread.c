/*
 * 注意：-pthread 选项
 * gcc -pthread pth.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/syscall.h>

void *thr_fn(void *arg)
{
    printf("thread 1 new thread: %d\n",syscall(SYS_gettid));
	sleep(10);
	printf("thread 1 pthread_exit: %d\n",syscall(SYS_gettid));
    pthread_exit(NULL);
}
 
void *thr_fn2(void *arg)
{
    printf("thread 2 new thread: %d\n",syscall(SYS_gettid));//1.要获取线程的LWP的ID（即PID），用gettid函数	
	
    //2.  getpid() ：所在进程的ID
    //3.  pthread_self() ： 线程的内部ID
	
	sleep(15);
	printf("thread 2 pthread_exit: %d\n",syscall(SYS_gettid));
    pthread_exit(NULL);
} 
 
int main(void)
{
    int err;
    pthread_t t1;
	pthread_t t2;
	
	printf("main thread: %d\n",syscall(SYS_gettid));		
	
	//create
    err = pthread_create(&t1, NULL, thr_fn, NULL);
    if (err != 0)
        printf("can't create thread: %s\n", strerror(err));	
	
	err = pthread_create(&t2, NULL, thr_fn2, NULL);
	if (err != 0)
        printf("can't create thread: %s\n", strerror(err));
	
	//join
	if(t1 != 0)		//这里要判断！上面的线程可能没有创建成功，导致下面不可能等到那个线程结束，
					//而在用pthread_join的时候出现段错误（访问了未知的内存区）。
	{
		printf("pthread_join thread 1\n",syscall(SYS_gettid));
		pthread_join(t1,NULL);				//主线程会阻塞在这里，直到等待的线程推出
	}
	if(t2 != 0)
	{
		printf("pthread_join thread 2\n");	
		pthread_join(t2,NULL);		
	}

	printf("main pthread_exit: %d\n",syscall(SYS_gettid));
    return EXIT_SUCCESS;
}

