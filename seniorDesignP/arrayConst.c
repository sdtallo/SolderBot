#include "arrayConst.h"

//distance between our calibrated A0 to F0 or generally a to f
//on each board in inches
const static double calDistance = .68;

int createArray(arrayConst ** arrayPointer, char *fileLoc){
    FILE* file_ptr = fopen(fileLoc, "rb");
    if(file_ptr == NULL){
        printf("Error opening file!\n");
        exit(1);
    }

    char buffer[255];
    int lineNum = 0;
    //initialize as all zero since cal.txt is not going to be those numbers
    //and I can assume something went wrong if still have those values
    //asfter scanning the file
    double x1 = 0;
    double x2 = 0;
    double x3 = 0;

    double y1 = 0;
    double y2 = 0;
    double y3 = 0;

    double z1 = 0;
    double z2 = 0;
    double z3 = 0;
    //gets the specific calibrations numbers in the cal.txt file
    while(fgets(buffer, 255, (FILE*) file_ptr)) {
        char temp[4];
        strncpy ( temp, buffer+2, 4);
        //converts lines in file to respective double values
        if(lineNum == 1){
            x1 = atof(temp);
        }else if(lineNum == 2){
            y1 = atof(temp);
        }else if(lineNum == 3){
            z1 = atof(temp);
        }else if(lineNum == 5){
            x2 = atof(temp);
        }else if(lineNum == 6){
            y2 = atof(temp);
        }else if(lineNum == 7){
            z2 = atof(temp);
        }else if(lineNum == 9){
            x3 = atof(temp);
        }else if(lineNum == 10){
            y3 = atof(temp);
        }else if(lineNum == 11){
            z3 = atof(temp);
        }
        lineNum += 1;
    }

    fclose(file_ptr);

    //this is where I check I something might have went wrong
    if(x1 == 0.0 || x2 == 0.0 || x3 == 0.0){
        return 1;
    }else if(y1 == 0.0 || y2 == 0.0 || y3 == 0.0){
        return 1;
    }else if(y1 == 0.0 || y2 == 0.0 || y3 == 0.0){
        return 1;
    }else{

    }

    //3 boards of a-j and 1-46 are split into 5 by 5 location references based on 3 calibrations given
    //was used because we were unsure how many calibration positions to intitially use and code was already written
    //when decided
    arrayConst absArray1[10][6] = {
    {{x1,y1+0.0,z1},{x1+calDistance,y1+0.0,z1},{x2,y2+0.0,z2},{x2+calDistance,y2+0.0,z2},{x3,y3+0.0,z3},{x3+calDistance,y3+0.0,z3}},

    {{x1,y1+0.5,z1},{x1+calDistance,y1+0.5,z1},{x2,y2+0.5,z2},{x2+calDistance,y2+0.5,z2},{x3,y3+0.5,z3},{x3+calDistance,y3+0.5,z3}},

    {{x1,y1+1.0,z1},{x1+calDistance,y1+1.0,z1},{x2,y2+1.0,z2},{x2+calDistance,y2+1.0,z2},{x3,y3+1.0,z3},{x3+calDistance,y3+1.0,z3}},

    {{x1,y1+1.5,z1},{x1+calDistance,y1+1.5,z1},{x2,y2+1.5,z2},{x2+calDistance,y2+1.5,z2},{x3,y3+1.5,z3},{x3+calDistance,y3+1.5,z3}},

    {{x1,y1+2.0,z1},{x1+calDistance,y1+2.0,z1},{x2,y2+2.0,z2},{x2+calDistance,y2+2.0,z2},{x3,y3+2.0,z3},{x3+calDistance,y3+2.0,z3}},

    {{x1,y1+2.5,z1},{x1+calDistance,y1+2.5,z1},{x2,y2+2.5,z2},{x2+calDistance,y2+2.5,z2},{x3,y3+2.5,z3},{x3+calDistance,y3+2.5,z3}},

    {{x1,y1+3.0,z1},{x1+calDistance,y1+3.0,z1},{x2,y2+3.0,z2},{x2+calDistance,y2+3.0,z2},{x3,y3+3.0,z3},{x3+calDistance,y3+3.0,z3}},

    {{x1,y1+3.5,z1},{x1+calDistance,y1+3.5,z1},{x2,y2+3.5,z2},{x2+calDistance,y2+3.5,z2},{x3,y3+3.5,z3},{x3+calDistance,y3+3.5,z3}},

    {{x1,y1+4.0,z1},{x1+calDistance,y1+4.0,z1},{x2,y2+4.0,z2},{x2+calDistance,y2+4.0,z2},{x3,y3+4.0,z3},{x3+calDistance,y3+4.0,z3}},

    {{x1,y1+4.5,z1},{x1+calDistance,y1+4.5,z1},{x2,y2+4.5,z2},{x2+calDistance,y2+4.5,z2},{x3,y3+4.5,z3},{x3+calDistance,y3+4.5,z3}}

    };
    //assign created array values to array const pointer
    for(int i = 0; i<10;++i){
        for(int j=0; j<6 ; ++j){
            arrayPointer[i][j] = absArray1[i][j];
        }

    }

    return 0;

}
