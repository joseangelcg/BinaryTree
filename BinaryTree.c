
#include "BinaryTree.h"

static stNode* root=NULL;

void BT_printnode(stNode* p);
void BT_inorder(stNode* p);
void BT_preorder(stNode* p);
void BT_postorder(stNode* p);
stNode* BT_createNode(uint16_t data);

stNode* BT_createNode(uint16_t data){
    stNode temp=BT_allocate();
    if(NULL!=temp){
        temp->data=data;
        temp->red=BT_TRUE;
        temp->left=NULL;
        temp->right=NULL;
        temp->parent-NULL;
    }
    return temp;
}

void main(void){

    root=BT_insertnode(5,root);
    (void)BT_insertnode(9,root);
    (void)BT_insertnode(7,root);
    
    BT_inorder(root); printf("\n");
    BT_preorder(root); printf("\n");
    BT_postorder(root); printf("\n");
}

stNode* BT_insertnode(uint16_t data, stNode* p){
    
    //stNode toInsert=BT_createNode(data);

    if(p==NULL){
        p=BT_allocate();
        p->data=data;
        p->left=NULL;
        p->right=NULL;
        return p;
    }else{
        
        stNode* temp=p;
        
        while(1){
            
            if(data==p->data){
                printf("Data %d already exists in tree\n",p->data);
                return NULL; //Node exists

            }else if(data > p->data){

                //Data is inserted to the right of the node
                if(p->right==NULL){
                    temp=BT_allocate();
                    
                    p->right=temp;
                    temp->data=data;
                    return temp;
                }else{
                    p=p->right;
                }

            }else{
                //Data is inserted to the left of the node
                if(p->left==NULL){
                    temp=BT_allocate();
                    
                    p->left=temp;
                    temp->data=data;
                    return temp;
                }else{
                    p=p->left;
                } 
            }
        }
    }
}


void BT_inorder(stNode* p){
    if(p->left!=NULL){
        BT_inorder(p->left);
    }

    printf("|%d| ",p->data);
    
    if(p->right!=NULL){
            BT_inorder(p->right);
    }
}

void BT_preorder(stNode* p){
    printf("|%d| ",p->data);   
    
    if(p->left!=NULL){
        BT_preorder(p->left);
    }
                    
    if(p->right!=NULL){
        BT_preorder(p->right);
    }
}

void BT_postorder(stNode* p){

    if(p->left!=NULL){
        BT_postorder(p->left);
    }

    if(p->right!=NULL){
        BT_postorder(p->right);
    }
    printf("|%d| ",p->data);
}
void BT_printnode(stNode* p){
    printf("Parent: %d\n",p->data);
    if(p->left != NULL) printf("L Child: %d\n",(p->left)->data);
    if(p->right!= NULL) printf("R Child: %d\n",(p->right)->data);
}
