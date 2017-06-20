#include <iostream>
#include "weak.h"

int fun1 (int i) __attribute__ ((weak));

int main(int argc, char** argv)
{

	if(!fun) 
	{
		std::cout << "strong fun is not defined! " << std::endl;
	}
	else//只有在有强符号时次函数才被定义
		fun(5);
	
	if(!fun1) 
		std::cout << "strong fun1 is not defined! " << std::endl;

	return 0;
}
