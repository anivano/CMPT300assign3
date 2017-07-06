#include <stdio.h>
#include "list.h"

extern LIST * jobQueue;
extern LIST * highQueue;
extern LIST * medQueue;
extern LIST * lowQueue;
extern LIST * deviceQueue;

//Proccess Control Block - PCB
typedef struct {
    int PID; //Process ID
    int priority; //Priority can be: 0, 1, 2
    int state; // 0 - running, 1 - ready, 2 - blocked
} PCB;

int init(){

}

int create(int priority){


    return priority; //return priority ID on success.
}

int fork(){

    return 1;
}

int kill(int pid){

    return pid;
}

//Kill currently running process.
int ex(){

    return 1;
}

int quantum(){

    int pid = 0;
    return pid;
}

//Send a message to another process 
//- block until reply is recieved.
//ARGS: 
//  pid of process to send msg to.
//  null-terminated string, max 40 chars.
int send(int pid, char *msg){

    return 1;
}

//Receive a message - block until one arrives.
int receive(){


    return 1;
}

//Unblock sender and deliver reply
int reply(int pid, char *msg){

    return 1;
}

//Initialize the named semaphore with the value gives.
//ID's can take a value from 0 to 4. This can only be done
//once for a semaphore - subsequent attempts result in error.
int newSemaphore(int semaphore, int initVal){
    
    return 1;
}

//Execute the semaphore P operation on behalf of the running
//process. You can assume semaphores IDs are 0 to 4.
int semaphoreP(int semID){

    return 1;
}

//Execute V operation on behalf of running process.
int semaphoreV(int semID){

    return 1;
}

//Dump complete state information of process to screen
//This includes process status and anything else you
//can think of
int procinfo(int pid){

    return 1;
}

//Display all process queues + their contents.
int totalinfo(){

    return 1;
}
