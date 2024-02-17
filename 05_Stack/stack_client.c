// Headers
#include<stdlib.h>
#include<assert.h>
#include"stack.h"

//   Entry point of main function
int main(void)
{
    stack_t stack1 = NULL;
    data_t  data = 0;

    //   creating stack
    stack1 = create_stack();

    //   check for stack is empty or not
    assert(is_stack_empty(stack1) == true);

    //    inserting data
    for(data = 0; data != 10; ++data)
    {
        assert(push(stack1, data) == success); 
    }

    //   printing stack
    show_stack(stack1, "\tafter insertion in stack");

    //   getting top data
    data = -1;
    top(stack1, &data);
    printf("top data data: %d\n\n", data);

    data = -1;
    while(is_stack_empty(stack1) != Stack_empty)
    {
        assert(success == pop(stack1, &data));           // removing data from stack
        printf("poped data: %d\n", data);
    }
    
    show_stack(stack1, "\t after using stack");

    //  destroying stack
    destroy_stack(&stack1);

    printf("end");

    exit(EXIT_SUCCESS);
}

