//cpp templates systems and prototype object system
//this file for func decs and data types
#ifndef _object_h //ifndef 'if not defined'
#define _object_h

typedef enum {
    NORTH, SOUTH, EAST, WEST
} DIRECTION;

typedef struct {
    char *description;
    int (*init )(void *self);
    void (*describe)(void *self);
    void (*destroy)(void *self);
    void *(*move)(void *self, Direction direction);
    int (*attack)(void *self, int damage);
} Object;

int Object_init(void *self);
void Object_destroy(void *self);
void Object_describe(void *self);
void Object_move(void *self, Direction direction);
int Object_attack(void *self, int damage);
void *Object_new(size_t size, Object proto, char *description);

#define NEW(T, N) Object_new(sizeof(T), T##Proto, N) //makes a macro, uses code on right when ever macro on left is called
//'##' operator concatenates T with Proto, so you can call as 'TProto'
#define _(N) proto.N //syntax trick. let's me write obj->proto.thing ans obj->_(thing)

#endif
