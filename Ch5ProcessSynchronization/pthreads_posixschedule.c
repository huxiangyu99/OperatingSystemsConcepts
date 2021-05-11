#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5

void *runner(void *param);

int main(int argc, char **argv) {
  int policy;
  pthread_t tid[NUM_THREADS];
  pthread_attr_t attr;

  pthread_attr_init(&attr);
  if (pthread_attr_getschedpolicy(&attr, &policy) != 0) {
    fprintf(stderr, "unable to get policy.\n");
  } else {
    if (policy == SCHED_OTHER) {
      printf("SCHED_OTHER\n");
    } else if (policy == SCHED_RR) {
      printf("SCHED_RR\n");
    } else if (policy == SCHED_FIFO) {
      printf("SCHED_FIFO\n");
    }
  }
  if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0) {
    fprintf(stderr, "unable to set policy.\n");
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    char num[2];
    sprintf(num, "%d", i);
    pthread_create(&tid[i], &attr, runner, &num);
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  return 0;
}

void *runner(void *param) {
  printf("the %d pthread.\n", atoi(param));
  pthread_exit(0);
}