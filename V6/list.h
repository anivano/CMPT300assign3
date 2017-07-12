//This header files contains the LIST ADT declaration without any
//of the underlying details - it is up to the implementer list.c
//to fully declare the ADT in the source module.

#ifndef _LIST_H //This checks if _LIST_H has been #defined earlier or in any
        //included file. If not defined (ifndef) then everything between         //this and #endif is included.

#define _LIST_H //This is used to define the preprocessor macros for the texts.
        //It is used to make substitutions throught the file it is 
        //located in.

//ENUM to define if item is inUse or not
typedef enum boolean{
    FALSE,
    TRUE
} BOOL;

// This should be in the main.h file
BOOL messageReady;

//Node type definition
typedef struct node{
    void * data;        //data at current address.
    struct NODE *next;  //This is the address of the next item
    struct NODE *prev;  //Address of previous item
    BOOL inUse;         //Weather or not the node is inUse
} NODE;

//List type definition
typedef struct list{
    struct NODE *head;              //head of list
    struct NODE *current;           //Current item
    struct NODE *tail;              //end of list
    BOOL inUse;                     //Weather or not the node is inUse.
} LIST;

//Initialize lists
void ListsInit();

//The functions which must be included according to the assignment specs.
LIST *ListCreate(); //Creates a new empty list. Returns reference on success
            //Returns NULL pointer on failure.
         
int ListCount(LIST *); //Returns the numer of items in the list.

void *ListFirst(LIST *); //Returns pointer to the first item in the list
               //makes this first item the current item

void *ListLast(LIST *); //Returns a pointer to the last item in list
              //makes it the current item.

void *ListNext(LIST *); //advances list's current item by one, and returns 
              //a pointer to the new current item. If this operation
              //advances the current item peyond the end of the list,
              //a NULL pointer is returned.

void *ListPrev(LIST *); //Backs up list's current item by one, and returns a 
              //pointer to the new current item. If this operation
              //backs up the current item beyond the start,
              //a NULL pointer is returned.

void *ListCurr(LIST *); //Returns a pointer to the current item in the list.

int ListAdd(LIST *, void*); //Adds the new item to the list directly after the
             //current item, and makes it the current item.
             //If the current pointer is before the start of the 
             //list, the item is added at the start. If the current
             //pointer is beyond the end of the list, the item is
             //added at the end. return 0 on success, -1 failure.

int ListInsert(LIST *, NODE *); //Adds item to list directly before the current item                
                //makes the new item the current one. If the current
                //pointer is before the start: the item is added at
                //the start. If current is beyond the end, item is
                //added at the end. return 0 success, -1 failure.

int ListPrepend(LIST *, void *); //Adds item to beginning of list and makes
                //it the current item

int ListAppend(LIST *, void *); //Adds items to end of list, makes it current.
                //return 0 success, -1 failure.

void *ListRemove(LIST *); //Return current item and remove it from list. Make next
            //item current.

void ListConcat(LIST *, LIST *); //Adds list2 to end of list1. Current is set to
                   //current of list1. List2 no longer exists.

void ListFree(LIST *, NODE *); //Delete list. itemFree is a pointer to a 
                   //routine that frees an item. It should be
                   //invoked as (*itemFree)(itemToBeFreed);

//(*itemFree)(itemToBeFreed);

void *ListTrim(LIST *); //Return last item and take it out of list. Make the 
              //new last item the current one.

void *ListSearch(LIST, NODE, NODE); //Searches list starting
    //at the current item until the end is reached or match is found.
    //Match is determined by the comparator parameter. This parameter
    //is a pointer to a routine that takes as its first argument an 
    //item pointer, and as its second argument comparisonArg. Comparator
    //returns 0 if the item and comparisonArg don't match, 1 if they do.
    //Current pointer is left at the matched item and the pointer to that
    //item is returned. If no match, current pointer is left beyond end of
    //list and a NULL pointer is returned.


#endif //This ends the #ifndef
