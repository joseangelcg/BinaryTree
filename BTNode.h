#ifndef _BTNODE_H
#define _BTNODE_H

#include <stdlib.h>
#include <stdint.h>

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

/* Function Prototypes */
stNode* BTNode_createNode(uint16_t data,stNode* nil);
stNode* BTNode_createEmptyNode(void);
void BTNode_freeNode(stNode* Node);
#endif
