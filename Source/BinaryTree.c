#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "types.h"
#include "BTNode.h"
#include "NodeQueue.h"
#include "BinaryTree.h"

#define BT_allocateRBT()    (pRBT)malloc(sizeof(stRBT))
#define BT_freeRBT(a)       free(a)

typedef struct RBTree{
    stNode* root;
    stNode* nil;
    uint16_t size;
}stRBT;

static void BT__inordera(stNode* p,stNode* nil);
static void BT__preordera(stNode* p,stNode* nil);
static void BT__postordera(stNode* p,stNode* nil);

static void BT__leftRotate(pRBT t, stNode* x);
static void BT__rightRotate(pRBT t, stNode* y);

static void BT__insertFixup(pRBT t, stNode* node);

static void BT__deleteNode(pRBT t, stNode* node);
static void BT__deleteFixup(pRBT t, stNode* node);

static uint8_t BT__log2(uint16_t num);

static stNode* BT__SubTreeminimum(stNode* n, pRBT t);
static stNode* BT__SubTreemaximum(stNode* n, pRBT t);

stNode* BT__searchNode(uint16_t data, pRBT t);

static void BT__Transplant(pRBT t, stNode* u, stNode* v);
/**************************************************************************
****************************PUBLIC FUNCTIONS****************************** 
***************************************************************************/

pRBT BT_createTree(void){
   pRBT temp=BT_allocateRBT();

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



BT_bool BT_insertNode(uint16_t data, pRBT t){
    
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

BT_bool BT_deleteNode(uint16_t data, pRBT t)
{
    stNode* aux;

    aux = BT__searchNode(data, t);

    if( aux != t->nil)
    {
        /* data exists. Delete it */
        BT__deleteNode(t, aux);
        return BT_TRUE;
    }
    else
    {
        /*data does not exist. Return false */
        return BT_FALSE;
    }
}

BT_bool BT_searchNode(uint16_t data, pRBT t)
{
    stNode* aux;
    aux = BT__searchNode(data, t);

    return (aux != t->nil ? BT_TRUE : BT_FALSE);
}


void BT_inorder(pRBT t){
    BT__inordera(t->root,t->nil);
    printf("\n");
    printf("Tree size is: %d \n",t->size);
}

void BT_preorder(pRBT t){
    BT__preordera(t->root,t->nil);
    printf("\n");
    printf("Tree size is: %d \n",t->size);
}

void BT_postorder(pRBT t){
    BT__postordera(t->root,t->nil);
    printf("\n");
    printf("Tree size is: %d \n",t->size);
}

void BT_printTree(pRBT t)
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
    /* Delete queue used for printing */
    NodeQueue_delete(q);

    }

    /* Print a last new line */
    printf("\n");
}

uint16_t BT_minimum(pRBT t)
{
    if( t != NULL)
    {
        stNode* n;
        n = BT__SubTreeminimum(t->root, t);
        if(n != t->nil)
        {
            return ( n->data );
        }
        else
        {
            /* tree is empty */
            printf("BT_minimum: Tree is empty\n");
            return 0xFFFF;
        }
    }

    printf("BT_minimum: Tree does not exist\n");
    return 0xFFFF;
}

uint16_t BT_maximum(pRBT t)
{
    if( t != NULL)
    {
        stNode* n;
        n = BT__SubTreemaximum(t->root, t);
        if(n != t->nil)
        {
            return ( n->data );
        }
        else
        {
            /* tree is empty */
            printf("BT_maximum: Tree is empty\n");
            return 0xFFFF;
        }
    }

    printf("BT_maximum: Tree does not exist\n");
    return 0xFFFF;
}
/**************************************************************************
****************************PRIVATE FUNCTIONS****************************** 
***************************************************************************/
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


static stNode* BT__SubTreeminimum(stNode* n, pRBT t)
{
    while(n != t->nil && n->left != t-> nil)
        n = n->left;
    return n;
}

static stNode* BT__SubTreemaximum(stNode* n, pRBT t)
{
    while(n != t->nil && n->right != t-> nil)
        n = n->right;
    return n;
}

stNode* BT__searchNode(uint16_t data, pRBT t){
    stNode* aux=t->root;

    while(aux != t->nil){
        
        if(data == aux->data) return aux;

        if(data < aux->data){
            //search in left subtree
            aux=aux->left;
        }else if(data > aux->data){
            //search in right subtree
            aux=aux->right;
        }
    }
    return t->nil;
}

static void BT__leftRotate(pRBT t, stNode* x){
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

static void BT__rightRotate(pRBT t, stNode* y){
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

static void BT__insertFixup(pRBT t, stNode* node){

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

static void BT__deleteNode(pRBT t, stNode* node)
{
    stNode* x;
    stNode* y;
    BT_bool y_original_color = node->red;
    
    if( node->left == t->nil)
    {
        /* Deleted node has right child or Nil childs
         * Transplant right child subtree to deleted node
         * This works even if right child is also NIL */
        x = node->right;
        BT__Transplant(t, node, node->right);
    }
    else if( node->right == t->nil )
    {
        /* Deleted node has left child 
         * Transplant left child subtree to deleted node */
        x = node->left;
        BT__Transplant(t, node, node->left);
    }
    else
    {
        /* Deleted node has two children
         * Determine succesor and make 
         * proper adjustments */
        
        /*obtain sucessor of node*/
        y = BT__SubTreeminimum(node->right, t);
        y_original_color = y-> red;

        /* Obtain right child of succesor */
        x = y->right;

        if( node == y->parent)
        {
            /* Sucessor is a direct child of removed node
             * force x to mantain y as parent */
            x->parent = y;
        }
        else
        {
            /* Sucessor is not a direct child of removed node*/
            /* Transplant right subtree of sucessor to Sucessor spot*/
            BT__Transplant(t, y, y->right);

            /* Sucessor adopts right child from deleted node */
            y->right = node->right;
            (y->right)->parent = y;
        }

        /* Transplant sucessor to deleted node spot */
        BT__Transplant(t, node, y);
        
        /* Sucessor adopts left child from deleted node */
        y->left = node->left;
        (y->left)->parent = y;
        /* Keep color from removed node */
        y->red = node->red;
    }

    /* Free memory of deleted node */
    BTNode_freeNode(node);

    /* if a Black node was removed/moved, run fixup function */
    if(y_original_color == BT_FALSE)
        BT__deleteFixup(t, x);

    /*update tree size */
    (t->size)--;
}

static void BT__deleteFixup(pRBT t, stNode* node)
{
    while((node != t->root) && (node->red == BT_FALSE))
    {
        stNode* bro;

        if(node == (node->parent)->left)
        {
            /* Node is a left child */

            /* Get right brother */
            bro = (node->parent)->right;

            /* If bro is red and node is black
             * then bro has to turn black and parent to red*/
            if(bro->red == BT_TRUE)
            {
                /* Set bro color to black*/
                bro->red = BT_FALSE;
                
                /* set parent color to red */
                (node->parent)->red = BT_TRUE;
                
                /* Rotate parent to left*/
                BT__leftRotate(t, node->parent);

                /* As parent was rotated, update brother*/
                bro = (node->parent)->right;
            }

            /* if new brother has two black childs, then he must be red*/
            if( ((bro->left)->red == BT_FALSE) && ((bro->right)->red == BT_FALSE))
            {
                /* Bro has two black childs, he must be black*/
                bro->red = BT_TRUE;

                /* Pass problem to parent*/
                node = node->parent;
            }
            else
            {
                /* Bro has one or two red childs. 
                 * We are almost done*/ 
                
                /* Enter here only if
                 * Bro has a right black child */
                if( (bro->right)->red = BT_FALSE)
                {
                    /* Bro right child is black*/

                    /* Set bro left child to black*/
                    (bro->left)->red = BT_FALSE;

                    /* Bro must be red */
                    bro->red = BT_TRUE;

                    /* Rotate bro to the right*/
                    BT__rightRotate(t, bro);

                    /* As bro was rotated, update brother*/
                    bro = (node->parent)->right;
                }

                /* Pass color of parent to bro */
                bro->red = (node->parent)->red;
                
                /* Set parent color to black */
                (node->parent)->red = BT_FALSE;

                /* Set bro right child color to black*/
                (bro->right)->red = BT_FALSE;

                /* Rotate parent to left */
                BT__leftRotate(t, node->parent);

                /* set node to root to foce end of while*/
                node = t->root;
            }
        }
        else
        {
            /* Node is a right child */

            /* Get left brother */
            bro = (node->parent)->left;

            /* If bro is red and node is black
             * then bro has to turn black and parent to red*/
            if(bro->red == BT_TRUE)
            {
                /* Set bro color to black*/
                bro->red = BT_FALSE;
                
                /* set parent color to red */
                (node->parent)->red = BT_TRUE;
                
                /* Rotate parent to right*/
                BT__rightRotate(t, node->parent);

                /* As parent was rotated, update brother*/
                bro = (node->parent)->left;
            }

            /* if new brother has two black childs, then he must be red*/
            if( ((bro->left)->red == BT_FALSE) && ((bro->right)->red == BT_FALSE))
            {
                /* Bro has two black childs, he must be black*/
                bro->red = BT_TRUE;

                /* Pass problem to parent*/
                node = node->parent;
            }
            else
            {
                /* Bro has one or two red childs. 
                 * We are almost done*/ 
                
                /* Enter here only if
                 * Bro has a left black child */
                if( (bro->left)->red = BT_FALSE)
                {
                    /* Bro left child is black*/

                    /* Set bro right child to black*/
                    (bro->right)->red = BT_FALSE;

                    /* Bro must be red */
                    bro->red = BT_TRUE;

                    /* Rotate bro to the left*/
                    BT__leftRotate(t, bro);

                    /* As bro was rotated, update brother*/
                    bro = (node->parent)->left;
                }

                /* Pass color of parent to bro */
                bro->red = (node->parent)->red;
                
                /* Set parent color to black */
                (node->parent)->red = BT_FALSE;

                /* Set bro left child color to black*/
                (bro->left)->red = BT_FALSE;

                /* Rotate parent to right */
                BT__rightRotate(t, node->parent);

                /* set node to root to foce end of while*/
                node = t->root;
            }
            
        }
    }

    /* Set node color to black */
    node->red = BT_FALSE;
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

static void BT__Transplant(pRBT t, stNode* u, stNode* v)
{
    if(u->parent == t->nil)
        t->root = v;
    else if(u == (u->parent)->left)
        (u->parent)->left = v;
    else
        (u->parent)->right = v;

    v->parent = u->parent;
}
