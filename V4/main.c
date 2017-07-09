#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "main.h"


//-------------------------------------------------------------------------------getMenuResponse()
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

//-----------------------------------------------------------------------------------------init()
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

    //Allocate space for the the PCB
    PCB * controlBlock = (PCB *)malloc(sizeof(PCB));

    //This will be the process ID
    int id = ListCount(jobQueue) + 1;

    controlBlock->pid = id;
    controlBlock->priority = priority;
    controlBlock->state = 'r';
    controlBlock->ready = true;

    //Place PCB in appropriate Queue depending on Priority.
    if(priority == 0){
        ListAppend(highPriority, controlBlock);
    } else if(priority == 1){
        ListAppend(normalPriority, controlBlock);
    } else {
        ListAppend(lowPriority, controlBlock);
    }

    ListAppend(jobQueue, controlBlock);

//    int count = ListCount(jobQueue);
//    printf("Number of jobs in Queue: %d\n", count);

    printf("\n");
    printf("\n");

//    while(item != NULL) {
//
//        printf("\n");
//        PCB * test = (PCB *) item->data;
//
//        printf("Priority: %d\n", test->priority);
//        printf("Process ID: %d\n", test->pid);
//        printf("state: %c\n", test->state);
//        item = item->next;
//
//        printf("\n");
//    }

    printf("\n");
    printf("\n");

    return id; //return process ID on success.
}


//-------------------------------------------------------------------------Commmand 'K'
//Kill process with given process ID.
int kll(int id){

    //Find the PCB with that particular ID
    //ListSearch(jobQueue, controlBlock.pid);

    NODE * control = ListFirst(jobQueue);

    //Declare PCB.
    PCB * block;
    int currentID;

    //Get PCB from that NODE
    //Get info from PCB
    //Print that info.
    printf("\n");

    //Find the Queue item with the appropriate ID
    do{

        //Assign node data to PCB h.
        block = (PCB *) control->data;

        printf("\n");
        currentID = block->pid; 
        control = control->next;

    }while(currentID != id);

    //Remove item from the priority queue.
    if(block->priority == 0){
        //remove from highPriority queue. 
        printf("Remove item from HP queue.\n");

	//Set This item to current then use
        //ListRemove() to remove it.

    } else if(block->priority == 1){
        //remove from normalPriority queue. 
        printf("Remove item from NP queue.\n");

	//Set This item to current then use
        //ListRemove() to remove it.

    } else {
        //remove from lowPriority queue. 
        printf("Remove item from LP queue.\n");

	//Set This item to current then use
        //ListRemove() to remove it.

    }

    //Remove PCB from jobQueue.

    return 1;
}


//--------------------------------------------------------------------------Command 'T'
//Display all process queues + their contents.
void totalinfo(){

    //Check that there is something to print.
    //If list is empty, there are no processes
    //print message then return.
    if(ListCount(jobQueue) == 0){
	printf("No process to show!\n");
        return;
    }


    //Create NODE then assign the head of the jobQueue to this node.
    NODE * ctrlContainer = ListFirst(jobQueue);

    //Declare PCB.
    PCB * block;

    int pr;
    int id;
    char * st;

    //Get PCB from that NODE
    //Get info from PCB
    //Print that info.
    printf("\n");
    printf("ALL JOBS:\n");

    //While there is a next item in the Queue, 
    //print it's information.
    do{

        //Assign node data to PCB h.
        block = (PCB *) ctrlContainer->data;

        printf("\n");

        //Get info from PCB, assign to these variables.
        //Not actually necessary. But here it is.
        pr = block->priority;
        id = block->pid; 
        st = block->state;

        printf("\n");
        printf("\n");

        printf("Priority: %d\n", pr);
        printf("Process ID: %d\n", id);
        printf("state: %c\n", block->state);
        ctrlContainer = ctrlContainer->next;

        printf("\n");
        printf("\n");

    }while(ctrlContainer != NULL);

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
void procinfo(int id){

    //Check that there is something to print.
    //If list is empty, there are no processes
    //print message then return.
    if(ListCount(jobQueue) == 0){
	printf("No process to show!\n");
        return;
    }

    int x = ListCount(jobQueue);

    if(id > x){
        printf("Invalid Process ID. Try again.\n");
        return;
    }

    //Declare a NODE then assign the head of the jobQueue to this node.
    NODE * ctrlContainer = ListFirst(jobQueue);

    //Declare PCB.
    PCB * block;
    int currentID;

    //Get PCB from that NODE
    //Get info from PCB
    //Print that info.
    printf("\n");
    printf("ALL JOBS:\n");

    //Find the Queue item with the appropriate ID
    do{

        //Assign node data to PCB h.
        block = (PCB *) ctrlContainer->data;

        printf("\n");
        currentID = block->pid; 
        ctrlContainer = ctrlContainer->next;

    }while(currentID != id);

    printf("Priority: %d\n", block->priority);
    printf("Process ID: %d\n", currentID);
    printf("state: %c\n", block->state);
    printf("\n");

    return; 
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

		//Check that the priority entered is legitimate.
		//If not, print error message and break.
                if(prty > 2 || prty < 0){
		    printf("You've entered an invalid priority level."
			 	"Please try again.\n");
		    break;
                }

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
    
            //Command T
            case 'T':
                totalinfo();
                break;
    	
            case 'X':
                run = false;
                break;
                //EXIT THE PROGRAM IF ! IS ENTERED.
        
            case 'I':
		printf("Enter the process ID of the process you wish to see: \n");

                char i;
                while ((i = getchar()) == '\n' || i == EOF) { }

                pid = (int) i - 0x30;

                int x = ListCount(jobQueue);
                printf("Job queue: %d\n", x);


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
