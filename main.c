#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"


//--------------------------------------------------------------------------getMenuResponse()
//Gets the response from user for Switch statement
//Display file path with ">" at the end for user to input command.
char getMenuResponse()
{
    char input;                      //Users menu choice.
    char cwd[1024];                  //Current Working Directory

    getcwd(cwd, sizeof(cwd));        //Gets the CWD
    printf("%s > ", cwd);
    
    while ((input = getchar()) == '\n' || input == EOF) { } //Ignores the \n char at end of input

    //If the user enters a lower-case letter, this 
    //converts it to an upper-case letter.
    return toupper(input);
}

//------------------------------------------------------------------------------init()
void init(){
    
    normalPriority = ListCreate();
    jobQueue = ListCreate();
    readyQueue = ListCreate();
    highPriority = ListCreate();
    lowPriority = ListCreate();
    printf("Queue's declared.\n");

    return;
}

//------------------------------------------------------------------------------------Command 'C' 
//A new PCB is created, initialized, and placed on the queue.
int create(int priority){
    

    
    //Allocate space for the node and the PCB
    NODE * item = (NODE *) malloc(sizeof(NODE));
    PCB * controlBlock = (PCB *)malloc(sizeof(PCB));

    //This will be the process ID
    int id = ListCount(jobQueue) + 1;

    //Assign the PCB to the data of the new item NODE.
    item->data = controlBlock;

    //Assign ready as false. It will be false until the PCB
    //is placed in the appropriate ready Queue's.
    controlBlock->ready = false;
    controlBlock->pid = id;

    //Place PCB in appropriate Queue depending on Priority.
    if(priority == 0){

	//If Priority is High, add PCB to the highPriority queue
	//and assign priority of 0.
	controlBlock->priority = 0;
	controlBlock->state = 'r';
        controlBlock->ready = true;
        ListAppend(highPriority, item);

    } else if(priority == 1){

	//If Priority is Normal, add the PCB to the normalPriority
	//Queue, and assign a priority of 1.
	controlBlock->priority = 1;
	controlBlock->state = 'r';
        controlBlock->ready = true;
        printf("normalPriority address = %ld\n", normalPriority);
        ListAppend(normalPriority, item);

    } else {

	//If Priority is Low, add PCB to the lowPriority queue
	//Assign priority = 2.
	//Assign ready = true.
	controlBlock->priority = 2;
	controlBlock->state = 'r';
        controlBlock->ready = true;
        ListAppend(lowPriority, item);
    }

    printf("jobQueue address = %ld\n", jobQueue);
    ListAppend(jobQueue, &controlBlock);

    int count = ListCount(jobQueue);
    printf("Number of jobs in Queue: %d\n", count);

    return id; //return process ID on success.
}


//-------------------------------------------------------------------------Commmand 'K'
//Kill process with given process ID.
int kll(int pid){

    //Find the PCB with that particular ID
    //ListSearch(jobQueue, controlBlock.pid);

    PCB * controlBlock = ListFirst(jobQueue);

    //Remove item from the priority queue.
    if(controlBlock->priority == 0){
    
	

    } else if(controlBlock->priority == 1){

    } else {

    }

    //Remove PCB from jobQueue.

    return 1;
}


//--------------------------------------------------------------------------Command 'T'
//Display all process queues + their contents.
void totalinfo(){

    //Create NODE which we will read from?
    NODE * high = ListFirst(jobQueue);

    //This is the PCB which we will print.
    PCB * h = (PCB *) malloc(sizeof(PCB));

    //Check that there is something to print.
    //If list is empty, there are no processes
    //print message then return.

    if(ListCount(jobQueue) == 0){
	printf("No process to show!\n");
        return;
    }

    printf("\n");
    printf("ALL JOBS:\n");

    h = high -> data;

    do{
        printf("Priority: %d\n", h->priority);
        printf("Process ID: %d\n", h->pid);
        printf("state: %c\n", h->state);
        high = high->next;
    }while(high != NULL);


//    NODE * high = ListFirst(highPriority);
//    NODE * normal = ListFirst(normalPriority);
//    NODE * low = ListFirst(lowPriority);
//    if(high == NULL && normal == NULL && low == NULL) {
//        printf("No processes to show\n");
//        return;
//    }
//
//    //Print PCB for each data in all the priority queue's
//    //Print priority, id, ready, and state.
//    printf("High Priority Processes:\n");
//
//        PCB * h = high->data;
//	
//        do{
//            printf("Priority: %d\n", h->priority);
//            printf("Process ID: %d\n", h->pid);
//            printf("state: %s\n", h->state);
//            high = high->next;
//	}while(high != NULL);
//
//    printf("Normal Priority Processes:\n");
//   
//        PCB * n = normal->data;
//	
//        do{
//            printf("Priority: %d\n", n->priority);
//            printf("Process ID: %d\n", n->pid);
//            printf("state: %s\n", n->state);
//            normal = normal->next;
//	}while(normal != NULL);
//
//    printf("Low Priority Processes:\n");
//
//        PCB * l = low->data;
//	
//        do{
//            printf("Priority: %d\n", l->priority);
//            printf("Process ID: %d\n", l->pid);
//            printf("state: %s\n", l->state);
//            low = low->next;
//	}while(low != NULL);

    return; 
}

//------------------------------------------------------------------Command 'F'
//Copy the currently running process and put it on the read Q corresponding to
//the original process' priority.
//Attempting to fork the 'init()' process should fail.
int fork(){

    PCB * block; //Create a new PCB for a new process. 
		 //Copy currently running process to
		 //this new process/PCB.

    PCB * current;    

    block->priority = current->priority;
 
    block->state = "ready";
    current->state = "ready";
    //remove from 'running' list??
    //move to ready queue

    if(block->priority == 0){
        ListAppend(highPriority, &block);
    } else if(block-> priority == 1){
        ListAppend(normalPriority, &block);
    } else if(block->priority == 2){
        ListAppend(lowPriority, &block);
    } else {
        printf("Error, please try again.\n");
        return 4; 
    }

    ListAppend(jobQueue, &block);

    block-> pid = ListCount(jobQueue) + 1;
    return block->pid;
}

//---------------------------------------------------------------------Command 'Q'
int quantum(){

    return 0;
}


//---------------------------------------------------------------------Command 'I'
//Dump complete state information of process to screen
//This includes process status and anything else you
//can think of
int procinfo(int id){

    NODE * proc = ListFirst(jobQueue);
    
    PCB * block = proc->data;

    int i = ListCount(jobQueue);

    while(block->pid != id){
        proc = proc->next;
        block = proc->data;
    }

    printf("Process ID: %d\n", block->pid);
    printf("Process Priority: %d\n", block->priority);
    printf("Process State: %s\n", block->state);

    return 1;
}

int main(){
    ListsInit();

    bool run = true;

    //if(ListCount(readyQueue) == 0){
       init(); //This gets called first and does:
    //} 
    
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
            
            //Command C
            case 'C':
    	        printf("Enter Process Priority:"
    		   "0 - high, 1 - medium, 2 - low.\n");
                char tmp;
                while ((tmp = getchar()) == '\n' || tmp == EOF) { }

                prty = (int) tmp - 0x30;
                printf("\nInteger is: %d\n", prty);
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
