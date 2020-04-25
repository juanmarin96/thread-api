
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>


#define MAXLON 1000

void *cuenta(void *nombre);

int main (int argc, char *argv[]) {
  pthread_t threads[argc];
  for (int i = 0; i < argc - 1; i++)
    {
        pthread_create(&threads[i], NULL, &cuenta,(void *)argv[i+1]);
    }
  for (int j = 0; j < argc - 1; j++)
    {
        pthread_join(threads[j],NULL);
    }
}

void *cuenta (void *nombre) {
  char* fileName;
  fileName = (char *) nombre;
  int pos, cont= 0, leidos;
  char cadena[MAXLON];
  int fd;
  fd= open(fileName,O_RDONLY);
  while ((leidos =read(fd,cadena,MAXLON))!= 0) {
    for (pos= 0; pos< leidos; pos++) {
      if ((cadena[pos]== 'a') || (cadena[pos]== 'A')) {
        cont++;
      }
    }
  }
  printf("Fichero %s: %d caracteres 'a' o 'A' encontrados\n", nombre, cont);
  close(fd);
}