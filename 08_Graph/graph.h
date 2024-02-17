
#ifndef _GRAPH_H
#define _GRAPH_H

#include<stdbool.h>
#include<stdlib.h>
#include"list.h"

#define    SUCCESS          0
#define    FAILURE          1
#define    GRAPH_EMPTY      2

#define    G_VEXISTS        3
#define    G_EEXISTS        4
#define    G_VINVALID       5
#define    G_EINVALID       6
#define    G_CORRUPTED      7 

#define    SIZE_GRAPH       sizeof(struct graph)
#define    SIZE_VNODE       sizeof(struct vertex)
#define    SIZE_ENODE       sizeof(struct edge)

typedef    int       data_t;
typedef    int*      p_data_t;
typedef    int       status_t;
typedef    int       len_t;
typedef    double    weight_t;
typedef    int       color_t;
typedef    int       vertex_t;
typedef    unsigned long   count_t;

typedef    struct graph        graph_data_t;
typedef    struct graph*       graph_t;          // represents graph in client side 
typedef    struct graph**      p_graph_t;        // pointer to graph for client (but it is pointer to pointer to struct graph)

typedef    struct vertex       vnode_t;           //  Vertex node
typedef    struct vertex*      p_vnode_t;         //  pointer to vertex node (vertical list)
typedef    struct edge         enode_t;
typedef    struct edge*        p_enode_t;         //  pointer to edge node (horizontal list)

enum color
{
   White = 0,
   Gray,
   Black
};
   

//  struct type definitions

//     node will contain pointer to graph  and details
struct graph
{
   list_t    p_graph;         // pointer to the list of vertices and their adjacency list
   count_t   nr_vertex;       // total no. of vertices
   count_t   nr_edges;        // total no. of edges
};

//    node of graph  (vertical list)
struct vertex
{
   data_t    v_data;
   color_t   color;
   weight_t  d;          // cost from source node to vertex
   p_vnode_t u_pred;
   list_t    adj_list;   // pointer to the list which contain adjacent vertices of vertex     
};

struct edge
{
   data_t  e_data;
   weight_t weight;    // weight of edge
};

//     node of adjacency list   (horizontal list)
/* struct adjacency
{
   data_t data;          // vertex
   p_adjacency_t  prev;
   p_adjacency_t  next;
}; */

//********************************************  INTERFACE FUNCTIONS   **************************************
status_t  create_graph(p_graph_t graph);

status_t  add_vertex(graph_t graph, data_t vdata);
status_t  add_edge(graph_t graph, data_t v_start, data_t v_end, weight_t weight);

status_t  remove_vertex(graph_t graph, data_t vdata);
status_t  remove_edge(graph_t graph, data_t  v_start, data_t v_end);

void dfs(graph_t graph);

status_t bfs(graph_t graph, int v);
 
status_t dijkstra(graph_t graph, data_t source);

status_t print_shortest_path(graph_t graph, vertex_t vertex);

void All_shortest_path(graph_t graph);

void print_graph(graph_t graph, const char* msg);

status_t destroy_graph(p_graph_t p_graph); 



//********************************************   AUXILLARY FUNCTIONS   **************************************
static void* xmalloc(size_t Size);

static p_vnode_t search_vnode(list_t vlist, data_t vdata);         // return the address of vnode which is list data 
static p_dcll_node_t search_dvnode(list_t vlist, data_t vdata);    // return the address of list node's address
static p_enode_t search_enode( list_t adj_list, data_t edata);

static status_t adj_insert(list_t list, data_t adj_data, weight_t weight);
static status_t adj_remove(list_t list, list_data_t adj_data);

static status_t remove_vnode(list_t vlist , data_t vdata);

// DFS and BFS
static void dfs_visit(graph_t graph, p_dcll_node_t print_node);

static void reset(graph_t graph);

// DIJKSTRA
static void initialize_source(graph_t graph, p_vnode_t source);
static void relax(graph_t graph, p_vnode_t u, p_vnode_t v);     // u - vertex, v - adjacent vertices of u



//  interface function
//static status_t  priority_dequeue(queue_t queue, p_vnode_t* pv_node);

#endif


// p directly dispatched to pageing unit 
