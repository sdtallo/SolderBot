#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gcode_decoder.h"
#include "location_list.h"
#include "reference_loc.h"
#include "arrayConst.h"

int main(int argc, char *argv[])
{

    int i;
    for(i = 0;i<argc;++i){
        printf("%s \n",argv[i]);
    }
    return 0;
    /*
    char *t = argv[1];
//        char *t = "gsdfdfsfdsfdsfds";
    char tempName[] = "/home/pi/solderbot/gCodeLoc.txt";

//        char tempName[] = "C:\\Users\\andre\\desktop\\testFile.txt";


    FILE* file_ptr = fopen(tempName, "w");
    if(file_ptr == NULL){
        printf("Error opening file!\n");
        exit(1);
    }

    fclose(file_ptr);


    file_ptr = fopen(tempName, "a+");
    if(file_ptr == NULL){
        printf("Error opening file!\n");
        exit(1);
    }

    fputs(t,file_ptr);
    fputs ("\n", file_ptr);

    fclose(file_ptr);*/



    /*
    Location **locs = (Location**)malloc(sizeof(Location)*50);
    int i;
    for(i=0;i<12;i++){
        locs[i] = location_new((rand()%100),rand()%100,rand()%10);
        print_loc(locs[i]);
    }


    Location_List* head = NULL;
// //    head = createLL(locs[0]);
    head = createLLWiR(1,locs[0]->x_loc,locs[0]->y_loc);
    for(i=1;i<11;i++){
// //        head = push(head,locs[i]);
        head = addLocRef(head, 1, locs[i]->x_loc,locs[i]->y_loc);
    }

//    char tempName[] = "C:\\Users\\andre\\desktop\\testFile.txt";

    char tempName[] = "/home/pi/solderbot/gCodeLoc.txt";
    createFile(tempName);

// //    append(head,locs[11]);

    printf("Created DLL is: ");
    printList(head);

    moveAllLoc(head,tempName);

    for(i=0;i<12;i++){
        location_free(locs[i]);
    }


//     printf("this is our test message");



    freeList(head);
    return 0;

    printf("this is our test message ");
//    printf("%lf", absArray[6][5].x_loc); */

//    return 0;
}
