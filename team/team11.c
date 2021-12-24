#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/rbtree.h>
#include <linux/slab.h> // for kmalloc
#include <linux/ktime.h>
#include <linux/time.h>
#include <linux/hashtable.h> //

#define MY_HASH_BITS 2
#define DATASIZE 100000

struct my_node{
    struct list_head list;
    int data;
};

struct my_node* list[1000001];
struct list_head* Lists[1000001];


void LL_example(void)
{  


    ktime_t start, end, delta;
   
    struct my_node myList;
    INIT_LIST_HEAD(&myList.list);
    
    int i;
    
    // Add nodes
    start = ktime_get();
    for(i=0;i<DATASIZE;i++){
      struct my_node *new = kmalloc(sizeof(struct my_node),GFP_KERNEL);
      new->data=i;

      Lists[i]= &(new->list);
      list_add(&new->list, &myList.list);
      //printk("%d    %p \n",new->data, &new->list);
    }
    end = ktime_get();
    delta = ktime_sub(end, start);
    printk("INSERT %d , %lldNS\n", DATASIZE, delta);
    
    
    struct my_node *temp=NULL;
    struct list_head* pos = NULL;
    i=0;
    
    start = ktime_get();
    list_for_each(pos, &myList.list){
       temp= list_entry(pos,struct my_node,list);
       if(temp-> data == DATASIZE/2){
          printk("%d ", temp->data);
          break;
       }
       i++;
    }
    end = ktime_get();
    delta = ktime_sub(end, start);
    printk("original search %d , %lldNS\n", DATASIZE, delta);


   int j;
    start = ktime_get();
    pos=Lists[DATASIZE/2];
    temp= list_entry(pos,struct my_node,list);
    printk("search %d \n", temp->data);

    /*
    for(j=0;j<DATASIZE;j++){
       printk("search %d \n", *(int *)Lists[j]);
    }
    */

    end = ktime_get();
    delta = ktime_sub(end, start);
    printk("new search %d , %lldNS\n", DATASIZE, delta);
    
}

int __init hello_module_init(void)
{
    printk("module init\n");
    
    LL_example();
        
    return 0;
}

void __exit hello_module_cleanup(void) {
    printk("Bye Module\n");
}

module_init(hello_module_init);
module_exit(hello_module_cleanup);
MODULE_LICENSE("GPL");


