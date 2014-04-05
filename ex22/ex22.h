#ifndef _ex22_h
#define _ex22_h
//setting up external vars and funcs
//makes THE_SIZE in ex22.c available to other .c files
//extern tells compiler the variable exists in another locations
extern int THE_SIZE;

//gets and sets internal static variable in ex22.c
int get_age();
void set_age(int age);

//updates a static variable inside update_ratio
double update_ratio(double ratio);

void print_size();

#endif
