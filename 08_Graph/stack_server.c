//Headers
#include<stdio.h>
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
    return pop_end(stack, poped_data);
}

status_t top(stack_t stack, list_data_t* top_data)
{
    return get_end(stack, top_data);
}


void     show_stack(stack_t stack, const char* msg)
{
    show_list(stack, msg);
    return;
}


status_t  is_stack_empty(stack_t stack)
{
    if(is_list_empty(stack) == true)
    {
        return(Stack_empty); 
    }

    return(false);
}


/*status_t destroy_stack(p_stack_t p_stack)
{
    stack_t stack = *p_stack;
    status_t status = 0;

    while(is_stack_empty(stack) != Stack_empty)
    {
       status = remove_end(stack);
       assert(status == success);
    }

    free(stack);
    *p_stack = NULL;

    return(success);
}*/

status_t  destroy_stack(p_stack_t p_stack)
{
    return(destroy_list(p_stack));
}

