/**Incluyo las librerias a utilizar.*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

/**Defino constantes globales, para probar con nuevos parametros simplemente modificar.*/
#define MAXUSERS 10
#define MAXPRIORIDADES 3
#define MAXIMPRESORAS 2

/**Defino algunas constantes para cambiar los colores de la letra y marcar el estado de la operacion*/
#define ROJO "\E[0;31m"
#define VERDE "\E[0;32m"
#define AZUL "\E[0;34m"
#define CERRAR "\E[00m"

/**Declaro semaforos*/
sem_t impresoras[MAXIMPRESORAS];//Este arreglo de semaforos almacena las impresoras
sem_t usuariosP[MAXPRIORIDADES]; //Este arreglo de semaforos almacena las colas de usarios con prioridad P
sem_t mutex; //Este semaforo actua como un mutex, permitiendo acceso a secciones de codigo o negandolo.
sem_t listos[MAXPRIORIDADES]; //Este arreglo de semaforos almacena los usuarios que ya estan listos para imprimir.
sem_t impresoraDisponible; //Este semaforo es para verificar que hay una impresora libre
sem_t hayAlguien; //Este semaforo es para verificar que llego alguien a imprimir.

/**Estructura auxiliar que me permite pasar los datos como parametro*/
typedef struct aux{
    int contador;
    int prioridad;
} aux;


/**Metodo auxiliar que vigila constantemente los semaforos ante la llegada de un nuevo usuario*/
void* revisarSemaforos(void* args){
    while(1){
        sem_wait(&impresoraDisponible); //Ejecuto solo cuando hay impresoras libres
        sem_wait(&hayAlguien); //Ejecuto solo cuando hay alguien
        sem_post(&impresoraDisponible); //Debo dejar las impresoras como estaban.
        int termine=0,i=MAXPRIORIDADES-1;
            while(!termine && i>=0){ //Recorro todas las colas de prioridad.
                if(sem_trywait(&usuariosP[i])==0){ //Si tiene un usuario dentro.
                    sem_post(&listos[i]);//Lo marco como listo para imprimir, la impresion se hace en el metodo principal de cada usuario.
                    termine=1;
                }
                else //Si no hay nadie paso a la siguiente cola.
                i--;
            }
        sleep(1);
    }
}

/**Metodo auxiliar para pedir una impresora libre*/
int requerirImpresora(int j,int prioridad){
    sem_wait(&mutex);//Bloqueo el mutex para que nadie pueda interrumpir esta parte
    printf("%s[%d] VENGO A IMPRIMIR. Mi prioridad es: %d.%s\n",VERDE,j,prioridad,CERRAR);
    sem_post(&usuariosP[prioridad]); //Pongo en el semaforo la prioridad del usuario.
    sem_post(&hayAlguien);
    sem_post(&mutex); //Libero el mutex
    sem_wait(&listos[prioridad]); //Si es el siguiente a imprimir.
    sem_wait(&impresoraDisponible);// Si hay impresoras libres...
    /**Pido la impresora*/
    if(sem_trywait(&impresoras[0])==0){
        printf("La impresora 1 esta libre.\n");
        return 1;
    }
    if(sem_trywait(&impresoras[1])==0){
        printf("La impresora 2 esta libre.\n");
        return 2;
    }
    return -1;
}

/**Metodo auxiliar que imprime.*/
void imprimir(int j,int n){
    printf("%s[%d] Estoy imprimiendo en la impresora nro %d.%s\n",AZUL,j,n,CERRAR);
    sleep((rand()%3)+1); //Tiempo que espero para simular el retardo de la impresion.(1-3)
    printf("%s[%d] Ya termine de imprimir en la impresora nro %d.%s\n",AZUL,j,n,CERRAR);
}

/**Metodo auxiliar que desbloquea la impresora*/
void liberar(int impresora){
    if(impresora==1){
        sem_post(&impresoras[0]);
    }
    if(impresora==2){
        sem_post(&impresoras[1]);
    }
}

/**Metodo ejecutado por cada hilo*/
void* fHilo(void* arg){
    /**Comienza la etapa de ingreso*/
    aux* est=(aux*) arg;
    int j=est->contador; //Recupero el contador
    int prioridad=est->prioridad; //Recupero la prioridad
    /**Comienza la etapa de impresion*/
    int n=requerirImpresora(j,prioridad); //El usuario pide una impresora.
    printf("[%d] Hay impresoras libres. Voy a imprimir.\n",j);
    if(n==-1){
        printf("%sOcurrio un error inesperado.%s\n",ROJO,CERRAR);
        exit(-1);
    }
    imprimir(j,n);//El usuario j imprime en la impresora n.
    liberar(n); //Libero la impresora utilizada para que pueda ser usada por otro usuario.
    sem_post(&impresoraDisponible);//Ahora hay una nueva impresora disponible
    pthread_exit(EXIT_SUCCESS);
}

int main(){
    /**Genero una seed nueva para que no se repitan prioridades entre distintas ejecuciones.*/
    time_t t;
    srand((unsigned) time(&t));
    int i;
    /**Creo el semaforo de bloqueo de datos*/
    sem_init(&mutex,0,1);
    aux* arregloEst[MAXUSERS];
    pthread_t hilos[MAXUSERS];
    /**Creo los semaforos para cada impresora.*/
    for(i=0; i<MAXIMPRESORAS; i++){
        sem_init(&impresoras[i],0,1);
    }
    /**Inicializo un semaforo auxiliar que cuenta la cantidad de impresoras disponibles*/
    sem_init(&impresoraDisponible,0,MAXIMPRESORAS);
    /**Inicializo un semaforo auxiliar que cuenta las personas que llegaron*/
    sem_init(&hayAlguien,0,0);
    /**Creo los semaforos contadores para las prioridades*/
    for(i=0; i<MAXPRIORIDADES;i++){
        sem_init(&usuariosP[i],0,0);
        sem_init(&listos[i],0,0);
    }
    pthread_t hiloAux;
    pthread_create(&hiloAux,NULL,revisarSemaforos,(void*)1);//Creo un hilo auxiliar que maneje los semaforos
    /**Creo los usuarios*/
    for(i=0; i<MAXUSERS; i++){
        aux* est=(aux*)malloc(sizeof(aux));
        est->contador=i;
        est->prioridad=rand()%MAXPRIORIDADES;//Asigno prioridad. Las posibles son 0,1,2.La prioridad 2 es la mas alta.
        arregloEst[i]=est;
        pthread_create(&hilos[i],NULL,fHilo,(void*)est);
    }
    /**Espero a que terminen los usuarios.*/
    for(i=0; i<MAXUSERS; i++){
        pthread_join(hilos[i],NULL);
    }
    /**Destruyo todos los semaforos usados*/
    for(i=0; i<MAXIMPRESORAS; i++)
    sem_destroy(&impresoras[i]);

    for(i=0; i<MAXPRIORIDADES; i++){
        sem_destroy(&usuariosP[i]);
		sem_destroy(&listos[i]);
	}
	sem_destroy(&mutex);
    /**Libero la memoria de todas las estructuras usadas*/
    for(i=0; i<MAXUSERS;i++){
        free(arregloEst[i]);
    }
    return 0;
}
