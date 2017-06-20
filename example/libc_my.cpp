/*
C标准库本来就没检查这些的 所以微软才自己搞了一套 xxx_s(即这些函数的safe版)
C里的很多字符串函数都是不保证不越界的，因为额外的规定会增加复杂性和不可移植性。
ansi c, 标准C的一些源码:
http://read.pudn.com/downloads17/doc/61824/ansi/strcpy.c__.htm
*/
#include <iostream>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <errno.h>  
using namespace std;  

//assert(expression):断言expression 成立（真），并往后执行。假则abort。

/*
【注意】
	1.这个文件中的函数尽量不要有很多函数的彼此调用，会降低执行效率
	2.测试用例:
		a.两个str同长，相等；
		b.一个str个数少于另一个
		c.<=号

*/

inline bool isspace(char c)
{
	return c == '\t' ||
		   c == ' '  ||
		   c == '\n';
}

//知识点:这种小函数用inline，高效
inline char tolower(char c)  
{  
    return (c >= 'A' && c <= 'Z') ? ('a' + c - 'A') : c;  
}  


int atoi(const char *s)
{
	if(!s)
		return 0;
	const long long max_int = 0x7fffffff;
	const long long min_int = (-0x7fffffff-1);

	int sign = 1;
	if(*s == '-')
	{
		sign = -1;
		++s;
	}
		
	long long res = 0;					//注意 long long
	for(; *s >= '0' && *s <= '9'; ++s )	//不必考虑'\0'，因为满足这里的范围已经不含'\0'的
	{
		res = res * 10 + (*s - '0');
		
		if(sign * res >= max_int)
			return max_int;
		if(sign * res <= min_int)
			return min_int;
	}
	return (int)((sign * res));			//注意强制转换
}

//itoa并不是一个标准的C函数，它是Windows特有的
void itoa(int val, char *str)  
{
	if(!str)
		return;
	int power = 1;
	if(val < 0)
	{
		val = -val;						//全部转为正数
		*str++ = '-';
	}
	for(int i = val; i > 10; i /= 10) 	//用另一个变量i来迭代
		power *= 10; 					//求数量级,如:10000
	for(; power > 0; power /= 10)
	{
		*str++ = '0' + val / power;
		val %= power;					//val去掉高位
	}
	*str = '\0';
}


//16进制字符串转10进制整数
//注意不要忘记大写情况
//可以考虑溢出的情况，负号负数
int htoi(const char *s)				//注意:const
{
	if(!s)
		return 0;
	int i = 0;
	int n = 0;
	if (s[0] == '0' && (s[1]=='x' || s[1]=='X'))
		i = 2;
	for (; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >='A' && s[i] <= 'F');++i)
	{
		if (tolower(s[i]) > '9')
			n = 16 * n + (10 + tolower(s[i]) - 'a');
		else
			n = 16 * n + (tolower(s[i]) - '0');
	}
	return n;
}

void * memcpy(void *s1, void *s2, size_t n)
{
	if(!s1 || !s2 || !n) 
		return s1;							//若n为0，返回s1，比返回NULL更有意义
	
	char *d = (char *)s1;					//c++中需要强转之后再赋值，
	char *s = (char *)s2;

	while(n)	
	{
		*d++ = *s++;
		--n;
	}

	return s1;
}


/*
http://blog.chinaunix.net/uid-22780578-id-3346391.html
memmove考虑重叠，而memcpy不考虑
char s[] = "1234567890";//注:即使是在栈中，s数组也是从低往高增长的。
char* p1 = s;
char* p2 = s+2;
*/
void * memmove(void *s1, void *s2, size_t n)
{
	if(!s1 || !s2 || !n)
		return s1;
	
	char *d = (char *)s1;		//若不强转，会报错
	char *s = (char *)s2;

	if(d > s)						//(s.....[d.....)........]
	{
		while(n)
		{
			--n;
			d[n] = s[n];			//从后边往前面赋值
		}
	}
	else
	{
		while(n)
		{
			*d++ = *s++;
			--n;
		}
	}
	return s1;
}

 

void * memset(void *s1, int c, size_t n)	//注意:返回值为void *
{
	if(!s1 || !n)
		return s1;
	
	char *c1 = (char *)s1;				

	while(n--)
		*c1++ = (char)c;   			//*tmp++ = (unsigned char )c;//不加括号会报错!!
	
	return s1;
}

int memcmp(void *dst, void *src, size_t n)
{
	if(!n || !dst || !src)//NULL指针不可以应用 *p,返回0不妥
		return -2;
	
	char *d = (char *)dst;
	char *s = (char *)src;
	
	while(n)
	{
		if(*d != *s)							
			return (*d < *s) ? -1 : 1;
		++d;
		++s;
		--n;
	}
	return 0;
}

/*finds the start of the first occurrence of the substring needle 
of length needlelen in the memory area haystack of length*/
void *memmem(void *s1, size_t n1, void *s2, size_t n2)
{
	if(!s1 || !n1 || !s2 || !n2)
		return NULL;
	size_t x1 = 0, x2 = 0;
	char * c1 = (char *)s1, *c2 = (char *)s2;
	while(x1 <= n1 - n2)						//这里可以=
	{
		x2 = 0;
		while(x2 < n2 && c1[x1 + x2] == c2[x2])
			++x2;
		if(x2 == n2)
			return (void *)(&c1[x1]);
		++x1;
	}
	return NULL;
}

/** 
 * memscan - Find a character in an area of memory. 
 * @addr: The memory area 
 * @c: The byte to search for 
 * @size: The size of the area. 
 * 
 * returns the address of the first occurrence of @c, or 1 byte past 
 * the area if @c is not found 
 */  
void *memscan(void *s1, int c, size_t n)
{
	if(!s1 || n < 1)
		return NULL;
	
	char *c1 = (char *)s1;		//signed或unsigned没关系，只要*s1 和 c一致就OK
	while(n)
	{
		if(*c1 == (char)c)
			return (void *)c1;
		++c1;
		--n;
	}
	return (void *)(++c1);	//没找到则返回末尾的下一个字节
}

void *memchr(void *s1, int c, size_t n)
{
	if(!s1 || !n)
		return NULL;
	
	char *c1 = (char *)s1;
	while(n)
	{
		if(*c1 == (char)c)
			return (void *)c1;
		++c1;
		--n;
	}
	return NULL;
}


/*find the last occurrence of a byte in a memory block*/
void *memrchr(void *s1, int c, size_t n)
{
	if(!s1 || !n)
		return NULL;
	char *c1 = (char *)s1;
	while(n)
	{
		--n;
		if(c1[n] == (char)c)
			return (void *)(&c1[n]);
	}
	return NULL;
}

/*
OK too:

void *memrchr(void *s1, int c, size_t n)
{
	if(!s1 && !n)
		return NULL;
	char *c1 = (char *)s1 + n - 1;
	while(c1 >= (char *)s1)
	{
		if(*c1 == (char)c)
			return (void *)c1;
		--c1;
	}
	return NULL;
}
*/


char *strcat(char *dst, const char *src)
{
	if(!dst || !src)
		return NULL;
	char *d = dst;

	while(*d )
		++d;

	while(*src)				//【知识点】如下所述,所以注意:在while中带有++,--的赋值，放在条件处和循环里不一样!!!
		*d++ = *src++;

	*d = '\0';			//将src的'\0'也要拷贝过来;如果while(*tmp++ = *src++)，则这里可以省去，因为while中最后一步会拷贝'\0'
	return dst;
}


/*如果提前遇到'\0'，则后面不管了*/
char *strncat(char *dst, const char *src, size_t n)  
{  
  	if(!dst || !src || !n)
		return NULL;
    char *d = dst;  
    while(*d)  
        ++d;  
	while(*src && n)
	{
		*d++ = *src++;
		--n;
	}
	
	*d = '\0';
    return dst;  
}  


//因为dst可能是数组等，所以无需考虑其大小
char *strcpy(char *dst, const char *src)
{
	if(!dst || !src)
		return NULL;
	char *d = dst;
	while(*src)
		*d++ = *src++;
	
	*d = '\0';				//将src的'\0'也要拷贝过来
	return dst;
}


//和strncat不同，这里要完整的拷贝n个，不够补'\0'
char *strncpy(char *dst, const char *src, size_t n)
{
	if(!dst || !src || !n)
		return NULL;
	char *d = dst;
	while(n)
	{			
		*d++ = *src;	//如果src长度不够n个，则之后的每一个位置都填充为'\0'
		if(*src)
			++src;
		--n;
	}											//最后不用*d = '\0';	标准源码中无此处理
	return dst;
}
/*
百度文库:用C语言实现strcpy,strncpy,strcat,strcmp,strlen函数
http://blog.csdn.net/lsxk2008/article/details/5422748
http://blog.chinaunix.net/uid-20788636-id-1841351.html
*/

size_t strlen(const char *s)
{
	if(!s)
		return 0;
	
	char *p = (char *)s;			//注意:必须在此处定义，尤其是for循环中，不要错将变量定义在for(中)
	while(*p)					//注意2:上面要是const char *p,不然编译警告
		++p;
	return p - s;
}


/** 
 * strnlen - Find the length of a length-limited string 
 * @s: The string to be sized 
 * @count: The maximum number of bytes to search 
 */  
size_t strnlen(const char *s, size_t n)  
{  
	if(!s || !n)			//必须要有此，因为不能对NULL指针进行*p操作。
		return 0;
	
	const char *p = s;		
	while(*p && n)			//注意2:上面要是const char *p,不然编译警告
	{
		++p;
		--n;
	}
	return p - s;
}  


/*find the first match*/
char *strchr(const char *s, int c)
{
	if(!s)
		return NULL;
	
	while(*s)
	{
		if(*s == (char)c)
			return (char *)s;	//注意这里要强转,将const转为非const
		++s;
	}
	return NULL;
}


/*find the last match*/
char *strrchr(const char *s, int c)
{
	if(!s)
		return NULL;
	int n = strlen(s);
	while(n)
	{
		--n;
		if(s[n] == (char)c)
			return (char *)(&s[n]);
	}
	return NULL;
}


char *strnchr(const char *s, int c, size_t n)
{
	if(!s || !n)
		return NULL;
	while(n && *s)
	{
		if(*s == (char)c)
			return (char *)s;
		++s;
		--n;
	}
	return NULL;
}

//判断字符串src是否是dst的子串。



char *strstr(const char *dst, const char *src)
{
	if(!dst || !src)
		return NULL;
	
	int n1 = strlen(dst);
	int n2 = strlen(src);
	int x1 = 0, x2 = 0;
	while(x1 <= n1 - n2)
	{
		x2 = 0;
		while(x2 < n2 && dst[x1+x2] == src[x2])
			++x2;
		if(x2 == n2)
			return (char *)(&dst[x1]);
		++x1;
	}
	return NULL;
}


/*
//注意:下面的方法中，不完善:当dst的剩余长度小于src时其实是不必比较的，
char *strstr(const char *dst, const char *src)
{
	if(!dst && !src)
		return NULL;
	const char *d = dst;
	const char *s = src;

	if(!*s)						//注意:src为空时，要返回dst；
		return (char *)dst;

	while(*dst)
	{
		d = dst;
		s = src;
		while(*s && *d && *s == *d)
		{
			++s;
			++d;
		}
		if(!*s)
			return (char *)dst;	//勿丢强转(char *)
		++dst;					//这里也可以判断*d，提前返回，但是每次判断*d，也影响效率
	}
	return NULL;

}
*/


/** 
 * strnstr - Find the first substring in a length-limited string 
 * @s1: The string to be searched 
 * @s2: The string to search for 
 * @len: the maximum number of characters to search 
 */  
char *strnstr(const char *dst, const char *src, size_t n)
{
	if(!dst || !src)
		return NULL;
	
	size_t n1 = strlen(dst);
	size_t n2 = strlen(src);
	size_t x1 = 0, x2 = 0;
	while(x1 <= n1 - n2 && n >= n2)
	{
		x2 = 0;
		while(x2 < n2 && dst[x1+x2] == src[x2])
			++x2;
		if(x2 == n2)
			return (char *)(&dst[x1]);
		++x1;
		--n;
	}
	return NULL;
}


int strcmp(const char *s1, const char *s2)
{
	if(!s1 || !s2)
		return 0;
	while(*s1 && *s2)
	{
		if(*s1 != *s2)
			return *s1 > *s2 ? 1 : -1;
		++s1;
		++s2;
	}
	if(*s1)
		return 1;
	if(*s2)
		return -1;
	return 0;
}


int strncmp(const char *s1, const char *s2, size_t n)
{
	if(!s1 || !s2)
		return 0;
	while(*s1 && *s2 && n)
	{
		if(*s1 != *s2)
			return *s1 > *s2 ? 1 : -1;
		++s1;
		++s2;
		--n;
	}
	if(n)
	{
		if(*s1)
			return 1;
		if(*s2)
			return -1;		
	}
	return 0;
}


/*

【错误1】举例:while 后不能n--，这样n=0时，到return那里时，n已经是-1了!!!!
int strncmp(const char *s1, const char *s2, size_t n)
{
	assert(s1 && s2 && n);
	while(n-- && *s1 == *s2 && *s1 != '\0')
	{
		++s1;
		++s2;
	}
	return (n==0) ? 0 : (*s1 < *s2 ? -1 : 1);
}

【错误2】不可以 (n == -1) ? ... , 因为 n 为size_t，是非负数的。

*/


int strcasecmp(const char *s1, const char *s2)  
{  
	if(!s1 || !s2)
		return 0;
	while(*s1 && *s2)
	{
		if(tolower(*s1) != tolower(*s2))
			return tolower(*s1) < tolower(*s2) ? -1 : 1;
		++s1;
		++s2;
	}
	if(*s1)
		return 1;
	if(*s2)
		return -1;
	return 0;

}  

int strncasecmp(const char *s1, const char *s2, size_t n)
{
	if(!s1 || !s2)
		return 0;
	while(*s1 && *s2 && n)
	{
		if(tolower(*s1) != tolower(*s2))
			return tolower(*s1) < tolower(*s2) ? -1 : 1;
		++s1;
		++s2;
		--n;
	}
	if(n)
	{
		if(*s1)
			return 1;
		if(*s2)
			return -1;		
	}
	return 0;
}
/*
1. 因为大小写字母都在127范围内，所以上面不必强转为(unsigned char *)

【错误1】
while (n && ((*s1 == *s2) || (tolower(*s1) == tolower(*s2)))) 
//注意:别在这里用后缀表达式--或++，由于短路原则有可能会执行不到


【错误2】不能再while中++，这样之后，return那里比较的是下一个s1和s2了!

	while(n && *s1 && tolower(*s1++) == tolower(*s2++))
		--n;

	return !n ? 0 : (tolower(*s1) < tolower(*s2) ? -1 : 1);

*/

/*skip the space at the head*/
char *skip_space(const char *s)
{
	if(!s)
		return NULL;
	while(*s && isspace(*s))
		++s;
	return (char *)s;		
}

/** 
 * strim - Removes leading and trailing whitespace from @s. 
	注意:中间有空格的情况
 */  
char *strim(char *s)
{
	if(!s)
		return NULL;
	
	while(*s && isspace(*s))
		++s;
	if(!strlen(s))
		return s;	
	char *h = s;
	s += strlen(s) - 1;
	while((s > h) && isspace(*s))
		--s;
	*(s + 1) = '\0';
	
	return h;
}


/** 
 * strspn - Calculate the length of the initial substring of @s which only contain letters in @accept 
 * @s: The string to be searched 
 * @accept: The string to search for 
 */  
/** 
函数说明 strspn()从参数s 字符串的开头计算连续的字符，
而这些字符都完全是accept 所指字符串中的字符。简单的说，若strspn()返回的数值为n，
则代表字符串s 开头连续有n 个字符都是属于字符串accept内的字符。
 */  
size_t strspn(const char *s, const char *accept)  
{  
	if(!s || !accept)
		return 0;
    const char *p = s, *a;  

	while(*s)
	{
		a = accept;
		while(*a && *a != *s)
			++a;
		if(!*a)		
			return s - p;
		++s;
	}
	return s - p;

}  


size_t strcspn(const char *s, const char *reject)  
{  
	if(!s || !reject)
		return 0;
    const char *p = s, *r = reject;

	while(*s)
	{
		r = reject;
		while(*r && *s != *r)
			++r;
		if(*r)					//和上面的strspn差别在这里
			return s-p;
		++s;
	}
	return s-p;
}  


/*strpbrk是在源字符串（s1）中找出最先含有搜索字符串（s2）
中任一字符的位置并返回，若找不到则返回空指针。*/
char *strpbrk(const char *s1, const char *s2)
{
	if(!s1 || !s2)
		return NULL;
	const char *c2 = s2;

	while(*s1)
	{
		c2 = s2;
		while(*c2 && *s1 != *c2)
			++c2;
		if(*c2)
			return (char *)s1;
		++s1;
	}
	return NULL;
}


#define __NO__SEE__


/*
s1为指向欲分割的字符串，
s2为分隔符，函数将返回分隔符前面的字符串，
s1将指向分隔符之后的字符串
*/
char *strsep(char **s1, const char *s2)
{
	if(!s1 && !s2)
		return NULL;
	char *ret = *s1;
	char *c1 = NULL;

	if(!*s1)
		return NULL;
		
	c1 = strpbrk(*s1, s2);
	if(c1)
		*c1 = '\0';
	*s1 = ++c1;
	return ret;
	
}


/*可重入版本
http://www.cnblogs.com/longzhao1234/archive/2012/05/31/2528317.html
strtok()用来将字符串分割成一个个片段。参数s 指向欲分割的字符串，
参数delim 则为分割字符串，当strtok()在参数s 的字符串中发现到参数delim 
的分割字符时则会将该字符改为\0 字符。在第一次调用时，strtok()必需给予参数s 
字符串，往后的调用则将参数s 设置成NULL。每次调用成功则返回下一个分割后的字符串指针。
*/
char *strtok_r(char * s1, const char * s2, char ** next_start)
{
	if(!s1 || !s2 || !next_start)
		return NULL;
	char *s, *p;
	
	s = s1;
	if (!s) 
		s = *next_start;

	if(s)
	{
		s = s + strspn(s, s2);
		if(*s)
		{
			p = s + strcspn(s, s2);
			if(*p)
				*p++ = 0;
			*next_start = p;
			return s;		
		}
	}
	
	return NULL;
}

/*strtok内部记录上次调用字符串的位置，所以不支持多线程，可重入版本为strtok_r*/
char *strtok(char * s1, const char * s2)
{
	static char *next_start;	/* Initialized to 0 since in bss. */
	return strtok_r(s1, s2, &next_start);
}

char *stndup(const char *s, size_t n)
{
	if(!s)
		return NULL;
	size_t len = strnlen(s, n);
	char *p = (char *)malloc(len + 1);
	if(!p)
		return NULL;
	memcpy(p, s, len);
	*(p+len) = '\0';
	return p;
}

 
#define __TEST__CASE__

void memcpy_my_test()
{
    char s[] = {1,2,3,4,5};
	char d[10] = {};
	memcpy(d, s, sizeof(s));		//	memcpy(d, s, 5);//注意:这里并不是5!!!不是5个字节，单位是字节

	for(int i =0; i < 10; ++i)
		cout << (int)d[i] << endl;
}

void memmove_my_test()
{
    char s[] = {1,2,3,4,5,6};
	for(int i =0; i < 6; ++i)
		cout << s[i]+0 << endl;	
	cout << "after move:" << endl;
	
	memmove(s-2, s, 4);
	for(int i =0; i < 6; ++i)
		cout << s[i]+0  << endl;	//+0使得转换为数字，而不是assc码
}
/*
char c=2;
cout<<c<<endl;控制台没输出任何内容-------->这是因为assic码值2在你的系统是一个不可见字符
cout<<c+0<<endl;控制台可以输出2。------>这是隐式类型转换的原因，c+0是一个int值，所以输出为int值2了
*/

void strcat_test()  
{  
        char str[10] = "abc";
		const char *str1 = "defg"; 		//这里要定义为const !!!!
		
        cout << strcat(str, str1) << endl;  
}  

void strncat_test(size_t n)  
{  
        char str[10] = "abc";
		const char *str1 = "defg"; 		//这里要定义为const !!!!

        cout << strncat(str, str1, n ) << endl;  
}  
void strcpy_test()  
{  
        char str[10] = "abc";
		const char *str1 = "defg"; 		//这里要定义为const !!!!
		
        strcpy(str, str1);  
        cout << str << endl;  
}  

void strncpy_test()  
{  
        char str[10] = "abc";
		const char *str1 = "defg"; 		//这里要定义为const !!!!
		
        strncpy(str, str1, 6);  
        cout << str << endl;  
}  

void strcmp_test()  
{  
        char str[10] = "abc";
		const char *str1 = "ab"; 		//这里要定义为const !!!!
		
        cout << strcmp(str, str1) << endl;  
}  

void strncmp_test(int n)  
{  
        char str[10] = "abc";
		const char *str1 = "ab"; 		//这里要定义为const !!!!
		
        cout << strncmp(str, str1, n) << endl;  
}  

void strchr_test(int n)  
{  
        char str[10] = "abc";
		char c = '\0'; 		//这里要定义为const !!!!
		
        cout << strchr(str, c) << endl;  
}  


void strrchr_test(int n)  
{  
        char str[10] = "asdbgfbc";
		char c = 'c'; 		//这里要定义为const !!!!
		
        cout << strrchr(str, c) << endl;  
}  

void strnchr_test(int n)  
{  
        char str[10] = "adfbc";
		char c = 'b'; 		//这里要定义为const !!!!
		
        cout << strnchr(str, c, n) << endl;  
}  


void strlen_test()  
{  
        char str[10] = "abc";
		
        cout << strlen(str) << endl;  
}  

void strim_test()  
{  
        char str[10] = " ab c  ";
        cout << strim(str) << "|<---"<< endl;  
		
        char str1[10] = " ab c";
        cout << strim(str1) << "|<---"<< endl;  
		
        char str2[10] = " ";
        cout << strim(str2) << "|<---"<< endl;  
}  


void strspn_test()  
{  
        const char* s1 = "ab";
        const char* s2 = "abb";
		
        cout << strspn(s1, s2) << endl;  
}  


void strcspn_test()  
{  
        const char* s1 = "asfdbcdefegd";
        const char* s2 = "bd";
		
        cout << strcspn(s1, s2) << endl;  
}  


void strpbrk_test()  
{  
        const char* s1 = "asfdbcdefegd";
        const char* s2 = "bd";
		
        cout << strpbrk(s1, s2) << endl;  
}  

void strstr_test()
{
	const char *str = "A man cacna";
	
//	cout << strstr(str, "xx") <<endl;
//	cout << strstr(str, NULL) <<endl;
//	cout << strstr(NULL, "an ") <<endl;	
//	cout << strstr(str, "cn") <<endl;	
	cout << strstr(str, "na") <<endl;	
}

void strnstr_test(int n)
{
	const char *str = "abcd";
	const char *str1 = "bc";
	const char *tmp = strnstr(str, str1, 3) ;

	if(tmp == nullptr)
	{
		cout << "Not matched!" << endl;
		exit(0);
	}
	cout << tmp << endl;
}


void strsep_test()
{

    char token[] ="abdzxbcdefgh";
	printf("%s\n",token);
	char *tokenremain = token;
	char *tok1 = strsep(&tokenremain,"cde");
	printf("tok1:%s,token:%s\n",tok1,tokenremain);
	tok1 = strsep(&tokenremain,"cde");                                                                  
	printf("tok1:%s,token:%s\n",tok1,tokenremain);

}

void strtok_test()
{

    char token[] ="abdczxbcdefgh";
    printf("%s\n",token);
    char *tokenremain = token;
    char *tok1 = strtok(tokenremain,"cde");
    printf("tok1:%s\n",tok1);
//    tok1 = strtok(NULL,"cde");                                                                          
    printf("tok1:%s\n",tok1);

}
/*
[root@ test]# ./strtok 
abdczxbcdefgh
tok1:ab
tok1:zxb
*/

void atoi_my_test()
{
	const char *str = "234999999999999";
	string str1 = "111";
	
	cout << atoi(str) << endl;
}

void itoa_test()  
{  
        char *str = new char[10];  
        itoa(1, str);  
        cout << str << endl;  
}  



#define __NO__SEE__
#define __NO__SEE__
#define __NO__SEE__

//----------------------------以下暂时忽略-----------------------------------


/*
以下用于测试unsigned char * 和signed char *的区别

signed char取值范围是 -128 到 127
unsigned char 取值范围是 0 到 255
即便是同样的字节内容，但是两者判等的结果不同!

所以当向memchr(const void *s, int c, size_t n)
中的c 传入值如255时，对于负数不同的转换是不同的结果!
而这几个有int参数的函数，既然传入是int，那就是可以正负，
那干脆一律以有符号的char 对待，且我的/lib/string.c里也是以char对待。
*/
void mecp(void *s, int c)
{
	char *ss = (char *)s;
	
	printf("mecp:%d, %d\n", *ss, c);
	if(*ss == c)
		printf("==\n");
	else
		printf("!=\n");

}
void mecp_u(void *s, int c)
{
	unsigned char *ss = (unsigned char *)s;
	
	printf("mecp_u:%d, %d\n", *ss, c);
	if(*ss == c)
		printf("==\n");
	else
		printf("!=\n");

}
int test_uc_c()
{
	int i = 122;
	signed char c = (char)i;

	mecp(&c, 200);
	c = 200;
	mecp(&c, 200);

	mecp_u(&c, 200);

	unsigned char uc1 = -1;		//将-1赋给unsigned类型，相当于给该变量赋unsigned的最大值
	cout << "(int)uc1: " << (int)uc1 << endl;


	unsigned short us = -1;		//将-1赋给unsigned类型，相当于给该变量赋unsigned的最大值
	//对比1:用(short)强转,同等长度的类型强转
	cout<< "(short)us: " << (short)us << endl;	//结果: -1
	//对比1:用(int)强转，用高一级的类型强转
	cout<< "(int)us: " << (int)us << endl;		//结果: 65535(最大的unsigned short)
	
	
	unsigned int uc2 = -1;		//将-1赋给unsigned类型，相当于给该变量赋unsigned的最大值
	cout << (long long)uc2 << endl;

	unsigned long long ull = -1;		//将-1赋给unsigned类型，相当于给该变量赋unsigned的最大值
	cout << (unsigned long long)ull << endl;

	unsigned int ui = 0;
	cout << ui << endl;			//结果:0
	cout << --ui << endl;		//结果:4294967295,
	//错误的想法:原以为while(ui--)会导致再运行一轮(max size_t 次)，其实只有while(--ui)会出错，因为0--依然是0




	//测试大类型转换到小类型
	/*
	知识点:要看一个负数的值是多少，要转换为补码。
	原码->补码:对于负数，符号位不变，其他位取反，之后加一
	*/
	int i2 = 32780;
	short c2 = (short)i2;
	cout << c2 << endl;			//结果:-32756
	unsigned short us2 = (unsigned short)i2;
	cout << us2 << endl;		//32780
	cout << hex << i2 << " " << c2 << " "  << us2 << endl;
	/*结果:
	-32756
	32780
	800c 800c 800c
	*/
	
	return 0;
}/*
argc:1
mecp:122, 200
!=
mecp:-56, 200
!=
mecp_u:200, 200
==
(int)uc1: 255
(short)us: -1
(int)us: 65535
4294967295
18446744073709551615
0
4294967295
*/



int main(int argc, char ** argv)
{
	int n = 1;
	if(argc != 1)
		n = atoi(argv[1]);
	cout << "argc:" << n << endl;
//	memcpy_my_test();
//	memmove_my_test();
//	atoi_my_test();

//	strcat_test();
//	strncat_test(6);

//	strcpy_test();  
//	strncpy_test();  

//	strcmp_test();  

//	strlen_test();  

//	itoa_test();  
//	cout << htoi("0xff");

//	strncmp_test(n);
//	strchr_test(n) ;
//	strrchr_test(3);
//	strnchr_test(n);
	strim_test();
//	strspn_test();
//	strcspn_test();
//	strpbrk_test() ;
//	strsep_test();
//	strstr_test();
//	strnstr_test(5);
//	strtok_test();

//	cout << strncasecmp("Abad", "AbadD", 4) << endl;
//	cout << strcasecmp("Aa", "") << endl;

//	cout << strcmp("abhi", "abh") << endl;
//	test_uc_c();

//	char a1[]={1,2,3,4,5}, a2[] = {1,2,4};
//	cout <<(int)a1 << " , " <<(int)memmem(a1, 4, a2, n) << endl;

//	char a1[]={1,2,3,4,200};
//	cout <<(int)a1 << " , " <<(int)memchr(a1, 200, n) << endl;

//	char a1[]={1,2,3,4,5,3};
//	cout <<(int)a1 << " , " <<(int)memrchr(a1, 3, 6) << endl;

//	char a1[5] = {0};
//	memset(a1, 1, 5);
//	cout << strnlen(a1, n) << endl;

//	cout << strchr("", 'c') << endl;
//	cout << strrchr("safds", 's') << endl;
//	cout << strnchr("safds", 'd', n) << endl;

//	cout << strcmp("", "s") << endl;
//	cout << strncmp("abCDe", "abCDE", 5) << endl;
	
//	cout << strcasecmp("abc", "aB") << endl;
//	cout << strncasecmp("abc", "", n) << endl;

//	char str[] = "  ab  c  ";
//	cout << strim(str) << "|<"<< endl;

	//下面错误，因为"  ab  c  "是const，不能对齐修改，上面的数组才可以。
//	cout << strim("  ab  c  ") << "|<"<< endl;

//	cout << strspn("abbbcd", "ab" ) << endl;
//	cout << strcspn("abbbcd", "c" ) << endl;
//	cout << strpbrk("abbbcd", "bb" ) << endl;
//	cout << strpbrk("abbbcd", "bb" ) << endl;
//	cout << strstr("abbbcd", "abbbcd" ) << endl;
	
	
	return 0;
}

