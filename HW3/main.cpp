/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Shaowei Zhou
 *
 * Created on 2016年10月17日, 下午2:51
 */
#include <list>
#include <stack>
#include <fstream>
#include <string>
#include <istream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "input_error.h"
using namespace std;

typedef struct
{
    int x;
    int y; 
} point;

// represent a graph
class Graph
{
	int V; // the vertex's namount

	// Pointer to an array containing adjacency listsList
	list<int> *adj;

	//used by topologicalSort
	void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);
        bool isCyclicUtil(int v, bool visited[], bool *rs); 
public:
	Graph(int V); // Constructor

	// add edges to graph
	void addEdge(int v, int w);

	// prints the topological sort
	void topologicalSort(char** argv);
        bool isCyclic();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
    if(visited[v] == false)
    {
        // make visited node and recursion
        visited[v] = true;
        recStack[v] = true;
 
        // put all vertex in adj
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
                return true;
            else if (recStack[*i])
                return true;
        }
 
    }
    recStack[v] = false;  // clear the vertex
    return false;
}

bool Graph::isCyclic()
{
    //same as above
    bool *visited = new bool[V];
    bool *recStack = new bool[V];
    for(int i = 0; i < V; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }
 
    // Call the recursive helper function to determine cycle
    // DFS trees function
    for(int i = 0; i < V; i++)
        if (isCyclicUtil(i, visited, recStack))
            return true;
 
    return false;
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to vertex list.
}

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[], 
								stack<int> &Stack)
{
	// set the current node as visited.
	visited[v] = true;

	// Recursion for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			topologicalSortUtil(*i, visited, Stack);

	// push vertex
	Stack.push(v);
}

//  Topological Sort. It is recursive 
void Graph::topologicalSort(char **argv)
{
	stack<int> Stack;

	// mark all the vertices  not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// store Topological
	// Sort starting from all vertices one by one
	for (int i = 1; i < V; i++)
	if (visited[i] == false)
		topologicalSortUtil(i, visited, Stack);

	// Print out and write in file
       
        ofstream file(argv[2]);
	while (Stack.empty() == false)
	{
		cout << Stack.top() << " ";
                file << Stack.top() << "\n";
		Stack.pop();
                
	}
        
}

// Driver
int main(int argc, char** argv)
{   
    if(argc != 3)//Incorrect Command line arguments
    {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    int numLines = 0;
    ifstream inData(argv[1]);
    // open file count lines
    if(!inData){
        exit(FILE_FAILED_TO_OPEN);
    }
    //check empty file
    if(inData.peek() == std::ifstream::traits_type::eof()){
        inData.close();
        exit(PARSING_ERROR_EMPTY_FILE);
    }
    //lines count
    string unused;
    while(getline(inData, unused)){
        ++numLines;
    }
    
    printf("edges number:%d\n", numLines - 1);
//    point points[numLines + 100] = {0};
//    char delim;
//    int i;
//    if(inData.is_open()){
//        inData >> points[0].size;
//        for(i = 0; i < numLines; i++){
//        inData >> points[i].x
//                >>delim
//                >>points[i].y;
//        }
//    }      
//    printf("size:%d\n", points[0].size);
//    
    //open file error chekc failed to open
    FILE * fp = fopen(argv[1], "r");
    if(!fp){
        exit(FILE_FAILED_TO_OPEN);
    }
    int size = 0;
    point points[numLines + 100];
    int i = 0;
    //get the size of vertex
    if(fscanf(fp, "%d\n", &size) != 1){
        exit(PARSING_ERROR_INVALID_FORMAT);
    }
    if(feof(fp))//File is empty
    {
        fclose(fp);//Just in case
        exit(PARSING_ERROR_EMPTY_FILE);
    }
    char term;
    //read every coordinates line by line
    while(!feof(fp)){
        if(fscanf(fp, "(%d,%d)\n", &points[i].x, &points[i].y) != 2){
            
            exit(INTEGER_IS_NOT_A_VERTEX);
            
        }

        if(points[i].x <= 0 || points[i].x > size || points[i].y <= 0 || points[i].y > size){
            exit(INTEGER_IS_NOT_A_VERTEX);
        }
        ++i;
    }
    printf("vertax number:%d\n", size);
    printf("x1:%d, y1:%d\n", points[0].x, points[0].y);
    

    int vertex = size + 1;
    // Create a graph given in the above diagram
    Graph g(vertex);
    //make graph
    for(i = 0; i < numLines - 1; i++){
         g.addEdge(points[i].x,points[i].y);
    }
    //cycle check
    if(g.isCyclic()){
    cout << "Graph contains cycle";
    FILE * wp = fopen(argv[2], "w");
    if(!wp){
        exit(FILE_FAILED_TO_OPEN);
    }
        fprintf(wp,"0\n");
    }
    else{
    cout << "Graph doesn't contain cycle\n";

    cout << "Following is a Topological Sort of the given graph \n";

    g.topologicalSort(argv);
    } 
    //file close
    if (fclose(fp) == EOF)//File doesn't close
    {
        exit(FILE_FAILED_TO_CLOSE);
    }

    return 0;
}
