#include "../include/vector.h"
#include "../include/secondmode.h"
#include "../include/parsing.h"
#include "../include/input_error.h"

int main(int argc, char** argv) {
    struct vector v;
    unsigned int answer;
    
    if (argc != 2)
         exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    
    FILE* fp = fopen(argv[1], "r");
    if (!fp)
        exit(FILE_FAILED_TO_OPEN);
    init_vector(&v);
    
    
    
    parse_getline(fp, &v);
    //print_vector(&v);
    
    answer=second_mode(&v);
   
    
    printf("%d\n", answer);
    free_vector(&v);
    
    if (fclose(fp) == EOF)
        exit(FILE_FAILED_TO_CLOSE);
    
    return 0;
    
}


