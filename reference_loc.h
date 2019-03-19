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

refLoc * newRefLoc(double zHeight, double leftX, double leftY, double middleX, double middleY, double rightX, double rightY);//used to keep track where the board is in reference to solder

void changeRefLoc(refLoc * ref,double zHeight, double leftX, double leftY, double middleX, double middleY, double rightX, double rightY);

Location_List * createLLWiR(refLoc ref,int board, char column, int row);

Location_List * addLocRef(Location_List* head,int board, char column, int row, refLoc ref);

void insertAfterRef(Location_List* prev_node, int board, char column, int row, refLoc ref);

void appendRef(Location_List* head, int board, char column, int row, refLoc ref);

Location * createLocWiRef(refLoc ref, int board, char column, int row);//allows converting from user input to actual locations

#endif
