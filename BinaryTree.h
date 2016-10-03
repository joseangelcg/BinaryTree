#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BT_allocate() (stNode*)malloc(sizeof(stNode))
#define BT_allocateRBT() (stRBT*)malloc(sizeof(stRBT))

#define BT_FALSE    0
#define BT_TRUE     1

typedef unsigned char BT_bool;

typedef struct Node{
    uint16_t data;
    BT_bool red;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} stNode;

typedef struct RBTree{
    stNode* root;
    stNode* nil;
}stRBT;

BT_bool BT_insertnode(uint16_t data, stRBT* t);
BT_bool BT_deletenode(uint16_t data, stRBT* t);
BT_bool BT_searchnode(uint16_t data, stRBT* t);


#endif
