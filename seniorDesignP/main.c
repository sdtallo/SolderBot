#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gcode_decoder.h"
#include "location_list.h"
#include "reference_loc.h"
#include "arrayConst.h"

int main(int argc, char *argv[])
{
    char *tempName = "/home/pi/solderbot/gCodeLoc.txt";

//        char *tempName = "C:\\Users\\andre\\desktop\\testFile.txt";

    createFile(tempName);

//        char *input = " A2, B2, A2:B3 _ _ ";

    char *input = argv[1];

    //    printf(input);
    //    printf("\n");


    size_t itest = strlen(input);
    char *sTest = (char *)malloc((itest+1) * sizeof(char));

    strcpy(sTest, input);
    remove_all_chars(sTest, ' ');

    int testS = checkFormat(sTest);

    if(testS == 1){
        printf("This is a valid string\n");
    }else{
        printf("This is NOT a valid string!\n");

        FILE* file_ptr = fopen(tempName, "a+");
        if(file_ptr == NULL){
            printf("Error opening file!\n");
            exit(1);
        }
            fputs ("This is NOT a valid string!\n", file_ptr);

            fclose(file_ptr);


            return 0;
    }


    size_t iLen = strlen(input);
    char *sInput = (char *)malloc((iLen+1) * sizeof(char));



    strcpy(sInput, input);
    printf("String => %s\n", sInput);

    char *sSeparator = "_";
    char *pToken = strtok(sInput, sSeparator);

    int boardNum = 1;
    char * board1Str = NULL;
    char * board2Str = NULL;
    char * board3Str = NULL;
    //https://stackoverflow.com/questions/30415663/c-using-strtok-to-parse-command-line-inputs
    while(1)
    {

        if(pToken == NULL){
            break;
        }
        if(boardNum == 1){
            iLen = strlen(pToken);
            board1Str = (char *)malloc((iLen+1) * sizeof(char));
            strcpy(board1Str, pToken);

        }else if(boardNum == 2){
            iLen = strlen(pToken);
            board2Str = (char *)malloc((iLen+1) * sizeof(char));
            strcpy(board2Str, pToken);
        }else if(boardNum == 3){
            iLen = strlen(pToken);
            board3Str = (char *)malloc((iLen+1) * sizeof(char));
            strcpy(board3Str, pToken);
        }
        boardNum += 1;

//        printf("Token = %s\n", pToken);

        pToken = strtok(NULL, sSeparator);
    }

    Location_List* head = NULL;
    Location * loc0 = location_new(0,0,0);
    head = createLL(loc0);
    //Make sure Sam send " _ " otherwise this method is useless
    remove_all_chars(board1Str, ' ');
    remove_all_chars(board2Str, ' ');
    remove_all_chars(board3Str, ' ');

    printf("Board 1 = .%s.\n", board1Str);
    printf("Board 2 = .%s.\n", board2Str);
    printf("Board 3 = .%s.\n", board3Str);

    if(board1Str[0] != '\0'){
        pushGivenBoardStr(head, 1,board1Str);
    }
    if(board2Str[0] != '\0'){
        pushGivenBoardStr(head, 2,board2Str);
    }
    if(board3Str[0] != '\0'){
        pushGivenBoardStr(head, 3,board3Str);
    }



    printf("Created DLL is: ");

    deleteRepeats(head);

    if(head->next != NULL){
        printList(head->next);
        moveAllLoc(head->next,tempName);
    }


    freeList(head);


//    Py_Initialize();
//    FILE* file = fopen("/gpasser.py", "r");
//    PyRun_SimpleFile(file, "/gpasser.py");
//    Py_Finalize();


    return 0;

    /* used for testing purposes
//    int i;
//    for(i = 0;i<argc;++i){
//        printf("%s\n",argv[i]);
//    }
//    return 0;

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

    int i;
    for(i = 1;i<argc;++i){
        fputs("\n",file_ptr);
        fputs(argv[i],file_ptr);
        fputs("\n",file_ptr);
    }
//    fputs(t,file_ptr);
//    fputs ("\n", file_ptr);

    fclose(file_ptr);


    return 0;
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
