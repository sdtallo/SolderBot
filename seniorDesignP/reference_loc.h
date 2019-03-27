#ifndef REFERENCE_LOC_H
#define REFERENCE_LOC_H
#include "location_list.h"
#include "gcode_decoder.h"

typedef struct refLoc refLoc;

struct refLoc{
    double zHeight;
    double leftX;
    double leftY;
    double middleX;
    double middleY;
    double rightX;
    double rightY;
};


#endif
//refLoc * newRefLoc(double zHeight, double leftX, double leftY, double middleX, double middleY, double rightX, double rightY);//used to keep track where the board is in reference to solder

//void changeRefLoc(double zHeight, double leftX, double leftY, double middleX, double middleY, double rightX, double rightY);

Location_List * createLLWiR(int board, char column, int row);

Location_List * addLocRef(Location_List* head,int board, char column, int row);

void insertAfterRef(Location_List* prev_node, int board, char column, int row);

void appendRef(Location_List* head, int board, char column, int row);

Location * createLocWiRef(int board, char column, int row);//allows converting from user input to actual locations

void pushGivenBoardStr(Location_List * head,int board, char * str1);

void remove_all_chars(char* str, char c);

int countChars( char* s, char c );

int converChartoNum(char c);

char convertNumtoChar(int n);

void appendGivenRange(Location_List * head, int board, int firstColumn, int lastColumn, int firstRow, int lastRow);

int isNum(char c);

int isLet(char c);

int checkFormat(char * c);



