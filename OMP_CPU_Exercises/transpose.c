//
// Program: transpose
//
// Purpose: This is a simple program to tranpose a matrix.  
//          we can use this to explore the features of the
//          memory subsystem on a single node.
//  
// Usage:   To keep the code as simple as possible, matrix
//          order is set below in a #define.  So compile
//          and run the executable.  No input required.
//
// History: Written by Tim Mattson, September 2021
//
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(val1, val2) (((val1)>(val2)) ? (val2):(val1))
#define ORDER 10000 

void init_arrs(int N, double *A, double *B)
{

// initialize arrays A and B 
   for (int i=0; i<N; i++) { 
     for (int j=0; j<N; j++) { 
          B[i+N*j] = 0.0;
          A[i+N*j] = 5.0*i+(double)j; 
     } 
   } 
}

void trans_test(int N, double *A, double *B)
{

   double start_time, time;

   start_time = omp_get_wtime();
   for (int i=0; i<N; i++) { 
     for (int j=0; j<N; j++) { 
                 B[i+N*j] = A[j+N*i]; 
      } 
   } 
   time = omp_get_wtime() - start_time;

// Test transpose results
   long err = 0;
   for (int i=0; i<N; i++) { 
     for (int j=0; j<N; j++) { 
          if(B[i+N*j] != (5.0*j+(double)i)) err++; 
//          printf(" B[%d][%d] = %f   %f\n",i,j,B[i+N*j], 5.0*j+(double)i); 
     } 
   } 
   printf(" Sequential Transpose in %f seconds with %ld errors\n",time,err);
}


int main()
{
   int N = ORDER;
   double *A = (double*)malloc(N*N*sizeof(double));
   double *B = (double*)malloc(N*N*sizeof(double));

   init_arrs(N, A, B);
   trans_test(N, A, B);

}
