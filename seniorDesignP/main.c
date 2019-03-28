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
//    char *tempName = "C:\\Users\\andre\\desktop\\testFile.txt";

    createFile(tempName);

//    char *input = " A2, B2, A2:B3 _ A2:f6 _ ";

        char *input = argv[1];

    //    printf(input);
    //    printf("\n");


    size_t itest = strlen(input);
    char *sTest = (char *)malloc((itest+1) * sizeof(char));

    strcpy(sTest, input);
    remove_all_chars(sTest, ' ');

    int testS = checkFormat(sTest);
    free(sTest);

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
//    free(pToken);
//    free(sInput);


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


    return 0;
}
