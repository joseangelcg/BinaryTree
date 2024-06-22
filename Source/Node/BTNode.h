#ifndef _BTNODE_H
#define _BTNODE_H

#include "types.h"

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
