#include "../include/vector.h"
#include "../include/parsing.h"
#include "../include/input_error.h"
#include "../include/graph.h"



void parse_getline(FILE* fp, struct graph* grph)
{
    char* line = NULL;
    unsigned int number_of_vertices, in_vertex, out_vertex;
    char **endptr=NULL;
    int j,k;
    //int i=1;
    
    //Check if file is empty
    int c = fgetc(fp);
    if (c==EOF)
       exit(PARSING_ERROR_EMPTY_FILE);
    ungetc(c,fp);
	
    size_t nbytes = 0;
    int linelen=0;



    // Read the number of vertices. 
     linelen = getline(&line, &nbytes, fp);
    
    // EmptyLine
     if (linelen == -1) 
        {exit(PARSING_ERROR_INVALID_FORMAT);}

    // Removing the newline and adding the NULL character
     line[linelen-1] = '\0';
    
    // Check that everything on the line is a digit
     j = 1;
     while (j< linelen -1)
      if (isdigit(line[j++])==0)
         exit(PARSING_ERROR_INVALID_FORMAT);
      

    //Compute the number of vertices
    number_of_vertices = strtoumax(line,endptr,0);
    
    //Check that number of vertices are >0
    if (number_of_vertices==0)
        exit(PARSING_ERROR_INVALID_FORMAT);
    
    
    //DEBUG:printf("number of vertices=%d\n",number_of_vertices);
      
     // Initialize the graph.
    init_graph(grph,number_of_vertices);

    //Read in the edges.
     while ((linelen=getline(&line, &nbytes, fp)) != -1)
    {
        line[linelen-1] = '\0'; //removing the newline and adding the NULL character
        //DEBUG:printf("%s\n", line);
        
        //First character has to be a (
        if (line[0] != '(')
           exit(PARSING_ERROR_INVALID_FORMAT);
        
        //Second character is a digit
        j = 1;
        if (isdigit(line[j++])==0)
            exit(PARSING_ERROR_INVALID_FORMAT);
        
        // Check that everything before a , is a digit
        while ((j< linelen -1) && (line[j] != ','))
            if (isdigit(line[j++])==0)
               exit(PARSING_ERROR_INVALID_FORMAT);
        
        
        
        //This is the starting point of the edge
         in_vertex=strtoumax(&line[1],endptr,0);
        
        //Check that the starting point is a legitimate vertex
         if ((in_vertex>number_of_vertices) || (in_vertex==0))
             exit(INTEGER_IS_NOT_A_VERTEX);
        
         
        k=++j;
        
        //Check if you reached the end of line and if the charatcer after the , is a digit
        if (isdigit(line[j++])==0)
           exit(PARSING_ERROR_INVALID_FORMAT);
    
        // Check that everything before a ) is a digit
         while ((j< linelen -1) && line[j] != ')')
           if (isdigit(line[j++])==0)
               exit(PARSING_ERROR_INVALID_FORMAT);
        
        /*If you reach end of line then that is an error
        if (j==linelen)
        {   printf("Hello2\n");
            //exit(PARSING_ERROR_INVALID_FORMAT);
        }*/
        
        // Check if there is a )
        if (line[j] != ')')
            exit(PARSING_ERROR_INVALID_FORMAT);
        
        //Check that the line ends at )
        if (line[j+1]!='\0')
           exit(PARSING_ERROR_INVALID_FORMAT);
        
       //This is the starting point of the edge
         out_vertex=strtoumax( &line[k],endptr,0);
       
        //Check that the starting point is a legitimate vertex
        if ((out_vertex>number_of_vertices)||(out_vertex==0))
            exit(INTEGER_IS_NOT_A_VERTEX);

       //DEBUG: printf("Line number: %d Edge: (%d,%d)\n",++i,in_vertex, out_vertex);
       
       //Insert the edge
        insert_edge(grph,in_vertex,out_vertex);
        
    }
    
    free(line);

    
}


