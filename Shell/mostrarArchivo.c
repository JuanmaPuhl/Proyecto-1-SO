#include "common.h"

/**Metodo para mostrar por pantalla el contenido de un archivo*/
/**Necesita recibir una direccion o un argumento vacio*/
void mostrarContenidoArchivo(char* n){
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
    char c;
    int fd=open(nombre,O_RDONLY);
    if(fd!=-1){
        printf("%s---------------------------------Contenido--------------------------------------%s\n",AZUL,CERRAR);
        while(read(fd,&c,sizeof(c)!=0))
        printf("%c",c);
        printf("\n");
        printf("%s------------------------------------Fin-----------------------------------------%s\n",AZUL,CERRAR);
        close(fd);
    }
    else{
        putc(0x07, stdout);
        printf("%sNo se ha podido abrir el archivo.%s\n",ROJO,CERRAR);
    }
}

int main(int argc, char ** argv){
    if(argc>2){
        printf("%sDemasiados Argumentos%s.\n",ROJO,CERRAR);
        return -1;
    }
    mostrarContenidoArchivo(argv[1]);
    return 1;
}
