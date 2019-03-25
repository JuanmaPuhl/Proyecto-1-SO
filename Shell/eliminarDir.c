#include "common.h"

/**Metodo para eliminar directorios*/
/**Necesita recibir una direccion o un argumento vacio*/
void eliminarDirectorio(char* n){
    char nombre[200];
    if(n==NULL){ //No se ingreso un argumento
        char cwd[200];
        getcwd(cwd,200*sizeof(char));
        sprintf(nombre,"%s/NuevaCarpeta",cwd);//Pongo en el arreglo nombre la direccion predeterminada.
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
    int err=rmdir(nombre); //Elimino el directorio en la direccion elegida
    if(!err)
        printf("%sDirectorio eliminado con exito.%s\n",VERDE,CERRAR);
    else{
        putc(0x07, stdout);
        printf("%sNo se ha podido eliminar el directorio.%s\n",ROJO,CERRAR);
        }
}

int main(int argc, char ** argv){
    if(argc>2){
        printf("%sDemasiados Argumentos%s.\n",ROJO,CERRAR);
        return -1;
    }
    eliminarDirectorio(argv[1]);
    return 1;
}
