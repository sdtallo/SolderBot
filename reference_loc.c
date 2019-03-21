#include <stdlib.h>
#include "reference_loc.h"
#include "location_list.h"



refLoc * newRefLoc(double zHeight, double leftX, double leftY, double middleX, double middleY, double rightX, double rightY){
    refLoc *ref = NULL;
    ref = (refLoc *)malloc(sizeof(refLoc));
    ref->zHeight = zHeight;
    ref->leftX = leftX;
    ref->leftY = leftY;
    ref->middleX = middleX;
    ref->middleY = middleY;
    ref->rightX = rightX;
    ref->rightY = rightY;

    return ref;


}

void changeRefLoc(refLoc * ref,double zHeight, double leftX, double leftY, double middleX, double middleY, double rightX, double rightY){
    ref->zHeight = zHeight;
    ref->leftX = leftX;
    ref->leftY = leftY;
    ref->middleX = middleX;
    ref->middleY = middleY;
    ref->rightX = rightX;
    ref->rightY = rightY;

}

Location_List * createLLWiR(refLoc ref,int board, char column, int row){
    Location_List *locL = NULL;
    locL = (Location_List*)malloc(sizeof(Location_List));
    Location * loc = createLocWiRef( ref,  board,  column, row);
    locL->cur = loc;
    locL->next = NULL;
    locL->prev = NULL;

    return locL;

}

Location_List * addLocRef(Location_List* head, int board, char column, int row, refLoc ref){
    Location * loc = createLocWiRef( ref,  board,  column, row);
    head = push(head,loc);


}

void insertAfterRef(Location_List* prev_node, int board, char column, int row, refLoc ref){
    Location * loc = createLocWiRef( ref,  board,  column, row);
    insertAfter(prev_node,loc);


}

void appendRef(Location_List* head, int board, char column, int row, refLoc ref){
    Location * loc = createLocWiRef( ref,  board,  column, row);
    head = push(head,loc);


}



Location * createLocWiRef(refLoc ref, int board, char column, int row){
    double boardTopLeftX;
    double boardTopLeftY;

    double locX;
    double locY;

    if(board == 1){
        boardTopLeftX = ref.leftX;
        boardTopLeftY = ref.leftY;

    }else if(board == 2){
        boardTopLeftX = ref.middleX;
        boardTopLeftY = ref.middleY;
    }else{
        boardTopLeftX = ref.rightX;
        boardTopLeftY = ref.rightY;
    }

    locY = boardTopLeftY + (row*.1);

    if(column == 'A' || column == 'a'){
        locX = boardTopLeftX;

    }else if(column == 'B' || column == 'b'){
        locX = boardTopLeftX + .1;

    }else if(column == 'C' || column == 'c'){
        locX = boardTopLeftX + .2;

    }else if(column == 'D' || column == 'd'){
        locX = boardTopLeftX + .3;

    }else if(column == 'E' || column == 'e'){
        locX = boardTopLeftX + .4;

    }else if(column == 'F' || column == 'f'){
        locX = boardTopLeftX + .7;

    }else if(column == 'G' || column == 'g'){
        locX = boardTopLeftX + .8;

    }else if(column == 'H' || column == 'h'){
        locX = boardTopLeftX + .9;

    }else if(column == 'I' || column == 'i'){
        locX = boardTopLeftX + 1.0;

    }else{//else J
        locX = boardTopLeftX + 1.1;

    }

    return location_new(locX, locY, ref.zHeight);

}

