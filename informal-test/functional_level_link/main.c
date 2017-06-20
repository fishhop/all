#include <stdio.h>
#include "fun1.h"


int main(int argc, const char *argv[])
{
    fun1_0();
    printf("file:%s\tfunc:%s\n", __FILE__, __FUNCTION__);
    return 0;
}