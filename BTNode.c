#include "BTNode.h"

#define BT_allocate()       (stNode*)malloc(sizeof(stNode))
#define BT_free(a)          free(a)

/**************************************************************************
****************************PUBLIC FUNCTIONS****************************** 
***************************************************************************/
stNode* BTNode_createNode(uint16_t data,stNode* nil)
{
    stNode* temp=BT_allocate();
    if(NULL!=temp){
        temp->data=data;
        temp->red=BT_TRUE;
        temp->left=nil;
        temp->right=nil;
        temp->parent=nil;
    }
    return temp;
}

stNode* BTNode_createEmptyNode(void)
{
        stNode* node=BT_allocate();
        return node;
}

void BTNode_freeNode(stNode* Node)
{
    if(Node != NULL)
        BT_free(Node);
}
