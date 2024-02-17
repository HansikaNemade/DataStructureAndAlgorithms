/**
* @file:   ND_Array.c
* @brief:  it is the server file where all the auxillary and interface function is defined.
* @author: Hansika Nemade(hansikanemade@gmail.com)
* @date:   06/12/2023 (wednesday)
*/

//Headers
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<assert.h>

#include"ND_Array.h"

//********************************************   AUXILLARY FUNCTIONS   **************************************

static void* xmalloc(size_t no_of_bytes)
{
    void* p = NULL;

    p = malloc(no_of_bytes);

    if(p == NULL)
    {
        fprintf(stderr, "ERROR:fatal1: Out of virtual memory\n");
        return(NULL);
    }

    return(p);
}

static void* xcalloc(size_t nr_elements, size_t element_size)
{
    void* p = NULL;

    p = calloc(nr_elements, element_size);

    if(p == NULL)
    {
        fprintf(stderr, "ERROR:fatal2: Out of virtual memory\n");
        return(NULL);
    }

    return(p);
}

//********************************************  INTERFACE FUNCTIONS   **************************************

extern p_array_t create_array(size_t no_of_dimension, ...)
{
    size_t no_of_elements ;

    #ifdef	MY_DEBUG
		assert(no_of_dimension != 0 );	//	for developer
	#else
		if(no_of_dimension == 0)	//	for client
		{
			fprintf(stderr, "0 dimension array not possible.\n");
			return(NULL);
		}
	#endif

    //           /* allocating the the main struct array which contain our main array and information related to it */
    p_array_t pArray = (p_array_t) xmalloc(SIZE_ARRAY);

    //                     /* assigning the no of dimension given by the user */
    pArray->no_of_dimension = no_of_dimension;

    //                        /* allocation the pDimension array */
    pArray->pDimension = (long*) xcalloc(no_of_dimension, sizeof(long));

    //                  /* storing the size of each dimension in the pDimension array */
    va_list indices;
    va_start(indices, no_of_dimension);
    for(long le = 0; le < no_of_dimension; le++)
    {
        pArray->pDimension[le] = va_arg(indices, long);
    }
    va_end(indices); 

    //                  /* calculating the total no. of elements in the array */
    no_of_elements = pArray->pDimension[0];
    for(long le = 1; le < no_of_dimension; le++)
	{
		no_of_elements *= (pArray->pDimension[le]);
	}

	pArray->no_of_elements = no_of_elements;


    //                    /* Allocating the main N-Dimensional array */
    pArray->ptr = (data_t*) xcalloc(no_of_elements, sizeof(data_t));
    memset(pArray->ptr, 0, no_of_elements * sizeof(void*));
    
	// 
    pArray->to_jump_dimension = (size_t*) xcalloc(no_of_dimension, sizeof(size_t));

    pArray->to_jump_dimension[no_of_dimension - 1]  = 1;
    for(int le = no_of_dimension - 2; le >= 0; le--)
    {
        pArray->to_jump_dimension[le] = pArray->pDimension[le+1] * pArray->to_jump_dimension[le+1];
    }
	
    return(pArray);
}

extern status_t  insert_at(p_array_t pArray, data_t data, ...)
{
    long*	indices = NULL;
    size_t  final_index = 0;

    #ifdef MY_DEBUG
		assert( pArray != NULL );
	#else
		if(pArray == NULL)
		{
			fprintf(stderr, "Error: No array found.\n");
			return(FAILURE);
		}
	#endif

    
	// allocating array of indices
    indices = (long*) xcalloc( pArray->no_of_dimension, sizeof(long));

    // storing the given indices in the indices array
    va_list arg;
	va_start(arg, data);
	for( long le = 0; le < pArray->no_of_dimension; ++le)
	{
		long index = va_arg(arg, long);

		#ifdef	MY_DEBUG
			assert(index >= 0 && index < pArray->pDimension[le]);
		#else
			if(index < 0 ||	index >= pArray->pDimension[le])
			{
				fprintf(stderr, "ERROR: Index Out Of Bound.\n");
				va_end(arg);
				free(indices);
				return(FAILURE);
			}
		#endif

		indices[le] = index;
	}
	va_end(arg);

    // calculating the final index of array on which data has to insert
    for(long le = 0; le < pArray->no_of_dimension; le++)
	{
		final_index = final_index + pArray->to_jump_dimension[le] * indices[le];
	}

    // inserting data on the given index
    pArray->ptr[final_index] = data;

    // freeing allocated array
    free(indices);

    return(SUCCESS);
}

extern data_t get_data(p_array_t pArray, ...)
{
    long*	indices = NULL;
    size_t  final_index = 0;;
    data_t  return_data;

	#ifdef	MY_DEBUG
		assert(pArray != NULL );
	#else
		if(pArray == NULL)
		{
			fprintf(stderr, "ERROR: No array found.\n");
			return(NULL);
		}
	#endif

    // allocating array of indices
    indices = (long*) xcalloc(pArray->no_of_dimension, sizeof(long));


    // storing the given indices in the indices array
    va_list arg;

    va_start(arg, pArray);
    for(long le = 0; le < pArray->no_of_dimension; le++)
    {
        long index = va_arg(arg, long);

        #ifdef MY_DEBUG
			assert(index >= 0 && index < pArray->pDimension[le]);
		#else
			if(index < 0 || index >= pArray->pDimension[le])
			{
				fprintf(stderr, "ERROR: Index out of bound.\n");
				va_end(arg);
				free(indices);
				return(NULL);
			}
		#endif

        indices[le] = index;
    } 
    va_end(arg);


    // calculating the final index of array on which data has to insert
    for(int le = 0; le < pArray->no_of_dimension; le++)
    {
        final_index = final_index + pArray->to_jump_dimension[le] * indices[le];
    }


    // getting data from the given index
    return_data = pArray->ptr[final_index];

    // freeing allocated array
    free(indices);

    return(return_data);
}

status_t show_data(p_array_t pArray)
{
	#ifdef DEBUG
        assert(pArray != NULL);
    #else
        if(pArray == NULL)
        {
            fprintf(stderr, "ERROR: No array found to destroy\n");
			return(FAILURE);
        }
    #endif

    return(SUCCESS);
}

extern long get_size_of_dimension(p_array_t pArray, long index)
{
	#ifdef MY_DEBUG
		assert(pArray != NULL);
		assert(pArray->no_of_dimension >= index)
	#else
		if(pArray == NULL)
		{
			fprintf(stderr, "ERROR: No array found to destroy.\n");
			return(0);
		}

		if(pArray->no_of_dimension < index)
		{
			fprintf(stderr, "ERROR: Dimension does not exists.\n");
			return(0);
		}
	#endif

	return( pArray->pDimension[index] );
}

extern status_t destroy(pp_array_t ppArray)
{
    p_array_t pArray = *ppArray;

    #ifdef DEBUG
        assert(pArray != NULL);
    #else
        if(pArray == NULL)
        {
            fprintf(stderr, "ERROR: No array found to destroy\n");
			return(FAILURE);
        }
    #endif

    //	Free the to jump dimension
	if(pArray->to_jump_dimension)
	{
		free(pArray->to_jump_dimension);
		pArray->to_jump_dimension = NULL;
	}

	// Free the data array
	if(pArray->ptr)
	{
		free(pArray->ptr);
		pArray->ptr = NULL;
	}

	//	Free the size of each dimension array
	if(pArray->pDimension)
	{
		free(pArray->pDimension);
		pArray->pDimension = NULL;
	}

	//	Free the struct object
	if(pArray)
	{
		free(pArray);
		pArray = NULL;
	}

	//	Assign NULL to the client side pointer
	*ppArray = NULL;

	return(SUCCESS);
}

