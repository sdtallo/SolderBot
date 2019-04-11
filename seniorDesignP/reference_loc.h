#ifndef REFERENCE_LOC_H
#define REFERENCE_LOC_H
#include "location_list.h"
//#include "gcode_decoder.h"
#include "arrayConst.h"

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

//refLoc * newRefLoc(double zHeight, double leftX, double leftY, double middleX, double middleY, double rightX, double rightY);//used to keep track where the board is in reference to solder

//void changeRefLoc(double zHeight, double leftX, double leftY, double middleX, double middleY, double rightX, double rightY);

//creates a LL with a given board location
Location_List * createLLWiR(int board, char column, int row, arrayConst ** arrayPointer);

//Adds a location to the LL
Location_List * addLocRef(Location_List* head, int board, char column, int row, arrayConst ** arrayPointer);

//Inserts after a specific node
void insertAfterRef(Location_List* prev_node, int board, char column, int row, arrayConst ** arrayPointer);

//addds to end of LL
void appendRef(Location_List* head, int board, char column, int row, arrayConst ** arrayPointer);

//allows converting from user input to actual locations
Location * createLocWiRef(int board, char column, int row, arrayConst ** arrayPointer);

//Converts a given board string into locations and puts them in a LL
void appendGivenBoardStr(Location_List * head,int board, char * str1, arrayConst ** arrayPointer);

//removes all characters of certain type in a string
void remove_all_chars(char* str, char c);

//count number of characters of certain type in a string
int countChars( char* s, char c );

//converts characters A-J to numbers since given string contains them
int converChartoNum(char c);

//converts the num back to what the character was
char convertNumtoChar(int n);

//adds all the locations to the LL given a col and row range
void appendGivenRange(Location_List * head, int board, int firstColumn, int lastColumn, int firstRow, int lastRow, arrayConst ** arrayPointer);

//checks to see if the char is a num ie 0-9
int isNum(char c);

//check to see if letter char but only from a-j
int isLet(char c);

//check the format of the first given argument string to see if it complies with what we want
int checkFormat(char * c);


#endif


