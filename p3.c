
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
  if (argc!= 2) {
    printf ("Indica el nombre de un fichero.\n");
    exit(0);
  }
  pthread_t reader;
  pthread_create(&reader, NULL, &cuenta, (void *)argv[1]);
  pthread_join(reader, NULL);
  return 0;
}

void *cuenta (void *nombre) {
  char* fileName;
  fileName = (char *) nombre;
  printf("%s",fileName);
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