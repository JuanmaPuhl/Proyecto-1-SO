#include "common.h"

/**Metodo para eliminar archivos*/
/**Necesita recibir una direccion o un argumento vacio*/
void eliminarArchivo(char* n){
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
    int i=remove(nombre);  //Elimino el archivo
    if(i!=0){
        putc(0x07, stdout);
        printf("%sNo se ha podido eliminar el archivo.%s\n",ROJO,CERRAR);
        }
    else
        printf("%sEliminado correctamente.%s\n",VERDE,CERRAR);
}

int main(int argc, char ** argv){
    if(argc>2){
        printf("%sDemasiados Argumentos%s.\n",ROJO,CERRAR);
        return -1;
    }
    eliminarArchivo(argv[1]);
    return 1;
}
