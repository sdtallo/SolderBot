#include "reference_loc.h"

Location_List * createLLWiR(int board, char column, int row,
                            arrayConst ** arrayPointer){
    Location_List *locL = NULL;
    locL = (Location_List*)malloc(sizeof(Location_List));
    Location * loc = createLocWiRef(board,  column, row, arrayPointer);
    locL->cur = loc;
    locL->next = NULL;
    locL->prev = NULL;

    return locL;

}

Location_List * addLocRef(Location_List* head, int board, char column,
                          int row, arrayConst ** arrayPointer){
    Location * loc = createLocWiRef(board,  column, row, arrayPointer);
    head = push(head,loc);
    return head;
}

void insertAfterRef(Location_List* prev_node, int board, char column, int row,
                    arrayConst ** arrayPointer){
    Location * loc = createLocWiRef(board,  column, row, arrayPointer);
    insertAfter(prev_node,loc);

}

void appendRef(Location_List* head, int board, char column, int row,
               arrayConst ** arrayPointer){
    Location * loc = createLocWiRef(board,  column, row, arrayPointer);
    append(head,loc);

}

Location * createLocWiRef(int board, char column, int row,
                          arrayConst ** arrayPointer){

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
    //the row on the baords are 1-46 but in array is 0-45 so subtract 1
    if(row > 0){
        yArray = row -1;
    }else{
        yArray = 0;
    }

    int absXArray;
    int absYArray;

    int remainderX;
    int remainderY;
    //each board has 2 reference each so to get the reference locations
    //multiple the board by 10 since it is made of 5 pins each in each column
    xArray += (board-1)*10;

    if(yArray > 45){
        absXArray = 5;
        absYArray = 9;
        remainderY = (yArray - 45);
    }else{
        //finds the reference by divinding by 5
        absXArray = xArray/5;
        absYArray = yArray/5;
        //finds remainder so know location in reference since spacing is
        //assumed to be exact inside the reference
        remainderY = yArray%5;
    }
    remainderX = xArray%5;
    //creates the locations from the reference and relative postion in the reference
    locX = (arrayPointer[absYArray][absXArray].x_loc)+(remainderX*.1);
    locY = (arrayPointer[absYArray][absXArray].y_loc)+(remainderY*.1);
    locZ = (arrayPointer[absYArray][absXArray].z_loc);

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

//splits board strings into smaller stings of location values
void appendGivenBoardStr(Location_List * head, int board, char * str1,
                         arrayConst ** arrayPointer){
    size_t iLen = strlen(str1);
    char *sInput = (char *)malloc((iLen+1) * sizeof(char));

    strcpy(sInput, str1);

    char *sSeparator = ",";
    char *pToken = strtok(sInput, sSeparator);
    //continues to split string locations till empty and breaks
    while(1)
    {
        if(pToken == NULL)
            break;

        int ifSemiColon = countChars(pToken, ':');
        //checks if location in a range which more complicated to break up
        if(ifSemiColon > 0){
            //if there is a semicolon
            size_t iLen = strlen(pToken);
            char *semiColon = (char *)malloc((iLen+1) * sizeof(char));

            strcpy(semiColon, pToken);
            //splits the strings with ':' like a1:a8 into 2 letters and 2 numbers
            int colonLoc = 0;
            while(semiColon[colonLoc] != ':'){
                colonLoc += 1;
            }

            char * secondLetter = &semiColon[colonLoc+1];

            char letter1[1];
            memcpy( letter1, &semiColon[0], 1 );

            iLen = (size_t)colonLoc;
            char *num1 = (char *)malloc((iLen+1) * sizeof(char));
            memcpy(num1, &semiColon[1], iLen);
            //converts char into int
            int row1 = atoi(num1);

            char letter2[1];
            memcpy( letter2, secondLetter, 1 );

            char * num2 = &secondLetter[1];

            int row2 = atoi(num2);
            int lNum1 = converChartoNum(letter1[0]);
            int lNum2 = converChartoNum(letter2[0]);

            //code wrttin to call appends for all the values in t range
            //since got the actual numbers to go through in the range here
            appendGivenRange(head, board, lNum1,lNum2,row1,row2, arrayPointer);

            //free pointers
            if(num1){
                free(num1);
            }
            if(semiColon){
                free(semiColon);
            }

        }else{
            //if not get parts and split them
            size_t numLen = strlen(pToken);
            char * temp1 = (char *)malloc((numLen+1) * sizeof(char));
            strcpy(temp1, pToken);

            char letter[1];
            memcpy( letter, &temp1[0], 1 );

            char * temp2 = &temp1[1];

            int row = atoi(temp2);

            appendRef(head,board, letter[0], row, arrayPointer);

            if(temp1){
                free(temp1);
            } 
        }
        pToken = strtok(NULL, sSeparator);
    }
    if(sInput){
        free(sInput);
    }
}

//https://stackoverflow.com/questions/4235519/counting-number-of-occurrences-of-a-char-in-a-string-in-c
int countChars(char* s, char c)
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


//goes through a given range value like 1-1 to 5-6 it requires the columns
//be converted to ints first to make it easier the converts columnes
//back into characters before colled the appedRef which takes in a location
void appendGivenRange(Location_List * head, int board, int firstColumn,
                      int lastColumn, int firstRow, int lastRow, arrayConst ** arrayPointer){
    if(firstRow > lastRow){
        int temp = lastRow;
        lastRow = firstRow;
        firstRow = temp;
    }
    if(firstColumn > lastColumn){
        int temp = lastColumn;
        lastColumn = firstColumn;
        firstColumn = temp;
    }
    for(int j = firstRow;j<=lastRow;++j){
        for(int i = firstColumn; i <= lastColumn;++i){
            //convertes num back to char because appendRef requires it
            char col = convertNumtoChar(i);
            appendRef(head,board,col,j, arrayPointer);
        }
    }

}

int isNum(char c){//checks if character is a num ie (0,1,2,...9)
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

int isLet(char c){//checks if valid letter on board ie (a,b,c...j)

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

//check if the format is valid and if the range is valid as well
int checkFormat(char * c){
    size_t itest = strlen(c);
    char * sTest = (char *)malloc((itest+1) * sizeof(char));
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
    for(size_t i =0; i<(itest-1);++i){//checks if invalid format
        current = sTest[i];
        next = sTest[i+1];
        if(current == '_' && isalpha(next)){

        }else if(current == '_' && next == '_'){

        }else if(isalpha(current) && isNum(next) == 1){

        }else if(isNum(current) == 1 && isNum(next) == 1){

        }else if(isNum(current) == 1 && next == '_'){

        }else if(isNum(current) == 1 && next == ','){

        }else if(isNum(current) == 1 && next == ':'){

        }else if(current == ':' && isalpha(next)){

        }else if(current == ',' && isalpha(next)){

        }else{
            if(t == 1){
                t = 0;
            }
        }

    }for(size_t i =0; i<(itest-1);++i){//checks if invalid range in x
        current = sTest[i];

        if(isalpha(current)){
            if(isLet(current) == 1){

            }else{
                if(t == 1){
                    t = 2;//return 2 if letter isn't correct;
                }
            }
        }
    }
    size_t begining = 0;
    size_t end = 0;
    //checks if invalid range for y
    for(size_t i =0; i<(itest-1);++i){
        current = sTest[i];
        next = sTest[i+1];
        if(isNum(current) == 1&& begining ==0){
            begining = i;

        }if(isNum(current) == 1 && isNum(next) != 1){
            end = i;
        //if there is a number at the very end of the string
        }else if(i == itest - 2 && isNum(next) == 1){
            end = i + 1;
        }
        if(begining != 0 && end != 0){
            size_t length = end - begining;
            char * c = (char *)malloc((length+1) * sizeof(char));
            strncpy(c,&sTest[begining],length+1);
            int test = atoi(c);
            free(c);
            begining = 0;
            end = 0;
            if(test > 46 || test < 1){
                if(t==1){
                    t = 2;
                }
            }
        }
    }
    if(sTest){
        free(sTest);
    }

    return t;
}
