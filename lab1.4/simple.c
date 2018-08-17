#include <linux/init.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/utsname.h>

struct Student {
	int ID;
	char* name;
	int age;

};
int nextStudent=0;
struct Student students[10];

// Custom functions.
void uptime(void);
void getSystemInfo(void);
void add(int, char*, int);
void list(void);

// This function is called when the module is loaded.
int simple_init(void)
{
       printk(KERN_INFO "Loading Module by Karol!\n");
       uptime();
       getSystemInfo();
       add(1, "Karol", 20);
       add(2, "Amanda", 16);
       add(3, "Juan", 14);
       list();
       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "The module was removed by Karol!\n");
}

// This functions gets the uptime
void uptime() {
  printk("Uptime: %i\n", jiffies_to_msecs(get_jiffies_64())/1000);
}

// This function gets the general system information
void getSystemInfo(){  
  struct new_utsname *buf;
  buf = utsname();

  printk("Nodename: %s\n",buf->nodename);
  printk("Machine: %s\n",buf->machine);
  printk("Sysname: %s\n",buf->sysname);
  printk("Release: %s\n",buf->release);
  printk("Version: %s\n",buf->version);
#ifdef __linux__
  printk("Domain Name: %s\n", buf->domainname); // GNU extension
#endif
}

// This function adds an student to the array
void add(int id, char* newname, int a){
	students[nextStudent].ID=id;
	students[nextStudent].name=newname;
	students[nextStudent].age=a;
	nextStudent++;
}

// This function lists all the students
void list(void){
    	int i=0;
	printk("Listing all students: \n");
    	for(i; i<nextStudent; i++){
        	printk("    ID: %u, Name: %s, Age: %u years\n", students[i].ID, students[i].name, students[i].age);
    	}
	printk("Done! \n");
}


/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

