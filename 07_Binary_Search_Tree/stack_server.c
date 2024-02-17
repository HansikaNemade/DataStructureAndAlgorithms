// Headers
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"stack.h"


/*
*                     Stack is a linear data structure or a list that follows a particular order in which the operations are performed.
*                     The order is LIFO (last in first out)       
*/

stack_t  create_stack(void)
{
    return create_list();
}


status_t push(stack_t stack, list_data_t new_data)
{
    return insert_end(stack, new_data);
}
 
status_t pop(stack_t stack, list_data_t* poped_data)
{
    status_t pop = pop_end(stack, poped_data); 

    return(pop); 
}

status_t top(stack_t stack, list_data_t* top_data)
{
    return get_end(stack, top_data);
} 

status_t top_flag_status(stack_t stack, flag_t* flag_status)
{
    if(is_list_empty(stack) == true)
    {
       return(stack_empty);
    }

    return(get_flag_status(stack->prev, flag_status));
}

status_t  set_top_flag(stack_t stack, flag_t set)
{
    if(is_list_empty(stack) == true)
    {
       return(stack_empty);
    } 

    return(set_flag_status(stack->prev, set));
}
 
void     show_stack(stack_t stack, const char* msg)
{
    show_list(stack, msg);
    return;
}


status_t  is_stack_empty(stack_t stack)
{
    return is_list_empty(stack);
}


status_t destroy_stack(p_stack_t p_stack)
{
    stack_t stack = *p_stack;

    while(is_stack_empty(stack) != true)
    {
       assert( success == remove_end(stack));
    }

    free(stack);
    *p_stack = NULL;

    return(success);
}

