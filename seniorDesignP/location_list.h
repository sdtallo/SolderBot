#include "gcode_decoder.h"

#ifndef location_list_H
#define location_list_H

typedef struct Location_List Location_List;

struct Location_List
{
    Location *cur;
    Location_List *prev;
    Location_List *next;
};

Location_List * createLL(Location *new_data);

Location_List * push(Location_List* head, Location *new_data);

void insertAfter(Location_List* prev_node,Location *new_data);

void append(Location_List* head, Location *new_data);

//Need to create destructor for the DLL
//del specific node and also destroy entire DLL

void printList(Location_List* loc);

void freeList(Location_List *head);

void moveAllLoc(Location_List *head,char *fileLoc);

void moveLocToLoc(Location * firstLoc, Location * secondLoc, char *fileLoc);

void solder(void);//stub function for yet to be written code, just waits 1 second

void createFile(char *fileLoc);

void deleteRepeats(Location_List * head);

#endif
