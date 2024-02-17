/**
* @file:   ND_Client.c
* @brief:  it is the client side file which can uses ND_Array interface functions.
* @author: Hansika Nemade(hansikanemade@gmail.com)
* @date:   06/12/2023 (wednesday)
*/

//Headers
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include"ND_Array.h"


// macros
#define		NO_OF_ELEMENTS	6
#define		NO_OF_1D_ARRAY	6
#define		NO_OF_2D_ARRAY	6
#define		NO_OF_3D_ARRAY	5
#define		NO_OF_4D_ARRAY	5
#define		NO_OF_5D_ARRAY	4
#define		NO_OF_6D_ARRAY	4
#define		NO_OF_7D_ARRAY	3
#define		NO_OF_8D_ARRAY	3
#define		NO_OF_9D_ARRAY	3
#define		NO_OF_10D_ARRAY	3
#define		NO_OF_11D_ARRAY	3

// global variable declaration
p_array_t  my_array = NULL;
p_array_t  my_12Darray = NULL;
status_t status;


// Entry point of Main function
int main(void)
{
    my_array = create_array(3, 5, 4, 3);

    assert(my_array != NULL);

    size_t count = 0;

    // inserting value
    for(long index1 = 0; index1 < 5; index1++)
    {
        for(long index2 = 0; index2 < 4; index2++)
        {
            for(long index3 = 0; index3 < 3; index3++)
            {
                status = insert_at(my_array, (data_t) (++count), index1, index2, index3);
                assert(status == SUCCESS);
            }
        }
    }

    // Read value
    for(long index1 = 0; index1 < 5; index1++)
    {
        printf("\t%d 2D Array\n", index1);
        for(long index2 = 0; index2 < 4; index2++)
        {
            printf("\t%d 1D Array\n", index2);
            for(long index3 = 0; index3 < 3; index3++)
            {
                fprintf(stdout, "my_array[%d][%d][%d] = %lld\n", index1, index2, index3, (long long)get_data(my_array, index1, index2, index3));
            }

            printf("\n");
        }

        printf("\n");
    }

    //printf("end\n");

    status = destroy(&my_array);
    //assert(status == SUCCESS);

    printf("*********************************************************************************************************\n");

    my_12Darray = create_array(12, 
							NO_OF_11D_ARRAY, NO_OF_10D_ARRAY,
							NO_OF_9D_ARRAY, NO_OF_8D_ARRAY,
							NO_OF_7D_ARRAY, NO_OF_6D_ARRAY,
							NO_OF_5D_ARRAY, NO_OF_4D_ARRAY,
							NO_OF_3D_ARRAY, NO_OF_2D_ARRAY,
							NO_OF_1D_ARRAY, NO_OF_ELEMENTS);

    count = 0;
	for( long index1 = 0; index1 < get_size_of_dimension(my_12Darray, 0); ++index1 )
    {
		for( long index2 = 0; index2 < get_size_of_dimension(my_12Darray, 1); ++index2 )
        {
			for( long index3 = 0; index3 < get_size_of_dimension(my_12Darray, 2); ++index3)
            {
				for( long index4 = 0; index4 < get_size_of_dimension(my_12Darray, 3); ++index4)
                {
					for( long index5 = 0; index5 < get_size_of_dimension(my_12Darray, 4); ++index5)
                    {
						for( long index6 = 0; index6 < get_size_of_dimension(my_12Darray, 5); ++index6)
                        {
							for( long index7 = 0; index7 < get_size_of_dimension(my_12Darray, 6); ++index7)
                            {
								for( long index8 = 0; index8 < get_size_of_dimension(my_12Darray, 7); ++index8)
                                {
									for( long index9 = 0; index9 < get_size_of_dimension(my_12Darray, 8); ++index9)
                                    {
										for( long index10 = 0; index10 < get_size_of_dimension(my_12Darray, 9); ++index10)
                                        {
											for( long index11 = 0; index11 < get_size_of_dimension(my_12Darray, 10); ++index11)
                                            {
												for( long index12 = 0; index12 < get_size_of_dimension(my_12Darray, 11); ++index12)
                                                {
													insert_at(	my_12Darray, 
																(data_t)(++count), 
																index1,  index2, 
																index3, index4, 
																index5, index6, 
																index7, index8, 
																index9, index10, 
																index11, index12);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    fprintf(stdout, "\t\t 12D Array\n");

    fprintf(stdout," First Element of 12D array = %lld\n", (long long)get_data(my_12Darray, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) );
	fprintf(stdout," Last Element of 12D array = %lld\n", (long long)get_data(my_12Darray, 
																		NO_OF_11D_ARRAY-1, 
																		NO_OF_10D_ARRAY-1, 
																		NO_OF_9D_ARRAY-1, 
																		NO_OF_8D_ARRAY-1, 
																		NO_OF_7D_ARRAY-1, 
																		NO_OF_6D_ARRAY-1, 
																		NO_OF_5D_ARRAY-1, 
																		NO_OF_4D_ARRAY-1, 
																		NO_OF_3D_ARRAY-1, 
																		NO_OF_2D_ARRAY-1, 
																		NO_OF_1D_ARRAY-1, 
																		NO_OF_ELEMENTS-1));

    fprintf(stdout, "\n************************************* end ************************************\n\n\n");

    destroy(&my_12Darray);

    return(SUCCESS);
}

