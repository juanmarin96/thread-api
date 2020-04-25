
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h> 


#define MAXLON 1000


typedef struct arr
{
    int n;
    int *data;
} my_array;


void sumaSecuencial(my_array *arr);
void* construirVector(char *file, my_array *arr);
void anadirItem(my_array *arr, int item);

int main (int argc, char *argv[]) {
    struct timeval start, end;
    char* file = argv[1];
    my_array arr={};
    construirVector(file,&arr);
    gettimeofday(&start, NULL); //Inicia conteo
    sumaSecuencial(&arr);
    gettimeofday(&end, NULL); // Finaliza conteo
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000) + end.tv_usec) - (start.tv_usec);
    printf("Tiempo que tomó la suma: %d segundos | %d microsegundos\n", seconds, micros);
}

void* construirVector(char *file, my_array *arr) {
    int pos,cont = 0, leidos;
    char cadena[MAXLON];
    int fd;
    fd= open(file,O_RDONLY);
    while ((leidos =read(fd,cadena,MAXLON))!= 0) {
        for (pos= 0; pos< leidos; pos++) {;
            int numero = cadena[pos] - 48;
            anadirItem(arr, numero);
        }
    }
    close(fd);
}


void anadirItem(my_array *arr, int item){
    void* tmp;
    if(arr->n==0){
        tmp = malloc(sizeof(int));
        arr->n=1;
        arr->data=tmp;
    }
    else
    {
        arr->n=arr->n+1;
        tmp = realloc(arr->data, arr->n*sizeof(int));
        if (tmp != NULL) {
            arr->data=tmp;
        }
    }
    
    arr->data[arr->n-1]=item;
}

void sumaSecuencial(my_array *arr){
    int suma = 0;
    for(int i = 0; i< arr->n; i++){
        suma = suma + arr->data[i];
    }
    printf("Total elementos del vector: %d\n", arr->n);
    printf("Todos los elementos del vector suman: %d\n", suma);
}