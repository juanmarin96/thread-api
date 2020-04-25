
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h> 
#include <pthread.h>

#define MAXLON 1000


typedef struct arr
{
    int n;
    int *data;
} my_array;


typedef  struct args
{
    my_array *arr;
    int init;
    int end;
} my_args;

void* sumaHilos(void *args);
void* construirVector(char *file, my_array *arr);
void anadirItem(my_array *arr, int item);

int main (int argc, char *argv[]) {
    struct timeval start, end;
    char* file = argv[1];
    my_array arr = {};
    pthread_t t1, t2;
    construirVector(file,&arr);
    int mitad = arr.n / 2;
    printf ("%d",mitad);
    printf("Total elementos del vector: %d\n", arr.n);
    my_args args1={&arr,0,mitad};
    my_args args2={&arr,mitad,arr.n};

    int *sum1, *sum2;
    


    
    gettimeofday(&start, NULL); //Inicia conteo
    pthread_create(&t1, NULL, &sumaHilos, &args1);
    pthread_create(&t2, NULL, &sumaHilos, &args2);

    pthread_join(t1, (void **)&sum1);
    pthread_join(t2, (void **)&sum2);
    
    gettimeofday(&end, NULL); // Finaliza conteo
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000) + end.tv_usec) - (start.tv_usec);
    printf("Tiempo que tomó la suma: %d segundos | %d microsegundos\n", seconds, micros);
    printf("Resultado de la suma suma: %d \n",*sum1+*sum2);
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

void* sumaHilos(void *arg){
    int suma = 0;
    my_args args=*((my_args *)arg);
    for(int i = args.init; i < args.end; i++){
        suma = suma + args.arr->data[i];
    }
    printf("Todos los elementos del vector suman: %d\n", suma);

    int *returnf = malloc(sizeof(int));
    *returnf = suma;
    return returnf;
}