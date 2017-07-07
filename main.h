#include <stdio.h>
#include <ctype.h>
#include "list.h"

//Process Control Block
//One exists for each process. Inside it it stored the Process ID,
//the Process Priority, and the process state.
typedef struct {
    int pid;
    int priority;
    int state; //ready, running, blocked, deadlock.
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

//A new PCB is created, initialized, and placed on the queue.
int create(int priority){

    int x = 2;
    PCB controlBlock;
    int id = 0;


    id = ListCount(jobQueue) + 1;

    if(priority = 0){
	//If Priority is High, add PCB to the highPriority queue
	//and assign priority of 0.
	controlBlock.priority = 0;
        ListAppend(highPriority, &controlBlock);
    } else if(priority = 1){
	//If Priority is Normal, add the PCB to the normalPriority
	//Queue, and assign a priority of 1.
	controlBlock.priority = 1;
        ListAppend(normalPriority, &controlBlock);

    } else {
	//If Priority is Low, add PCB to the lowPriority queue
	//Assign priority = 2.
	controlBlock.priority = 2;
        ListAppend(lowPriority, &controlBlock);
    }

	controlBlock.pid = id;
        ListAppend(jobQueue, &controlBlock);

    return id; //return priority ID on success.
}



/************************NON-COMMAND FUNCTIONS. HELPERS?***************************/

//Gets the response from user for Switch statement
char getMenuResponse()
{
  char response;      //Response to the menu.
  char input[256];    //Users menu choice.

  printf("(C)reate, (K)ill, Find an A(U)thor,\n");

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

//int fork(){
//
//    return pid;
//}
//
//int kill(int pid){
//
//    return pid;
//}
//
////Kill currently running process.
//int exit(){
//
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
////Display all process queues + their contents.
//int totalinfo(){
//
//    return 1;
//}
