#include <stdlib.h>
#include "reference_loc.h"
#include "location_list.h"
#include "arrayConst.h"
#include <string.h>
#include <stdio.h>


//refLoc * newRefLoc(double zHeight, double leftX, double leftY, double middleX, double middleY, double rightX, double rightY){
//    refLoc *ref = NULL;
//    ref = (refLoc *)malloc(sizeof(refLoc));
//    ref->zHeight = zHeight;
//    ref->leftX = leftX;
//    ref->leftY = leftY;
//    ref->middleX = middleX;
//    ref->middleY = middleY;
//    ref->rightX = rightX;
//    ref->rightY = rightY;

//    return ref;


//}

//void changeRefLoc(double zHeight, double leftX, double leftY, double middleX, double middleY, double rightX, double rightY){
//    ref->zHeight = zHeight;
//    ref->leftX = leftX;
//    ref->leftY = leftY;
//    ref->middleX = middleX;
//    ref->middleY = middleY;
//    ref->rightX = rightX;
//    ref->rightY = rightY;

//}

Location_List * createLLWiR(int board, char column, int row){
    Location_List *locL = NULL;
    locL = (Location_List*)malloc(sizeof(Location_List));
    Location * loc = createLocWiRef(board,  column, row);
    locL->cur = loc;
    locL->next = NULL;
    locL->prev = NULL;

    return locL;

}

Location_List * addLocRef(Location_List* head, int board, char column, int row){
    Location * loc = createLocWiRef(board,  column, row);
    head = push(head,loc);
    return head;
}

void insertAfterRef(Location_List* prev_node, int board, char column, int row){
    Location * loc = createLocWiRef(board,  column, row);
    insertAfter(prev_node,loc);


}

void appendRef(Location_List* head, int board, char column, int row){
    Location * loc = createLocWiRef(board,  column, row);
    append(head,loc);


}



Location * createLocWiRef(int board, char column, int row){

    double locX;
    double locY;
    double locZ;

    int newColumn;


    if(column == 'A' || column == 'a'){
        newColumn = 1;

    }else if(column == 'B' || column == 'b'){
        newColumn = 2;

    }else if(column == 'C' || column == 'c'){
        newColumn = 3;

    }else if(column == 'D' || column == 'd'){
        newColumn = 4;

    }else if(column == 'E' || column == 'e'){
        newColumn = 5;

    }else if(column == 'F' || column == 'f'){
        newColumn = 6;

    }else if(column == 'G' || column == 'g'){
        newColumn = 7;

    }else if(column == 'H' || column == 'h'){
        newColumn = 8;

    }else if(column == 'I' || column == 'i'){
        newColumn = 9;

    }else{//else J
        newColumn = 10;

    }

    int xArray = newColumn -1;
    int yArray;
    if(row > 0){
        yArray = row -1;
    }else{
        yArray = 0;
    }

    if(yArray > 45){
        yArray = 45;
    }
    xArray += (board-1)*10;


    int absXArray = xArray/5;
    int absYArray = yArray/5;

    int remainderX = xArray%5;
    int remainderY = yArray%5;

    locX = (absArray[absYArray][absXArray].x_loc)+(remainderX*.1);
    locY = (absArray[absYArray][absXArray].y_loc)+(remainderY*.1);
    locZ = (absArray[absYArray][absXArray].z_loc);

//    locX = (absArray[absXArray][absYArray].x_loc)+(remainderX*.1);
//    locY = (absArray[absXArray][absYArray].y_loc)+(remainderY*.1);
//    locZ = (absArray[absXArray][absYArray].z_loc);


    return location_new(locX, locY,locZ);

}


//https://stackoverflow.com/questions/9895216/how-to-remove-all-occurrences-of-a-given-character-from-string-in-c
void remove_all_chars(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}


void pushGivenBoardStr(Location_List * head,int board, char * str1){
    size_t iLen = strlen(str1);
    char *sInput = (char *)malloc((iLen+1) * sizeof(char));

    strcpy(sInput, str1);
//    printf("String => %s\n", sInput);


    char *sSeparator = ",";
    char *pToken = strtok(sInput, sSeparator);


    while(1)
    {
        if(pToken == NULL)
            break;
//        printf("Token = %s\n", pToken);

        int ifSemiColon = countChars(pToken, ':');

        if(ifSemiColon > 0){
            //if there is a semicolon
            size_t iLen = strlen(pToken);
            char *semiColon = (char *)malloc((iLen+1) * sizeof(char));

            strcpy(semiColon, pToken);

//            printf("semiColon = %s\n",semiColon);

            char *s = ":";
            char *t = strtok(semiColon, s);


            iLen = strlen(t);
            char beforesemiColon[iLen];
            strcpy(beforesemiColon, t);
//            printf("before semiColon = %s\n",beforesemiColon);

            t = strtok(NULL, s);

            iLen = strlen(t);
            char aftersemiColon[iLen];
            strcpy(aftersemiColon, t);
//            printf("after semiColon = %s\n",aftersemiColon);


            char letter1[1];
            memcpy( letter1, &beforesemiColon[0], 1 );

            char * num1 = &beforesemiColon[1];

            int row1 = atoi(num1);

            char letter2[1];
            memcpy( letter2, &aftersemiColon[0], 1 );

            char * num2 = &aftersemiColon[1];

            int row2 = atoi(num2);
            int lNum1 = converChartoNum(letter1[0]);
            int lNum2 = converChartoNum(letter2[0]);


//            printf("first column is %i.\n",lNum1);
//            printf("last column is %i.\n",lNum2);
//            printf("first row is %i.\n",row1);
//            printf("last row is %i.\n",row2);

            appendGivenRange(head, board, lNum1,lNum2,row1,row2);


        }else{
            //if not get parts and split them
            size_t numLen = strlen(pToken);
            char temp1[numLen];
            strcpy(temp1, pToken);

            char letter[1];
            memcpy( letter, &temp1[0], 1 );
//           strncpy(letter, temp1[0],1);


            char * temp3 = &temp1[1];
//            printf("letter is %c\n", letter[0]);
//            printf("number is %s\n", temp3);

            int row = atoi(temp3);
//            printf("this is row int %i\n",row);
            appendRef(head,board, letter[0], row);

        }

        pToken = strtok(NULL, sSeparator);
    }
}


//https://stackoverflow.com/questions/4235519/counting-number-of-occurrences-of-a-char-in-a-string-in-c
int countChars( char* s, char c )
{
    return *s == '\0'
              ? 0
              : countChars( s + 1, c ) + (*s == c);
}

int converChartoNum(char column){
    int newColumn;
    if(column == 'A' || column == 'a'){
        newColumn = 1;

    }else if(column == 'B' || column == 'b'){
        newColumn = 2;

    }else if(column == 'C' || column == 'c'){
        newColumn = 3;

    }else if(column == 'D' || column == 'd'){
        newColumn = 4;

    }else if(column == 'E' || column == 'e'){
        newColumn = 5;

    }else if(column == 'F' || column == 'f'){
        newColumn = 6;

    }else if(column == 'G' || column == 'g'){
        newColumn = 7;

    }else if(column == 'H' || column == 'h'){
        newColumn = 8;

    }else if(column == 'I' || column == 'i'){
        newColumn = 9;

    }else{//else J
        newColumn = 10;

    }
    return newColumn;
}

char convertNumtoChar(int n){
    char c;

    if(n == 1){
        c = 'A';
    }else if(n == 2){
        c = 'B';
    }else if(n == 3){
        c = 'C';
    }else if(n == 4){
        c = 'D';
    }else if(n == 5){
        c = 'E';
    }else if(n == 6){
        c = 'F';
    }else if(n == 7){
        c = 'G';
    }else if(n == 8){
        c = 'H';
    }else if(n == 9){
        c = 'I';
    }else{
        c = 'J';
    }

    return c;
}




void appendGivenRange(Location_List * head, int board, int firstColumn, int lastColumn, int firstRow, int lastRow){

    for(int j = firstRow;j<=lastRow;++j){
        for(int i = firstColumn; i <= lastColumn;++i){

            char col = convertNumtoChar(i);
            appendRef(head,board,col,j);
        }
    }

}


int isNum(char c){
    int check;
    if(c == '0'){
        check = 1;

    }else if(c == '1'){
        check = 1;

    }else if(c == '2'){
        check = 1;

    }else if(c == '3'){
        check = 1;

    }else if(c == '4'){
        check = 1;

    }else if(c == '5'){
        check = 1;

    }else if(c == '6'){
        check = 1;

    }else if(c == '7'){
        check = 1;;

    }else if(c == '8'){
        check = 1;

    }else if(c == '9'){//else J
        check = 1;

    }else {
        check = 0;
    }
    return check;
}

int isLet(char c){

    int check;
    if(c == 'A' || c == 'a'){
        check = 1;

    }else if(c == 'B' || c == 'b'){
        check = 1;

    }else if(c == 'C' || c == 'c'){
        check = 1;

    }else if(c == 'D' || c == 'd'){
        check = 1;

    }else if(c == 'E' || c == 'e'){
        check = 1;

    }else if(c == 'F' || c == 'f'){
        check = 1;

    }else if(c == 'G' || c == 'g'){
        check = 1;

    }else if(c == 'H' || c == 'h'){
        check = 1;;

    }else if(c == 'I' || c == 'i'){
        check = 1;

    }else if(c == 'J' || c == 'j'){//else J
        check = 1;

    }else {
        check = 0;
    }
    return check;
}


int checkFormat(char * c){
    size_t itest = strlen(c);
    char sTest[itest];
    strcpy(sTest, c);
    char first = sTest[0];
    char last = sTest[itest-1];
    if(isLet(first) != 1 && first != '_'){
        return 0;
    }
    if(isNum(last) != 1 && last != '_'){
        return 0;
    }
    char current;
    char next;
    int t = 1;
    for(size_t i =0; i<(itest-1);++i){
        current = sTest[i];
        next = sTest[i+1];
        if(current == '_' && isLet(next) == 1){

        }else if(current == '_' && next == '_'){

        }else if(isLet(current) == 1 && isNum(next) == 1){

        }else if(isNum(current) == 1 && isNum(next) == 1){

        }else if(isNum(current) == 1 && next == '_'){

        }else if(isNum(current) == 1 && next == ','){

        }else if(isNum(current) == 1 && next == ':'){

        }else if(current == ':' && isLet(next) == 1){

        }else if(current == ',' && isLet(next) == 1){

        }else{
            t = 0;
        }
    }



    return t;
}
