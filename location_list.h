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

void push(Location_List** head, Location *new_data);

void insertAfter(Location_List* prev_node,Location *new_data);

void append(Location_List** head, Location *new_data);

//Need to create destructor for the DLL
//del specific node and also destroy entire DLL

void printList(Location_List* loc);
#endif
