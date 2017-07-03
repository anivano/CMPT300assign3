#include <stdio.h>
#include <list.h>


LIST * queue;

int init(){

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

int create(int priority){

    return pid; //return priority ID on success.
}

int fork(){

    return pid;
}

int kill(int pid){

    return pid;
}

//Kill currently running process.
int exit(){

}

int quantum(){

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
