#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include <stdlib.h>
#include <stdint.h>

/* include Node library */
#include "BTNode.h"

#define BT_allocateRBT()    (stRBT*)malloc(sizeof(stRBT))
#define BT_freeRBT(a)       free(a)

typedef struct RBTree{
    stNode* root;
    stNode* nil;
    uint16_t size;
}stRBT;

stRBT* BT_createTree(void);

BT_bool BT_insertnode(uint16_t data, stRBT* t);
BT_bool BT_deletenode(uint16_t data, stRBT* t);
BT_bool BT_searchnode(uint16_t data, stRBT* t);

void BT_inorder(stRBT* t);
void BT_preorder(stRBT* t);
void BT_postorder(stRBT* t);

void BT_printTree(stRBT* t);

uint16_t BT_minimum(stRBT* t);
uint16_t BT_maximum(stRBT* t);
#endif
