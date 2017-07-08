#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
//#include "list.h"

int main(){


    bool run = true;

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

    printf("\n");
    printf("\n");
    printf("\n");
    printf("ASSIGNMENT THREE: COMPT 300\n");
    printf("Enter 'X' as a command to exit the program.\n");
    printf("\n");
    printf("\n");
    printf("\n");


    do{
        
    
        switch(getMenuResponse()){
            
            
            case 'C':
    	    printf("Enter Process Priority:"
    		   "0 - high, 1 - medium, 2 - low.\n");
    	    scanf("%d", &prty);
    	    
                create(prty);
                break;
    
    
            case 'K':
                printf("Enter the process ID"
    		   " of the process to kill: \n");
       	        scanf("%d", &pid);
    	
    	    //Find process of this ID. If it does not exist, 
    	    //output error message then continue on and user
    	    //can enter ID again if needed.
    
                kll(pid);
                break;
    
            case 'T':
                totalinfo();
                break;
    	
            case 'X':
                run = false;
                break;
                //EXIT THE PROGRAM IF ! IS ENTERED.
        
            case 'I':
		printf("Enter the process ID of the process you wish to see: \n");
		scanf("%d", pid);

    	    //Find process of this ID. If it does not exist, 
    	    //output error message then continue on and user
    	    //can enter ID again if needed.

                procinfo(pid);
                break;

            case 'Q':
                quantum();
                break;

            //If command is not recognized, print error message and continue.
            default:
    	        printf("Command not recognized, please try again.\n");
//       	        break;
    

    
    /*
            case 'F':
                fork(); 
                break;
    
    
            case 'E':
                exit();
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
    
    
    
    */
    
        } //END SWITCH

    }while(run == true); //END DO-WHILE

    return 0;
}
