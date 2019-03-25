#include "common.h"

/**Metodo para mostrar la lista de comandos y su utilidad.*/
void mostrarManual(){
    printf("%s-----------------------------------Manual---------------------------------------%s\n",AZUL,CERRAR);
    printf("\n");
    printf("creaD: Crea un directorio en el sistema, el usuario puede elegir la direccion ingresandola como argumento.\n");
    printf("elimD: Elimina un directorio en el sistema, el usuario puede elegir la direccion ingresandola como argumento.\n");
    printf("creaF: Crea un archivo de texto en el sistema, el usuario puede elegir la direccion ingresandola como argumento.\n");
    printf("elimF: Elimina un archivo de texto en el sistema.\n");
    printf("showD: Muestra por pantalla el contenido de un directorio dado.\n");
    printf("showF: Muestra por pantalla el contenido de un archivo dado.\n");
    printf("showM: Muestra informacion sobre los posibles comandos.\n");
    printf("exit: Finaliza la ejecucion del shell.\n");
    printf("\n");
    printf("%s--------------------------------------------------------------------------------%s\n",AZUL,CERRAR);
    printf("\n");
}

int main(int argc, char ** argv){
    if(argc>1){
        printf("%sDemasiados Argumentos%s.\n",ROJO,CERRAR);
        return -1;
    }
    mostrarManual();
    return 1;
}
