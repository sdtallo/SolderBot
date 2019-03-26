#include <stdlib.h>
#include "reference_loc.h"
#include "location_list.h"
#include "arrayConst.h"



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


}

void insertAfterRef(Location_List* prev_node, int board, char column, int row){
    Location * loc = createLocWiRef(board,  column, row);
    insertAfter(prev_node,loc);


}

void appendRef(Location_List* head, int board, char column, int row){
    Location * loc = createLocWiRef(board,  column, row);
    head = push(head,loc);


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

    int xArray = newColumn;
    int yArray = row;
    xArray += (board-1)*10;


    int absXArray = xArray/5;
    int absYArray = yArray/5;

    int remainderX = xArray%5;
    int remainderY = yArray%5;

    locX = (absArray[absYArray-1][absXArray-1].x_loc)+(remainderX*.1);
    locY = (absArray[absYArray-1][absXArray-1].y_loc)+(remainderY*.1);
    locZ = (absArray[absYArray-1][absXArray-1].z_loc);


    return location_new(locX, locY,locZ);

}



//void insertGivenArg(){

//}

