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
    semaphores = ListCreate();

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
    controlBlock->ready = true;

    //If this is the first process on the queue, then it will run
    if(ListCount(jobQueue) == 0){
        controlBlock->state = 'u';
    } else {
        controlBlock->state = 'r';
    }

    //Place PCB in appropriate Queue depending on Priority.
    if(priority == 0){
        ListAppend(highPriority, controlBlock);
    } else if(priority == 1){
        ListAppend(normalPriority, controlBlock);
    } else {
        ListAppend(lowPriority, controlBlock);
    }

    ListAppend(jobQueue, controlBlock);

    int count = ListCount(jobQueue);
    printf("Number of jobs in Queue: %d\n", count);

    printf("\n");
    printf("\n");

    NODE * item = ListFirst(jobQueue);

    return id; //return process ID on success.
}


//-------------------------------------------------------------------------Command 'K'
//Kill process with given process ID.
int kll(int id){

    NODE * control = ListFirst(jobQueue);

    PCB * block;
    int currentID;

    //Check that pid exists
    do{
        printf("CONTROL 1\n");
        block = (PCB *) control->data;
        currentID = block->pid;

        if(currentID == id){
            printf("CONTROL 2\n");
	    break;
	}

        if((currentID != id) && (control == jobQueue->tail)){
        printf("CONTROL 3\n");
	    printf("That process ID does not exist. Please try again.\n");
	    return 0;
        }

        control = control->next;
        printf("CONTROL 4\n");
    }while(control-> next != NULL);
        printf("CONTROL 5\n");

    //Find the Queue item with the appropriate ID
    do{
        printf("CONTROL 6\n");

        //Assign node data to PCB h.
        block = (PCB *) control->data;
        printf("CONTROL 9\n");

        printf("\n");
        currentID = block->pid; 
        printf("CONTROL 10\n");
        control = control->next;
        printf("CONTROL 7\n");

    }while(currentID != id);
        printf("CONTROL 8\n");

    control = control->prev;

    //Make this running item the current item
    jobQueue->current = control;
  
    NODE * tmp = control; //ListCurr(jobQueue);
    tmp = tmp->next;

    PCB * tmpBlock = (PCB *) tmp->data;
    tmpBlock->state = 'u'; //This is the new running process.

    ListRemove(jobQueue);

    return 1;
}

//-------------------------------------------------------------------------Command 'E'
//Kills the currently running process.
void killCurrent(){

    NODE * killThis = ListFirst(jobQueue);
    PCB * killBlock;
 
    char * currentState;
    int x = ListCount(jobQueue);
    int id;

    if(ListCount(jobQueue) == 1){
        ListRemove(jobQueue);
        return;
    }


    //Find the Queue item which is in a running state.
    do{
  
        //Assign node data to PCB h.
        killBlock = (PCB *) killThis->data;

        printf("\n");
        currentState = killBlock->state; 
        id = killBlock->pid;
        killThis = killThis->next;
        
        if(id == x && currentState != 'u'){

	    printf("There is no process currently running.\n");
  	    return;
	}

    }while(currentState != 'u');

    killThis = killThis->prev;

    //Make this running item the current item
    jobQueue->current = killThis;
  
    NODE * tmp = killThis; //ListCurr(jobQueue);
    tmp = tmp->next;

    PCB * tmpBlock = (PCB *) tmp->data;
    tmpBlock->state = 'u'; //This is the new running process.

    ListRemove(jobQueue);
   
    return;
}



//--------------------------------------------------------------------------Command 'T'
//Display all process queues + their contents.
void totalinfo(){

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

    //Find the currently running process.

    //Copy currently running process to new process with new pid.

    NODE * forkThis = ListFirst(jobQueue); //Currently running process
    PCB * forked;   //New copied process.

    do{
        forked = (PCB *)forkThis->data;
        forkThis = forkThis->next;
    }while(forked->state != 'u');

    //Now we've found the running process, next we need to create
    //a new process which is a copy of the running one, except
    //its state will be ready, and pid will be unique.

    int prty = forked->priority;
    create(prty);

    int newPID = ListCount(jobQueue) + 1;

    printf("Fork Created. Use Command 'T' to see change.\n");

    return newPID;
}

//---------------------------------------------------------------------Command 'Q'
int quantum(){
  
    //Find the current process such that state == 'u'
    NODE * findRun = ListFirst(jobQueue);
    PCB * thisState; 

    //Increment until we find the running process.
    //There should always be a process running.
    do{
        thisState = (PCB *)findRun->data;
        findRun = findRun->next;
    }while(thisState->state != 'u');

    //print to display information of currently running process.
    printf("\n");
    printf("Process currently running:\n");
    printf("\n");

    printf("Process ID: %d\n", thisState->pid);
    printf("Process priority: %d\n", thisState->priority);
    printf("Process state: 'u'\n");
    
    thisState->state = 'r'; //Change state to ready, it is no longer running.

    printf("\n");
    printf("This process has been removed from CPU,\n"
           "and is no longer running. The next process now running: \n");

    printf("\n");
    printf("\n");

    //Next process now has state 'u'
    //We decide which process is next by ????? ----> next in line and/or priority??
    //When we hit last process in ready Queue, go back to first?
 
    if(findRun == NULL){
        findRun = ListFirst(jobQueue);
 	thisState = (PCB *)findRun -> data;
    } else{
        thisState = (PCB *)findRun->data;
    }

    thisState->state = 'u';

    printf("Process ID: %d\n", thisState->pid);
    printf("Process priority: %d\n", thisState->priority);
    printf("Process state: 'u'\n");
    printf("\n");

    return 0;
}


//---------------------------------------------------------------------Command 'I'
//Dump complete state information of process to screen
//This includes process status and anything else you
//can think of
void procinfo(int id){


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

    //Check if given ID is a real process ID.

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


//---------------------------------------------------------------------Command 'N'
int newSemaphore(int semaphoreID, int initialVal){

    //Assign these values to the new semaphore
    //Append this new semaphore to the list of semaphores

   // NODE * semItem;

    SEMAPHORE * newSem;

    newSem->value = initialVal;
    newSem->sid = semaphoreID;

    ListAppend(semaphores, newSem);

    return 0;
}

//---------------------------------------------------------------------Command 'V'
int semaphoreV(int semaphoreID){

    //Find semaphore of that ID
    NODE * tmp = ListFirst(semaphores);
    SEMAPHORE * thisOne;

    int semID;

    do{

        //Assign node data to PCB h.
        thisOne = (SEMAPHORE *) tmp->data;

        printf("\n");
        semID = thisOne->sid; 
        tmp = tmp->next;

    }while(semID != semaphoreID);
    
    //Increment the value.
    thisOne->value = thisOne->value + 1;
    return 1;

}
//---------------------------------------------------------------------Command 'P'
int semaphoreP(int semaphoreID){

    return 1;

}

//--------------------------------------------------------------------Command 'S'
int sendMessage(int rid, char * m){

    NODE * receiver = ListFirst(jobQueue);
    PCB * findR;

    int i;
    int x = ListCount(jobQueue);

    //Check that recipient exists.
    do{
        findR = (PCB *) receiver->data;
        i = findR->pid; 
        receiver = receiver->next;
 
        if(i == x && i != rid){
	    printf("The item you are trying to message does not exist. Try again.\n");
	    return;
	}
    } while(i != rid); 
    
    NODE * sender = ListFirst(jobQueue);
    PCB * findSender;
 
    char * currentState;
    int id;

    //Find the Queue item which is in a running state.
    do{

        //Assign node data to PCB h.
        findSender = (PCB *) sender->data;

        printf("\n");
        currentState = findSender->state; 
        id = findSender->pid;
        sender = sender->next;

        if(id == x && currentState != 'u'){
	    printf("There is no process currently running.\n");
  	    return;
	}

    }while(currentState != 'u');

    MESPACK * packet;
    packet->senderID = 0; //ID of currently running process.
    packet->recipientID = rid;
    packet->message = m; 
  
    ListAppend(messages, m);

    //Find currently running process.
    //Change state to blocked.
    findSender->state = 'b';

    findSender = (PCB *) sender->data;
    findSender->state = 'u';

    printf("Running process is blocked until it gets a reply. Command 'Y' to reply.\n");

    return 1;
}

//--------------------------------------------------------------------Command 'R'
int receiveMessage(){

    //Look at messages Queue.
    //Find receiverID of first message

    //Process receives message,
    //Appropriate state changes are made.

    printf("Receive Message.\n");

    return 1;
}


//--------------------------------------------------------------------Command 'Y'
int replyMessage(int pid, char * message){

    //Similar to send message, but sender gets state = 'u' again, rather than 'b';

    printf("Reply to Message.\n");

    return 1;
}


int main(){
    ListsInit();

    bool run = true;

    init(); //This gets called first and does:
    
    int prty;           //Process Priority
    int pid;            //Process ID
    char * message;     //Message from/to (?) process
    char * command;     //User input command to simulation

    char i;             //character variable. Used when we're removing \n chars in user input.
    int semaphoreID;    //ID of the newly created Semaphore
    int initialVal;     //Initial Value of the Semaphore

    int sendTo;

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
            
            //**********************************************Command C
            case 'C':
    	        printf("Enter Process Priority:"
    		   "0 - high, 1 - medium, 2 - low.\n");
                i;
                while ((i = getchar()) == '\n' || i == EOF) { }

                prty = (int) i - 0x30;

		//Check that the priority entered is legitimate.
		//If not, print error message and break.
                if(prty > 2 || prty < 0){
		    printf("You've entered an invalid priority level."
			 	"Please try again.\n");
		    break;
                }

                create(prty);
                break;
    
    
            //********************************************Command K
            case 'K':

                if(ListCount(jobQueue) == 0){
		    printf("\n");
		    printf("There are no processes to kill.\n"
			   "Init() process still exists, but use command 'X' to kill and exit the simulation.\n");
		    printf("\n");
 		    break;
                }

                printf("Enter the process ID"
    		   " of the process to kill: \n");
       	        scanf("%d", &pid);
    	
    	    //Find process of this ID. If it does not exist, 
    	    //output error message then continue on and user
    	    //can enter ID again if needed.
    
                kll(pid);
                break;
    
            //********************************************Command T
            case 'T':
                if(ListCount(jobQueue) == 0){
		    printf("\n");
		    printf("No processes to show.");
		    printf("\n");
 		    break;
                }
                totalinfo();
                break;
    	
            //********************************************Command X
            case 'X':
                printf("All processes killed, simulation terminated.\n");
                run = false;
                break;
        
            //********************************************Command I
            case 'I':
    
                //If the jobQueue is empty, there is no use in running procinfo()
                if(ListCount(jobQueue) == 0){
		    printf("\n");
                    printf("No processes to show!\n");
		    printf("\n");
		    break;
                }

                //Get user input
		printf("Enter the process ID of the process you wish to see: \n");

                while ((i = getchar()) == '\n' || i == EOF) { }

                pid = (int) i - 0x30;

                int x = ListCount(jobQueue);

                procinfo(pid);
                break;

            //********************************************Command E
            case 'E':

 		if(ListCount(jobQueue) == 0){
		    printf("\n");
		    printf("No currently running process which can be killed with this command.\n"
			   "If all processes have been exited, and you with to quit the sim, use command 'X'\n");
		    printf("\n");
                }

                killCurrent();
                break;

            //********************************************Command Q
            case 'Q':

		if(ListCount(jobQueue) == 0){
		    printf("\n");
		    printf("No processes to remove from CPU,\n"
		           "or no new processes to move into CPU.\n");
		    printf("\n");
		    break;
		}

                quantum();
                break;


            //*********************************************Command F
            case 'F':

                //Check that there is a job that can be forked. If not, break
                if(ListCount(jobQueue) == 0){
		    printf("\n");
		    printf("There are no processes that can be forked.\n");
		    printf("\n");
		    break;
		}
         
		//Copy the currently running process, and assign a new pid
		//then place it on the readyQueue.
                fork();
		break;

            //*********************************************Command N
            case 'N':

                //First check if there is space to create new semaphores.
                if(ListCount(semaphores) >= 5){
		    printf("\n");
		    printf("There is no space for new semaphores at this time.\n");
                    printf("Please try another command.\n");
		    printf("\n");
		    break;
		}
 
                //Get a semaphore initial value from the user
                printf("Give the semaphore an integer value greater than 0:\n");

                while ((i = getchar()) == '\n' || i == EOF) { }

                initialVal = (int) i - 0x30;

                //Assign semaphoreID to semaphore. 
                semaphoreID = ListCount(semaphores);
             
                newSemaphore(semaphoreID, initialVal);
                break;

            //*********************************************Command P
            case 'P':

                if(ListCount(semaphores) == 0){
		    printf("\n");
		    printf("No semaphores exist. Create a new semaphore to run this command.\n");
		    printf("\n");
		    break;
		}

                printf("Enter the ID of the semaphore executing the P operation\n"
			"on behalf of the running process\n");

                
                while ((i = getchar()) == '\n' || i == EOF) { }

                semaphoreID = (int) i - 0x30;

                semaphoreP(semaphoreID);
                break;



            //*********************************************Command V
            case 'V':
 
                if(ListCount(semaphores) == 0){
		    printf("\n");
		    printf("No semaphores exist. Create a new semaphore to run this command.\n");
		    printf("\n");
		    break;
		}

                printf("Enter the ID of the semaphore executing the V operation\n"
			"on behalf of the running process\n");

                
                while ((i = getchar()) == '\n' || i == EOF) { }

                semaphoreID = (int) i - 0x30;

                semaphoreV(semaphoreID);
                break;

            //*******************************************Command S
            case 'S':

                if(ListCount(jobQueue) == 0){
		    printf("\n");
		    printf("No process to send to. Create process first (Command C)\n");
		    printf("\n");
		    break;
		}

                printf("Current process will send a message to another process.\n"
		       "Please enter the Process ID of the process you wish to send a message to:\n");
		
                while ((i = getchar()) == '\n' || i == EOF) { }

                //Check that input is an integer.

                sendTo = (int) i - 0x30;
 		
                printf("Enter the message you wish to send, max 40 chars: \n");


                char * ch;
                int n = 0;

                sendMessage( sendTo, message);
                break;


            //*******************************************Command R
            case 'R':
                receiveMessage();
                break;
    
            //*******************************************Command Y
            case 'Y':

                message = "This doesn't work.\n"; 
                int yid = 1; 

                replyMessage(yid, message);
                break;
    
            //*******************************************Command Unrecognized
            //If command is not recognized, print error message and continue.
            default:
	        printf("\n");
    	        printf("Command not recognized, please try again.\n");
		printf("\n");
    
        } //END SWITCH

    }while(run == true); //END DO-WHILE

    return 0;
}
