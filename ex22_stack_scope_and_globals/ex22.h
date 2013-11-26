#ifndef _ex22_h
#define _ex22_h

// one .c file is going to use a variable that's been defined in another .c file
extern int THE_SIZE;

int get_age();
void set_age(int age);

double update_ratio(double ratio);

void print_size();
#endif
