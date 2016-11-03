#include "../include/graph.h"
#include "../include/input_error.h"
#include "../include/parsing.h"
#include "../include/stack.h"

int main(int argc, char** argv) {
    struct graph grph;
    unsigned int answer;
    unsigned int* topsort=NULL;
    
    // Check the number of arguments
    if (argc != 3)
         exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    
    // Open the input file
    FILE* fp = fopen(argv[1], "r");
    if (!fp)
    {
        exit(FILE_FAILED_TO_OPEN);
    }
    
    //Open the output file
    FILE* fpout = fopen(argv[2], "w");
    if (!fpout)
    {
        exit(FILE_FAILED_TO_OPEN);
    }

    //Input the graph
    parse_getline(fp, &grph);

    //DEBUG print_graph(&grph);

    //Malloc the space needed for storing the topological sort of the graph.
    topsort=malloc(sizeof(unsigned int)*(grph.num_vertices+1));

    //Call the DFS. Returns 0 if graph is cylic and 1 otherwise. topsort stores the topological sort in the second case
    
    answer = dfs_graph(&grph,topsort);
    //printf("%d\n", answer);
    
    //If the graph is acylic
    if (answer==0)
       fprintf(fpout,"0\n");
    
    //If the graph is cylic, print the topological sort
    if (answer==1)
    {
       for (answer=1; answer<=grph.num_vertices; answer++)
       fprintf(fpout,"%u\n",topsort[answer]);
    }
    
    //free the graph
    free_graph(&grph);
    
    //free the topologcial sort
    free(topsort);

    //close the input file
    if (fclose(fp) == EOF)
        exit(FILE_FAILED_TO_CLOSE);
    
    //close the output file
    if (fclose(fpout) == EOF)
        exit(FILE_FAILED_TO_CLOSE);

    
    return 0;
    
}


