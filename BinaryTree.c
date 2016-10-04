
#include "BinaryTree.h"


static void BT__inordera(stNode* p,stNode* nil);
static void BT__preordera(stNode* p,stNode* nil);
static void BT__postordera(stNode* p,stNode* nil);

static stNode* BT__createNode(uint16_t data,stRBT* t);

static void BT__leftRotate(stRBT* t, stNode* x);
static void BT__rightRotate(stRBT* t, stNode* y);

static void BT__insertFixup(stRBT* t, stNode* x);

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

    BT_inorder(myTree);
    
}

/**************************************************************************
****************************PRIVATE FUNCTIONS****************************** 
 **************************************************************************/

stRBT* BT_createTree(void){
   stRBT* temp=BT_allocateRBT();

   if(NULL!=temp){
        stNode* node=BT_allocate();
        if(NULL!=node) temp->nil = temp->root = node; //node was allocated
        else temp=NULL; //node couldn't be allocated. Error
   }
   return temp;
}



BT_bool BT_insertnode(uint16_t data, stRBT* t){
    
    stNode* toInsert=BT__createNode(data,t);

    //Unsuccesfull memory allocation of new node.
    if(NULL==toInsert) return BT_FALSE;

    if(t->nil==t->root){
        //Root node is nil node, so new node will be root.
        t->root=toInsert;
        (t->root)->red=BT_FALSE;
        return BT_TRUE;
    }else{
        
        stNode* aux=t->root;
        
        while(1){
            
            if(data==aux->data){
                printf("Data %d already exists in tree\n",aux->data);
                return BT_FALSE; //Node exists

            }else if(data > aux->data){

                //Data is inserted to the right of the node
                if(aux->right==t->nil){
                    toInsert->parent=aux;
                    aux->right=toInsert;
                    return BT_TRUE;
                }else{
                    aux=aux->right;
                }

            }else{
                //Data is inserted to the left of the node
                if(aux->left==t->nil){
                    toInsert->parent=aux;
                    aux->left=toInsert;
                    return BT_TRUE;
                }else{
                    aux=aux->left;
                } 
            }
        }

        BT__insertFixup(t,toInsert);
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
}

void BT_preorder(stRBT* t){
    BT__preordera(t->root,t->nil);
}

void BT_postorder(stRBT* t){
    BT__postordera(t->root,t->nil);
}

/**************************************************************************
****************************PRIVATE FUNCTIONS****************************** 
 **************************************************************************/
static stNode* BT__createNode(uint16_t data,stRBT* t){
    stNode* temp=BT_allocate();
    if(NULL!=temp){
        temp->data=data;
        temp->red=BT_TRUE;
        temp->left=t->nil;
        temp->right=t->nil;
        temp->parent=t->nil;
    }
    return temp;
}

static void BT__inordera(stNode* p,stNode* nil){
    if(p->left!=nil){
        BT__inordera(p->left,nil);
    }

    printf("|%d| ",p->data);
    
    if(p->right!=nil){
            BT__inordera(p->right,nil);
    }
}

static void BT__preordera(stNode* p,stNode* nil){
    printf("|%d| ",p->data);   
    
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
    printf("|%d| ",p->data);
}


static void BT__leftRotate(stRBT* t, stNode* x){
    stNode* y=x->right;

    x->right=y->left; //move y left subtree into x right's
    if(y->left!= t->nil) (y->left)->parent=x; //in case y left subtree is nil, link x as a parent of that subtree
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

static void BT__insertFixup(stRBT* t, stNode* x){

    while((x->parent)->red){
        stNode* y;

        //check if parent is left child
        if(x->parent==((x->parent)->parent)->left){
            //parent is left child
            y=((x->parent)->parent)->right;//get uncle

            if(y->red){ //uncle is red
                y->red=BT_FALSE;
                x->parent=BT_FALSE;
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

            if(y->red){ //uncle is red
                y->red=BT_FALSE;
                x->parent=BT_FALSE;
                ((x->parent)->parent)->red=BT_TRUE;
                x=(x->parent)->parent;//pass problem to grandpa

            }else{//uncle is black

                if(x==(x->parent)->left){
                    x=x->parent;
                    BT__rightRotate(t,x);
                }

                (x->parent)->red=BT_FALSE;
                ((x->parent)->parent)->red=BT_TRUE;
                BT__leftRotate(t,((x->parent)->parent));
            }
        }
    }
}
