#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_OF_LISTS 9
#define MAX_NUM_NODES 300

//Array of LIST heads
LIST listHeads[NUM_OF_LISTS];
//Array of nodes of lists.
NODE listNodes[MAX_NUM_NODES];

//Initializes static arrays
void ListsInit(){
    
    for(int i = 0; i < NUM_OF_LISTS; i++){
        listHeads[i].head = NULL;
        listHeads[i].current = NULL;
        listHeads[i].tail = NULL;
        listHeads[i].inUse = FALSE;
    }

    for(int i = 0; i <MAX_NUM_NODES; i++){
        listNodes[i].next = NULL;
        listNodes[i].prev = NULL;
        listNodes[i].data = 0;
        listNodes[i].inUse = FALSE;
    }
}

//This function returns a LIST pointer.
//This will create a new array for that List, and the
//head of the list (address) will be stored in the array element
//of the headsArray thing, headsArray stores the first address
//of every list.
LIST *ListCreate(){
    LIST *newList = NULL; //= (LIST*)malloc(sizeof(LIST));

    for(int i = 0; i < NUM_OF_LISTS; i++){
        if(listHeads[i].inUse == FALSE){
            newList = &listHeads[i];     //Assign newList to that listHead[i]
            listHeads[i].inUse = TRUE;  //Mark this slot as inUse
            break;
        }
    }

    //Return NULL on failure.
    return newList;
}

//Counts and returns number of items in list.
int ListCount(LIST * list){

    // validate input parameter
    if(list == NULL)
        return -1;


    int numItems = 0;


//    printf("CONTROL 100\n");
//    printf("Head: %ld\n", list->head);
//    printf("Current: %ld\n", list->current);
//    printf("Tail: %ld\n", list->tail);
    NODE *current = list -> head;

    while(current != NULL) {

        numItems++;

        current = current -> next;
    }


    return numItems;
}

//int PrintList(LIST *list){
//    if(list == NULL)
//        return -1;
//
//    NODE *curr = list->head;
//    if(curr == NULL) {
//        printf("Empty list\n");
//        return 0;
//    }
//
//    printf("--------------------------------------------------------------\n");
//
//    int i = 0;
//    while(curr != NULL) {
//        printf("Node #%d:\n", i);
//        printf("next = %d\n", curr->next);
//        printf("prev = %d\n", curr->prev);
//        printf("inUse = %d\n", curr->inUse);
//        printf("data = %d\n", *((int *)(curr->data)));
//        ++i;
//        if(i >= 3)
//            return -2;
//        curr = curr->next;
//    }
//
//    printf("--------------------------------------------------------------\n");
//
//    return 0;
//}
//
//
////Need to insert this item in array!
////Inserts a new Item at beginning of list.
//int ListPrepend(LIST *list, void * val){
//
//    // Verify input parameters
//    if(list == NULL)
//        return -1;
//    
//    BOOL found = FALSE;
//    for(int i = 0; i < NUM_OF_LISTS; i++){
//        if(listHeads[i].head == list->head){
//            found = TRUE;
//        }
//    }
//
//    if(found == FALSE) {
//        // The list does not exist
//        return -2;
//    }
//
//    if(val == NULL) {
//        return -3;
//    }
//
//
//    // Search for empty node
//    for(int t = 0; t < MAX_NUM_NODES; t++){
//
//
//        if(listNodes[t].inUse == FALSE){
//
//            //Assign value to data of empty node.
//            listNodes[t].data = val;
//    
//            // mark the node as 'in use'
//            listNodes[t].inUse = TRUE;
//
//            // Connect the empty node with the head node through next and prev pointers
//            listNodes[t].next = list -> head;
//
//            listNodes[t].prev = NULL;
//
//            //If
//            NODE *temp = list->head;
//            if(temp != NULL)
//                temp->prev = &listNodes[t];
//
//            //Move head of list to new node.
//            list -> head = &listNodes[t];
//            list -> current = list -> head;
//            
//            if(list -> tail == NULL)
//                list -> tail = list->head;
//
//            return 0;
//
//        }
//    }
//
//    // if an empty node not found, return -4
//    return -4;
//}


void *ListCurr(LIST *list){
    if(list == NULL)
        return NULL;
    return list->current;
}

void *ListPrev(LIST *list){
    if(list == NULL)
        return NULL;
    NODE * tmp = list -> current;

    if(tmp == NULL)
        return NULL;

    list -> current = tmp -> prev;
    return list -> current;
}

void *ListNext(LIST *list){
    if(list == NULL)
        return NULL;
    NODE * tmp = list -> current;
    if(tmp == NULL)
        return NULL;
    list -> current = tmp -> next;
    return list -> current;
}

void *ListFirst(LIST *list){
    if(list == NULL)
        return NULL;
    list -> current = list -> head;
    return list -> current;
}

void *ListLast(LIST *list){
    if(list == NULL)
        return NULL;

    list -> current = list -> tail;
    return list -> current;
}

int ListAppend(LIST *list, void * val){
  
    
    if(list == NULL)
        return -1;
    
    BOOL found = FALSE;
    for(int i = 0; i < NUM_OF_LISTS; i++){
        if(listHeads[i].tail == list->tail){
            found = TRUE;
        }
    }

    if(found == FALSE) {
        // The list does not exist
        return -2;
    }

    if(val == NULL) {
        return -3;
    }

    //Find an empty node to use for the new tail.
    for(int t = 0; t < MAX_NUM_NODES; t++){
        if(listNodes[t].inUse == FALSE){

            //Assign value to data of empty node.
            listNodes[t].data = val;

            // mark the node as 'in use'
            listNodes[t].inUse = TRUE;

            // Connect the empty node with the tail node through next and prev pointers
            listNodes[t].next = NULL;
            listNodes[t].prev = list -> tail;


            NODE *temp = list->tail;
            if(temp != NULL)
                temp->next = &listNodes[t];

            //Move tail of list to new node.
            list -> tail = &listNodes[t];
            list -> current = list -> tail;
            
            // if an empty list, set the head
            if(list->head == NULL)
                list->head = &listNodes[t];
            return 0;

        }
    }

    return -1;
}



//Adds the new item to the list directly after the
//current item, and makes it the current item.
//If the current pointer is before the start of the 
//list, the item is added at the start. If the current
//pointer is beyond the end of the list, the item is
//added at the end. return 0 on success, -1 failure

int ListAdd(LIST *list, void * val){
    
    if(list == NULL)
        return -1;
    
    BOOL found = FALSE;
    for(int i = 0; i < NUM_OF_LISTS; i++){
        if(listHeads[i].head == list->head){
            found = TRUE;
        }
    }

    if(found == FALSE) {
        // The list does not exist
        return -2;
    }

    if(val == NULL) {
        return -3;
    }

    for(int t = 0; t < MAX_NUM_NODES; t++){
        if(listNodes[t].inUse == FALSE){

            //Assign value to data of empty node.
            listNodes[t].data = val;

            // mark the node as 'in use'
            listNodes[t].inUse = TRUE;

            // Connect the empty node with the tail node through next and prev pointers
            NODE * curr = list -> current;
            listNodes[t].next = curr -> next;
            listNodes[t].prev = list -> current;

            //If the current item (before new is added) is tail, 
            //then we need to adjust for a new tail
            if(list -> current = list -> tail){
                list -> tail = &listNodes[t];
            }

            if(curr != NULL) {
                NODE *tmp = curr->next;
                tmp->prev = curr->next = &listNodes[t];
            }

            list -> current = &listNodes[t];
            return 0;
        }
    }
    return -1;
}

//Adds item to list directly before the current item                
//makes the new item the current one. If the current
//pointer is before the start: the item is added at
//the start. If current is beyond the end, item is
//added at the end. return 0 success, -1 failure.
//int ListInsert(LIST *list, NODE *val){
//        
//    if(list == NULL)
//        return -1;
//    
//    BOOL found = FALSE;
//    for(int i = 0; i < NUM_OF_LISTS; i++){
//        if(listHeads[i].head == list->head){
//            found = TRUE;
//        }
//    }
//
//    if(found == FALSE) {
//        // The list does not exist
//        return -2;
//    }
//
//    if(val == NULL) {
//        return -3;
//    }
//
//    for(int t = 0; t < MAX_NUM_NODES; t++){
//        if(listNodes[t].inUse == FALSE){
//
//            //Assign value to data of empty node.
//            listNodes[t].data = val;
//
//            // mark the node as 'in use'
//            listNodes[t].inUse = TRUE;
//
//            // Connect the empty node with the tail node through next and prev pointers
//            NODE * curr = list -> current;
//            listNodes[t].next = list -> current; 
//            listNodes[t].prev = curr -> prev;
//
//            if(list -> current = list -> head){
//                list -> head = &listNodes[t];
//            }
//
//            //If current is NULL,
//            //Assign new node to Current -> previous
//            if(curr != NULL) {
//                NODE *tmp = curr->prev;
//                tmp->next = curr->prev = &listNodes[t];
//            }
//
//            list -> current = &listNodes[t];
//            return 0;
//        }
//    }
//    return -1;
//}
//
//void reverse(LIST *list){
//
//    NODE * prev = NULL;
//    NODE * current = list -> head;
//    NODE * nxt;
//
//    while(current != NULL){
//        nxt  = current->next;  
//        current->next = prev;   
//        prev = current;
//        current = nxt;        
//    }
//
//    list -> head = prev;
//    PrintList(list);
//}
