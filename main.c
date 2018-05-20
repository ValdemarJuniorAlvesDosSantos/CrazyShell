/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: 2015100354
 *
 * Created on 23 de Abril de 2018, 12:02
 */
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // For the syscall functions.
#include <sys/wait.h>
#include <signal.h>
/*
 *
 */

 int PID_filho = 0; //pid do processo filho

 void CtrlC(int sig){ //tratamento do Ctrl+C
     signal(SIGINT, SIG_IGN); //ignora sinais
     sigset_t mask; //máscara
     sigfillset(&mask);
     sigprocmask(SIG_SETMASK, &mask, NULL);
     char c;
     if ("%d",PID_filho);
     if (PID_filho==0){ //caso não haja filhos, retorna
         signal(SIGINT, CtrlC);
         sigemptyset(&mask);
         sigprocmask(SIG_SETMASK, &mask, NULL);
         return;
     }
     printf("Não adianta me enviar um sinal por Ctrl-c, não vou morrer! Você quer suspender meu filho que está rodando em foreground? s/n:\n");
     c = getchar();
     if (c == '\n' || c == 's'){
        kill(PID_filho, SIGSTOP); //suspende o filho
        if (c=='s'){
            getchar();
        }
     }
        sigemptyset(&mask);
        sigprocmask(SIG_SETMASK, &mask, NULL);
        signal(SIGINT, CtrlC);     
 }

void libera(char** recebido){ //libera alocação
    for (int o=0;o<6;o++){
        free(recebido[o]);
    }
    free(recebido);
}

int daExec(char** recebido,int b){ //executa um programa 
    switch (b){
        case 0:{
            execlp(recebido[0],recebido[0],NULL);
            return  execl(recebido[0],recebido[0],NULL);
        }
        case 1:{
            execlp(recebido[0],recebido[0],recebido[1],NULL);
            return execl(recebido[0],recebido[0],recebido[1],NULL);
        }
        case 2:{
            execlp(recebido[0],recebido[0],recebido[1],recebido[2],NULL);
            return execl(recebido[0],recebido[0],recebido[1],recebido[2],NULL);
        }
        case 3:{
            execlp(recebido[0],recebido[0],recebido[1],recebido[2],recebido[3],NULL);
            return execl(recebido[0],recebido[0],recebido[1],recebido[2],recebido[3],NULL);
        }
        case 4:{
            execlp(recebido[0],recebido[0],recebido[1],recebido[2],recebido[3],recebido[4],NULL);
            return execl(recebido[0],recebido[0],recebido[1],recebido[2],recebido[3],recebido[4],NULL);
        }
        
        
    }
    
}
void trataWait(){ //faz o tratamento do wait
    int status;
    int a;
    pid_t childpid;
    while ((childpid = waitpid(-1, &status,WNOHANG))){
        if ((childpid == -1))
            break;
        printf("o processo %d ",childpid);
        if (WIFEXITED(status)){
            printf("morreu de morte morrida(exit)\n");
        }else{
            printf("morreu de morte matada(signal)\n");
        }
    }
    printf("Todos os filhos estão descançando em paz\n");
}

void trataExit(){ //trata o Exit
    int a;
    int status;
    while (a=wait(&status)!=-1){// espera todos os filho até terminarem
    }
    printf("Fim da shell.\n"); //finaliza a CrazyShell
}

int main(int argc, char** argv) {
    signal(SIGINT, CtrlC);
    int pai= getpid();
    fork();
    if (getpid()!=pai){
        execlp("clear","clear",NULL);
    }
    int h=wait(&h);
   
    char** recebido=(char**)(malloc(sizeof(char*)*5));
    for (int o=0;o<6;o++){
        recebido[o]=malloc(sizeof(char)*50);
    }
    int filho;
    int neto=-1;
    int i=0,j=0;

    while (1) {
        if (pai==getpid()){
                printf("ModoCrazyShell:");
                PID_filho=0;
                strcpy(recebido[0],"");
                strcpy(recebido[1],"");
                strcpy(recebido[2],"");
                strcpy(recebido[3],"");
                strcpy(recebido[4],"");
                i=0;
                j=0;
                char c;
                scanf("%c",&c);
                while (c!='\n' && i<5){
                    if(c!=' '){
                        recebido[i][j]=c;
                        scanf("%c",&c);
                        j++;                                          
                    }else{
                        recebido[i][j]='\0';
                        i++;
                        j=0;
                        scanf("%c",&c);
                    }                    
                }
                recebido[i][j]='\0';          
                if (!strcmp(recebido[0],"exit")){
                   
                   trataExit();
                   
                    return 0;
                }
                if (!strcmp(recebido[0],"wait")){
                    trataWait();
                }else{
                    filho = fork();
                    PID_filho = filho;
                    int status;
                    int h = waitpid(filho,&status,WUNTRACED);
                }
        }
        
        if (filho==0){
            filho=getpid();
            
            int a=0;
            neto = fork();                     
            if (filho == getpid()){ 
                signal(SIGINT, SIG_IGN);                         
                a = daExec(recebido,i);               
                exit(0);
            }
            
        }
        
        if (neto==0){
            int a;
           if (setsid()==-1){
               printf("o processo neto nao foi pra background");
            }
            a = daExec(recebido,i);
            
            exit(0);

        }
    }
    
        

}
