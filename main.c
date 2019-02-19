#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gcode_decoder.h"
#include "location_list.h"

int main()
{
    Location **locs = (Location**)malloc(sizeof(Location)*50);
    int i;
    for(i=0;i<12;i++){
        locs[i] = location_new((rand()%100),rand()%100,rand()%10);
        print_loc(locs[i]);
    }

    Location_List* head = NULL;
    head = createLL(locs[0]);
    for(i=1;i<11;i++){
        head = push(head,locs[i]);
    }

    char tempName[] = "C:\\Users\\andre\\desktop\\testFile.txt";
    createFile(tempName);

    append(head,locs[11]);

    printf("Created DLL is: ");
    printList(head);

    moveAllLoc(head,tempName);

    for(i=0;i<12;i++){
        location_free(locs[i]);
    }

    freeList(head);
    return 0;
}
