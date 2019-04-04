#ifndef GCODE_DECODER_H
#define GCODE_DECODER_H

typedef struct Location Location;

struct Location{
    double x_loc;
    double y_loc;
    double z_loc;
};

#endif
Location *location_new(double x, double y, double z);

void location_free(Location *loc);

void move_loc(Location *future_loc, Location *current_loc, char *gcodeloc);

void move_loc2(Location *future_loc, char *gcodeloc);//doesn't include error messages, just moves to the loation given

void move_home(Location *current_loc, char *gcodeloc);

void print_loc(Location *loc);

int loc_comp(Location *loc1, Location *loc2);

int Equality(double a, double b, double epsilon);


