#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <string.h>
#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>


int main(){

    if(ListCount(readyQueue) == 0){
        init(); //This gets called first and does:
    } 

    
    //Comands:
    //C - create
    //F - fork
    //K - kill
    //E - exit
    //Q - quantum
    //S - send
    //R - receive
    //Y - reply
    //N - New Semaphore
    //P - Semaphore P
    //V - Semaphore V
    //I - Procinfo
    //T - Totalinfo

    int prty;
    int pid;
    char * message;
    char * command;


    
	    printf("Enter Process Priority:"
		   "0 - high, 1 - medium, 2 - low.\n");
	    scanf("%d", &prty);
            printf("You entered: %d", prty);

    switch(getMenuResponse()){
        
        
        case 'C':
	    printf("Enter Process Priority:"
		   "0 - high, 1 - medium, 2 - low.\n");
	    scanf("%d", &prty);
	    
            create(prty);
            break;
/*
        case 'F':
            fork(); 
            break;

        case 'K':
            kill();
            break;

        case 'E':
            exit();
            break;

        case 'Q':
            quantum();
            break;

        case 'S':
            send();
            break;

        case 'R':
            receive();
            break;

        case 'Y':
            reply();
            break;

        case 'N':
            newSemaphore();
            break;

        case 'P':
            semaphoreP();
            break;

        case 'V':
            semaphoreV();
            break;

        case 'I':
            procinfo();
            break;

        case 'T':
            totalinfo();
            break;

        case '!':
            break;
            //EXIT THE PROGRAM IF ! IS ENTERED.
*/

    }

    return 0;
}
