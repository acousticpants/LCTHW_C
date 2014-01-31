//this .c file will become a .o file for main.c file. it's a source file
#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

int THE_SIZE = 1000;

static int THE_AGE = 37;//opposite of extern. only available here. another instance of 'THE_AGE' will take a different place in mem and return different results if dec'd in another file

int get_age();//get age and set age can access the static var 'THE_AGE' from outside the file, becuase they aren't static nor is their call of 'THE_AGE' static
{
    return THE_AGE;
}

void set_age(int age)
{
    THE_AGE = age;
}

double update_ratio(double new_ratio)
{
    static double ratio = 1.0;//static only available in this function in this file, not by other callers outside of this function or this file

    double old_ratio = ratio;
    ratio = new_ratio;

    return old_ratio;
}

void print_size()
{
    log_info("I think size is: %d", THE_SIZE);
}
