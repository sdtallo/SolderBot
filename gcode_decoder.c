#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gcode_decoder.h"

static int loc_comp(Location *loc1, Location *loc2)
{
    if ((loc1->x_loc == loc2->x_loc) && (loc1->y_loc == loc2->y_loc) && (loc1->z_loc == loc2->z_loc))
    {
        return 1;
    }
    else if ((loc1->x_loc != loc2->x_loc) || (loc1->y_loc != loc2->y_loc) || (loc1->z_loc != loc2->z_loc))
    {
        return 0;
    }
    else
    {
        return 2;
    }
}

Location *location_new(double x, double y, double z)
{
    Location *loc = NULL;
    loc = (Location *)malloc(sizeof(Location));
    loc->x_loc = x;
    loc->y_loc = y;
    loc->z_loc = z;
    return loc;
}

void location_free(Location *loc)
{
    free(loc);
}

void move_loc(Location *current_loc, Location *future_loc, char *gcodeloc)
{
    if (0 == loc_comp(current_loc, future_loc))
    {
        current_loc->x_loc = future_loc->x_loc;
        current_loc->y_loc = future_loc->y_loc;
        current_loc->z_loc = future_loc->z_loc;
        char tempgloc[15];
        strcpy(gcodeloc, "G00 X");
        sprintf(tempgloc, "%.3f Y", future_loc->x_loc);
        strcat(gcodeloc, tempgloc);
        sprintf(tempgloc, "%.3f Z", future_loc->y_loc);
        strcat(gcodeloc, tempgloc);
        sprintf(tempgloc, "%.3f f400", future_loc->z_loc);
        strcat(gcodeloc, tempgloc);
    }
    else if (1 == loc_comp(current_loc, future_loc))
    {
        printf("FUTURE LOCATION IS CURRENT LOCATION");
    }
    else
    {
        printf("ERROR IN LOCATION COMPARISON\n");
    }
}

void move_loc2(Location *future_loc, char *gcodeloc)
{
    char tempgloc[15];
    strcpy(gcodeloc, "G00 X");
    sprintf(tempgloc, "%.3f Y", future_loc->x_loc);
    strcat(gcodeloc, tempgloc);
    sprintf(tempgloc, "%.3f Z", future_loc->y_loc);
    strcat(gcodeloc, tempgloc);
    sprintf(tempgloc, "%.3f f400", future_loc->z_loc);
    strcat(gcodeloc, tempgloc);
}

void move_home(Location *current_loc, char *gcodeloc)
{
    current_loc->x_loc = 0;
    current_loc->y_loc = 0;
    current_loc->z_loc = 0;
    strcpy(gcodeloc, "G28");
}

void print_loc(Location *loc){
    printf("loc\nX:%.3f,Y:%.3f,Z:%.3f\n", loc->x_loc, loc->y_loc, loc->z_loc);
}


