
#ifdef __KERNEL__
	#pragma message("定义了: __KERNEL__")
	#include <linux/list.h>		//【beta】include会报各种错，用户态使用，一般要移植到另一个my_list.h，之后再include
	#include <linux/mm.h>
#else
	#pragma message("没有定义: __KERNEL__")
#endif

#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "hello" << std::endl;
	return 0;
}
