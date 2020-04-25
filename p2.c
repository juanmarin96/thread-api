#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

void *factorial (void *arg);

int main (int argc, char *argv[]) {
  srand(time(0));
  pthread_t threads[argc];
  int results[argc];
  for (int i = 0; i < argc - 1; i++)
    {
        int valdir = atoi(argv[i + 1]);
        pthread_create(&threads[i], NULL, &factorial, &valdir);
    }
  for (int j = 0; j < argc - 1; j++)
    {
        pthread_join(threads[j], (void *)&results[j]);
        printf("Factorial de: %d es: %lld con identificador: %d\n",
                atoi(argv[j + 1]),
                results[j],
                threads[j]);
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