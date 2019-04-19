/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <sys/times.h>
#include <sys/types.h>
#include <time.h>
#define CACHE_MIN (1024) /***smallest cache***/
#define CACHE_MAX (1024 * 1024) /***largest cache***/
#define SAMPLE 10
#ifndef CLK_TCK
#define CLK_TCK 60
#endif
int x[CACHE_MAX];
double get_seconds (){
    struct tms rusage;
    times(&rusage);
    return (double) (rusage.tms_utime)/CLK_TCK;
}


void main()
{
    int register i ,index, stride,limit,temp;
    int steps,tsteps,csize;
    double sec0, sec;
    /* Initialize output */
    for (csize= CACHE_MIN;csize<=CACHE_MAX;csize=csize*2)
      for (stride=1; stride <=csize/2;stride=stride*2){
         sec=0; /* Initialize the timer*/
         limit=csize-stride+1;
         steps=0;
         do {/*repeat until collect 1 second */
         sec0 = get_seconds();/*start timer*/
         for (i=SAMPLE*stride;i!=0;i=i-1)/*larger sample*/
         for (index=0;index<limit;index=index+stride)
         x[index] =x[index]+1;/*cache access*/
         steps = steps+1;/*count while loop iterations*/
         sec= sec+(get_seconds()-sec0);/*end timer*/
         }while (sec < 1.0); /*until collect 1 second*/
         
         tsteps=0;
         do {
             sec0 = get_seconds();/*start timer*/
         for (i=SAMPLE*stride;i!=0;i=i-1)/*larger sample*/
           for (index=0;index<limit;index=index+stride)
              temp=temp+index;
              tsteps = tsteps+1;
              sec = sec - (get_seconds() - sec0);
         }while (tsteps - steps);
         printf ("Size : %7d Stride: %7d read+write :%14.0f ns\n",csize*sizeof(int), stride*sizeof(int),(double)sec*1e9/(steps * SAMPLE*stride*((limit-1)/stride+1)));
         
         }; /*end of both outer loops*/
 

}
