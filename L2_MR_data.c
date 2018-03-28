#include <stdio.h>
#include <stdlib.h>
#include "papi.h"
#define NUM_EVENTS 2
//Array declaration
double *A, *B, *C;
int dimension;

void simple_multiply(void);
void block_multiply(int);
void reset_matrix (void);

int main(int argc, char **argv)
{
  int i,j;
  long long start_time, end_time;
  float MR_L2 = 0;
  //float rtime, ptime, mflops;
  //long long flpins;
  long long values[NUM_EVENTS];
  int eventset = PAPI_NULL;
  PAPI_library_init(PAPI_VER_CURRENT);
  PAPI_create_eventset(&eventset);
  PAPI_add_event(eventset, PAPI_L2_DCM);
  PAPI_add_event(eventset, PAPI_L2_DCA);
  //PAPI_add_event(eventset, PAPI_L2_TCM);
  //PAPI_add_event(eventset, PAPI_L2_TCA);
  //PAPI_add_event(eventset, PAPI_TLB_TL);
  printf("created and added events.\n");

  if ( argc < 2) {
    printf("Usage: matmul <dimension>\n");
    exit(-1);
  }
        
  dimension = atoi(argv[1]);
    
  A = (double*)malloc(dimension*dimension*sizeof(double));
  B = (double*)malloc(dimension*dimension*sizeof(double));
  C = (double*)malloc(dimension*dimension*sizeof(double));
  if ( NULL == A || NULL == B || NULL == C ) {
    printf("Could not allocate memory. Aborting \n");
    exit (-1);
  }

  //Initialize the arrays with random values
  for(i = 0; i < dimension; i++) {
    for(j = 0; j < dimension; j++) {
      A[dimension*i+j] = (rand()/(RAND_MAX + 1.0));
      B[dimension*i+j] = (rand()/(RAND_MAX + 1.0));
      C[dimension*i+j] = 0.0;
    }
  }

  printf("***********************************simple multiply**********************************************\n");
  PAPI_start(eventset);
  //PAPI_flops(&rtime, &ptime, &flpins, &mflops);
  start_time = PAPI_get_real_usec();
  simple_multiply();
  end_time = PAPI_get_real_usec();
  //PAPI_flops(&rtime, &ptime, &flpins, &mflops);
  printf("Done with simple multiply\n");
  PAPI_read(eventset, values);
  PAPI_stop(eventset, values);
  MR_L2 = (float) values[0]/values[1];
  printf("L2 data misses = %d\nL2 total data cache access = %d\nL2 data miss rate = %f\nexecution time = %lli\n", values[0], values[1], MR_L2, end_time - start_time);
  PAPI_reset(eventset);

  /* Reset the result matrix to zero */
  reset_matrix ();
  MR_L2 = 0;
  //rtime = 0.0; ptime = 0.0;
  //mflops = 0.0; flpins = 0;
  printf("***********************************block size 16************************************************\n");
  PAPI_start(eventset);
  //PAPI_flops(&rtime, &ptime, &flpins, &mflops);
  start_time = PAPI_get_real_usec();
  block_multiply( 16 );
  end_time = PAPI_get_real_usec();
  //PAPI_flops(&rtime, &ptime, &flpins, &mflops);
  printf("Done with block multiply block size 16\n");
  PAPI_read(eventset, values);
  PAPI_stop(eventset, values);
  MR_L2 = (float) values[0]/values[1];
  //printf("L1 misses = %d\nL2 misses = %d\nTLB misses = %d\n", values[0], values[1], values[2]);
  //printf("L1 misses = %d\nL1 miss rate = %f\nL2 misses = %d\nL2 miss rate = %f\nTLB misses = %d\n", values[0], values[0]/values[1], values[2], values[2]/values[3], values[4]);
  //printf("L2 data misses = %d\nL2 total data cache access = %d\nL2 data miss rate = %f\nrtime = %d\nptime = %d\n", values[0], values[1], MR_L2, rtime, ptime);
  printf("L2 data misses = %d\nL2 total data cache access = %d\nL2 data miss rate = %f\nexecution time = %lli\n", values[0], values[1], MR_L2, end_time - start_time);
  PAPI_reset(eventset);

  /* Reset the result matrix to zero */
  reset_matrix ();
  MR_L2 = 0.0f;
  //rtime = 0.0; ptime = 0.0;
  //mflops = 0.0; flpins = 0;
  printf("***********************************block size 32************************************************\n");
  PAPI_start(eventset);
  //PAPI_flops(&rtime, &ptime, &flpins, &mflops);
  start_time = PAPI_get_real_usec();
  block_multiply( 32 );
  end_time = PAPI_get_real_usec();
  //PAPI_flops(&rtime, &ptime, &flpins, &mflops);
  printf("Done with block multiply block size 32\n");
  PAPI_read(eventset, values);
  PAPI_stop(eventset, values);
  MR_L2 = (float) values[0]/values[1];
  //printf("L1 misses = %d\nL2 misses = %d\nTLB misses = %f\n", values[0], values[1], values[2]);
  //printf("L1 misses = %d\nL1 miss rate = %f\nL2 misses = %d\nL2 miss rate = %f\nTLB misses = %d\n", values[0], values[0]/values[1], values[2], values[2]/values[3], values[4]);
  //printf("L2 data misses = %d\nL2 total data cache access = %d\nL2 data miss rate = %f\nrtime = %d\nptime = %d\n", values[0], values[1], MR_L2, rtime, ptime);
  printf("L2 data misses = %d\nL2 total data cache access = %d\nL2 data miss rate = %f\nexecution time = %lli\n", values[0], values[1], MR_L2, end_time - start_time);
  PAPI_reset(eventset);

  /* Reset the result matrix to zero */
  reset_matrix ();
  MR_L2 = 0.0f;
  //rtime = 0.0; ptime = 0.0;
  //mflops = 0.0; flpins = 0;
  printf("***********************************block size 64************************************************\n");
  PAPI_start(eventset);
  //PAPI_flops(&rtime, &ptime, &flpins, &mflops);
  start_time = PAPI_get_real_usec();
  block_multiply( 64 );
  end_time = PAPI_get_real_usec();
  //PAPI_flops(&rtime, &ptime, &flpins, &mflops);
  printf("Done with block multiply block size 64\n");
  PAPI_read(eventset, values);
  PAPI_stop(eventset, values);
  MR_L2 = (float) values[0]/values[1];
  //printf("L1 misses = %d\nL2 misses = %d\nTLB misses = %d\n", values[0], values[1], values[2]);
  //printf("L1 misses = %d\nL1 miss rate = %f\nL2 misses = %d\nL2 miss rate = %f\nTLB misses = %d\n", values[0], values[0]/values[1], values[2], values[2]/values[3], values[4]);
  //printf("L2 data misses = %d\nL2 total data cache access = %d\nL2 data miss rate = %f\nrtime = %d\nptime = %d\n", values[0], values[1], MR_L2, rtime, ptime);
  printf("L2 data misses = %d\nL2 total data cache access = %d\nL2 data miss rate = %f\nexecution time = %lli\n", values[0], values[1], MR_L2, end_time - start_time);
  PAPI_reset(eventset);


  /* Reset the result matrix to zero */
  reset_matrix ();
  MR_L2 = 0.0f;
  //rtime = 0.0; ptime = 0.0;
  //mflops = 0.0; flpins = 0;
  printf("***********************************block size 128***********************************************\n");
  PAPI_start(eventset);
  //PAPI_flops(&rtime, &ptime, &flpins, &mflops);
  start_time = PAPI_get_real_usec();
  block_multiply( 128 );
  end_time = PAPI_get_real_usec();
  //PAPI_flops(&rtime, &ptime, &flpins, &mflops);
  printf("Done with block multiply block size 128\n");
  PAPI_read(eventset, values);
  PAPI_stop(eventset, values);
  MR_L2 = (float) values[0]/values[1];
  //printf("L1 misses = %d\nL2 misses = %d\nTLB misses = %d\n", values[0], values[1], values[2]);
  //printf("L1 misses = %d\nL1 miss rate = %f\nL2 misses = %d\nL2 miss rate = %f\nTLB misses = %d\n", values[0], values[0]/values[1], values[2], values[2]/values[3], values[4]);
  //printf("L2 data misses = %d\nL2 total data cache access = %d\nL2 data miss rate = %f\nrtime = %d\nptime = %d\n", values[0], values[1], MR_L2, rtime, ptime);
  printf("L2 data misses = %d\nL2 total data cache access = %d\nL2 data miss rate = %f\nexecution time = %lli\n", values[0], values[1], MR_L2, end_time - start_time);
  PAPI_reset(eventset);



  free(A);
  free(B);
  free(C);
  return 0;
}

void simple_multiply ( void )
{
    int i, j, k;

    for(i = 0; i < dimension; i++) {
      for(j = 0; j < dimension; j++) {
	for(k = 0; k < dimension; k++) {
	  C[dimension*i+j] += A[dimension*i+k] *
	    B[dimension*k+j];
	}
      }
    }

    return;
}

void block_multiply ( int block )
{
    int i, j, k, p, q, r;
    int block_i, block_j, block_k;
    int num_blocks = dimension / block;

    for(i = 0; i < num_blocks; i++)  {
        block_i = i * block;
        for(j = 0; j < num_blocks; j++)  {
            block_j = j * block;
            for(k = 0; k < num_blocks; k++) {
                block_k = k * block;
                
                for (p=block_i; p < block_i+block; p++)
                    for (q=block_j; q < block_j+block; q++)
                        for (r=block_k; r < block_k+block; r++)
                            C[dimension*p+q] += A[dimension*p+r] *
                                B[dimension*r+q];
            }
        }
    }

    return;
}

void reset_matrix ( void )
{
  int i, j;

  for(i = 0; i < dimension; i++) {
    for(j = 0; j < dimension; j++) {
      C[dimension*i+j] = 0.0;
    }
  }

  return;
}
