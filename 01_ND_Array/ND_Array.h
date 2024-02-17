
/**
* @file:   ND_Array.h
* @brief:  header file of N dimensional array which includes declaration of struct and Interface function.
* @author: Hansika Nemade(hansikanemade@gmail.com)
* @date:   06/12/2023 (wednesday)
*/

//  Macros 
#ifndef _ND_ARRAY_H
#define _ND_ARRAY_H


#define     SUCCESS       0
#define     FAILURE       1

#define     SIZE_ARRAY    sizeof(struct array)
#define     SIZE_DATA     sizeof(data_t)

// struct declaration
struct array;

// Typedefs
typedef       void*               data_t;
typedef       struct array        array_t;
typedef       struct array*       p_array_t;
typedef       struct array**      pp_array_t;
typedef       int                 status_t; 
 

//structure type definition
struct array
{
    data_t*    ptr;                 // actual array
    long*      pDimension;          // array of storing size of each dimension
    size_t     no_of_dimension;     // total no of dimension
    size_t     no_of_elements;      // total no. of element present in the array
    size_t*    to_jump_dimension;   // jump dimension       
};


//********************************************  INTERFACE FUNCTIONS   **************************************

/*
*  FUNCTION NAME : create_array()
*                       it basically allocated our main array and initialized the information in the structure and return the address of 
*                       of that structure
* 
*  PARAMETERS :  
*                1) size_t :  it takes the no of dimension of array
*                2) ...    :  (variadic function)  which take count of each dimension elements
* 
*  RETURNS :
*                p_array_t :  return the address of allocated struct array 
*/
p_array_t create_array(size_t no_of_dimension, ...);


/*
*  FUNCTION NAME : insert_at()
*                       This function inserts the given data on the given indices.
* 
*  PARAMETERS :  
*                1) p_array_t : it takes the struct array pointer of that array in which data has to be inserted
*                2) data_t    : it is the data which has to insert
*                3) ...       : indices of array on which data has to insert
* 
*  RETURNS :
*                status_t : SUCCESS - if data successfully inserted
*                           FAILURE - if array not found
*/
status_t  insert_at(p_array_t array, data_t data, ...);

/*
*  FUNCTION NAME : get_data()
*                      this function gives you data on the specified indices
* 
*  PARAMETERS :  
*                1) p_array_t :  it takes the struct array pointer of that array in which data has to be inserted
*                2) ...       :   indices of the array from which you have to get data
*    
*  RETURNS :
*                data_t :   return the data of the specified indices
*/
data_t get_data(p_array_t array, ...);


/*
*  FUNCTION NAME : get_size_of_dimension()
*                      this function gives the size of the given dimension
* 
*  PARAMETERS :  
*                1) p_array_t :  it takes the struct array pointer of that array 
*                2) long      :  dimension of array
*    
*  RETURNS :
*                long :   returns size of that dimension
*/
long get_size_of_dimension(p_array_t pArray, long index);


status_t show_data(p_array_t array);

/*
*  FUNCTION NAME : destroy()
*                      this function free the allocated arrays
* 
*  PARAMETERS :  
*                1) pp_array_t :  address of the variable which stores the address of the struct array
*    
*  RETURNS :
*                data_t :   SUCCESS - if all the allocated memory free successfully
*                           FAILURE - if array not found
*/
status_t destroy(pp_array_t p_array);


#endif

