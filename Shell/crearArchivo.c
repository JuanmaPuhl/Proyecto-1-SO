#include "common.h"

/**Metodo para crear archivos*/
/**Necesita recibir una direccion o un argumento vacio*/
void crearArchivo(char* n){
    char nombre[200];
    if(n==NULL){ //No se ingreso un argumento
        char cwd[200];
        getcwd(cwd,200*sizeof(char));
        sprintf(nombre,"%s/NuevoArchivo",cwd);//Pongo en el arreglo nombre la direccion predeterminada.
    }
    else{
        if(esAbsoluta(n))
            sprintf(nombre,"%s",n); //Sino, uso la direccion pasada como argumento
        else{
            char cwd[200];
            getcwd(cwd,200*sizeof(char));
            sprintf(nombre,"%s/%s",cwd,n);
        }
    }
    int fd=open(nombre,O_CREAT|O_EXCL,S_IRWXU);
    if(fd!=-1){
        printf("%sArchivo creado con exito.%s\n",VERDE,CERRAR);
        close(fd);
    }
    else{
        putc(0x07, stdout);
        printf("%sNo se ha podido crear el archivo.%s\n",ROJO,CERRAR);
    }
}

int main(int argc, char ** argv){
    if(argc>2){
        printf("%sDemasiados Argumentos%s.\n",ROJO,CERRAR);
        return -1;
    }
    crearArchivo(argv[1]);
    return 1;
}
