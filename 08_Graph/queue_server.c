//Headers
#include<stdio.h>

#include"queue.h"

queue_t  create_queue(void)
{
    return(create_list()); 
}

status_t  enqueue(queue_t queue, list_data_t new_data)
{
    return(insert_end(queue, new_data));
} 

status_t  peek(queue_t queue, list_data_t* peek_data)
{
    return(get_start(queue, peek_data));
}

status_t  dequeue(queue_t queue, list_data_t* removed_data)
{
    return(pop_start(queue, removed_data));
}

void  show_queue(queue_t queue, const char* msg)
{
    show_list(queue, msg);
    return;
}



status_t  is_queue_empty(queue_t queue)
{
    if(is_list_empty(queue) == true)
    {
        return(queue_empty);
    }

    return(false);
}

status_t  destroy_queue(p_queue_t p_queue)
{
    return(destroy_list(p_queue));
}

