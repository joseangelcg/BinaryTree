#include "BinaryTree.h"
#include "NodeQueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


static void BT__inordera(stNode* p,stNode* nil);
static void BT__preordera(stNode* p,stNode* nil);
static void BT__postordera(stNode* p,stNode* nil);

static void BT__leftRotate(stRBT* t, stNode* x);
static void BT__rightRotate(stRBT* t, stNode* y);

static void BT__insertFixup(stRBT* t, stNode* node);

static uint8_t BT__log2(uint16_t num);
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
}

/**************************************************************************
****************************PUBLIC FUNCTIONS****************************** 
***************************************************************************/

stRBT* BT_createTree(void){
   stRBT* temp=BT_allocateRBT();

   if(NULL!=temp){
        stNode* node = BTNode_createEmptyNode();
        if(NULL!=node)
        {
            temp->nil = temp->root = node; //node was allocated
            temp->size = 0; //Init size
            (temp->nil)->red = BT_FALSE;
        }
        else
        {
            temp=NULL; //node couldn't be allocated. Error
            free(temp); // Free previously allocated tree.
        }
   }
   return temp;
}



BT_bool BT_insertnode(uint16_t data, stRBT* t){
    
    stNode* toInsert=BTNode_createNode(data,t->nil);

    //Unsuccesfull memory allocation of new node.
    if(NULL==toInsert) return BT_FALSE;

    if(t->nil==t->root){
        //Root node is nil node, so new node will be root.
        t->root=toInsert;
        (t->root)->red=BT_FALSE;
        /* Update size */
        (t->size)++;
        return BT_TRUE;
    }else{
        
        stNode* aux=t->root;
        
        while(aux != t->nil){
            
            if(data==aux->data){
                printf("Data %d already exists in tree\n",aux->data);
                return BT_FALSE; //Node exists

            }else if(data > aux->data){

                //Data is inserted to the right of the node
                if(aux->right==t->nil){
                    toInsert->parent=aux;
                    aux->right=toInsert;
                    aux = t->nil;
                }else{
                    aux=aux->right;
                }

            }else{
                //Data is inserted to the left of the node
                if(aux->left==t->nil){
                    toInsert->parent=aux;
                    aux->left=toInsert;
                    aux = t->nil;
                }else{
                    aux=aux->left;
                } 
            }
        }

        BT__insertFixup(t,toInsert);
        /* Update size */
        (t->size)++;
        return BT_TRUE;
    }
}

BT_bool BT_searchnode(uint16_t data, stRBT* t){
    stNode* aux=t->root;

    while(aux != t->nil){
        
        if(data == aux->data) return BT_TRUE;

        if(data < aux->data){
            //search in left subtree
            aux=aux->left;
        }else if(data > aux->data){
            //search in right subtree
            aux=aux->right;
        }
    }
    return BT_FALSE;
}


void BT_inorder(stRBT* t){
    BT__inordera(t->root,t->nil);
    printf("\n");
    printf("Tree size is: %d \n",t->size);
}

void BT_preorder(stRBT* t){
    BT__preordera(t->root,t->nil);
    printf("\n");
    printf("Tree size is: %d \n",t->size);
}

void BT_postorder(stRBT* t){
    BT__postordera(t->root,t->nil);
    printf("\n");
    printf("Tree size is: %d \n",t->size);
}

/**************************************************************************
****************************PRIVATE FUNCTIONS****************************** 
 **************************************************************************/
static void BT__inordera(stNode* p,stNode* nil){
    if(p->left!=nil){
        BT__inordera(p->left,nil);
    }

    printf("|%d, %d| ",p->data, p->red);
    
    if(p->right!=nil){
            BT__inordera(p->right,nil);
    }
}

static void BT__preordera(stNode* p,stNode* nil){
    printf("|%d, %d| ",p->data, p->red);
    
    if(p->left!=nil){
        BT__preordera(p->left,nil);
    }
                    
    if(p->right!=nil){
        BT__preordera(p->right,nil);
    }
}

static void BT__postordera(stNode* p,stNode* nil){

    if(p->left!=nil){
        BT__postordera(p->left,nil);
    }

    if(p->right!=nil){
        BT__postordera(p->right,nil);
    }
    printf("|%d, %d| ",p->data, p->red);
}


static void BT__leftRotate(stRBT* t, stNode* x){
    stNode* y=x->right;

    x->right=y->left; //move y left subtree into x right's
    if(y->left != t->nil) (y->left)->parent=x; //in case y left subtree is not nil, link x as a parent of that subtree
    y->parent=x->parent; //set y parent as x parent. X parent will be y after all
    
    if(x->parent==t->nil) 
            t->root=y; //if x parent is nil, x is the root, so need to fix this
    else if(x==(x->parent)->left) 
            (x->parent)->left=y; //if x is left child, lets replace it for y
    else if(x==(x->parent)->right)
            (x->parent)->right=y;//if x is right child, lets replace it for y

    y->left=x;
    x->parent=y; //final fixes
}

static void BT__rightRotate(stRBT* t, stNode* y){
    stNode* x=y->left;
    
    y->left=x->right;
    if(x->right!=t->nil) (x->right)->parent=y;
    x->parent=y->parent;

    if(y->parent==t->nil)
            t->root=x;
    else if(y==(y->parent)->left)
            (y->parent)->left=x;
    else if(y==(y->parent)->right)
            (y->parent)->right=x;

    x->right=y;
    y->parent=x;
}

static void BT__insertFixup(stRBT* t, stNode* node){

    stNode* x = node;
    while((x->parent)->red)
    {
        stNode* y;

        //check if parent is left child
        if(x->parent==((x->parent)->parent)->left){

            //parent is left child
            y=((x->parent)->parent)->right;//get uncle

            if(y->red){ //uncle is red
                y->red=BT_FALSE;
                (x->parent)->red=BT_FALSE;
                ((x->parent)->parent)->red=BT_TRUE;
                x=(x->parent)->parent;//pass problem to grandpa

            }else{//uncle is black

                if(x==(x->parent)->right){
                    x=x->parent;
                    BT__leftRotate(t,x);
                }

                (x->parent)->red=BT_FALSE;
                ((x->parent)->parent)->red=BT_TRUE;
                BT__rightRotate(t,((x->parent)->parent));
            }

        }else{
            //parent is right child
            y=((x->parent)->parent)->left;//get uncle

            if(y->red == BT_TRUE)
            { //uncle is red

                y->red=BT_FALSE;
                (x->parent)->red=BT_FALSE;
                ((x->parent)->parent)->red=BT_TRUE;
                x=(x->parent)->parent;//pass problem to grandpa

            }
            else
            {//uncle is black

                if(x==(x->parent)->left)
                {
                    x=x->parent;
                    BT__rightRotate(t,x);
                }

                (x->parent)->red=BT_FALSE;
                ((x->parent)->parent)->red=BT_TRUE;
                BT__leftRotate(t,((x->parent)->parent));
            }
        }
    }
    (t->root)->red = BT_FALSE;
}

static uint8_t BT__log2(uint16_t num)
{
    int8_t i8cnt;
    if(num)
    {
        for(i8cnt=15; i8cnt>=0; i8cnt--)
        {
            if((1U<<i8cnt) & num)
                return i8cnt;
        }
    }
    else
    {
        return 0xFF;
    }
}
void BT_printTree(stRBT* t)
{
    stNode* n = t->root;
    uint16_t elements = t->size;
    uint16_t elem_cnt,level_cnt;

    /*check that tree has something*/
    if(elements > 0)
    {
        printf("The given tree has the following structure:\n");
        printf("Tree size: %d\n", elements);
        printf("Tree max levels (counted from 0): %d\n\n", BT__log2(elements)+1 );
        stNodeQueue *q;
        q = NodeQueue_create();

        (void)NodeQueue_enqueue(q, n);
        level_cnt =1;
        elem_cnt= 0;

        /*While tree has valid elements*/
        while(elements)
        {
            /*dequeue element*/
            n = NodeQueue_dequeue(q);

            /*if not nil, decrement elemnts*/
            if(n != t->nil) elements--;

            /*Enqueue left and right nodes*/
            (void)NodeQueue_enqueue(q, n->left);
            (void)NodeQueue_enqueue(q, n->right);

            /*print current element*/
            if(n != t->nil)
                printf("|%d, %d|",n->data, n->red);
            else
                printf("|NIL, 0|");

            /*element was added to tree level*/
            elem_cnt++;

            if(elem_cnt == level_cnt)
            {
                /*current level was filled.
                 * reset elem_cnt and double level_cnt*/
                elem_cnt = 0;
                level_cnt = level_cnt << 1;
                /*print new line for new level*/
                printf("\n");
            }
        }
    }
}

