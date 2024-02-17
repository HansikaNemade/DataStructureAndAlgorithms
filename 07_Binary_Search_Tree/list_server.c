//Headers
#include<stdio.h>
#include<stdlib.h>
#include"list.h"


//********************************************   INTERFACE FUNCTIONS   **************************************

list_t create_list(void)
{
   list_t list = NULL;

   list = list_get_node(NULL);

   if(list == NULL)
   {
      fprintf(stderr, "ERROR: list is not created\n");
      return(NULL);
   }
 
   list->next = list; 
   list->prev = list;

   return(list);    
}
 
status_t  insert_start(list_t list, list_data_t data)
{
   p_dcll_node_t new_node = NULL;

   new_node = list_get_node(data);
   if(new_node == NULL)
   {
      return(failure);
   }

   list_generic_insert(list, new_node, list->next);
   return(success);
}

status_t  insert_end(list_t list, list_data_t data)
{
   p_dcll_node_t new_node = NULL;

   new_node = list_get_node(data); 
   if(new_node == NULL)
   {
      return(failure);
   }

   list_generic_insert(list->prev, new_node, list);

   return(success);
}

status_t  get_start(list_t list, list_data_t* p_data)      // p_data - pointer to data_t
{
   if(list->next == list)
   {
      return(list_empty);
   }

   *p_data = list->next->data;
   return(success);
}

status_t  get_end(list_t list, list_data_t* p_data)
{
   if(list->next == list)
   {
      return(list_empty);
   }

   *p_data = list->prev->data;
   return(success);
}  

status_t  pop_start(list_t list, list_data_t* p_data)
{
   if(list->next == list)
   {
      return(list_empty);
   }
 
   *p_data = list->next->data;
   list_generic_delete(list->next);

   return(success);
}

status_t  pop_end(list_t list, list_data_t* p_data)
{
   if(list->next == list)
   {
      return(list_empty);
   }

   *p_data = list->prev->data;
   list_generic_delete(list->prev);

   return(success);
}

status_t  remove_end(list_t list)
 {
   if(list->next == list)
   {
      return(list_empty);
   }

   list_generic_delete(list->prev);

   return(success);
 }


bool  is_list_empty(list_t list)
{
   if(list->next == list)
   {
      return(true);
   }

   return(false);
}

status_t get_flag_status(p_dcll_node_t node, flag_t* flag_status)
{
   *flag_status = node->flag;

   return(success);
}

status_t set_flag_status(p_dcll_node_t node, flag_t set)
{
   node->flag = set;

   return(success);
}

void  show_list(list_t list, const char* msg)
{
   p_dcll_node_t p_run = NULL;
   puts(msg);

   p_run = list->next;
   printf("[start]<->");
   while(p_run != list)
   {
      printf("[%p]<->", p_run->data);
      p_run = p_run->next;
   }
   printf("[end]\n\n");

   return;
}

status_t  destroy_list(p_list_t p_list)
{
   p_dcll_node_t p_run = NULL;
   p_dcll_node_t list = NULL;
   p_dcll_node_t delete = NULL;

   list = *p_list;
   p_run = list->next;
   while(p_run != list)
   {
      delete = p_run;
      p_run = p_run->next;
      free(delete);
   }
 
   free(list);
   list = NULL;

   *p_list = NULL;

   return(success);
}


//********************************************   AUXILLARY FUNCTIONS   **************************************

static p_dcll_node_t list_get_node(void* data)
{
    p_dcll_node_t  new_node = NULL;

    new_node = (p_dcll_node_t)malloc(NODE_SIZE);

    if(new_node == NULL)
    {
        fprintf(stderr, "ERROR:fatal: out of virtual memory\n");
        return(NULL);
    }

    new_node->data = data;
    new_node->flag = 0;
    new_node->prev = NULL;
    new_node->next = NULL;

    return(new_node);
}

static void  list_generic_insert(p_dcll_node_t p_start, p_dcll_node_t p_mid, p_dcll_node_t p_end)
{
   p_mid->prev = p_start;
   p_mid->next = p_end;

   p_start->next = p_mid;
   p_end->prev = p_mid; 
}

static void  list_generic_delete(p_dcll_node_t p_delete)
{
   p_delete->prev->next = p_delete->next;
   p_delete->next->prev = p_delete->prev;

   free(p_delete);
   p_delete = NULL;

   return;
} 

