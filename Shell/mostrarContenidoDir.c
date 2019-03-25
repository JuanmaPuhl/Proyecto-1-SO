#include "common.h"

/**Metodo para mostrar por pantalla el contenido de un directorio*/
/**Necesita recibir una direccion o un argumento vacio*/
void mostrarContenidoDirectorio(char* n){
    char nombre[200];
    if(n==NULL){ //No se ingreso un argumento
        char cwd[200];
        getcwd(cwd,200*sizeof(char));
        sprintf(nombre,"%s",cwd);//Pongo en el arreglo nombre la direccion predeterminada.
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
    DIR * dir_ptr = NULL;
	struct dirent * dirent_ptr;
	int count = 0;
	dir_ptr = opendir(nombre); //Intento abrir la direccion
    if(dir_ptr==NULL){//Si no se pudo...
        putc(0x07, stdout);
        printf("%sNo se ha encontrado el directorio.%s\n",ROJO,CERRAR);
    }
    else{
        dirent_ptr=readdir(dir_ptr); //Leo el primer directorio
        while (dirent_ptr != NULL) { //Mientras tenga directorios para leer
        printf( "[%03d] %s\n", ++count, dirent_ptr -> d_name); //Imprimo el directorio
        dirent_ptr=readdir(dir_ptr); //Leo el siguiente directorio
        }
    }
}

int main(int argc, char ** argv){
    if(argc>2){
        printf("%sDemasiados Argumentos%s.\n",ROJO,CERRAR);
        return -1;
    }
    mostrarContenidoDirectorio(argv[1]);
    return 1;
}
