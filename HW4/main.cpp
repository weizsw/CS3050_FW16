
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <stack>
#include <fstream>
#include <istream>
#include <iostream>
#include "input_error.h"
using namespace std;
// a structure to represent a weighted edge in graph
struct Edge
{
    int src, dest, weight;
};
 
// a structure to represent a connected, undirected and weighted graph
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges. Since the graph is
    // undirected, the edge from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    struct Edge* edge;
};
 
// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
    graph->V = V;
    graph->E = E;
 
    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
 
    return graph;
}
 
// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};
 
// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and increment
    // its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

int isCycle( struct Graph* graph )
{
    int V = graph->V;
    int E = graph->E;
 
    // Allocate memory for creating V sets
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );
 
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Iterate through all edges of graph, find sets of both
    // vertices of every edge, if sets are same, then there is
    // cycle in graph.
    for(int e = 0; e < E; ++e)
    {
        int x = find(subsets, graph->edge[e].src);
        int y = find(subsets, graph->edge[e].dest);
 
        if (x == y)
            return 1;
 
        Union(subsets, x, y);
    }
    return 0;
}
 
// The main function to construct MST using Kruskal's algorithm
void KruskalMST(struct Graph* graph, char **argv)
{
    int V = graph->V;
    struct Edge result[V];  // Tnis will store the resultant MST
    int e = 0;  // An index variable, used for result[]
    int i = 0;  // An index variable, used for sorted edges
 
    // Step 1:  Sort all the edges in non-decreasing order of their weight
    // If we are not allowed to change the given graph, we can create a copy of
    // array of edges
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
 
    // Allocate memory for creating V ssubsets
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );
 
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Number of edges to be taken is equal to V-1
    while (e < V - 1)
    {
        // Step 2: Pick the smallest edge. And increment the index
        // for next iteration
        struct Edge next_edge = graph->edge[i++];
 
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
 
        // If including this edge does't cause cycle, include it
        // in result and increment the index of result for next edge
        if (x != y)
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }
 
    // print the contents of result[] to display the built MST
    
    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src + 1, result[i].dest + 1,
                                                   result[i].weight);
    }
    FILE * fp = fopen(argv[2], "w");
    if(!fp){
        exit(FILE_FAILED_TO_OPEN);
    }
    
    for (i = 0; i < e; ++i) {
        fprintf(fp, "(%d,%d)\n", result[i].src + 1, result[i].dest + 1);
    }
    return;
}
 
// Driver program to test above functions
int main(int argc, char** argv)
{
    if(argc != 3)//Incorrect Command line arguments
    {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    int numLines = 0;
    ifstream inData(argv[1]);
    if(!inData){
        exit(FILE_FAILED_TO_OPEN);
    }
    if(inData.peek() == std::ifstream::traits_type::eof()){
        inData.close();
        exit(PARSING_ERROR_EMPTY_FILE);
    }
    string unused;
    while(getline(inData, unused)){
        ++numLines;
    }
    printf("edges number:%d\n", numLines - 1);
    int size = 0;
    int i = 0;
    //get the size of vertex
    FILE * fp = fopen(argv[1], "r");
    if(!fp){
        exit(FILE_FAILED_TO_OPEN);
    }
     
    
    if(feof(fp))//File is empty
    {
        fclose(fp);//Just in case
        exit(PARSING_ERROR_EMPTY_FILE);
    }
    if(fscanf(fp, "%d\n", &size) != 1){
        exit(PARSING_ERROR_INVALID_FORMAT);
    }

     struct Graph* graph = createGraph(size, numLines - 1);
 
   
    char term;
   
    //read every coordinates line by line
    while(!feof(fp)){
        if(fscanf(fp, "(%d,%d,%d)\n", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight) != 3){
            
            exit(PARSING_ERROR_INVALID_FORMAT);
            
        }

        if(graph->edge[i].src <= 0 || graph->edge[i].src > size || graph->edge[i].dest <= 0 || graph->edge[i].dest > size){
            exit(INTEGER_IS_NOT_A_VERTEX);
        }
        ++i;
    }
    printf("vertax number:%d\n\n", size);
    
    for(i = 0; i < numLines - 1; i++) {
        graph->edge[i].src = ((graph->edge[i].src) - 1);
        graph->edge[i].dest = ((graph->edge[i].dest) - 1);
    }
    
    for(i = 0; i < numLines - 1; i++) {
         printf("x%d:%d, y%d:%d, weight:%d\n", i,graph->edge[i].src + 1, i,graph->edge[i].dest + 1, graph->edge[i].weight);
    }
    FILE* fp2 = fopen(argv[2], "w");
    if (isCycle(graph)){
        printf("\ngraph contains cycle\n\n");
        KruskalMST(graph, argv);
    }
    else if(!fp2){
        exit(FILE_FAILED_TO_OPEN);
    }
    else{
        printf( "\ngraph doesn't contain cycle\nPrint 0\\n in the output file" );
        fprintf(fp2, "0\n");
    } 
    if (fclose(fp) == EOF)//File doesn't close
    {
        exit(FILE_FAILED_TO_CLOSE);
    }
    
    if (fclose(fp2) == EOF)//File doesn't close
    {
        exit(FILE_FAILED_TO_CLOSE);
    }
    
 
    return 0;
}