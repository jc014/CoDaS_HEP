/*

This program will numerically compute the integral of

                  4/(1+x*x)

from 0 to 1.  The value of this integral is pi -- which
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <stdio.h>
#include <omp.h>
static long num_steps = 100000000;
#define Thread_Num 4
double step;
void main ()
{
	  int i, nthreads;
	  double pi, sum = 0.0;
	  double start_time, run_time;
		//double sumpart[Thread_Num];
	  step = 1.0/(double) num_steps;

	  start_time = omp_get_wtime();
		omp_set_num_threads(Thread_Num);
		#pragma omp parallel
		{

			int ID = omp_get_thread_num();
			int nthrds =omp_get_num_threads();
			double x,sumpart;

			int i, is, ie;
			is=ID*num_steps/nthrds;
			ie=(ID+1)*num_steps/nthrds;
			if (ID==(nthrds-1)) ie=num_steps;
			if (ID==0) nthreads=nthrds;
	  	for (i=is,sumpart=0.0;i<ie ; i++){
			  x = (i+0.5)*step;
		  	sumpart += 4.0/(1.0+x*x);
	  	}

			#pragma omp critical
				sum+=sumpart;
		}

		//for(i=0, sum=0.0;i<nthreads;i++) {
		//	sum+=sumpart[i];
		//}
	  pi = step * sum;
	  run_time = omp_get_wtime() - start_time;
	  printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}
