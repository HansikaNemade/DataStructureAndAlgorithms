#ifndef _BST_H_
#define _BST_H

//  Headers
#include<stdbool.h>

//    Symbolic Constants     
#define   SUCCESS                0
#define   FAILURE                1
#define   TREE_EMPTY             2 
#define   TREE_DATA_NOT_FOUND    3
#define   NO_SUCCESSOR           4
#define   NO_PREDECESSOR         5

#define   NO_VISIT               1
#define   Left_Visit             2
#define   Right_Visit            3

#define   SIZE_NODE              sizeof(struct bst_node)
#define   SIZE_TREE              sizeof(struct bst)    


//        Typedefs
typedef     int                  data_t;
typedef     int                  status_t; 
typedef     int                  len_t;

typedef     struct bst_node      node_t;
typedef     struct bst_node*     p_node_t;
typedef     struct bst_node**    pp_node_t;
typedef     struct bst           bst_t;
typedef     struct bst*          tree_t;
typedef     struct bst**         p_tree_t;


//struct type definition of bst_node
struct bst_node
{
   data_t     data;
   p_node_t   parent;
   p_node_t   left;
   p_node_t   right;
};

//  struct type definition of bst
struct bst
{
  p_node_t   p_root;
  size_t     nr_elements;
};


//********************************************  INTERFACE FUNCTIONS   **************************************

status_t  create_bst(p_tree_t p_tree);

status_t bst_insert(tree_t tree, data_t data);

void  preorder_recursive(tree_t tree);        // recursive preorder traversal    -   parent, LST, RST
void  inorder_recursive(tree_t tree);         // recursive inorder traversal     -   LST, parent, RST
void  postorder_recursive(tree_t tree);       // recursive postorder traversal   -   LST, RST, parent

void  preorder_nr(tree_t tree);               // non recursive preorder traversal
void  inorder_nr(tree_t tree);                // non recursive inorder traversal
void  postorder_nr(tree_t tree);              // non recursive postorder traversal

status_t bst_max(tree_t tree, data_t* p_max_data);
status_t bst_min(tree_t tree, data_t* p_min_data);

//status_t bst_inorder_predecessor(tree_t tree, data_t data, data_t* p_pred_data);
//status_t bst_inorder_successor(tree_t tree, data_t data, data_t* p_succ_data);

status_t get_all_occurrence(tree_t tree, data_t search_data);

bool  bst_search(tree_t tree, data_t data);

bool  bst_is_empty(tree_t tree); 

len_t  get_length(tree_t tree);

status_t bst_remove(tree_t tree, data_t data);

status_t destroy_bst(p_tree_t p_tree);



//********************************************   AUXILLARY FUNCTIONS   **************************************

static p_node_t  get_bst_node(data_t data);
static void  transplant(tree_t tree, p_node_t remove, p_node_t replace);

static void  generic_insert(tree_t tree, p_node_t new_node);
static void  generic_delete(tree_t tree, p_node_t e_node);

static void  preorder_r(p_node_t p_root_node);               // recursive preorder traversal
static void  inorder_r(p_node_t p_root_node);                // recursive inorder traversal
static void  postorder_r(p_node_t p_root_node);              // recursive postorder traversal

static p_node_t  inorder_predecessor(p_node_t p_node);
static p_node_t  inorder_successor(p_node_t p_node);

static p_node_t  search_node(tree_t tree, data_t data);
 
static void  destroy_node(p_node_t node);


#endif


