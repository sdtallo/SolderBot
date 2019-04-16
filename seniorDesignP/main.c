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
    //for integrated program since will be given arguments
    if(argc > 1){
        tempName = "/home/pi/solderbot/gCodeLoc.txt";
        input = argv[1];
        calRead = "/home/pi/solderbot/cal.txt";
    //if testing on personal computer
    }else{
        tempName = "C:\\Users\\andre\\desktop\\testFile.txt";
        input = " _ a1:b4 _ ";
        calRead = "C:\\Users\\andre\\desktop\\cal.txt";
    }
    //error messages
    char * error1 = "Format is invalid\n";
    char * error2 = "Invalid Range\n";
    //shouldn't print error 3 unless cal.txt file is deleted
    char * error3 = "not valid format for calibration\n";
    char * error4 =  "String is empty\n";


    createFile(tempName);
    //copying the input string into a string I can edit without
    //worrying of erasing the initially given value
    size_t itest = strlen(input);
    char *sTest = (char *)malloc((itest+1) * sizeof(char));

    strcpy(sTest, input);
    //remove the spaces in the string
    remove_all_chars(sTest, ' ');
    //check the format
    int testS = checkFormat(sTest);
    //free the temporary copy because is no longer needed
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
    //https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
    arrayPointer = (arrayConst **) malloc(10*sizeof(arrayConst *));

    for(int i=0;i<10;i++)
        arrayPointer[i] = (arrayConst *) malloc(6*sizeof(arrayConst));

    int arrayReport = createArray(arrayPointer, calRead);

    if(arrayReport == 0){

    }else{
        if(arrayPointer){
            //frees pointers before leaving
            for(int i=0;i<10;i++)
                free(arrayPointer[i]);
            free(arrayPointer);
        }
        printf("%s", error3);
        //return 3 if something is wrong in file
        return 3;
    }
    //creates another copy of the initial input
    size_t iLen = strlen(input);
    char *sInput = (char *)malloc((iLen+1) * sizeof(char));

    strcpy(sInput, input);

    char *sSeparator = "_";//deleimiter seperating each board
    char *pToken = strtok(sInput, sSeparator);

    int boardNum = 1;
    char * board1Str = NULL;
    char * board2Str = NULL;
    char * board3Str = NULL;
    //Code splitting the string into three seperate strings for each board
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
    //put a basic value in the head since my code LL code require LL not be empty
    head = createLL(loc0);
    //Make sure calling program sends " _ " otherwise this method is useless
    remove_all_chars(board1Str, ' ');
    remove_all_chars(board2Str, ' ');
    remove_all_chars(board3Str, ' ');

    //goes about splitting each substring into smaller parts to get each location in each
    if(board1Str[0] != '\0'){//checks if string is empty before splitting it further
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
    //delete repeates in LL
    deleteRepeats(head);

    printf("This is a valid string\n");
    printf("String => %s\n", sInput);

    printf("Board 1 = .%s.\n", board1Str);
    printf("Board 2 = .%s.\n", board2Str);
    printf("Board 3 = .%s.\n", board3Str);

    printf("Created DLL is: ");

    Location_List ** headPointer = &head;

    //sorts the LL with largest Y's going first
    sortDLL(headPointer);

    //checks if LL is empty before printing it and freeing variables
    if(head->next != NULL){
        printList(head->next);
        moveAllLoc(head->next,tempName);

        //freeing pointers

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

    //still need to free LL if 'empty', I always put an initial value into it
    //though unlikely since previous code
    //already checks if given string is empty and returns
    freeList(head);

    //returns 0 if completed successfully
    return 0;
}

//return 0 = completed successfully
//return 1 = something is wrong in given string argument, likely format, printf("Format is invalid\n");
//return 2 = entered values are out of range, printf("Invalid Range\n");
//return 3 = something wrong in cal.txt likely not valid format
//return 4 = "String is empty\n"


//links

//https://www.geeksforgeeks.org/doubly-linked-list/
//https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/

//https://stackoverflow.com/questions/30415663/c-using-strtok-to-parse-command-line-inputs

//https://stackoverflow.com/questions/9895216/how-to-remove-all-occurrences-of-a-given-character-from-string-in-c
//https://stackoverflow.com/questions/4235519/counting-number-of-occurrences-of-a-char-in-a-string-in-c
