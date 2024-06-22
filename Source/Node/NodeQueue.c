#include <stdlib.h>

#include "BTNode.h"
#include "NodeQueue.h"

typedef struct queueNode{
    stNode* node;
    struct queueNode* next;
}stQueueElem;


/**************************************************************************
****************************PUBLIC FUNCTIONS****************************** 
***************************************************************************/
stNodeQueue* NodeQueue_create(void)
{
    stNodeQueue *ret= (stNodeQueue*) malloc(sizeof(stNodeQueue));
    
    if(ret != NULL)
    {
        ret->head = ret->tail = NULL;
        ret->size = 0;
    }
}

void NodeQueue_delete(stNodeQueue* q)
{
    if(q != NULL)
    {
        stQueueElem* temp_head = (stQueueElem*) q->head;

        /*First, release all elements memory*/
        while((q->size)--)
        {
            stQueueElem* temp = temp_head;
            temp_head = temp_head->next;

            free(temp);
        }

        /* release stNodeQueue struct */
        free(q);
    }
    return;
}

bool NodeQueue_enqueue(stNodeQueue* q, stNode* node)
{

    if( node != NULL && q != NULL)
    {
        /*Allocate new queue element in queue */
        stQueueElem *p = (stQueueElem*) malloc(sizeof(stQueueElem));

        if( p != NULL)
        {
            /*Allocation succesfull.*/
            p->node = node;
            /* New element next always point to NULL*/
            p->next = NULL;

            if(q->size > 0)
            {
                /*queue has elements. Add at tail*/
                stQueueElem *temp= (stQueueElem*) q->tail;
                
                temp->next = p;
                q->tail = (void*) p;
            }
            else
            {
                /*queue is empty. */
                q->head = q->tail = (void*) p;
            }

            /*update size*/
            (q->size)++;

            /*Insert successful. Return true*/
            return true;
        }
    }

    return false;
}

stNode* NodeQueue_dequeue(stNodeQueue* q)
{
    stQueueElem* temp;
    stNode* ret;

    if( q!= NULL )
    {
        /* queue empty*/
        if(q->size == 0) return NULL;

        /*get node from queue*/
        temp = (stQueueElem*) q->head;
        ret = temp->node;

        /*update head*/
        q->head = (void*) temp->next;

        /* if head is NULL, then queue was emptied. 
         * Set tail to NULL*/
        if(q->head == NULL) q->tail = NULL;

        /* update size */
        (q->size)--;

        /*Free allocation of released element*/
        free(temp);

        /*return value of dequeued element*/
        return ret;
    }

    return NULL;
}

uint16_t NodeQueue_getSize(stNodeQueue* q)
{
    if(q != NULL) return q->size;

    /*Return xFFFF when null queue*/
    return 0xFFFF;
}
