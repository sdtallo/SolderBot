#ifndef GCODE_DECODER_H
#define GCODE_DECODER_H

typedef struct location Location;

struct location
{
    double x_loc;
    double y_loc;
    double z_loc;
};

//enum Gcode{"G00"};
//G00 is a rapid positioning(moves 2 axis at once)
//G01 is a linear interpolation(moves 1 axis at once)

Location *location_new(double x, double y, double z);
//Don't know if this should be G00 or G01
void move_loc(Location *future_loc, Location *current_loc, char *gcodeloc);

void move_home(Location *current_loc, char *gcodeloc);
/*
More possible gcode generating functions
move_loc_multi_axis()---This would let us move fast to a point instead of us moving one axis at a time by using G00 instead of G01
set inches-- this would set it into inches instead of mm possible to change
set home-- this could be ncessary to calibrate to home (G92 is the command of this double check this)
move_head_retract--
move_head_extract--
*/

void location_free(Location *loc);

static int loc_comp(Location *loc1, Location *loc2);

#endif