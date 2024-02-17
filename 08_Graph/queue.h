
#ifndef   _QUEUE_H
#define   _QUEUE_H

#include "list.h"

#define    queue_empty    list_empty

typedef    list_t      queue_t;
typedef    p_list_t    p_queue_t;



//********************************************  INTERFACE FUNCTIONS   **************************************

queue_t  create_queue(void);

status_t  enqueue(queue_t queue, list_data_t new_data);
status_t  peek(queue_t queue, list_data_t* peek_data); 
status_t  dequeue(queue_t queue, list_data_t* removed_data);

void  show_queue(queue_t queue, const char* msg);

status_t  is_queue_empty(queue_t queue);
 
status_t  destroy_queue(p_queue_t p_queue);

#endif

