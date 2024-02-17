// Headers
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include"list.h"
#include"queue.h"
#include"stack.h"
#include"graph.h"


//********************************************   INTERFACE FUNCTIONS   **************************************


status_t  create_graph(p_graph_t p_graph)
{
   graph_t graph = NULL; 
   graph = (graph_t)xmalloc(SIZE_GRAPH);

   if(graph == NULL)
   {
      *p_graph = NULL;
      return(FAILURE);
   }

   graph->p_graph = create_list();
   graph->nr_vertex = 0;
   graph->nr_edges = 0;

   *p_graph = graph;
   return(SUCCESS);
}
 
status_t  add_vertex(graph_t graph, data_t vdata)
{
   status_t status = 0;
   p_vnode_t vnode = NULL;

   vnode = search_vnode(graph->p_graph, vdata);

   if(vnode != NULL)
   {
      return(G_VEXISTS);
   }
   
   vnode = (p_vnode_t)xmalloc(SIZE_VNODE);

   vnode->v_data =  vdata;
   vnode->color = 0;
   vnode->adj_list = create_list();

   status = insert_end(graph->p_graph, vnode);
   if(status == FAILURE)
   {
      free(vnode);
      return(FAILURE);
   }

   graph->nr_vertex = graph->nr_vertex + 1;

   return(SUCCESS);
}

status_t  add_edge(graph_t graph, data_t v_start, data_t v_end, weight_t weight)
{
   p_vnode_t start_vnode = NULL;
   p_vnode_t end_vnode = NULL;
   p_enode_t start = NULL;
   p_enode_t end = NULL;
   status_t status;

   //  checking vertex is valid or not
   start_vnode = search_vnode(graph->p_graph, v_start);
   if(start_vnode == NULL)
   {
      return(G_VINVALID);
   }

   end_vnode = search_vnode(graph->p_graph, v_end);
   if(end_vnode == NULL)
   {
      return(G_VINVALID);
   }

   //  checking if edge is exists or not
   start = search_enode(start_vnode->adj_list, v_end);
   end = search_enode(end_vnode->adj_list, v_start);

   if(start != NULL && end != NULL)
   {
      return(G_EEXISTS);
   }
   else if((start != NULL) || (end != NULL))
   {
      return(G_CORRUPTED);
   }

   status = adj_insert(start_vnode->adj_list, v_end, weight);
   assert(status == SUCCESS);

   status = adj_insert(end_vnode->adj_list, v_start, weight);
   assert(status == SUCCESS);

   graph->nr_edges = graph->nr_edges + 1;

   return(SUCCESS);
}

status_t  remove_vertex(graph_t graph, data_t vdata)
{
   p_vnode_t vdelete = NULL;
   p_enode_t v_start = NULL;
   p_vnode_t v_end = NULL;
   p_dcll_node_t p_erun = NULL;
   p_dcll_node_t p_erun_next = NULL;
   data_t  data = 0;
   status_t status = 0;

   vdelete = search_vnode(graph->p_graph, vdata);

   if(vdelete == NULL)
   {
      return(G_VINVALID);
   }

   // checking and removing the adjacent node / edges of vertex 
   p_erun = vdelete->adj_list->next;
   while(p_erun != vdelete->adj_list)
   {
      p_erun_next = p_erun->next;

      data = ((p_enode_t)p_erun->data)->e_data;
      v_end = search_vnode(graph->p_graph, data);     // v_end - vertex in graph

      if(v_end == NULL)          // checking  v_end vertex is valid or not
      {
         return(G_CORRUPTED);
      }

      v_start = search_enode(v_end->adj_list, vdelete->v_data);    // v_start - node in adjacent list

      if(v_start == NULL)          // checking v_start node is present in 
      {
         return(G_CORRUPTED);
      }

      //data = *((data_t*)v_start->data);
      status = adj_remove(v_end->adj_list, v_start);   // removed v_start from v_end
      assert(status == SUCCESS);

      //data = *((data_t*)p_erun->data);
      status = adj_remove(vdelete->adj_list, p_erun->data);  // removed v_end from v_start
      assert(status == SUCCESS);

      graph->nr_edges = graph->nr_edges - 1;

      p_erun = p_erun_next;
   }

   status = remove_vnode(graph->p_graph, vdata);
   assert(status == SUCCESS);

   graph->nr_vertex = graph->nr_vertex - 1;

   return(SUCCESS);
}

status_t  remove_edge(graph_t graph, data_t  v_start, data_t v_end)
{
   p_vnode_t start_vnode = NULL;
   p_vnode_t end_vnode = NULL;
   p_enode_t rm_start = NULL;
   p_enode_t rm_end  = NULL;
   status_t  status = 0;

   start_vnode = search_vnode(graph->p_graph, v_start);
   if(start_vnode == NULL)
   {
      return(G_VINVALID);
   }

   end_vnode = search_vnode(graph->p_graph, v_end);
   if(end_vnode == NULL)
   {
      return(G_VINVALID);
   }

   rm_start =  search_enode(start_vnode->adj_list, v_end);   // rm_start = remove node in start
   rm_end = search_enode(end_vnode->adj_list, v_start);      // rm_end = remove node in end

   if(rm_start == NULL && rm_end == NULL)
   {
      return(G_EINVALID);
   }
   else if((rm_start == NULL) || (rm_end == NULL))
   {
      return(G_CORRUPTED);
   }

   status = adj_remove(start_vnode->adj_list, rm_start);
   assert(status == SUCCESS);

   status = adj_remove(end_vnode->adj_list, rm_end);
   assert(status == SUCCESS);

   graph->nr_edges = graph->nr_edges - 1;

   return(SUCCESS);
}

void  print_graph(graph_t graph, const char* msg)
{
   p_vnode_t p_vnode = NULL;
   p_enode_t p_enode = NULL;
   p_dcll_node_t pv_run = NULL;
   p_dcll_node_t adj_run = NULL;
 
   if(msg)
     puts(msg);

   //printf("\n");

   printf("[Vertices] = %d -> [edges] = %d\n", graph->nr_vertex, graph->nr_edges);

   pv_run = graph->p_graph->next;
   while(pv_run != graph->p_graph)      // traversing the vertex list / vertical list
   { 
      p_vnode = pv_run->data;      // accessing data of vertical list 
      printf("[%d] ->\t", p_vnode->v_data);

      adj_run = p_vnode->adj_list->next;
      while(adj_run != p_vnode->adj_list)     // traversing the adjacency list / horizontal list
      {
         p_enode = adj_run->data;       // accessing data of horizontal list
         printf("[%d]<->", p_enode->e_data, p_enode->weight);   // dereferencing data of linked list and printing data
         //printf("[%d]--(%0.1f)--<->", p_enode->e_data, p_enode->weight);

         adj_run = adj_run->next;
      }

      printf("[end]\n");
      pv_run = pv_run->next;
   }

   printf("\n");

   return;
}

status_t destroy_graph(p_graph_t p_graph)
{
   graph_t graph = *p_graph;
   p_vnode_t p_vnode = NULL;
   p_data_t p_enode = NULL;
   p_dcll_node_t pv_run = NULL;
   p_dcll_node_t adj_run = NULL;
   p_dcll_node_t adj_run_next =  NULL;
   p_dcll_node_t pv_run_next = NULL;


   pv_run = graph->p_graph->next;
   while(pv_run != graph->p_graph)   // traversing the vertex list / vertical list
   {
      p_vnode = pv_run->data;

      adj_run = p_vnode->adj_list->next;
      while(adj_run != p_vnode->adj_list)  // traversing the adjacency list / horizontal list
      {
         free(adj_run->data);            // releasing the data of adjacency list (horizontal list) 
         adj_run_next = adj_run->next;
         free(adj_run);                 // releasing the node of the adjacency list (horizontal list)
         adj_run = adj_run_next;
      }

      free(p_vnode->adj_list);  // releasing the adjacent list of the vertex (horizontal list)
      free(pv_run->data);       // releasing the vnode (data of vertical list) / data of vertex list
 
      pv_run_next = pv_run->next;
      free(pv_run);            // releasing the vertex list node  (node of vertical list)
      pv_run = pv_run_next;

   }

   free(graph->p_graph);     // releasing the vertex list (pointer to graph) (vertical list)
   free(graph);           // releasing the client structure of graph

   *p_graph = NULL;
   return(SUCCESS);
}


void dfs(graph_t graph)
{
   p_dcll_node_t pv_run = NULL;

   reset(graph);

   printf("\n\t DFS Visit\n");
   printf("[START]-");

   pv_run = graph->p_graph->next;
   for(pv_run ; pv_run != graph->p_graph ; pv_run = pv_run->next)
   {
      if(((p_vnode_t)pv_run->data)->color == White)
      {
         dfs_visit(graph, pv_run);
      }
   }

   puts("[END]");

   return;
}

status_t bfs(graph_t graph, vertex_t vertex)
{
   queue_t v_queue = NULL;        // queue of vertex base address
   p_vnode_t p_vnode = NULL;      
   p_vnode_t de_node = NULL;
   p_dcll_node_t ph_run = NULL;
   p_vnode_t v_adj = NULL;

   reset(graph);

   v_queue = create_queue();

   p_vnode = search_vnode(graph->p_graph, vertex);
   if(p_vnode == NULL)
   {
      return(G_VINVALID);
   }

   assert(success == enqueue(v_queue, p_vnode));

   printf("\n\t BFS Visit\n");
   printf("[START]-");
   while(is_queue_empty(v_queue) != queue_empty)
   {
      assert(success == dequeue(v_queue, &de_node));
      de_node->color = Gray;
      printf("[%d]-", de_node->v_data);

      ph_run = de_node->adj_list->next;
      for(ph_run ; ph_run != de_node->adj_list ; ph_run = ph_run->next)
      {
         v_adj = search_vnode(graph->p_graph, ((p_enode_t)ph_run->data)->e_data);

         if(v_adj == NULL)
            return(G_CORRUPTED);

         if(v_adj->color == White)
         {
            v_adj->color = Gray;
            assert(success == enqueue(v_queue, v_adj));
         }

      }
   }
   printf("[END]\n");

   assert(success == destroy_queue(&v_queue));
   v_queue = NULL;

   return(SUCCESS);
}

status_t dijkstra(graph_t graph, vertex_t source)
{
   // u - vertex, v - adjacent vertices of u
   p_vnode_t sv_node = NULL;
   p_vnode_t pv_u = NULL;             // pointer to vnode of u
   p_vnode_t pv_v = NULL;
   p_dcll_node_t ph_run = NULL;       // pointer horizontal list traversal
   p_dcll_node_t pv_run = NULL;       // pointer to vertical list traversal
   queue_t queue = NULL;

   sv_node = search_vnode(graph->p_graph, source);

   if(sv_node == NULL)
     return(G_VINVALID);

   initialize_source(graph, sv_node);

   queue = create_queue();

   pv_run = graph->p_graph->next;
   while(pv_run != graph->p_graph)
   {
      assert(success == enqueue(queue, pv_run->data));
      pv_run = pv_run->next;
   }



   while( is_queue_empty(queue) != queue_empty )
   {
      pv_u = NULL;

      
      priority_dequeue(queue, &pv_u);
      
      ph_run = pv_u->adj_list->next;
      while(ph_run != pv_u->adj_list)
      {
         
         pv_v = search_vnode(graph->p_graph, ((p_enode_t)ph_run->data)->e_data);
         relax(graph, pv_u, pv_v);
         ph_run = ph_run->next;
      }

   
   }

   assert( success == destroy_queue(&queue));

   return(SUCCESS);
}

status_t print_shortest_path(graph_t graph, vertex_t vertex)
{
   stack_t stack = NULL;
   p_vnode_t poped_vnode = NULL;
   p_vnode_t p_vertex = NULL;
   p_vnode_t p_vnode = NULL;

   p_vertex = search_vnode(graph->p_graph, vertex);
   if(p_vertex == NULL)
   {
      return(G_VINVALID);
   }

   stack = create_stack();

   p_vnode = p_vertex;
   while(p_vnode != NULL)
   {
      push(stack, p_vnode);
      p_vnode = p_vnode->u_pred;
   }

   printf("shortest path to [%d] is : ", vertex);
   while(is_stack_empty(stack) != Stack_empty)
   {
      pop(stack, &poped_vnode);
      printf("[%d]<->", poped_vnode->v_data);
   }
   printf("[cost - %lf]\n", p_vertex->d);

   destroy_stack(&stack);

   return(SUCCESS);
}

void All_shortest_path(graph_t graph)
{
   p_dcll_node_t p_vnode = NULL;

   p_vnode = graph->p_graph->next;
   while(p_vnode != graph->p_graph)
   {
      print_shortest_path(graph, ((p_vnode_t)p_vnode->data)->v_data);
      p_vnode = p_vnode->next;
   }

   printf("\n");
   return;
}




//********************************************   AUXILLARY FUNCTIONS   **************************************

static void* xmalloc(size_t size)
{
   void* p = (void*) malloc(size);

   if(p == NULL)
   {
      fprintf(stderr, "ERROR:fatal: out of virtual memory\n");
      return(NULL);
   }

   return(p);
}

void dfs_visit(graph_t graph, p_dcll_node_t print_node)
{
   p_dcll_node_t ph_run = NULL;
   p_dcll_node_t pv = NULL;

   printf("[%d]-", ((p_vnode_t)print_node->data)->v_data);
   ((p_vnode_t)print_node->data)->color = Gray;

   // traversing horizontal list / adjacency list
   ph_run = ((p_vnode_t)print_node->data)->adj_list->next;
   for( ;ph_run != ((p_vnode_t)print_node->data)->adj_list ; ph_run = ph_run->next )
   {
      pv = search_dvnode(graph->p_graph, ((p_enode_t)ph_run->data)->e_data);
      if(((p_vnode_t)pv->data)->color == White)
      {
         dfs_visit(graph, pv);
      }
   }

   ((p_vnode_t)print_node->data)->color = Black;
   return;
}

static p_vnode_t search_vnode(list_t vlist, data_t vdata)  // it will return the address which kept as data in linked list
{
   p_dcll_node_t p_run = NULL;

   p_run = vlist->next;
   while(p_run != vlist)
   {
      p_vnode_t check = p_run->data;

      if(check->v_data == vdata)
      {
         return(check);
      }
      p_run = p_run->next;
   }

   return(NULL);
}

static p_dcll_node_t search_dvnode(list_t vlist, data_t vdata)   // it will return the address of linked list node
{
   p_dcll_node_t p_run = NULL;

   p_run = vlist->next;
   while(p_run != vlist)
   {
      p_vnode_t check = p_run->data;

      if(check->v_data == vdata)
      {
         return(p_run);
      }
      p_run = p_run->next;
   }

   return(NULL);
}


static p_enode_t search_enode( list_t adj_list, data_t edata)    // edata - edge data
{
   p_dcll_node_t p_run = NULL;
   
   p_run = adj_list->next;
   while(p_run != adj_list)
   {
      p_enode_t check = p_run->data;

      if(check->e_data == edata)
      {
         return(check);
      }
      p_run = p_run->next;
   }

   return(NULL);
}

static status_t adj_insert(list_t list, data_t adj_data, weight_t weight)
{
   p_enode_t enode = NULL;
   status_t status = 0;

   enode = (p_enode_t)xmalloc(SIZE_ENODE);
   
   enode->e_data = adj_data;
   enode->weight = weight;

   status = insert_end(list, enode);

   if(status == FAILURE)
   {
      free(enode);
      return(FAILURE);
   }
   
   return(SUCCESS);
}

static status_t adj_remove(list_t list, list_data_t adj_data)
{
   list_data_t data = NULL;
   status_t status = 0;

   status = remove_data(list, adj_data, &data);
   if(status == SUCCESS)
   {
      free(data);
      return(SUCCESS);
   }

   return(status);
}

static status_t remove_vnode(list_t vlist , data_t vdata)
{
   p_dcll_node_t p_run = NULL;
   p_dcll_node_t list_node = NULL;
   p_vnode_t data_vnode = NULL;    
   p_vnode_t delete_vertex = NULL;
   status_t status = 0;

   p_run = vlist->next;
   while(p_run != vlist)
   {
      p_vnode_t check = p_run->data;

      if(check->v_data == vdata)
      {
         data_vnode = check;
         list_node = p_run;
         break;
      }
      p_run = p_run->next;
   }

   free(data_vnode->adj_list);   // free the vertex adjacency list
   status = remove_data(vlist, data_vnode, &delete_vertex);
   assert(status == SUCCESS);

   free(delete_vertex);
   return(SUCCESS);
}

static void reset(graph_t graph)
{
   p_dcll_node_t pv_run = NULL;

   pv_run = graph->p_graph->next;
   for(pv_run; pv_run != graph->p_graph ; pv_run = pv_run->next)
   {
      ((p_vnode_t)pv_run->data)->color = White;
   }

   return;
}

static void initialize_source(graph_t graph, p_vnode_t p_source)
{
   p_dcll_node_t pv_run = NULL;

   pv_run = graph->p_graph->next;
   while(pv_run != graph->p_graph)
   {
      ((p_vnode_t)pv_run->data)->d = INFINITY;
      ((p_vnode_t)pv_run->data)->u_pred = NULL;

      pv_run = pv_run->next;
   }

   p_source->d = 0.0;

   return;
}

static void relax(graph_t graph, p_vnode_t u, p_vnode_t v)
{
   p_enode_t adj_node = NULL;
   weight_t e_weight = 0.0;   // weight of edge between u and v

   adj_node = search_enode(u->adj_list, v->v_data);
   e_weight = adj_node->weight;

   if(v->d > (u->d + e_weight) )
   {
      v->d = u->d + e_weight;
      v->u_pred = u;
   }

   return;
}

static status_t  priority_dequeue(queue_t queue, p_vnode_t* pv_node)
{
   p_dcll_node_t q_run = NULL;
   data_t curr_min = 0;
   p_vnode_t pv_curr_min = NULL;           // pointer to vnode of current minimum vertex
   p_dcll_node_t queue_min = NULL;
   status_t status = 0;
   

   curr_min = ((p_vnode_t)(queue->next->data))->d;

   q_run = queue->next;
   while(q_run != queue)
   {
      if(((p_vnode_t)q_run->data)->d <= curr_min)
      {
         curr_min = ((p_vnode_t)q_run->data)->d ;
         pv_curr_min = q_run->data;
         queue_min = q_run;        // list nodes address 
      }

      q_run = q_run->next;
   }

   //*pv_node = pv_curr_min;
   assert(success == remove_data(queue, pv_curr_min, pv_node));

   return(SUCCESS);
}


