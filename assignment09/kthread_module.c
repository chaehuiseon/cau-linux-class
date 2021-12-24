#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/delay.h>

 
int test_thread(void * _arg){

    

    int* arg =(int*)_arg;

    printk("argument: %d \n", *arg);
    kfree(arg);

    return 0;

}

 

void thread_create(void){

    int i;

    // thread create
    for(i = 0; i<10; i++){

        int* arg =(int*)kmalloc(sizeof(int), GFP_KERNEL);
        *arg = i;
        kthread_run(&test_thread, (void*)arg, "test_thread");

	}

}

 
int __init kernel_module_init(void){

    printk("hello module : 20185542 chae hui seon \n");

    thread_create();

    

    return 0;

}

 

void __exit kernel_module_cleanup(void){

    printk("bye module : 20185542 Chae Hui Seon \n");

}

 
module_init(kernel_module_init);
module_exit(kernel_module_cleanup);
MODULE_LICENSE("GPL");
