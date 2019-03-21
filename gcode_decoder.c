#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gcode_decoder.h"

///Reference
///struct_var.int_member = 0;
///struct_var->int_number = 0; // this statement is equivalent to: *struct_var.int_number = 0;
Location *location_new(double x, double y, double z)
{
    Location *loc = NULL;
    loc = (Location *)malloc(sizeof(Location));
    loc->x_loc = x;
    loc->y_loc = y;
    loc->z_loc = z;
    return loc;
}

void move_loc(Location *current_loc, Location *future_loc, char *gcodeloc)
{
    if (0 == loc_comp(current_loc, future_loc))
    {
        current_loc->x_loc = future_loc->x_loc;
        current_loc->y_loc = future_loc->y_loc;
        current_loc->z_loc = future_loc->z_loc;
        char tempgloc[15];
        strcpy(gcodeloc, "G01 X");
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

void move_home(Location *current_loc, char *gcodeloc)
{
    current_loc->x_loc = 0;
    current_loc->y_loc = 0;
    current_loc->z_loc = 0;
    strcpy(gcodeloc, "G28");
}

void location_free(Location *loc)
{
    free(loc);
}

//returns
//1 if loc's are equal
//0 if loc's are not equal
//2 if error in logic comparison
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
