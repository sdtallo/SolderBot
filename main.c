#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gcode_decoder.h"
int main()
{
    ///test1234567
    Location *loc_current = location_new(999, 0, 0); ///dynamically allocates and constructs a location struct and returns a pointer to that struct
    Location *loc_future = location_new(26.0, 13.0, 14.0);
    printf("Current_loc\nX:%.3f,Y:%.3f,Z:%.3f\n", loc_current->x_loc, loc_current->y_loc, loc_current->z_loc);
    printf("Future_loc\nX:%.3f,Y:%.3f,Z:%.3f\n", loc_future->x_loc, loc_future->y_loc, loc_future->z_loc);
    char gcode1[75];
    move_loc(loc_current, loc_future, gcode1);
    printf("%s\n", gcode1);
    location_free(loc_current);
    location_free(loc_future);
    return 0;
}