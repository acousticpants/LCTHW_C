#include <lcthw/dbg.h>
#include <lcthw/bstree.h>
#include <stdlib.h>
#include <lcthw/bstrlib.h>

static int default_compare(void *a, void *b)
{
    return bstrcmp((bstring)a, (bstring)b);
}

BSTree *BSTree_create(BSTree_compare compare)//see this in BSTree_struct in bstree.h
{
    BSTree *map = calloc(1, sizeof(BSTree));
    check_mem(map);

    mem->compare = compare == NULL ? default_compare : compare;//mofo fn eventually calls bstrcmp

    return map;

error:
    if(map) {
        BSTree_destroy(map);
    }
    return NULL;
}

static int BSTree_destroy_cb(BSTreeNode *node)//this fn does actual deletion, next calls function so no recursive calls
{
    free(node);
    return 0;
}

void BSTree_destroy(BSTree *map)//this fn calls the fn freeing the node and deleting preventing recursive call0
{
    if(map) {
        BSTree_traverse(map, BSTree_destroy_cb);
        free(map);
    }
}

static inline BSTreeNode *BSTreeNode_create(BSTreeNode *parent, void *key, void *data)
{
    BSTreeNode *node = calloc(1, sizeof(BSTreeNode));
    check_mem(node);

    node->key = key;
    node->data = data;
    node->parent = parent;
    return node;

error:
    return NULL;
}

static inline void BSTree_setnode(BSTree *map, BSTreeNode *node, void *key, void *data)
{
    int cmp = map->compare(node->key, key);

    if(cmp <= 0) {
        if(node->left) {
            BSTree_setnode(map, node->left, key, data);
        } else {
            node->left = BSTreeNode_create(node, key, data);
        }
    } else {
        if(node->right) {
            BSTree_setnode(map, node->right, key, data);
        } else {
            node->right = BSTreeNode_create(node, key, data);
        }
    }
}

int BSTree_set(BSTree *map, void *key, void *data)
{
    if(map->root == NULL) {
        //first so just make it and get out
        map->root = BSTreeNode_create(NULL, key, data);
        check_mem(map->root);
    } else {
        BSTree_setnode(map, map->root, key, data);
    }

    return 0;
error:
    return -1;
}

static inline BSTreeNode *BSTree_getnode(BSTree *map, BSTreeNode *node, void *key)//fn gets, called by get. is self similar function
{
    int cmp = map->compare(node->key, key);

    if(cmp == 0) {
        return node;
    } else if(cmp < 0) {
        if(node->left) {
            return BSTree_getnode(map, node->left, key);
        } else {
            return NULL;
        }
    } else {
        if(node->right) {
            return BSTree_getnode(map, node->right, key);//returns to caller works without needing to handle initial conditions
        } else {
            return NULL;
        }
    }
}

void *BSTree_get(BSTree *map, void *key)//calls get fn so not recursing with its own data
{
    if(map->root == NULL) {
        return NULL;
    } else {
        BSTreeNode *node = BSTree_getnode(map, map->root, key);
        return node == NULL ? NULL : node->data;
    }
}

static inline int BSTree_traverse_nodes(BSTreeNode *node, BSTree_traverse_cb traverse_cb)
{
    int rc = 0;

    if(node->left) {
        rc = BSTree_traverse_nodes(node->left, traverse_cb);
        if(rc != 0) return rc;
    }

    if(node->right) {
        rc = BSTree_traverse_nodes(node->right, traverse_cb);
        if(rc != 0) return rc;
    }

    return traverse_cb(node);

int BSTree_traverse(BSTree *map, BSTree_traverse_cb traverse_cb)
{
    if(map->root) {
        return BSTree_traverse_nodes(map->root, traverse_cb);
    }

    return 0;
}

static inline BSTreeNode *BSTree_find_min(BSTreeNode *node)
{//iterates through all left nodes to end of tree
    while(node->left) {
        node = node->left;
    }
//could easily have a find_max with while(node->right) 
    return node;
}

static inline void BSTree_replace_node_in_parent(BSTree *map, BSTreeNode *node, BSTreeNode *new_value)
{//target node replaced by its neighbour so no empty space left after delete target node
    if(node->parent) {
        if(node == node->parent->left) {
            node->parent->left = new_value;
        } else {
            node->parent->right = new_value;
        }
    } else {
        //this is the root so need to change it
        map->root = new_value;
    }

    if(new_value) {
        new_value->parent = node->parent;
    }
}

static inline void BSTree_swap(BSTreeNode *a, BSTreeNode *b)//swaps as name suggests
{
    void *temp = NULL;
    temp = b->key; b->key = a->key; a->key = temp;
    temp = b->data; b->data = a->data; a->data = temp;
}

static inline BSTreeNode *BSTree_node_delete(BSTree *map, BSTreeNode *node, void *key)//finds correct node and uses replace_node fn to move its children up to its parent. returns node to caller fn
{
    int cmp = map->compare(node->key, key);//next 2 code blocks compare node to choose left or right branches to traverse

    if(cmp < 0) {
        if(node->left) {
            return BSTree_node_delete(map, node->left, key);
        } else {
            //not found
            return NULL;
        }
    } else if(cmp > 0) {
        if(node->right) {
            return BSTree_node_delete(map, node->right, key);
        } else {
            //not found
            return NULL;
        }
    } else {//node and key are equal bec cmp return 0
        if(node->left && node->right) {
            // swap this node for the smallest node that is bigger than us
            BSTreeNode *successor = BSTree_find_min(node->right);
            BSTree_swap(successor, node);

            //this leaves the old successor with possibly a right child so replace it with that right child
            BSTree_replace_node_in_parent(map, successor, successor->right);

            //finally it's swapped, so return successor instead of node
            return successor;
        } else if(node->left) {
            BSTree_replace_node_in_parent(map, node, node->left);
        } else if(node->right) {
            BSTree_replace_node_in_parent(map, node, node->right);
        } else {
            BSTree_replace_node_in_parent(map, node, NULL);//found node with no children as left or right so replace with NULL
        }

        return node;//node returned to caller so it can be freed and managed
    }
}

void *BSTree_delete(BSTree *map, void *key)//setup fn for actual deletion recursive fn
{
    void *data = NULL;

    if(map->root) {
        BSTreeNode *node = BSTree_node_delete(map, map->root, key);

        if(node) {
            data = node->data;
            free(node);
        }
    }

    return data;
}