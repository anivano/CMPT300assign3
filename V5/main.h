#include <stdio.h>
#include <ctype.h>
#include "list.h"
#include <stdbool.h>
#include <unistd.h>

//---------------------------------Structs

//Process Control Block
//One exists for each process. Inside it it stored the Process ID,
//the Process Priority, and the process state.
typedef struct {
    int pid;                  //Process ID
    int priority;             //Process Priority
    bool ready;               //Is this process ready to run? ******** I don't thing this is necessary?? 
    char * state;             //(r)eady, r(u)nning, (b)locked, (d)eadlock.
    char * proc_message;      //Message to be printed when the process is scheduled.
} PCB;

//Semaphore
//We can only have a maximum of 5. 
//Semaphore ID's will be from 0 to 4. Only one semaphore
//of each ID can exist. Must wait for an ID to be freed
//before another new semaphore can be created.
typedef struct {
    int value;                //Value of semaphore. Between 0 and 4.
    int sid;		      //Semaphore ID
    PCB * waiting;            //Process waiting for Semaphore
} SEMAPHORE;

//---------------------------------Lists

LIST * jobQueue;         //ALL jobs
LIST * readyQueue;       //Ready jobs
LIST * highPriority;     //High Priority (0) jobs
LIST * normalPriority;   //Normal Priority (1) jobs
LIST * lowPriority;      //Low Priority (2) jobs
LIST * messages;	 //Messages to be send back and forth.
LIST * semaphores;	 //Semaphores


//---------------------------------Command Function Declarations
int create(int priority);
int kll(int pid);
void killCurrent();
void totalinfo();
int fork();
int quantum();
void procinfo(int processID);

int newSemaphore(int semaphoreID, int initVal);
int semaphoreP(int semaphoreID);
int semaphoreV(int semaphoreID);

int sendMessage(int pid, char * message);
int receiveMessage();
int replyMessage(int pid, char * message);

//---------------------------------Non-Command Function Declarations

char getMenuResponse();
void init();

