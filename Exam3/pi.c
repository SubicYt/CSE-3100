#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N_THREADS 2
#define SAMPLE_SIZE 10000000

typedef struct thread_arg_tag {
  int id; //id for the thread.
  int count; //num points whose distance is in radius
  int total; //num points that this thread should generate
} thread_arg_t;

double rand_double(unsigned int *s) { return (rand_r(s) / (double)RAND_MAX); }


void *thread_main(void *thread_arg) {
  thread_arg_t *arg = thread_arg;
  double x,y;
  unsigned int seed = arg->id;
  for(int i = 0; i < arg->total; i++){
    x = rand_double(&seed);
    y = rand_double(&seed);
    
    if( x*x + y*y <=1){
      arg->count++; //points inside of circle.
    }
  }
}

int main(int argc, char *argv[]) {

  int n = SAMPLE_SIZE;
  int n_threads = N_THREADS;

  int total_count = 0;

  if (argc > 1) {
    n = atoi(argv[1]);
  }
  if (argc > 2) {
    n_threads = atoi(argv[2]);
  }

  pthread_t thread_arr[n_threads];
  thread_arg_t thread_args[n_threads];
//generate_points(n , thread_args[i].id)
  for(int i = 0; i < n_threads; i++){
    thread_args[i].id = i;
    thread_args[i].count = 0;
    thread_args[i].total = n / n_threads;
    if(pthread_create(&thread_arr[i], NULL, thread_main, &thread_args[i]) != 0){
      perror("oh no, create failed");
      exit(1);
    }
  }

  for(int i =0; i < n_threads; i++){
    if(pthread_join(thread_arr[i], NULL)!= 0){
      perror(" join failed");
      exit(1);
    }
  }

  for(int i = 0; i < n_threads; i++){
    total_count = thread_args[i].count;
  }
  double pi = 4.0 * total_count / (double)n;

  printf("pi = %.2f\n", pi);

  return 0;
}
