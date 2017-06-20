#include <iostream>  
#include <cstring>  
#include <cerrno>  
  
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/mman.h>  
  
using namespace std;  
  
#define  PATH_NAME "/tmp/memmap"  
  
int main(int argc, char **argv)  
{  
    int fd;  
  
    fd = open(PATH_NAME, O_RDWR | O_CREAT, 0666);  
    if (fd < 0)  
    {  
        cout<<"open file "<<PATH_NAME<<" failed...";  
        cout<<strerror(errno)<<endl;  
        return -1;  
    }  
  
    if (ftruncate(fd, 5000) < 0)  
    {  
        cout<<"change file size  failed...";  
        cout<<strerror(errno)<<endl;  
          
        close(fd);  
        return -1;  
    }  
  
    char *memPtr;  
  
    memPtr = (char *)mmap(NULL, 5000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);  
    close(fd);  
  
    if (memPtr == MAP_FAILED)  
    {  
        cout<<"mmap failed..."<<strerror(errno)<<endl;  
        return -1;  
    }  

/*  
    cout<<"[0]:"<<(int)memPtr[0]<<endl;  
    cout<<"[4999]:"<<(int)memPtr[4999]<<endl;  
    cout<<"[5000]:"<<(int)memPtr[5000]<<endl;  
    cout<<"[8191]:"<<(int)memPtr[8191]<<endl;  
    cout<<"[8192]:"<<(int)memPtr[8192]<<endl;  
    cout<<"[4096 * 3 - 1]:"<<(int)memPtr[4096 * 3 - 1]<<endl;  
    cout<<"[4096 * 3]:"<<(int)memPtr[4096 * 3]<<endl;  
 */     
	pause();
    return 0;  
}  
