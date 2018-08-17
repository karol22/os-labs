#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <stdio.h>
#include <unistd.h>
#include <system/utsname.h>


long getUptime(){
	struct sysinfo s_info;
	return s_info.uptime;
}

/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module by Karol\n");
       printk(KERN_INFO "The module was initialized by Karol!\n");
       printk(KERN_INFO "Uptime: %ld\n", getUptime());
       

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
	printk(KERN_INFO "The module was removed by Karol!\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

