#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "location_list.h"
#include "gcode_decoder.h"

Location_List * createLL(Location *new_data){
    Location_List *locL = NULL;
    locL = (Location_List*)malloc(sizeof(Location_List));
    locL->cur = new_data;
    locL->next = NULL;
    locL->prev = NULL;

    return locL;
}

Location_List * push(Location_List *head, Location *new_data)
{

    /* 1. allocate node */
    Location_List *new_node = (Location_List *)malloc(sizeof(Location_List));
    /* 2. put in the data  */
    new_node->cur = new_data;
    /* 3. Make next of new node as head and previous as NULL */
    new_node->next = head;
    new_node->prev = NULL;
    /* 4. change prev of head node to new node */
    head->prev = new_node;
    /* 5. move the head to point to the new node */
    head = new_node;
    return head;

}

void insertAfter(Location_List *prev_node, Location *new_data)
{
    /*1. check if the given prev_node is NULL */
    if(prev_node == NULL){
        printf("The given previous node cannot be NULL");
        return;
    }
    /* 2. allocate new node */
    Location_List* new_node = (Location_List*)malloc(sizeof(Location_List));
    /* 3. put in the data  */
    new_node->cur = new_data;
    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;
    /* 5. Make the next of prev_node as new_node */
    prev_node->next = new_node;
    /* 6. Make prev_node as previous of new_node */
    new_node->prev = prev_node;
    /* 7. Change previous of new_node's next node */
    if(new_node->next != NULL)
        new_node->next->prev = new_node;
}

void append(Location_List *head, Location *new_data)
{
    /* 1. allocate node */
    Location_List *new_node = (Location_List *)malloc(sizeof(Location_List));
    Location_List *last = head;
    /* 2. put in the data  */
    new_node->cur = new_data; //this needs to assign data to cur
    /* 3. This new node is going to be the last node, so 
          make next of it as NULL*/
    new_node->next = NULL;
    new_node->prev = NULL;
    /* 4. If the Linked List is empty, then make the new 
          node as head */
    if (head->next == NULL)
    {
        head->next = new_node;
        printf("last value is");
        print_loc(head->next->cur);
        return;
    }
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
    /* 6. Change the next of last node */
    last->next = new_node;
    new_node->prev = last;
    /* 7. Make last node as previous of new node */

    return;
}

void printList(Location_List* node){
    Location_List* last = NULL;
    printf("\nTraversal in forward direction \n");
    while(node != NULL){
        print_loc(node->cur);
        last = node;
        node = node->next;
    }
    printf("#######################################################");
    printf("\nTraversal in reverse direction \n");
    while(last != NULL){
        print_loc(last->cur);
        last = last->prev;
    }
}


void freeList(Location_List *head){
    Location_List *tempPointer1 = head;
    Location_List *tempPointer2 = head;
    while(tempPointer1->next != NULL){
        tempPointer1 = tempPointer1->next;
        free(tempPointer2->prev);
        free(tempPointer2->cur);
        free(tempPointer2->next);
        tempPointer2 = tempPointer1->next;
    }
    tempPointer1 = NULL;
    tempPointer2 = NULL;

    return;
}

void moveAllLoc(Location_List *head,char *fileLoc){
    Location_List *temp = head;
    while(temp->next != NULL){
        Location *loc1 = location_new(temp->cur->x_loc,temp->cur->y_loc,temp->cur->z_loc);
        Location *loc2 = location_new(temp->next->cur->x_loc,temp->next->cur->y_loc,temp->next->cur->z_loc);
        moveLocToLoc(loc1,loc2,fileLoc);
//        solder();
        location_free(loc1);
        location_free(loc2);
        temp = temp->next;

    }
}

void solder(void){
    sleep(1);

}


void moveLocToLoc(Location * firstLoc, Location * secondLoc, char *fileLoc){
    char firstCommand[75];
    char secondCommand[75];
    char thirdCommand[75];
    double upZ = 3;//location of z we want it to go to, to avoid hitting the pins before we move it to the next location;

    Location * moveUp = location_new(firstLoc->x_loc,firstLoc->y_loc,upZ);//creat a location above the first pin to move to
    move_loc2(moveUp,firstCommand);
    Location * moveAboveSecond = location_new(secondLoc->x_loc,secondLoc->y_loc,upZ);
    move_loc2(moveAboveSecond,secondCommand);
    Location * moveDown = location_new(secondLoc->x_loc,secondLoc->y_loc,secondLoc->z_loc);
    move_loc2(moveDown,thirdCommand);


    location_free(moveUp);
    location_free(moveAboveSecond);
    location_free(moveDown);


    FILE* file_ptr = fopen(fileLoc, "a+");
    if(file_ptr == NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    fputs (firstCommand, file_ptr);
    fputs ("\n", file_ptr);
    fputs (secondCommand, file_ptr);
    fputs ("\n", file_ptr);
    fputs (thirdCommand, file_ptr);
    fputs ("\n", file_ptr);

    fclose(file_ptr);
}

void createFile(char *fileLoc)
{
    FILE* file_ptr = fopen(fileLoc, "w");
    if(file_ptr == NULL){
        printf("Error opening file!\n");
        exit(1);
    }

    fclose(file_ptr);
}
