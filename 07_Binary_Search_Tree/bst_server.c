//Headers
#include<stdio.h>
#include<stdlib.h>

#include"bst.h"
#include"stack.h"


/*###################################################################################################
. #                                  INTERFACE FUNCTIONS                                            #
. ###################################################################################################*/



status_t  create_bst(p_tree_t p_tree)
{
    tree_t tree = NULL;

    tree = (tree_t) malloc(SIZE_TREE);
 
    if(tree == NULL)
    {
        fprintf(stderr, "ERROR:fatal: Out of Virtual Memory\n");
        *p_tree = NULL; 
        return(FAILURE);
    } 

    tree->p_root = NULL;
    tree->nr_elements = 0;

    *p_tree = tree;
    return(SUCCESS);
}

status_t bst_insert(tree_t tree, data_t data)
{
    p_node_t new_node = get_bst_node(data);
    p_node_t p_run = NULL;

    if(new_node == NULL)
    {
        return(FAILURE);
    }
   
    generic_insert(tree, new_node);

    return(SUCCESS);
}

void  preorder_recursive(tree_t tree)
{
   printf("Preorder recursive: [Start]->");
   preorder_r(tree->p_root);
   printf("[End]\n\n");

   return; 
}

void  inorder_recursive(tree_t tree)
{
   printf("Inorder recursive: [Start]->");
   inorder_r(tree->p_root);
   printf("[End]\n\n");

   return;
}

void  postorder_recursive(tree_t tree)
{
   printf("Postorder recursive: [Start]->");
   postorder_r(tree->p_root);
   printf("[End]\n\n");

   return;
}

void  preorder_nr(tree_t tree)
{
    stack_t stack = create_stack();
    p_node_t  p_run = tree->p_root;

    printf("Preorder non recursive: [start]->");
    while(true)
    {
       while(p_run != NULL)
       {
          push(stack, p_run);
          printf("[%d]<->", p_run->data);
          p_run = p_run->left;
       } 

       if(pop(stack, &p_run) == stack_empty)
       {
          break;
       } 
       
       p_run = p_run->right;
    }
    printf("[End]\n\n");

    destroy_stack(&stack);

    return;
}

void  inorder_nr(tree_t tree)
{
   stack_t stack = create_stack();
   p_node_t p_run = tree->p_root;
    
   printf("inoreder non recursive: [start]->");
   while(true)
   {
      while(p_run != NULL)
      {
        push(stack , p_run);
        p_run = p_run->left;
      }

      if(pop(stack, &p_run) == stack_empty)
      {
        break;
      }
        
      printf("[%d]<->", p_run->data);
      p_run = p_run->right;
   }
   printf("[End]\n\n");

   destroy_stack(&stack);

   return;
}

void  postorder_nr(tree_t tree)
{
    stack_t  stack = create_stack();
    p_node_t p_run = tree->p_root;
    flag_t   flag_status = 0;

    printf("postorder non recursive: [start]->");
    while(true)
    {
        while(p_run != NULL)
        {
            push(stack, p_run);
            set_top_flag(stack, Left_Visit);
            p_run = p_run->left;
        }

        if(top_flag_status(stack, &flag_status) == stack_empty) 
        {
            break;
        }

        if(flag_status == Left_Visit)
        {
            set_top_flag(stack, Right_Visit);
            top(stack, &p_run);
            p_run = p_run->right;
        }
        else if(flag_status == Right_Visit)
        {
            pop(stack, &p_run);
            printf("[%d]<->", p_run->data);
            p_run = NULL;
        }
        
    }
    printf("[End]\n\n");

    destroy_stack(&stack);

    return;
}

status_t bst_max(tree_t tree, data_t* p_max_data)
{
    p_node_t p_run = tree->p_root;

    while(p_run->right != NULL)
    {
        p_run = p_run->right;
    }

    *p_max_data = p_run->data;

    return(SUCCESS);
}

status_t bst_min(tree_t tree, data_t* p_min_data)
{
    p_node_t p_run = tree->p_root;

    while(p_run->left != NULL)
    {
        p_run = p_run->left;
    }

    *p_min_data = p_run->data;

    return(SUCCESS);
}

status_t bst_inorder_predecessor(tree_t tree, data_t data, data_t* p_pred_data)
{
   p_node_t e_node = search_node(tree, data);            // e_node = existing node
   p_node_t p_pred = NULL;

   if(e_node == NULL)
   {
      return(TREE_DATA_NOT_FOUND);
   }

   p_pred = inorder_predecessor(e_node);

   if(p_pred == NULL)
   {
      return(NO_PREDECESSOR);
   }

   *p_pred_data = p_pred->data;

   return(SUCCESS);
}

status_t bst_inorder_successor(tree_t tree, data_t data, data_t* p_succ_data)
{
   p_node_t e_node = search_node(tree, data);           //  e_node = existing node
   p_node_t p_succ = NULL;

   if(e_node == NULL)
   {
      return(TREE_DATA_NOT_FOUND);
   }

   p_succ = inorder_successor(e_node);

   if(p_succ == NULL)
   {
      return(NO_SUCCESSOR);
   }

   *p_succ_data = p_succ->data;

   return(SUCCESS);

}

status_t bst_preorder_successor(tree_t tree, data_t data, data_t* p_succ_data)
{
    p_node_t e_node = search_node(tree, data);            // e_node = existing node
    p_node_t p_succ = NULL;

    if(e_node == NULL)
    {
        return(TREE_DATA_NOT_FOUND);
    }

    p_succ = inorder_successor(e_node);

    if(p_succ == NULL)
    {
        return(NO_SUCCESSOR);
    }

    *p_succ_data = p_succ->data;

    return(SUCCESS);
}

bool  bst_search(tree_t tree, data_t search_data)
{
    p_node_t node =  search_node(tree, search_data);

    if(node == NULL)
    {
        return(FAILURE);
    }

    return(SUCCESS);
}

bool  bst_is_empty(tree_t tree)
{
    if(tree != NULL && tree->p_root == NULL)
    {
        return(SUCCESS);
    }

    return(FAILURE);
}

len_t get_length(tree_t tree)
{
    return(tree->nr_elements);
}

status_t bst_remove(tree_t tree, data_t data)
{
   p_node_t e_node = search_node(tree, data);

   if(e_node == NULL)
   {
      return(TREE_DATA_NOT_FOUND);
   }

   generic_delete(tree, e_node);
   e_node = NULL;

   return(SUCCESS);
}

status_t destroy_bst(p_tree_t p_tree)
{
    destroy_node((*p_tree)->p_root);
    free(*p_tree);
    *p_tree = NULL;

    return(SUCCESS);
}



/*####################################################################################################
. #                                   AUXILLARY FUNCTIONS                                            #
. ####################################################################################################*/
 


static p_node_t get_bst_node(data_t data)
{
    p_node_t node = (p_node_t) malloc(SIZE_NODE);

    if(node == NULL)
    {
        fprintf(stderr , "ERROR:fatal: Out of Virtual Memory\n");
        return(NULL);
    }

    node->data = data;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return(node);
}

static void  transplant(tree_t tree, p_node_t remove, p_node_t replace)
{
    if(remove->parent == NULL)
    {
        tree->p_root = replace;
    }
    else if(remove->parent->left == remove)
    {
        remove->parent->left = replace;
    }
    else if(remove->parent->right == remove)
    {
        remove->parent->right = replace;
    }
    
    if(replace != NULL)
    {
        replace->parent = remove->parent;
    }
}

static void  generic_insert(tree_t tree, p_node_t new_node)
{
    p_node_t p_run = tree->p_root;
    data_t data = new_node->data;

    if(tree->p_root == NULL)
    {
        tree->p_root = new_node;
        tree->nr_elements = tree->nr_elements++;
        return;
    }

    while(p_run != NULL)
    {
        if(data <= p_run->data)
        {
            if(p_run->left == NULL)
            {
                p_run->left = new_node;
                new_node->parent = p_run;
                break;
            }
            p_run = p_run->left;
        }
        else
        {
            if(p_run->right == NULL)
            {
                p_run->right = new_node;
                new_node->parent = p_run;
                break;
            }
            p_run = p_run->right;
        }
    }

    tree->nr_elements = tree->nr_elements++;

    return;
}

static void  generic_delete(tree_t tree, p_node_t e_node)
{
   if(e_node->left == NULL)
   {
      transplant(tree, e_node, e_node->right);    
   }
   else if(e_node->right == NULL)
   {
      transplant(tree, e_node, e_node->left);
   }
   else
   {
      p_node_t min = NULL;
      
      min = inorder_successor(e_node);

      transplant(tree, min, min->right);

      // replacing min node with the node which has to remove
      // changing value  of min
      min->right = e_node->right;
      min->left = e_node->left;

      // connecting left, right node to mid
      min->left->parent = min;
      min->right->parent = min;
 
      //  connecting min node to parent
      transplant(tree, e_node, min);  
   }

   free(e_node);
   e_node = NULL;

   tree->nr_elements = tree->nr_elements - 1;

   return;
}

static void  preorder_r(p_node_t p_root_node)
{
    if(p_root_node != NULL)
    {
      printf("[%d]->", p_root_node->data);

      preorder_r(p_root_node->left);

      preorder_r(p_root_node->right);
    }
}

static void  inorder_r(p_node_t p_root_node)
{
    if(p_root_node != NULL)
    {
      inorder_r(p_root_node->left);

      printf("[%d]->", p_root_node->data);

      inorder_r(p_root_node->right);
    }
}

static void  postorder_r(p_node_t p_root_node)
{
    if(p_root_node != NULL)
    {
      postorder_r(p_root_node->left);

      postorder_r(p_root_node->right);

      printf("[%d]->", p_root_node->data);

    }
}

static p_node_t  preorder_successor(p_node_t p_node)
{
    p_node_t p_run = p_node;
    p_node_t parent = NULL;

    if(p_run->left != NULL)
    {
        p_run = p_run->left;
    }
    else if(p_run->right != NULL)
    {
        p_run = p_run->right;
    }
    else
    {
        while(1)
        {
           parent = p_run->parent;
           while(parent != NULL && parent->left != p_run)
           {
               p_run = parent;
               parent = parent->parent;
           }

           if(parent != NULL )
           {
               if(parent->right == NULL)
               {
                 p_run = parent;
                 continue;
               }
               else
               {
                 p_run = parent->right;
                 break;
               }
           }
           else
           {
              p_run = parent;
              break;
           }
        }
    }

    return(p_run);
}

static p_node_t  inorder_predecessor(p_node_t p_node)
{
   p_node_t p_run = p_node;
   p_node_t parent = NULL;

   if(p_run->left != NULL)
   {
      p_run = p_run->left;
      while(p_run->right != NULL)
      {
        p_run = p_run->right;
      }

      return(p_run);
   }
   else
   {
      parent = p_run->parent;
      while( parent != NULL && parent->right != p_run )
      {
        p_run = parent;
        parent = parent->parent;
      }

      return(parent);
   }

}

static p_node_t  inorder_successor(p_node_t p_node)
{
    p_node_t p_run = p_node;
    p_node_t parent = NULL; 

    if(p_run->right != NULL )
    {
        p_run = p_run->right;
        while(p_run->left != NULL)
        {
            p_run = p_run->left;
        }
 
        return(p_run);
    }
    else
    {
       parent = p_run->parent;
       while( parent != NULL && parent->left != p_run)
       {
          p_run = parent;
          parent = parent->parent;
       }

       return(parent);
    }

}

static p_node_t  search_node(tree_t tree, data_t search_data)
{
    p_node_t p_run = tree->p_root;

    while(p_run != NULL)
    {
        if(search_data == p_run->data)
        {
            break;
        }
        else if(search_data < p_run->data)
        {
           p_run = p_run->left;
        }
        else
        {
           p_run = p_run->right;
        }
    }

    return(p_run);
}


static void  destroy_node(p_node_t node)
{
   if(node != NULL)
   {
     destroy_node(node->left);
     destroy_node(node->right);
     free(node);
   }

}

