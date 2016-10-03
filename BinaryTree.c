
#include "BinaryTree.h"


void BT_inorder(stNode* p,stNode* nil);
void BT_preorder(stNode* p,stNode* nil);
void BT_postorder(stNode* p,stNode* nil);
stNode* BT_createNode(uint16_t data,stRBT* t);
stRBT* BT_createTree(void);

stNode* BT_createNode(uint16_t data,stRBT* t){
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

stRBT* BT_createTree(void){
   stRBT* temp=BT_allocateRBT();

   if(NULL!=temp){
        stNode* node=BT_allocate();
        if(NULL!=node) temp->nil = temp->root = node; //node was allocated
        else temp=NULL; //node couldn't be allocated. Error
   }
   return temp;
}

void main(void){

    stRBT* myTree=BT_createTree();
    stNode* aux;

    BT_insertnode(7,myTree);
    BT_insertnode(5,myTree);
    BT_insertnode(9,myTree);
    
    BT_inorder(myTree->root,myTree->nil); printf("\n");
    BT_preorder(myTree->root,myTree->nil); printf("\n");
    BT_postorder(myTree->root,myTree->nil); printf("\n");
    
    printf("Nil node:%p\n",myTree->nil);
    aux=myTree->root;
    printf("I'm: %p and My parent is %p\n",aux,aux->parent);
    aux=aux->right;
    printf("I'm: %p and My parent is %p\n",aux,aux->parent);
    aux=(aux->parent)->left;
    printf("I'm: %p and My parent is %p\n",aux,aux->parent);

    printf("Search of 8:%d",BT_searchnode(8,myTree));
    printf("Search of 9:%d",BT_searchnode(9,myTree));

}

BT_bool BT_insertnode(uint16_t data, stRBT* t){
    
    stNode* toInsert=BT_createNode(data,t);

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

void BT_inorder(stNode* p,stNode* nil){
    if(p->left!=nil){
        BT_inorder(p->left,nil);
    }

    printf("|%d| ",p->data);
    
    if(p->right!=nil){
            BT_inorder(p->right,nil);
    }
}

void BT_preorder(stNode* p,stNode* nil){
    printf("|%d| ",p->data);   
    
    if(p->left!=nil){
        BT_preorder(p->left,nil);
    }
                    
    if(p->right!=nil){
        BT_preorder(p->right,nil);
    }
}

void BT_postorder(stNode* p,stNode* nil){

    if(p->left!=nil){
        BT_postorder(p->left,nil);
    }

    if(p->right!=nil){
        BT_postorder(p->right,nil);
    }
    printf("|%d| ",p->data);
}
