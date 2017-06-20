#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/kernel.h> 
#include <linux/fs.h> 
#include <linux/interrupt.h> 

static struct tasklet_struct my_tasklet;    

	//1. tasklet处理函数  
static void tasklet_handler (unsigned long data)  
{
	printk(KERN_ALERT "tasklet_handler is running.\n");  
}
static int _init demo_init(void)
{
	//2. 创建tasklet，动态创建而不是静态创建
	tasklet_init(&my_tasklet, tasklet_handler,0);  

	//3. 调度tasklet,即:把my_tasklet标记为pending(挂起),以便在do_softirq()中得到执行。
	tasklet_schedule(&my_tasklet);  
	printk(KERN_ALERT "demo_init.\n");  
	return 0;
}
 
static void _exit demo_exit(void)  
{
	//4. 动态销毁tasklet
	tasklet_kill(&my_tasklet);
	printk(KERN_ALERT "demo_exit.\n");
}
MODULE_LICENSE("GPL");
module_init(demo_init);
module_exit(demo_exit);
