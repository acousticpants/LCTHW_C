#ifndef _lcthw_Hashmap_h
#define _lcthw_Hashmap_h
//fns declared here defined in hashmap.c
#include <stdint.h>
#include <lcthw/darray.h>

#define DEFAULT_NUMBER_OF_BUCKETS 100//things are in these buckets based on hash. each bucket is a DArray containing HashmapNode structs appended to end as needed

typedef int (*Hashmap_compare)(void *a, void b);
typedef uint32_t (*Hashmap_hash)(void *key);

typedef struct Hashmap {
    DArray *buckets;//this will hold HashmapNode pairs
    Hashmap_compare compare;// finds elements by their key defaults to bstrcmp to keys are bstrings
    Hashmap_hash hash;//the hashing fn takes key processes contents produces single uint32_t index number
} Hashmap;

typedef struct HashmapNode {
    void *key;
    void *data;
    uint32_t hash;//hash for this node make findnode quicker as only check key if hash first confirmed equal
} HashMapNode;

typedef int (*Hashmap_travers_cb)(HashmapNode *node);

Hashmap *Hashmap_create(Hashmap_compare compare, Hashmap_hash);
void Hashmap_destroy(Hashmap *map);

int Hashmap_set(Hashmap *map, void *key, void *data);
void *Hashmap_get(Hashmap *map, void *key);

int Hashmap_traverse(Hashmap *map, Hashmap_traverse_cb traverse_cb);

void *Hashmap_delete(Hashmap *map, void *key);

#endif