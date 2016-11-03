#include "../include/vector.h"
#include "../include/secondmode.h"

//The function sort_vector mergesorts the vector v starting from index left to the index right.
//The function is implemented iteratively and bottom-up. In each iteration, the vector between left and right
//is dividied into blocks of equal size which are sorted thanks to loop invariant; then two consecutive blocks
//(ie, block 1 and block 2, block 3 and 4  and so on) are merged. The block size is then doubled in
//subsequent iterations. The function assumes that left is at least 0 and right is at most vsize-1.
//The initial block-size is 1.

void sort_vector(struct vector *v, unsigned int left, unsigned int right)
{
      unsigned int number_of_elements = right-left+1;
      unsigned int block_size, block_begin;
      unsigned int *temp = malloc(number_of_elements * sizeof(unsigned int));
      unsigned int l_iter, r_iter, temp_iter, r_end, j;
      unsigned int *vec= v->data;
    
     //printf("left=%d,right=%d,number_of_elements=%d\n",left,right,number_of_elements);

      for (block_size =1; block_size < number_of_elements; block_size = block_size *2)
       {
          // In each iteration the block size is doubled. The merge of the two blocks is stored in the temporary array temp
          // and then copied back.
          // temp_iter is used to range over temp.
           
          temp_iter=0;
          for (block_begin =left; block_begin + block_size <= number_of_elements; block_begin = block_begin+ 2*block_size)
                {
                    
                   // In each iteration of this loop, two consecutive blocks of block-size are merged. block_begin
                   // remembers the starting of the left block. r_iter will initially compute the starting of the right block.
                    // r_end computes where the right block ends. Actually it is one past the end of right block.
                    l_iter =block_begin;
                    r_iter =block_begin+block_size;
                    r_end=r_iter + block_size;
                    if (r_end> right)
                       r_end = right+1;
                    //printf("block_size=%d, l_iter=%d,r_iter=%d,r_end=%d\n", block_size, l_iter,r_iter,r_end);
                    
                    while ((l_iter < block_begin +block_size)  && (r_iter < r_end))
                    // Merging the two consecutive blocks into temp
                          {
                              //printf( "l_iter=%d, r_iter= %d, temp_iter= %d\n ", l_iter, r_iter, temp_iter);
                            if (vec [l_iter] < vec [r_iter])
                                 {temp[temp_iter]= vec[l_iter];
                                     l_iter++;
                                     temp_iter++;
                                 }
                            else 
                                 {temp[temp_iter]= vec[r_iter];
                                     r_iter++;
                                     temp_iter++;
                                 }
                          }
                    
                     while (l_iter < block_begin +block_size)
                         { //printf("%d ", temp_iter);
                          temp[temp_iter]= vec[l_iter];
                          l_iter++;
                          temp_iter++;
                         }
                    
                     while (r_iter < r_end)
                          {  //printf("%d ", temp_iter);
                            temp[temp_iter]= vec[r_iter];
                            r_iter++;
                            temp_iter++;
                          }
                
                    for (j=block_begin; j<r_end; j++)
                    {
                        //Copy the temporary back to v
                        vec[j]= temp[j-left];
                        
                    }
                    //printf("\n");
                    //printf("Block_size=%d, Block_begin=%d\n", block_size, block_begin);
                    //print_vector(v);
                }
       }
    free (temp);    
}

