/*uses debug printing aka logging as application of scientific method of debugging. feels like the slow way but do it anyhow. 
*valgrind v gdb v debug printing:
*valgrind to catch all mem errors
*print with debug for logic and usage issues
*gdb for anything not covered by other two or in emergencies
*/
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i = 0;

    while(i < 100) {
        usleep(3000);
    }

    return 0;
}