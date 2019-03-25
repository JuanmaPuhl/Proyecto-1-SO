#include "common.h"

/**Metodo auxiliar para seleccionar la operacion correspondiente*/
/**Recibe la instruccion y los argumentos, ambos ingresados por el usuario*/
int seleccionarComando(char* instr,char ** argv){
    /**Verifico de que comando se trata*/
    if(strcmp(instr,"creaD")==0){
        int i=fork();
        if(i==0){
            if(execv("creaD",argv)<0)
                perror("Ocurrio un error: errno");
        }
        else
           waitpid(-1, NULL, 0);
    }
    else
    if(strcmp(instr,"elimD")==0){
        int i=fork();
        if(i==0){
            if(execv("elimD",argv)<0)
                perror("Ocurrio un error: errno");
        }
        else
           waitpid(-1, NULL, 0);
    }
    else
    if(strcmp(instr,"creaF")==0){
        int i=fork();
        if(i==0){
            if(execv("creaF",argv)<0)
                perror("Ocurrio un error: errno");
        }
        else
           waitpid(-1, NULL, 0);
    }
    else
    if(strcmp(instr,"elimF")==0){
        int i=fork();
        if(i==0){
            if(execv("elimF",argv)<0)
                perror("Ocurrio un error: errno");
        }
        else
           waitpid(-1, NULL, 0);
    }
    else
    if(strcmp(instr,"showD")==0){
        int i=fork();
        if(i==0){
            if(execv("showD",argv)<0)
                perror("Ocurrio un error: errno");
        }
        else
           waitpid(-1, NULL, 0);
    }
    else
    if(strcmp(instr,"showF")==0){
        int i=fork();
        if(i==0){
            if(execv("showF",argv)<0)
                perror("Ocurrio un error: errno");
        }
        else
           waitpid(-1, NULL, 0);
    }
    else
    if(strcmp(instr,"showM")==0){
        int i=fork();
        if(i==0){

        if(execv("showM",argv)<0)
            perror("Ocurrio un error: errno");
        }
        else
           waitpid(-1, NULL, 0);
    }
    else
    if(strcmp(instr,"exit")==0){
        return 0; //Retorno un 0 para que no itere mas y termine la ejecucion
    }
    else{
        putc(0x07, stdout);
        printf("%sComando Invalido.%s\n",ROJO,CERRAR);
    }
    return 1;
}

/**Metodo para manejar la entrada de comandos, devuelve 1 si debe seguir recibiendo comandos, devuelve 0 si se ingreso un exit*/
int iniciar(){
    //Inicializo variables
    char i[100],c,*instruccion,*argumento;
    int q=0,toReturn=1;
    c=getchar(); //Obtengo el primer caracter del comando
    while(c!='\n'){ //Y sigo leyendo mientras el usuario no apriete ENTER
        i[q]=c;
        q++;
        c=getchar();
    }
    i[q]='\0'; //Una vez que termine de leer agrego el caracter vacio al final para evitar problemas
    fflush(stdin);
    /**Creo un arreglo de arreglos de char para almacenar todos los argumentos*/
    char* argv[MAXARG+1];
    /**Lo seteo en NULL para evitar problemas*/
    int x;
    for(x=0; x<MAXARG+1;x++){
        argv[x]=NULL;
    }
    /**Pongo todos los argumentos en argv*/
    int termine=0,m=1;
    instruccion=strtok(i," ");
    argv[0]=instruccion;
    if(instruccion!=NULL){
        while(!termine && m<MAXARG){
            argumento=strtok(NULL," ");
            if(argumento!=NULL && argumento!=" "){
                argv[m]=argumento;
                m++;
            }
            else
                termine=1;
        }
        toReturn= seleccionarComando(instruccion,argv);//Veo que operacion se ingreso
    }
    return toReturn;   //Retorno 1 para seguir iterando
}

/**Metodo principal de shell*/
int main(){
printf("%s-------------------------------Bienvenido/a-------------------------------------\n",AZUL);
    printf("Ingresa showM para obtener ayuda.%s\n",CERRAR);
    int i=1;
    /**Permite al usuario ingresar comandos hasta que ingrese un exit*/
    while(i){
        printf(">>");
        i=iniciar();
    }
    printf("Adios!\n");
    return 0;
}
