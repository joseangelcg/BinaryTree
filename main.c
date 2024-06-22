#include "BinaryTree.h"
#include <stdio.h>

/************TEST MAIN*********************/
void main(void){

    pRBT myTree=BT_createTree();

    BT_insertNode(12,myTree);
    BT_insertNode(32,myTree);
    BT_insertNode(45,myTree);
    BT_insertNode(76,myTree);
    BT_printTree(myTree);
    printf("===================================================================\n");

    BT_insertNode(98,myTree);
    BT_insertNode(23,myTree);
    BT_insertNode(88,myTree);
    BT_insertNode(67,myTree);
    BT_printTree(myTree);
    printf("===================================================================\n");

    BT_insertNode(56,myTree);
    BT_insertNode(87,myTree);
    BT_insertNode(31,myTree);
    BT_insertNode(99,myTree);
    BT_printTree(myTree);
    printf("===================================================================\n");

    BT_insertNode(69,myTree);
    BT_insertNode(78,myTree);
    BT_insertNode(85,myTree);

    BT_deleteNode(56,myTree);
    BT_deleteNode(76,myTree);
    //BT_inorder(myTree);
    BT_printTree(myTree);
    printf("===================================================================\n");

    printf("Tree minimum is: %d\n", BT_minimum(myTree));
    printf("Tree maximum is: %d\n", BT_maximum(myTree));
}


