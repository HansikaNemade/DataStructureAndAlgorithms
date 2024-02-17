// Headers
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define    SUCCESS      0
#define    FAILURE      1
#define    VEC_SIZE     sizeof(struct vector)
#define    DATA_SIZE    sizeof(data_t)
 
typedef    int      data_t;
typedef    int      status_t;

typedef    data_t*            p_data_t;
typedef    struct vector*     vector_t;
typedef    struct vector**    p_vector_t;

struct  vector
{
    p_data_t    p_data;
    size_t      size;
};


//            INTERFACE FUNCTION
vector_t create_vec(void);
status_t insert_data(vector_t vector, data_t data);
status_t remove_data(vector_t vector, p_data_t rm_data);
void     print_vec(vector_t vector);
status_t destroy_vec(p_vector_t p_vector);

//             HELPER FUNCTIONS
void*  xmalloc(size_t size);
void*  xrealloc(p_data_t vector, size_t nr_elements, size_t size_element);


//        ENTRY POINT OF MAIN FUNCTION
int main(void)
{
    vector_t vector1 = NULL;
    data_t poped_data = 0;

    vector1 = create_vec();

    for(int le = 0; le < 30; le++)
    {
        assert(SUCCESS == insert_data(vector1, le));
    }

    print_vec(vector1);

    printf("\n\t\t Removing 5 elements\n");
    for(int le = 0; le < 5; le++)
    {
       assert(SUCCESS == remove_data(vector1, &poped_data));
       printf("poped data: %d\n",poped_data);
    }
    
    printf("\n\t\t After removing elements\n");
    print_vec(vector1);

    assert(SUCCESS == destroy_vec(&vector1));

    assert(vector1 == NULL);

    printf("end");

    exit(EXIT_SUCCESS);
}

//             FUNCTION DEFINATIONS

void*  xmalloc(size_t size)
{
   void* p = NULL;

   p = (void*) malloc(size);

   if(p == NULL)
   {
     fprintf(stderr, "ERROR:fatal: Out of virtual memory\n");
     return(NULL);
   }

   return(p);
}

void*  xrealloc(p_data_t vector, size_t nr_elements, size_t size_element)
{
    void* p = NULL;

    p = realloc(vector, nr_elements * size_element);

    if(p == NULL)
    {
        fprintf(stderr , "ERROR:fatal: Out of virtual memory\n");
        return(NULL);
    }

    return(p);
}

vector_t create_vec(void)
{
    vector_t vector = NULL;

    vector = (vector_t) xmalloc( VEC_SIZE);
    vector->p_data = (p_data_t) xmalloc(DATA_SIZE);
    vector->size = 0;
    
    return(vector);
}

status_t insert_data(vector_t vector, data_t data)
{
    data_t size = vector->size;

    if(vector == NULL)
    {
        printf("Vector is not present\n");
        return(FAILURE);
    }

    vector->p_data = (p_data_t)xrealloc(vector->p_data, size+1, DATA_SIZE);

    vector->p_data[size] = data;

    vector->size = size+1;

    return(SUCCESS);
}

status_t remove_data(vector_t vector, p_data_t rm_data)
{
    data_t size = vector->size;

    if(vector == NULL)
    {
        printf("Vector is not present\n");
        return(FAILURE);
    }

    *rm_data = vector->p_data[size-1];

    vector->p_data = (p_data_t)xrealloc(vector->p_data, size-1, DATA_SIZE);
    vector->size = size-1;

    return(SUCCESS);
}

void  print_vec(vector_t vector)
{
   data_t size = vector->size;

   if(vector == NULL)
   {
      printf("vector not present\n");
      return;
   }

   for(int index = 0; index < size; index++)
   {
      printf("vector[%d] = %d\n", index, vector->p_data[index]);
   }

   return;
}

status_t destroy_vec(p_vector_t p_vector)
{
    vector_t vector = *p_vector;

    free(vector->p_data);
    vector->p_data = NULL;

    free(vector);
    *p_vector = NULL;

    return(SUCCESS);
}