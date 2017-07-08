#include <stdio.h>
#include <ctype.h>
#include "list.h"
#include <stdbool.h>
#include <unistd.h>

//Process Control Block
//One exists for each process. Inside it it stored the Process ID,
//the Process Priority, and the process state.
typedef struct {
    int pid;
    int priority;
    bool ready; 
    char * state; //ready, running, blocked, deadlock.
} PCB;

LIST * jobQueue;
LIST * readyQueue;
LIST * highPriority;
LIST * normalPriority;
LIST * lowPriority;

int init(){

    jobQueue = ListCreate();
    readyQueue = ListCreate();
    highPriority = ListCreate();
    normalPriority = ListCreate();
    lowPriority = ListCreate();
}

//------------------------------------------------------------------------------------Command 'C' 
//A new PCB is created, initialized, and placed on the queue.
int create(int priority){

    PCB controlBlock;
    int id = 0;
    controlBlock.ready = false;

    id = ListCount(jobQueue) + 1;

    if(priority = 0){
	//If Priority is High, add PCB to the highPriority queue
	//and assign priority of 0.
	controlBlock.priority = 0;
        controlBlock.ready = true;
        ListAppend(highPriority, &controlBlock);
    } else if(priority = 1){
	//If Priority is Normal, add the PCB to the normalPriority
	//Queue, and assign a priority of 1.
	controlBlock.priority = 1;
        controlBlock.ready = true;
        ListAppend(normalPriority, &controlBlock);

    } else {
	//If Priority is Low, add PCB to the lowPriority queue
	//Assign priority = 2.
	//Assign ready = true.
	controlBlock.priority = 2;
        controlBlock.ready = true;
        ListAppend(lowPriority, &controlBlock);
    }

    controlBlock.pid = id;
    ListAppend(jobQueue, &controlBlock);

    printf("In create()");

    return id; //return priority ID on success.
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


//---------------------------------------------------------------Command 'T'
//Display all process queues + their contents.
void totalinfo(){

    NODE * high = ListFirst(highPriority);
    NODE * normal = ListFirst(normalPriority);
    NODE * low = ListFirst(lowPriority);
    if(high == NULL && normal == NULL && low == NULL) {
        printf("No processes to show\n");
        return;
    }

    //Print PCB for each data in all the priority queue's
    //Print priority, id, ready, and state.
    printf("High Priority Processes:\n");

        PCB * h = high->data;
	
        do{
            printf("Priority: %d\n", h->priority);
            printf("Process ID: %d\n", h->pid);
            printf("state: %s\n", h->state);
            high = high->next;
	}while(high != NULL);

    printf("Normal Priority Processes:\n");
   
        PCB * n = normal->data;
	
        do{
            printf("Priority: %d\n", n->priority);
            printf("Process ID: %d\n", n->pid);
            printf("state: %s\n", n->state);
            normal = normal->next;
	}while(normal != NULL);

    printf("Low Priority Processes:\n");

        PCB * l = low->data;
	
        do{
            printf("Priority: %d\n", l->priority);
            printf("Process ID: %d\n", l->pid);
            printf("state: %s\n", l->state);
            low = low->next;
	}while(low != NULL);

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

/************************NON-COMMAND FUNCTIONS. HELPERS?***************************/

//Gets the response from user for Switch statement
//Display file path with ">" at the end for user to input command.
char getMenuResponse()
{
    char response;      //Response to the menu.
    char input[256];    //Users menu choice.
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s >", cwd);

  scanf("%c", input);
  response = input[0];
  //cin.ignore(256, '\n');

  //If the user enters a lower-case letter, this 
  //converts it to an upper-case letter.
  return toupper(response);
}

//Displays the current file path in the cmd with > at the end.
//void displayPrompt()
//{
//  char currentWD[COMMAND_LENGTH];  // include working directory in prompt
//   if (getcwd(currentWD, sizeof(currentWD)) != NULL){
//     write(STDOUT_FILENO, currentWD, strlen(currentWD));
//   }
//   write(STDOUT_FILENO, "> ", strlen("> "));
//}

//
//int quantum(){
//
//    return pid;
//}
//
////Send a message to another process 
////- block until reply is recieved.
////ARGS: 
////  pid of process to send msg to.
////  null-terminated string, max 40 chars.
//int send(int pid, char *msg){
//
//    return 1;
//}
//
////Receive a message - block until one arrives.
//int receive(){
//
//
//    return 1;
//}
//
////Unblock sender and deliver reply
//int reply(int pid, char *msg){
//
//    return 1;
//}
//
////Initialize the named semaphore with the value gives.
////ID's can take a value from 0 to 4. This can only be done
////once for a semaphore - subsequent attempts result in error.
//int newSemaphore(int semaphore, int initVal){
//    
//    return 1;
//}
//
////Execute the semaphore P operation on behalf of the running
////process. You can assume semaphores IDs are 0 to 4.
//int semaphoreP(int semID){
//
//    return 1;
//}
//
////Execute V operation on behalf of running process.
//int semaphoreV(int semID){
//
//    return 1;
//}
//
////Dump complete state information of process to screen
////This includes process status and anything else you
////can think of
//int procinfo(int pid){
//
//    return 1;
//}
//
