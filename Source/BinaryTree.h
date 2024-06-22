#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include "types.h"

struct RBTree;
typedef struct RBTree * pRBT;

pRBT BT_createTree(void);

BT_bool BT_insertNode(uint16_t data, pRBT t);
BT_bool BT_deleteNode(uint16_t data, pRBT t);
BT_bool BT_searchNode(uint16_t data, pRBT t);

void BT_inorder(pRBT t);
void BT_preorder(pRBT t);
void BT_postorder(pRBT t);

void BT_printTree(pRBT t);

uint16_t BT_minimum(pRBT t);
uint16_t BT_maximum(pRBT t);
#endif
