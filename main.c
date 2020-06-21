#include "BinaryTree.h"
#include <stdio.h>

/************TEST MAIN*********************/
void main(void){

    stRBT* myTree=BT_createTree();
    stNode* aux;

    BT_insertnode(12,myTree);
    BT_insertnode(32,myTree);
    BT_insertnode(45,myTree);
    BT_insertnode(76,myTree);
    BT_insertnode(98,myTree);
    BT_insertnode(23,myTree);
    BT_insertnode(88,myTree);
    BT_insertnode(67,myTree);
    BT_insertnode(56,myTree);
    BT_insertnode(87,myTree);
    BT_insertnode(31,myTree);
    BT_insertnode(99,myTree);
    BT_insertnode(69,myTree);
    BT_insertnode(78,myTree);
    BT_insertnode(85,myTree);

    //BT_inorder(myTree);
    BT_printTree(myTree);

    printf("Tree minimum is: %d\n", BT_minimum(myTree));
    printf("Tree maximum is: %d\n", BT_maximum(myTree));
}


