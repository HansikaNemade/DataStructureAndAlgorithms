// Headers
#include<stdio.h>
#include<assert.h>
#include"graph.h"



struct edges
{
    data_t v_start;
    data_t v_end;
    weight_t weight;
};

// ENTRY POINT OF MAIN FUNCTION
int main(void)  
{
    graph_t graph = NULL;
    status_t status = 0;

    data_t vertex[] = {1, 2, 3, 4, 5, 6};
    struct edges E[] = { {1, 2, 3.0}, {1, 6, 1.0},
                        {2, 1, 3.0}, {2, 6, 4.0}, {2, 5, 3.0}, {2, 3, 5.0},
                        {3, 2, 5.0}, {3, 5, 3.0}, {3, 4, 1.0},
                        {4, 3, 1.0}, {4, 5, 2.0}, 
                        {5, 2, 3.0}, {5, 3, 3.0}, {5, 6, 4.0}, {5, 4, 2.0},
                        {6, 1, 1.0}, {6, 2, 4.0}, {6, 5, 4.0} 
                      };

    create_graph(&graph);

    for(int le = 0; le < sizeof(vertex)/sizeof(vertex[0]);  le++)
    {
        status = add_vertex(graph, vertex[le]);
        assert(status == SUCCESS);
    }

    for(int le = 0; le < sizeof(E)/sizeof(E[0]); le++)
    {
        status = add_edge(graph, E[le].v_start, E[le].v_end, E[le].weight);
        assert(status == SUCCESS || status == G_EEXISTS);
    }

    print_graph(graph, "after inserting data");

    dfs(graph);
    printf("\n\n");

    bfs(graph, 1);

    printf("\n\n");

    dijkstra(graph, 1);
    All_shortest_path(graph);

    status = remove_edge(graph, 1, 6); 
    assert(status == SUCCESS); 
    status = remove_edge(graph, 5, 3); 
    assert(status == SUCCESS); 


    print_graph(graph, "graph after removing edges, (1, 6), (5, 3)"); 

    status = remove_vertex(graph, 2); 
    assert(status == SUCCESS); 
    print_graph(graph, "graph after removing vertex 2"); 

    status = add_vertex(graph, 7); 
    assert(status == SUCCESS); 

    status = add_edge(graph, 1, 7, 3.0); 
    assert(status == SUCCESS); 

    status = add_edge(graph, 1, 4, 7.0); 
    assert(status == SUCCESS); 

    status = add_edge(graph, 3, 7, 5.0); 
    assert(status == SUCCESS); 

    status = add_edge(graph, 5, 7, 4.0); 
    assert(status == SUCCESS); 

    print_graph(graph, "graph after adding vertex 7 and adding edges (1, 7), (1, 4), (3, 7), (5, 7):"); 

    dfs(graph);
    printf("\n\n");

    bfs(graph, 1);

    printf("\n\n");


    status = destroy_graph(&graph); 
    assert(status == SUCCESS && graph == NULL); 

    printf("end");

    exit(0);
}
