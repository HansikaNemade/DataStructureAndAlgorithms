//Headers
#include<stdio.h>
#include<assert.h>

#include"bst.h"

//  ENTRY POINT OF MAIN FUNCTION
int main(void)
{
    tree_t tree = NULL;
    data_t num = 0;
    data_t tree_max = 0;
    data_t tree_min = 0;
    data_t inorder_succ = 0; 
    data_t inorder_pred = 0;

    data_t values[] = {50, 150, 25, 75, 125, 175, 65, 130, 200, 70, 127, 126, 128, 63, 73, 110, 115,107,105,109,180,185,210,205,206,212};

    create_bst(&tree);

    assert(SUCCESS == bst_insert(tree, 100));

    /*for(int i = 0; i < 10 ; i++)
    {
        num = rand(); 
        assert(SUCCESS == bst_insert(tree, num));
    }*/

    //  inserting values in the structure
    for(int i = 0; i < sizeof(values)/sizeof(data_t) ; i++)
    {
        assert(SUCCESS == bst_insert(tree, values[i]));
    }
    
    //  traversals
    preorder_recursive(tree);
    inorder_recursive(tree);
    postorder_recursive(tree);
  
    printf("\nLength of the structure = %d\n", get_length(tree));

    //   printing min max of the structure
    assert(SUCCESS == bst_max(tree, &tree_max));
    assert(SUCCESS == bst_min(tree, &tree_min));

    printf("maximum data of tree = %d\n", tree_max);
    printf("minimum data of tree = %d\n", tree_min);

    //     removing data
    assert(SUCCESS == bst_remove(tree, 75));

    printf("\n\t\tafter removing 75\n");
    preorder_recursive(tree);
    inorder_recursive(tree);
    postorder_recursive(tree);
    printf("\nLength of the structure = %d\n", get_length(tree));

    assert(SUCCESS == bst_remove(tree, 175));

    printf("\n\t\tafter removing 175\n");
    preorder_recursive(tree);
    inorder_recursive(tree);
    postorder_recursive(tree);
    printf("\nLength of the structure = %d\n", get_length(tree));

    assert(SUCCESS == bst_remove(tree, 125));

    printf("\n\t\tafter removing 125\n");
    preorder_recursive(tree);
    inorder_recursive(tree);
    postorder_recursive(tree);
    printf("\nLength of the structure = %d\n", get_length(tree));

    //        non recursive traversal
    printf("\n\t\t non recursive traversal\n");
    preorder_nr(tree);
    inorder_nr(tree);
    postorder_nr(tree);

    printf("\n\n");
    preorder_recursive(tree);
    inorder_recursive(tree);
    postorder_recursive(tree);
    
    //  printing min max of the structure
    assert(SUCCESS == bst_max(tree, &tree_max));
    assert(SUCCESS == bst_min(tree, &tree_min));

    printf("maximum data of tree = %d\n", tree_max);
    printf("minimum data of tree = %d\n", tree_min);


    //    printing inorder predecessor and successor of data
    assert(SUCCESS == bst_inorder_predecessor(tree, 130, &inorder_pred));
    assert(NO_SUCCESSOR == bst_inorder_successor(tree, 212, &inorder_succ));

    printf("\nInorder Predecessor of 130 = %d\n", inorder_pred);
    printf("Inorder Successor of 212 = %d \n", inorder_succ);


    //    checking data is present in structure or not
    assert(SUCCESS == bst_search(tree, 115));

    printf("\nLength of the structure = %d\n", get_length(tree));

    assert(FAILURE == bst_is_empty(tree));

    //    destroying structure
    assert(SUCCESS == destroy_bst(&tree));
    printf("end\n");

    exit(0);
}

