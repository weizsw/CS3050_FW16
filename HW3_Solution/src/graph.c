#include "../include/graph.h"

// Initializes a graph with number_of_vertices as the number of vertices. The color of the vertices are set to WHITE.
void init_graph(struct graph* grph, unsigned int number_of_vertices)
{
    unsigned int i;
    grph -> num_vertices = number_of_vertices;
    grph -> vertices= malloc(sizeof(struct vertex)*(number_of_vertices +1));
   
    for (i=1; i<= number_of_vertices; i++)
    {   grph->vertices[i].colour = WHITE;
        init_vector(&(grph->vertices[i].adj));
    }
}

// Returns the color of a vertex
enum Color vertex_color (struct graph *grph, unsigned int vertex)
{
   if (vertex >0)
   {
       return (grph->vertices[vertex].colour);
   }
    exit(VERTEX_OUT_OF_BOUNDS);
}

// Sets the color of a vertex
void set_color (struct graph *grph, unsigned int vertex, enum Color clr)
{
    if (vertex >0)
    {
         grph->vertices[vertex].colour = clr;
    }
}

// Returns the adjacency list of a vertex
struct vector *adj_list (struct graph *grph, unsigned int vertex)
{
    if (vertex >0)
    {
        return (&(grph->vertices[vertex].adj));
    }
    exit(VERTEX_OUT_OF_BOUNDS);
}

// Returns the number of vertices in the graph
unsigned int num_vertices (struct graph* grph)
{
   
    return (grph->num_vertices);


}

// Adds an edge to the graph
void insert_edge (struct graph* grph, unsigned int src, unsigned int dest)
{
    if ((src>0) && (dest >0))
    {
        insert_element_vector(&(grph->vertices[src].adj), dest);
    }
    else
    {exit(VERTEX_OUT_OF_BOUNDS);}
}

// Frees the memory allocated to the adjacency list in a graph
void free_graph(struct graph *grph)
{
    unsigned int i;
    for (i=1; i <= grph->num_vertices; i++)
    free_vector (&(grph->vertices[i].adj));
    free(grph->vertices);
    grph -> num_vertices =0;
    
}

//Prints the graph. Is included for debugging
void print_graph(struct graph *grph)
{
   unsigned int i;
    
    for (i=1; i <= grph->num_vertices; i++)
    {   printf("The adjacency list for vertex %u is:\n",i);
        printf("\n");
        print_vector(&(grph->vertices[i].adj));
    }
}

// Computes the dfs of the graph, returns 0 if the graph has a cycle and 1 otherwise. If the graph is acyclic then stores the topological sort in the array topsort. Uses the iterative version of the DFS.
unsigned int dfs_graph(struct graph *grph, unsigned int *topsort)
{
    // vst is for the stack needed in dfs
    struct stack vst;
    
    struct vector *adj;
    
    unsigned int vertex, adj_list_size, i, acyclic, nextvertex, j,k;
    
   
    if (grph->num_vertices >0)
    {
        
        j=grph->num_vertices;
        acyclic =1;
        init_stack(&vst);
        
        
        // Outer loop of the iterative dfs. Goes through each vertex one-by-one. Starts a dfs from the vertex if the vertex had never been discovered
        
        for (k=1;k<=grph->num_vertices;k++)
        {
          // If vertex k has not been discovered before, start a dfs
         if(vertex_color(grph,k) == WHITE)
         {  push(&vst,k);
            //printf("Vertex being pushed onto stack is %u\n",k);
            while (isempty(&vst)==0)
            {
            
            vertex=pop(&vst);
            //printf("Vertex being popped from stack is %u\n",vertex);
            if (vertex_color(grph, vertex) == GRAY) // The vertex was visited before and the DFS has finished.
            {
                set_color(grph,vertex,BLACK);
                topsort[j--]=vertex; // Store it in topsort in decreasing order of finish times
            }
            if (vertex_color(grph,vertex) == WHITE) // The vertex was not visited before. That is just discovered.
            {
                //printf("Color of vertex %u is %u\n", vertex,vertex_color(grph, vertex));
                set_color(grph,vertex,GRAY);
                push(&vst,vertex);
               // printf("Vertex being pushed onto stack is %u\n",vertex);
                adj = adj_list(grph, vertex); // get the adjacnecy list of the newly discoved vertex.
                adj_list_size = size_vector(adj);
                
                //Iterate through adjacency list
                for(i=0;i<adj_list_size;i++)
                {
                  nextvertex=access_element_vector(adj,i);
                  if (vertex_color (grph,nextvertex) == GRAY)
                       acyclic =0; // An edge from a GRAY vertex to a GRAY vertex. Means a back edge and hence a cycle
                  if (vertex_color (grph,nextvertex) == WHITE)
                      push(&vst,nextvertex);
                }
             }
            }
         }
        }
            return(acyclic);
    }
    return -1;
}

