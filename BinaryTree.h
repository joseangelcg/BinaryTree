#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BT_allocate() (stNode*)malloc(sizeof(stNode));

#define BT_FALSE    0
#define BT_TRUE     1

typedef unsigned char BT_bool;

typedef struct Node{
    uint16_t data;
    struct Node* left;
    struct Node* right;
} stNode;

stNode* BT_insertnode(uint16_t data, stNode* p);
stNode* BT_deletenode(uint16_t data, stNode* p);
stNode* BT_searchnode(uint16_t data);

#endif
