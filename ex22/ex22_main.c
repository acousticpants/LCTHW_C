//ex22 demo's scope, globals, and stack
#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "B.M.J. Hayward";//const is alternative to 'define' to create constant variables

void scope_demo(int count)
{
    log_info("count is: %d", count);//prints count from top of func

    if(count > 10) {//creates new scope bug and new instance of count
        int count = 100; // bad! bugs!

        log_info("count in this scope is %d", count);//prints count from this block, not what we passed to scope_demo
    }

    log_info("count is at exit: %d", count);//this log DOES print count as passed to the parent function

    count = 3000;

    log_info("count after assign: %d", count); //prints out new count as 3000. does not alter count as initially called by parent function as per final code block 
}

int main(int argc, char *argv[])
{
    //test out THE_AGE accessors
    log_info("My name: %s, age: %d", MY_NAME, get_age());

    set_age(100);

    log_info("My age is now: %d", get_age());

    //test out THE_SIZE extern
    log_info("THE_SIZE is: %d", THE_SIZE);
    print_size();

    THE_SIZE = 9;

    log_info("THE_SIZE is now: %d", THE_SIZE);

    //test ratio function static
    log_info("Ratio at first: %f", update_ratio(2.0));
    log_info("Ratio again: %f", update_ratio(10.0));
    log_info("Ratio once more: %f", update_ratio(300.0));

    //test scope demo
    int count = 4;
    scope_demo(count);
    scope_demo(count * 20);

    log_info("count after calling scope_demo: %d", count);

    return 0;
}
