#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/list.h>
#include <linux/time.h>
#include <linux/ktime.h>
#include <linux/mutex.h>

#define NODECOUNT 100000
int counter;
struct mutex my_mutex;
struct task_struct *writer_thread1, *writer_thread2, *writer_thread3, *writer_thread4;
struct my_node {
    struct list_head list;
    int data;
};

ktime_t start, end, delta;
struct list_head my_list;
struct my_node *current_node;
struct my_node *tmp;

static int insert_list(void *data){

    int i;

    while(!kthread_should_stop()){
        mutex_lock(&my_mutex);
        counter++;
        

        INIT_LIST_HEAD(&my_list);
        for(i =0; i < NODECOUNT; i++){

            struct my_node *new = kmalloc(sizeof(struct my_node), GFP_KERNEL);
            new->data = i;
            list_add(&new->list, &my_list);
        }
        mutex_unlock(&my_mutex);
        msleep(200);
    }
    do_exit(0);
}

static int search_list(void *data){
    while(!kthread_should_stop()){
        mutex_lock(&my_mutex);
        counter++;
        list_for_each_entry(current_node, &my_list, list){}
        mutex_unlock(&my_mutex);
        msleep(200);
    }
    do_exit(0);
}
static int delete_list(void * data){

    while(!kthread_should_stop()){
        mutex_lock(&my_mutex);
        counter++;
        list_for_each_entry_safe(current_node, tmp, &my_list, list){
        list_del(&current_node->list);
        kfree(current_node);
        }

        mutex_lock(&my_mutex); msleep(200);
    }
    do_exit(0);
}
static int __init my_mod_init(void){

    printk("%s, HELLO module~~~\n", __func__);
    counter =0;
    mutex_init(&my_mutex);
    //mutex_init(&my_mutex);
    
    start = ktime_get();
        
    writer_thread1 = kthread_run(insert_list, NULL, "insert_list");
    writer_thread2 = kthread_run(insert_list, NULL, "insert_list");
    writer_thread3 = kthread_run(insert_list, NULL, "insert_list");
    writer_thread4 = kthread_run(insert_list, NULL, "insert_list");
    end = ktime_get();

    delta = ktime_sub(end, start);

    kthread_stop(writer_thread1);
    kthread_stop(writer_thread2);
    kthread_stop(writer_thread3);
    kthread_stop(writer_thread4);
    printk("Mutex linked list insert time : %lld nano-seconds\n", delta);

    start = ktime_get();
    writer_thread1 = kthread_run(search_list, NULL, "serach_list");
    writer_thread2 = kthread_run(search_list,NULL,"serach_list");    
    writer_thread3 = kthread_run(search_list, NULL, "serach_list");
    writer_thread4 = kthread_run(search_list, NULL, "serach_list");
    end = ktime_get();

    delta = ktime_sub(end, start);
    kthread_stop(writer_thread1);
    kthread_stop(writer_thread2);
    kthread_stop(writer_thread3);
    kthread_stop(writer_thread4);
    printk("Mutex linked list search time : %lld ns\n", delta);

    start = ktime_get();
    writer_thread1 = kthread_run(delete_list, NULL, "delete_list");     
    writer_thread2 = kthread_run(delete_list, NULL, "delete_list");
    writer_thread3 = kthread_run(delete_list, NULL, "delete_list");
    writer_thread4 = kthread_run(delete_list, NULL, "delete_list");
    end = ktime_get();
    delta = ktime_sub(end, start);
    printk("Mutex linked list delete time : %lld ns\n", delta);
    return 0;

}
static void __exit my_mod_exit(void){

    kthread_stop(writer_thread1);
    kthread_stop(writer_thread2);
    kthread_stop(writer_thread3);
    kthread_stop(writer_thread4);
    printk("%s, BYE module \n", __func__);

}
module_init(my_mod_init);
module_exit(my_mod_exit);
MODULE_LICENSE("GPL");
