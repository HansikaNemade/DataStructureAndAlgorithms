// Headers
#include<stdlib.h>
#include<assert.h>
#include"queue.h"

//  Entry point of main function
int main(void)
{
    queue_t queue1 = NULL;
    data_t  data = 0;

    //  creating queue
    queue1 = create_queue();

    //  check for queue is empty or not
    assert(is_queue_empty(queue1) == queue_empty);

    //   inserting data in queue
    for(data = 0; data != 10; ++data)
        assert(queue_insert(queue1, data) == success); 

    //    printing queue
    show_queue(queue1, "\tafter insertion in Queue");


    //   getting the peek data of the queue
    data = -1;
    peek(queue1, &data);
    printf("peek data : %d\n\n", data);

    data = -1;
    while(is_queue_empty(queue1) != queue_empty)
    {
        assert(success == queue_remove(queue1, &data));
        printf("removed data: %d\n", data);
    }
    
    show_queue(queue1, "\t after using queue");

    destroy_queue(&queue1);

    printf("end");

    exit(EXIT_SUCCESS);
}

