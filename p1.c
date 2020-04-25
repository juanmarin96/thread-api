#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

void *factorial (void *arg);

int main (int argc, char *argv[]) {
  srand(time(0));
  int n1 = atoi(argv[1]);
  int n2 = atoi(argv[2]);
  pthread_t factorial1, factorial2;
  void *res1, *res2;
  if (argc== 3) {
    pthread_create(&factorial1, NULL, &factorial, &n1);
    pthread_create(&factorial2, NULL, &factorial, &n2);
    pthread_join(factorial1, &res1);
    pthread_join(factorial2, &res2);
    printf("Factorial de: %d es: %lld \n", n1, res1);
    printf("Factorial de: %d es: %lld \n", n2, res2);
  }
  return 0;
}

void *factorial (void *arg) {
  int resultado = 1;
  int n = *((int *)arg);
  int num;
  for (num=2; num<= n; num++) {
    resultado= resultado*num;
    printf ("Factorial de %d, resultado parcial %d\n", n, resultado);
  }
  return resultado;
}