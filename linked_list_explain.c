//linked lists
/*
----------        ----------
- Data   -        - Data   -    
----------        ----------   
- Pointer- - - -> - Pointer-  
----------        ----------
*/

//what the node struct needs to look like
#include <stdlib.h>

struct node {
    int x;
    struct node *next;
};

int main()
{
    struct node *root;

    root = (struct node *) malloc( sizeof(struct node) );
    root->next = 0;
    root->x = 5;
}

//traversing the list

#include <stdio.h>
#include <stdlib.h>

struct node {
    int x;
    struct node *next;
};

int main()
{
    struct node *root;//this doesn't change or we lose the list in memory

    struct node *conductor;//will point to each node as it traverses the list

    root = malloc( sizeof(struct node) );
    root->next = 0;
    root->x = 12;
    conductor = root;
    if ( conductor != 0 ) {//iterates through each pointer via next until end is reached
        while ( conductor->next != 0)
        {
            printf (" d\n", conductor->x)
            conductor = conductor->next;
        }
        printf (" d\n", conductor->x)
    }

    conductor->next = malloc( sizeof(struct node) );//creates a node at end of list

    conductor = conductor->next;

    if ( conductor == 0 )
    {
        printf( "Out of memory" );
        return 0;
    }
    //initialise new memory
    conductor->next = 0;
    conductor->x = 42;

    return 0;
}

