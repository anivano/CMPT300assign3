#include <stdio.h>
#include <string.h>
//#include "list.h"
#include "main.h"

int main(){

//    if(ListCount(*queue) == 0){
//        init(); //This gets called first and does:
//    } 

    char command;
    int prty;
    
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


    switch(command){
        
        case 'C':
	    printf("Input the priority of the proccess"
		   "0 - High, 1 - Normal, 2 - Low: \n");              
	    scanf("%d", &prty);
            create(prty);
            break;

        case 'F':
            fork(); 
            break;

        case 'K':
//            kill();
            break;

        case 'E':
            ex();
            break;

        case 'Q':
            quantum();
            break;

        case 'S':
//            send();
            break;

        case 'R':
//            receive();
            break;

        case 'Y':
//            reply();
            break;

        case 'N':
//            newSemaphore(0,0);
            break;

        case 'P':
//            semaphoreP(0);
            break;

        case 'V':
//            semaphoreV(0);
            break;

        case 'I':
//            procinfo(0);
            break;

        case 'T':
            totalinfo();
            break;

        case '!':
            break;
            //EXIT THE PROGRAM IF ! IS ENTERED.

    }

    return 0;
}
