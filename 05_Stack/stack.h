#ifndef _STACK_H
#define _STACK_H

#include"list.h"

#define  Stack_empty     list_empty

typedef  list_t     stack_t;
typedef  p_list_t   p_stack_t;


/*
*                     Stack is a linear data structure or a list that follows a particular order in which the operations are performed.
*                     The order is LIFO (last in first out)       
*/

//********************************************  INTERFACE FUNCTIONS   **************************************

stack_t  create_stack(void);

status_t push(stack_t stack, data_t new_data);
status_t pop(stack_t stack, data_t* poped_data);
status_t top(stack_t stack, data_t* top_data);

void   show_stack(stack_t stack, const char* msg);

status_t  is_stack_empty(stack_t stack);

status_t destroy_stack(p_stack_t p_stack);


#endif

