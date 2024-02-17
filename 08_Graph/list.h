
#ifndef  _LIST_H
#define  _LIST_H

#include<stdbool.h>

//     Symbolic Constants
#define  success                  0
#define  failure                  1
#define  list_data_not_found      2
#define  list_empty               3      
#define  NODE_SIZE                sizeof(struct dcll_node) 


//        Typedefs
typedef   void*   list_data_t;          // type of data stored in list
typedef   int     status_t;             // Success status of function
typedef   int     len_t;                // length of the list 
typedef   int     flag_t;

typedef   struct dcll_node     dcll_node_t;          //  data type  of node 
typedef   struct dcll_node*    p_dcll_node_t;        //  pointer to node 
typedef   p_dcll_node_t        list_t;               //  represents the list 
typedef   struct dcll_node**   p_list_t;             //  pointer to pointer to node or pointer to list


struct dcll_node
{ 
    list_data_t   data;            // data
    p_dcll_node_t prev;            // previous link
    p_dcll_node_t next;            // next link
};


//********************************************  INTERFACE FUNCTIONS   **************************************

list_t create_list(void);

status_t  insert_start(list_t list, list_data_t data);
status_t  insert_end(list_t list, list_data_t data); 

status_t  get_start(list_t list, list_data_t* p_data);                           // p_data - pointer to data_t
status_t  get_end(list_t list, list_data_t* p_data); 

status_t  pop_start(list_t list, list_data_t* p_data); 
status_t  pop_end(list_t list, list_data_t* p_data);

status_t  remove_start(list_t list);
status_t  remove_end(list_t list);
status_t  remove_data(list_t list, list_data_t data, list_data_t* p_data);

bool  is_list_empty(list_t list);

void  show_list(list_t list, const char* msg);

status_t  destroy_list(p_list_t p_list);



//********************************************   AUXILLARY FUNCTIONS   **************************************
p_dcll_node_t list_get_node(list_data_t data);

static void  list_generic_insert(p_dcll_node_t p_start, p_dcll_node_t p_mid, p_dcll_node_t p_end);

static void  list_generic_delete(p_dcll_node_t p_delete);

static p_dcll_node_t search_node(list_t list, list_data_t data);

#endif