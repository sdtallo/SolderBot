#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "location_list.h"
#include "gcode_decoder.h"

void push(Location_List **head, Location *new_data)
{
    /* 1. allocate node */
    Location_List *new_node = (Location_List *)malloc(sizeof(Location_List));
    /* 2. put in the data  */
    new_node->cur = new_data;
    /* 3. Make next of new node as head and previous as NULL */
    new_node->next = (*head);
    new_node->prev = NULL;
    /* 4. change prev of head node to new node */
    if ((*head) != NULL)
        (*head)->prev = new_node;
    /* 5. move the head to point to the new node */
    (*head) = new_node;
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

void append(Location_List **head, Location *new_data)
{
    /* 1. allocate node */
    Location_List *new_node = (Location_List *)malloc(sizeof(Location_List));
    Location_List *last = *head;
    /* 2. put in the data  */
    new_node->cur = new_data; //this needs to assign data to cur
    /* 3. This new node is going to be the last node, so 
          make next of it as NULL*/
    new_node->next = NULL;
    /* 4. If the Linked List is empty, then make the new 
          node as head */
    if (*head == NULL)
    {
        new_node->prev = NULL;
        *head = new_node;
        return;
    }
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
    /* 6. Change the next of last node */
    last->next = new_node;
    /* 7. Make last node as previous of new node */
    new_node->prev = last;
    return;
}

void printList(Location_List* node){
    Location_List* last;
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