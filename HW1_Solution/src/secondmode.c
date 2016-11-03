#include "../include/vector.h"
#include "../include/secondmode.h"

// The function second_mode computes the element with the second highest frequency in the vector v.
unsigned int second_mode(struct vector *v)
{
    unsigned int size= v->size;
    if (size==0)
    { return 0;}
    else
    {
     //First sort the vector.
     sort_vector(v,0,size-1);
     
     // We will read the sorted vector from left to right. The variable mode remembers the element with the highest frequency seen thus far and
     // highest_frequency remembers frequency of mode. The variable second_mode remembers the element with the second highest frequency seen thus far and
     // second_highest_frequency remembers frequency of second_mode. the variable current_frequency remembers the frequency of the current element.
     unsigned int highest_frequency=0;
     unsigned int second_highest_frequency =0;
     unsigned int mode=0;
     unsigned int sec_mode =0;
     unsigned int current_frequency =1;
     unsigned int current_number = v->data[0];
     unsigned int iter=1;
        
        
     //printf("Input Elements Sorted are\n");
     //print_vector(v);
        
     while (iter<=size)
     { //printf("iter=%d,highest_frequency=%d, second_highest_frequency=%d, mode=%d, sec_mode=%d, current_number=%d\n", iter, highest_frequency, sec_mode, mode,sec_mode,current_number);
        if ((iter<size) && (v->data[iter]==current_number))
        {current_frequency ++;}
       else
       {
         if (current_frequency > highest_frequency)
         {sec_mode=mode;
          mode=current_number;
          second_highest_frequency=highest_frequency;
          highest_frequency=current_frequency;
         }
         else
            if (current_frequency == highest_frequency )
              {if (current_number > mode) mode=current_number;
              }
            else
                if (current_frequency > second_highest_frequency || ((current_frequency == second_highest_frequency) && (sec_mode<current_number)) )
                {second_highest_frequency=current_frequency;
                 sec_mode=current_number;
                }
           
           if (iter<size)
           {current_frequency =1;
            current_number = v->data[iter];
           }
         
       }
         iter++;
     }
        return sec_mode;
    }
        
}

