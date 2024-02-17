#ifndef _LIST_H
#define _LIST_H

#include<stdbool.h>

#define  success               0
#define  failure               1
#define  list_data_not_found   2
#define  list_empty            3
#define  NODE_SIZE             (sizeof(struct node))
            

typedef   int   data_t;          //type of data stored in list
typedef   int   status_t;        //Success status of function
typedef   int   len_t;           //length of the list 

typedef   struct node   node_t;          // data type  of node 
typedef   struct node*  p_node_t;        //   pointer to node
typedef   p_node_t      list_t;         //   represents the list 
typedef   struct node** p_list_t;       //   pointer to pointer to node or pointer to list

struct node
{
    data_t   data;      // data
    p_node_t prev;      // previous link
    p_node_t next;      // next link
};



//                                                /* Interface Function */

 list_t create_list(void);
 
 status_t  insert_start(list_t list, data_t data);
 status_t  insert_end(list_t list, data_t data);
 status_t  insert_after(list_t list, data_t e_data, data_t data);              // e_data - existing data
 status_t  insert_before(list_t list, data_t e_data, data_t data);

 status_t  get_start(list_t list, data_t* p_data);                           // p_data - pointer to data_t
 status_t  get_end(list_t list, data_t* p_data);                             
 status_t  pop_start(list_t list, data_t* p_data);
 status_t  pop_end(list_t list, data_t* p_data);

 status_t  remove_start(list_t list);
 status_t  remove_end(list_t list);

 bool  is_list_empty(list_t list);
 len_t get_length(list_t list);

 void  show_list(list_t list, const char* msg);
 status_t  destroy_list(p_list_t p_list);

 

//                                                /* Helper Functions */
 
 static p_node_t get_node(data_t data);

 static void  generic_insert(p_node_t p_start, p_node_t p_mid, p_node_t p_end);
 static void  generic_delete(p_node_t p_delete); 

 static p_node_t search_node(list_t list, data_t data); 

#endif