#include <iostream>
#include <unistd.h>  
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

using namespace std;



//=======================================================
//--------------------- 创建线程 ------------------------
//=======================================================
/*
pthread_create():创建线程
fork():创建进程
*/
//http://blog.chinaunix.net/uid-704367-id-2679789.html
void t_consumer_and_producer()
{
	pthread_t tid_con, tid_pro;
	
	sem_init(&sem_con, 0, 3);
	sem_init(&sem_pro, 0, 7);//生产，10-3 =7
	sem_init(&sem_store, 0, 1);
	
	pthread_create(&tid_pro, nullptr, proThread(), nullptr);
	pthread_create(&tid_con, nullptr, conThread(), nullptr);

	pthead_join(tid_con, nullptr);
	pthead_join(tid_pro, nullptr);

	return 0;
}



//=======================================================
//------------------ 进程创建 : fork  -------------------
//=======================================================
void process_fork_childProcess()
{
	for(int i = 0; i != 5; ++i)
	{
		sleep(1);
		cout << "child, pid:" << getpid()<< endl;
	}
}
void process_fork_parentProcess()
{
	for(int i = 0; i != 5; ++i)
	{
		sleep(1);
		cout << "parent, pid:" << getpid() << endl;
	}

}
void process_fork()
{
	pid_t pid;
	//这个测试用例除pid == 0 之外均属于parentProcess
	cout << "test start, pid:" << getpid() << endl;
	if((pid = fork()) < 0)
		cout << "fork err" << endl;
	else if(pid == 0)
	{
		process_fork_childProcess();
	}
	else
	{
		process_fork_parentProcess();
	}
}
/*
$ g++ linux.cpp;a
test start, pid:7424
parent, pid:7424
child, pid:7500
parent, pid:7424
child, pid:7500
parent, pid:7424
child, pid:7500
child, pid:7500
parent, pid:7424
child, pid:7500
parent, pid:7424

*/


//=======================================================
//------------------ execl:借蛋生鸡  -------------------
//=======================================================

void test_exec()
{
	cout << "app start" << endl;
	if(fork() == 0)
	{
		execl("/bin/ls", "bin/ls", "-l", NULL);
		cout << "here cannot be seen" << endl;//这里执行不到了
	}
	cout << "app start" << endl;
}


//=======================================================
//------------------- UDP 示意版  -----------------------
//=======================================================
int server()
{

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    sock = socket(AF_INET, SOCK_DGRAM, 0)

    bind(sock, (struct sockaddr *)&addr, sizeof(addr))

	//clientAddr，从客户端接收,不用listen
    n = recvfrom(sock, buff, 511, 0, (struct sockaddr*)&clientAddr, &len);
    if (n>0)
        sendto(sock, buff, n, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
	
    return 0;
}
int client()
{
    sock=socket(AF_INET, SOCK_DGRAM, 0)

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    sendto(sock, buff, strlen(buff), 0, (struct sockaddr *)&addr, sizeof(addr));

    recvfrom(sock, buff, 512, 0, (struct sockaddr *)&addr, &len);

    return 0;
}


//=======================================================
//------------------- TCP 示意版  -----------------------
//=======================================================
Status socket_tcp_server()
{
	l_fd = socket(AF_INET, SOCK_STREAM, 0)//1. socket()

	addr.family = AF_INET;
	addr.s_addr = htonl(INADDR_ANY);//INADDR_ANY: 0.0.0.0的地址,即任意。所以有无htonl都行。
	addr.port = htons(8000);//注意htons!!!是s 上面才是l,htonl

	bind(l_fd, &addr, ...);	//2. bind()

	listen(l_fd, back_log);			//3. listen()
	
	c_fd = accept(l_fd);	//4. accept()

	recv(c_fd, buff, );
	send(c_fd, "ok", 2);	//5. read, write
	
	close(c_fd);			//6. close()
	close(l_fd);
	
}
Status socket_tcp_client()
{

	c_fd = socket(AF_INET, SOCK_STREAM, 0)
		
	addr.family = AF_INET;
	addr.port = htons(8000);//注意htons!!!是s 上面才是l,htonl
	inet_pton(AF_INET, "127.0.0.1", addr.s_addr);

	connect(c_fd, &addr, sizeof(addr))

	send(c_fd, buff, 2)
	recv(c_fd, buff, );
	
	close(c_fd);
}



//=======================================================
//---------------- TCP 完整版  -----------------------
//=======================================================
Status socket_tcp_server()
{
	struct sockaddr_in addr;
	int l_fd, c_fd, n;
	char buff[4096];
	
	if(l_fd = socket(AF_INET, SOCK_STREAM, 0) == -1)
		return ERR;

	memset(addr, 0, sizeof(addr));
	addr.family = AF_INET;
	addr.s_addr = htonl(INADDR_ANY);
	addr.port = htons(8000);//注意htons!!!是s 上面才是l,htonl

	if(bind(l_fd, &addr, sizeof(addr)) == -1)
		return ERR;

	if(listen(l_fd) == -1)
		return ERR;

	while(1)
	{
		if(c_fd = accept(l_fd,) == -1)
			return ERR;
		if(fork() == 0)
		{
			recv(c_fd, buff, );
			send(c_fd, "ok", 2);
		}
		close(c_fd);
	}
	close(l_fd);
}

Status socket_tcp_client()
{
	sockaddr_in addr;
	int c_fd;
	char buff[4096];
	
	if(c_fd = socket(AF_INET, SOCK_STREAM, 0) == -1)
		return ERR;

	memset(addr, 0 sizeof(addr));
	addr.family = AF_INET;
	addr.port = htons(8000);//注意htons!!!是s 上面才是l,htonl
	inet_pton(AF_INET, "127.0.0.1", addr.s_addr);
	if(bind(c_fd, &addr, sizeof(addr)) == -1)
		return ERR;

	if(connect(c_fd, &addr, sizeof(addr)) == -1)
		return ERR;

	if(send(c_fd, buff, 2) < 0)
		return ERR;

	close(c_fd);
}

//=======================================================
//---------------- UDP 完整版  -----------------------
//=======================================================
//socket--UDP
/*
 	一方可以不用bind()绑定地址和端口，由系统分配;
 	不绑定[ip,port]的一方必须首先向绑定地址的一方发送数据;
 	无连接的应用程序也可以调用connect()函数，但是它并不向对方发出建立连接的请求，而是在本地返回，由内核将connect()中指定的目标IP地址和端口号记录下来，在以后的通信中就可以使用面向连接(TCP)的数据发送函数send()和数据接收函数recv()
 	无连接的数据报传输过程中，作为服务器的必须先启动
 	无连接客户端一般不调用connect()，在数据发送前客户与服务器各自通过socket()和bind()建立了半相关，发送数据时除指定本地套接口的地址外，还需要指定接收方套接口地址，从而在数据收发过程中动态建立全连接。


*/
//http://www.cnblogs.com/uvsjoh/archive/2013/01/01/2841764.html





//=======================================================
//----------- 信号量方法: 生产者、消费者问题 ------------
//=======================================================

//http://www.cnblogs.com/hnrainll/archive/2011/04/21/2024089.html
int store = 3;
sem_t sem_con, sem_pro, sem_store; //三个信号量，两个是同步信号量，一个是互斥信号量

void *conThread()
{
	while(1)
	{
		sem_wait(&sem_con);//&
		sem_wait(&sem_store);
		store--;
		//slee(1);
		sem_post(&sem_store);
		sem_post(&sem_pro);//生产信号量加一
	}
}
void *proThread()
{
	while(1)
	{
		sem_wait(&sem_pro);
		sem_wait(&sem_store);
		store++;
		//slee(1);
		sem_post(&sem_store);
		sem_post(&sem_con);//消费信号量加一，通知消费者消费
	}
}




//=======================================================
//---------------- 三个进程的同步 -----------------------
//=======================================================
/*
有三个进程Producer，Transmitter，Consumer。
其中Producer负责将信息不断地输入ProduceBuf，
Transmitter负责从ProduceBuf取信息进行处理，
并将处理结果送至ConsumBuf，Consumer负责从ConsumBuf中读取结果。
（好像没有提每个Buf同一时刻只能有一个进程访问，反正我是默认了）。
假设ProduceBuf可以放12个信息，现在已经放了3个，ConsumBuf最多可放6个信息，
要求写出正确的同步互斥算法。 这个过程我认为关键在Transmiter这个进程，
如果ConsumBuf已经满了，不应从ProduceBuf里取信息，保证一旦从ProduceBuf
里取出信息那么就一定能放入ConsumBuf。
*/
PBufEmpty = 9; //ProduceBuf 可用数目
PBufFull = 3; //ProduceBuf 已用数目
CBufEmpty = 6; //ConsumBuf 可用数目
CBufFull = 0; //ConsumBuf 已用数目
PMutex = 1,
CMutex = 1;//控制资源互斥访问
void Produce()   //Producer 进程
{
    while(1)
    {
        P(PBufEmpty);//我要来存资源，有可用空间吗？
        P(PMutex);//我现在能访问PBuf吗？
            putPBuf();//有可用的空间，抢到了PBuf的访问权
        V(PMuxtex); //释放我的访问权
        V(PBufFull); //增加已用数目
    }
}

void Consumer()  //Consumer  进程
{
    while(1)
    {
        P(CBufFull);// 我要取资源，空间里有资源吗?
        P(CMutex);// 我现在能访问CBuf吗？
            getCBuf();// 空间有资源，抢到了CBuf的访问权
        V(CMutex);// 释放我的访问权
        V(PBufEmpty); // 增加可用空间的数目
    }
}

void Transmitter()  //Transmitter 进程
{
    while(1)
    {
        P(CBufEmpty); // 我要存资源，CBuf有剩余空间吗？(一旦有空间我就不担心了，因为剩余空间只会增多)
        P(PBufFull);// 我要取资源，PBuf里有资源吗？(一旦有资源我就不担心了，因为资源数只会增多)
        P(PMutex);// 很放心的来抢我的PBuf访问权。
            getPBuf(); //取出资源来
        V(PBufEmpty);// 增加可用空间
        V(PMutex);// 赶紧归还我的访问权  
        P(CMutex);// 很放心的来抢我的CBuf访问权。
            putCBuf();//放入资源
        V(CBufFull);// 增加资源数量
        V(CMutex);//归还我的访问权  
    }
}



//=======================================================
//----------- 线程同步: 条件变量方法 -------------------
//=======================================================

bool            	g_signaled  = false;	// （元素1：条件）
pthread_cond_t   	g_cond;					// （元素2：变量）
pthread_mutex_t  	g_mutex;				// （元素3：锁）

void thread_cond_wait() 
{  
    pthread_mutex_lock(&g_mutex);    
    while (!g_signaled)    
    {      
        pthread_cond_wait(&g_cond, &g_mutex);
    }
    //reset g_signaled if necessary.    
    g_signaled = false;    
    pthread_mutex_unlock(&g_mutex);  
}


void thread_cond_signal() 
{    
    pthread_mutex_lock(&g_mutex);   
    g_signaled = true; 
	pthread_cond_signal(&g_cond);     
    pthread_mutex_unlock(&g_mutex);    
}




//=======================================================
//---------------------- select示意版 -------------------
//=======================================================
int select_example(void)
 {
     sock_fd = socket(AF_INET, SOCK_STREAM, 0);
     bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr);
     listen(sock_fd, BACKLOG);
     fd_set fdsr;
     struct timeval tv;
     while (1) 
	 {
        FD_ZERO(&fdsr);
        FD_SET(sock_fd, &fdsr);//添加监听的sock_fd

        for (i = 0; i < BACKLOG; i++) //
		{
             if (fd_A[i] != 0) 
			 {
                 FD_SET(fd_A[i], &fdsr);
             }
         }

         ret = select(maxsock + 1, &fdsr, NULL, NULL, &tv);
         if (ret < 0) {
             perror("select");break;
         } else if (ret == 0) {
             printf("timeout\n");continue;
         }

        for (i = 0; i < conn_amount; i++) {//遍历fdset并读取数据。
             if (FD_ISSET(fd_A[i], &fdsr)) {
                 ret = recv(fd_A[i], buf, sizeof(buf), 0);
                 if (ret <= 0) {        // client close
                     close(fd_A[i]);
                     FD_CLR(fd_A[i], &fdsr);
                     fd_A[i] = 0;
                 }
             }
         }

         //新连接
        if (FD_ISSET(sock_fd, &fdsr)) {
             new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
             if (new_fd <= 0) {
                 perror("accept");continue;
             }

             fd_A[conn_amount++] = new_fd;
         }
     }//end while(1)
}



//=======================================================
//---------------------- select实例 -------------------
//=======================================================
/*
使用select函数可以以非阻塞的方式和多个socket通信。程序只是演示select函数的使用，功能非常简单，即使某个连接关闭以后也不会修改当前连接数，连接数达到最大值后会终止程序。
1. 程序使用了一个数组fd_A，通信开始后把需要通信的多个socket描述符都放入此数组。
2. 首先生成一个叫sock_fd的socket描述符，用于监听端口。
3. 将sock_fd和数组fd_A中不为0的描述符放入select将检查的集合fdsr。
4. 处理fdsr中可以接收数据的连接。如果是sock_fd，表明有新连接加入，将新加入连接的socket描述符放置到fd_A。
*/
#define MYPORT 1234    // the port users will be connecting to
#define BACKLOG 5     // how many pending connections queue will hold
#define BUF_SIZE 200

int fd_A[BACKLOG];    // accepted connection fd
int conn_amount;    // current connection amount

void showclient()
 {
     int i;
     printf("client amount: %d\n", conn_amount);
     for (i = 0; i < BACKLOG; i++) {
         printf("[%d]:%d  ", i, fd_A[i]);
     }
     printf("\n\n");
 }

int select_example(void)
 {
     int sock_fd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct sockaddr_in server_addr;    // server address information
    struct sockaddr_in client_addr; // connector's address information
    socklen_t sin_size;
     int yes = 1;
     char buf[BUF_SIZE];
     int ret;
     int i;

     if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
         perror("socket");
         exit(1);
     }

     if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
         perror("setsockopt");
         exit(1);
     }
     
     server_addr.sin_family = AF_INET;         // host byte order
    server_addr.sin_port = htons(MYPORT);     // short, network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

     if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
         perror("bind");
         exit(1);
     }

     if (listen(sock_fd, BACKLOG) == -1) {
         perror("listen");
         exit(1);
     }

     printf("listen port %d\n", MYPORT);

     fd_set fdsr;
     int maxsock;
     struct timeval tv;

     conn_amount = 0;
     sin_size = sizeof(client_addr);
     maxsock = sock_fd;
     while (1) 
	 {
         // initialize file descriptor set
        FD_ZERO(&fdsr);
         FD_SET(sock_fd, &fdsr);

         // timeout setting
        tv.tv_sec = 30;
         tv.tv_usec = 0;

         // add active connection to fd set
        for (i = 0; i < BACKLOG; i++) 
		{
             if (fd_A[i] != 0) {
                 FD_SET(fd_A[i], &fdsr);
             }
         }

         ret = select(maxsock + 1, &fdsr, NULL, NULL, &tv);
         if (ret < 0) {
             perror("select");
             break;
         } else if (ret == 0) {
             printf("timeout\n");
             continue;
         }

         // check every fd in the set
        for (i = 0; i < conn_amount; i++) {
             if (FD_ISSET(fd_A[i], &fdsr)) {
                 ret = recv(fd_A[i], buf, sizeof(buf), 0);
                 if (ret <= 0) {        // client close
                    printf("client[%d] close\n", i);
                     close(fd_A[i]);
                     FD_CLR(fd_A[i], &fdsr);
                     fd_A[i] = 0;
                 } else {        // receive val
                    if (ret < BUF_SIZE)
                         memset(&buf[ret], '\0', 1);
                     printf("client[%d] send:%s\n", i, buf);
                 }
             }
         }

         //新连接
        if (FD_ISSET(sock_fd, &fdsr)) {
             new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
             if (new_fd <= 0) {
                 perror("accept");
                 continue;
             }

             // add to fd queue
            if (conn_amount < BACKLOG) {
                 fd_A[conn_amount++] = new_fd;
                 printf("new connection client[%d] %s:%d\n", conn_amount,
                         inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                 if (new_fd > maxsock)
                     maxsock = new_fd;
             }
             else {
                 printf("max connections arrive, exit\n");
                 send(new_fd, "bye", 4, 0);
                 close(new_fd);
                 break;
             }
         }
         showclient();
     }

     // close other connections
    for (i = 0; i < BACKLOG; i++) {
         if (fd_A[i] != 0) {
             close(fd_A[i]);
         }
     }

     exit(0);
 }


//=======================================================
//---------------------- epoll实例 -------------------
//=======================================================
void epoll_example()
{
	
}

