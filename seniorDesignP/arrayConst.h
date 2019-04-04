#ifndef ARRAYCONST_H
#define ARRAYCONST_H

typedef struct arrayConst arrayConst;

struct arrayConst {
    double x_loc;
    double y_loc;
    double z_loc;

};

#endif
//extern struct arrayConst absArray[10][6];

int createArray(arrayConst ** arrayPointer, char *fileLoc);





