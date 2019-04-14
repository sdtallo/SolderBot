//#include "arrayConst.h"
//#include "gcode_decoder.h"
#include "location_list.h"
#include "reference_loc.h"
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{

    char *tempName;
    char *input;
    char *calRead;
    if(argc > 1){//for integrated program since will be given arguments
        tempName = "/home/pi/solderbot/gCodeLoc.txt";
        input = argv[1];
        calRead = "/home/pi/solderbot/cal.txt";

    }else{//if testing on personal computer
        tempName = "C:\\Users\\andre\\desktop\\testFile.txt";
        input = " _  _ ";
        calRead = "C:\\Users\\andre\\desktop\\cal.txt";
    }
    //error messages
    char * error1 = "Format is invalid\n";
    char * error2 = "Invalid Range\n";
    char * error3 = "not valid format for calibration\n";
    char * error4 =  "String is empty\n";


    createFile(tempName);

    size_t itest = strlen(input);
    char *sTest = (char *)malloc((itest+1) * sizeof(char));

    strcpy(sTest, input);
    remove_all_chars(sTest, ' ');

    int testS = checkFormat(sTest);
    free(sTest);

    if(testS == 1){

    }else if(testS == 2){
        printf("%s", error2);
        return 2;
    }else{
        //returns 1 if character pointer not in corret format
        printf("%s", error1);
        return 1;
    }

    arrayConst ** arrayPointer;

    arrayPointer = (arrayConst **) malloc(10*sizeof(arrayConst *));

    for(int i=0;i<10;i++)
        arrayPointer[i] = (arrayConst *) malloc(6*sizeof(arrayConst));

    int arrayReport = createArray(arrayPointer, calRead);

    if(arrayReport == 0){

    }else{
        if(arrayPointer){//frees before leaving
            for(int i=0;i<10;i++)
                free(arrayPointer[i]);
            free(arrayPointer);
        }
        printf("%s", error3);
        return 3;//return 3 if something is wrong in file
    }

    size_t iLen = strlen(input);
    char *sInput = (char *)malloc((iLen+1) * sizeof(char));

    strcpy(sInput, input);

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
    Location * loc0 = location_new(0,999,0);
    head = createLL(loc0);
    //Make sure Sam send " _ " otherwise this method is useless
    remove_all_chars(board1Str, ' ');
    remove_all_chars(board2Str, ' ');
    remove_all_chars(board3Str, ' ');


    if(board1Str[0] != '\0'){
        appendGivenBoardStr(head, 1,board1Str, arrayPointer);
    }
    if(board2Str[0] != '\0'){
        appendGivenBoardStr(head, 2,board2Str, arrayPointer);
    }
    if(board3Str[0] != '\0'){
        appendGivenBoardStr(head, 3,board3Str, arrayPointer);
    }

    if(head->next == NULL){
        printf("%s", error4);
        return 4;
    }

    deleteRepeats(head);

    double checkMaxX = 0;//check if out of range
    double checkMaxY =0;
    Location_List * pointerCheck = head->next;

    checkMaxX = pointerCheck->cur->x_loc;
    checkMaxY = pointerCheck->cur->y_loc;

    while(pointerCheck->next != NULL){
        pointerCheck = pointerCheck->next;
        if(pointerCheck->cur->y_loc > checkMaxY){
            checkMaxY = pointerCheck->cur->y_loc;
        }

        if(pointerCheck->cur->x_loc > checkMaxX){
            checkMaxX = pointerCheck->cur->x_loc;
        }
    }

    printf("This is a valid string\n");
    printf("String => %s\n", sInput);

    printf("Board 1 = .%s.\n", board1Str);
    printf("Board 2 = .%s.\n", board2Str);
    printf("Board 3 = .%s.\n", board3Str);


    printf("Created DLL is: ");


    Location_List ** headPointer = &head;
    sortDLL(headPointer);
    if(head->next != NULL){
        printList(head->next);
        moveAllLoc(head->next,tempName);

        //freeing pointers

        freeList(head);

        if(arrayPointer){
            for(int i=0;i<10;i++)
                free(arrayPointer[i]);
            free(arrayPointer);
        }
        if(board1Str){
            free(board1Str);
        }
        if(board2Str){
            free(board2Str);
        }
        if(board3Str){
            free(board3Str);
        }

    }
    //returns 0 if completed successfully
    return 0;
}

    //return 0 = completed successfully
    //return 1 = something is wrong in given string argument, likely format, printf("Format is invalid\n");
    //return 2 = entered values are out of range, printf("Invalid Range\n");
    //return 3 = something wrong in cal.txt likely not valid format
    //return 4 = "String is empty\n"

