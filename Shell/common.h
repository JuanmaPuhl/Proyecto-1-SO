/**Importo las librerias que voy a necesitar*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

/**Defino un maximo para cada parte del comando, de manera que sea mas facil manejarlo*/
#define MAXARG 5

/**Defino algunas constantes para cambiar los colores de la letra y marcar el estado de la operacion*/
#define ROJO "\E[0;31m"
#define VERDE "\E[0;32m"
#define AZUL "\E[0;34m"
#define CERRAR  "\E[00m"

///**Metodo auxiliar para saber si la direccion es absoluta o no*/
int esAbsoluta(char* n){
    if(n[0]=='/')
        return 1;
    else
        return 0;
}
