#include <linux/kernel.h>

#include <linux/module.h>

#include <linux/init.h>

#include <linux/rbtree.h>

#include <linux/slab.h>

#include <linux/ktime.h>

#include <linux/time.h>

#include <linux/hashtable.h>

#define MY_HASH_BITS 2

 

struct my_hash{

    u32 key;

    int value;

    struct hlist_node hnode;

};

 

struct my_node{

    struct rb_node node;

    int key;

    int value;

};

void rb_insert(struct rb_root *root, struct my_node *data){

    struct rb_node **new = &(root->rb_node), *parent = NULL;

 

    while(*new){

        parent = *new;

            if((data->key < 0))

            new = &((*new)->rb_left);

        else

            new = &((*new)->rb_right);

    }

    rb_link_node(&data->node,parent,new);

 

    rb_insert_color(&data->node,root);

    

}

void RB_example(int num)

{

    ktime_t start, end, delta;

    struct rb_root root_node =RB_ROOT;

    struct my_node *new_node;

    struct rb_node *iter_node;

    int i;

    printk("%ditems \n", num);

    // Add

    start = ktime_get();

    for(i=-(num/2);i<(num/2);i++){

        new_node = kmalloc(sizeof(struct my_node),GFP_KERNEL);

        new_node->value =i*10;

        new_node->key =i;

        rb_insert(&root_node, new_node);

    }

    end = ktime_get();

    delta = ktime_sub(end, start);

    printk("INSERT %d red-black tree, %lldNS\n", num, delta);

    /* Add new node and rebalance tree. */

    

 

 

    //test

    start=ktime_get();

    for(iter_node=rb_first(&root_node); iter_node; iter_node=rb_next(iter_node)){

    }

    end=ktime_get();

    delta=ktime_sub(end,start);

    printk("term project");

    printk("search %d red-black tree,%lldNS\n",num,delta);

 

 

    start = ktime_get();

    for(iter_node = rb_first(&root_node); iter_node; iter_node = rb_next(iter_node)){

 

    }

    end = ktime_get();

    delta = ktime_sub(end, start);

    printk("Search %d red-black tree, %lldNS\n", num, delta);

 

 

 

    // Delete nodes

        /* rb_tree delete node */

    start = ktime_get();

    for(iter_node = rb_first(&root_node); iter_node; iter_node = rb_next(iter_node)){

        rb_erase(iter_node, &root_node);

        // kfree(iter_node);

    }

    end = ktime_get();

    delta = ktime_sub(end, start);

    printk("Delete %d red-black tree, %lldNS\n\n", num, delta);

    /* check whether all nodes are erased */

    for(iter_node = rb_first(&root_node); iter_node; iter_node = rb_next( iter_node)){

        printk("(key,value)=(%d.%d)\n", rb_entry(iter_node, struct my_node , node)->key, rb_entry(iter_node, struct my_node, node)->value);

    }

 

}

int __init hello_module_init(void)

{

    int j;

    printk("module init\n");

    

    for(j = 1000; j<1000000; j*=10){

            RB_example(j);

    }

        return 0;

}

void __exit hello_module_cleanup(void) {

    printk("Bye Module\n");

}

module_init(hello_module_init);

module_exit(hello_module_cleanup);

MODULE_LICENSE("GPL"); 


