#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void  sleep_sort(int array[]);
void* print_number(void* n);

int main() {
  int array[] = {20, 6, 22, 6, 7, 8, 2, 15, 9, 6};
  sleep_sort(array);

  return 0;
}

void sleep_sort(int array[]) {
  pthread_t threads[10];

  // Spawn a thread for every value in the array, executing print_number
  for (int i = 0; i < 10; i++) {
    pthread_create(&threads[i], NULL, print_number, (void*)&array[i]);
  }

  // Suspend execution until all threads have completed
  for (int i = 0; i < 10; i++) {
    pthread_join(threads[i], NULL);
  }
}

void* print_number(void* n) {
  int val = *((int*)n);
  sleep(val);
  printf("%d\n", val);
}

/*
Output:

$ g++ -lpthread main.cpp && ./a.out
2
6
6
6
7
8
9
15
20
22

*/
