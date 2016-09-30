
#include "BinaryTree.h"

static stNode* root=NULL;

void BT_printnode(stNode* p);

void main(void){
    stNode *temp;

    root=BT_insertnode(8,root);
    (void)BT_insertnode(9,root);
    (void)BT_insertnode(7,root);
    
    BT_printnode(root);
}

stNode* BT_insertnode(uint16_t data, stNode* p){
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


void BT_printnode(stNode* p){
    printf("Parent: %d\n",p->data);
    if(p->left != NULL) printf("L Child: %d\n",(p->left)->data);
    if(p->right!= NULL) printf("R Child: %d\n",(p->right)->data);
}
