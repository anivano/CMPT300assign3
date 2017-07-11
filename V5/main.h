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
    char * state;             //(r)eady, r(u)nning, (b)locked, (d)eadlock.
    char * proc_message;      //Message to be printed when the process is scheduled.
} PCB;

typedef struct {
    int value;                //Value of semaphore. Between 0 and 4.
    PCB * waiting;            //Process waiting for Semaphore
} SEMAPHORE;

LIST * jobQueue;         //ALL jobs
LIST * readyQueue;       //Ready jobs
LIST * highPriority;     //High Priority (0) jobs
LIST * normalPriority;   //Normal Priority (1) jobs
LIST * lowPriority;      //Low Priority (2) jobs
LIST * messages;	 //Messages to be send back and forth.

int create(int priority);
int kll(int pid);
void killCurrent();
void totalinfo();
int fork();
int quantum();
void procinfo(int processID);

/************************NON-COMMAND FUNCTIONS. HELPERS?***************************/

char getMenuResponse();
void init();


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
//
