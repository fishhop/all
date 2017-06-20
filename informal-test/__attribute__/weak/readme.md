###文件组织，方式1： 

    weak.c ：强符号文件  
    weak.h ：内部定义弱符号函数  
    main.c ：调用文件，需#include "weak.h"  
>$ g++ main.cpp weak.cpp

注意:   
weak.c中不可以include包含弱符号的头文件（即不可以include weak.h）

###文件组织，方式2： 

    weak.c ：强符号文件  
    main.c ：调用文件，内部定义弱符号函数  

###注意
详见我的doc说明