#ifndef GCODE_DECODER_H
#define GCODE_DECODER_H

typedef struct Location Location;

struct Location{
    double x_loc;
    double y_loc;
    double z_loc;
};

Location *location_new(double x, double y, double z);

void location_free(Location *loc);

void move_loc(Location *future_loc, Location *current_loc, char *gcodeloc);

void move_home(Location *current_loc, char *gcodeloc);

void print_loc(Location *loc);

#endif