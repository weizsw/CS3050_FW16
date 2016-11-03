#include "../include/vector.h"
#include "../include/parsing.h"
#include "../include/input_error.h"

//Parses the input file fp into integers and stores them in vector v. returns 1 if parsing error found.
//Returns 2 if empty file found.

void parse_getline(FILE* fp, struct vector* v)
{
    char* line = NULL;
    unsigned int val;
    char **endptr=NULL;
    int j;
    //int i=1;
    
    //Check if file is empty

    int c = fgetc(fp);
     if (c==EOF)
    {exit(PARSING_ERROR_EMPTY_FILE);}
    
    ungetc(c,fp);
	
    size_t nbytes = 0;
    int linelen=0;
	while ((linelen=getline(&line, &nbytes, fp)) != -1)
    {
		line[linelen-1] = '\0'; //removing the newline and adding the NULL character
        for (j=0; j<linelen-1;j++)
          {if (isdigit(line[j])==0)
               {exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);}
          }
        if (linelen>1) //ignoring empty lines
        {   val = strtoumax(line,endptr,0); //  Convert strings into type uintmax_t. You may use atoi also.
            insert_element_vector(v, val);
        }
		 
         // printf("Line number: %d Content: %s\n",++i,line);
    }
    
    
    free(line);
    
}


