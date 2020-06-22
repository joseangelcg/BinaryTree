#ifndef _NODEQUEUE_H
#define _NODEQUEUE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "BTNode.h"

typedef struct Queue{
   void *head;
   void *tail;
   uint16_t size;
}stNodeQueue;

/* Function Prototypes */

stNodeQueue* NodeQueue_create(void);

void NodeQueue_delete(stNodeQueue* q);

bool NodeQueue_enqueue(stNodeQueue* q, stNode* node);

stNode* NodeQueue_dequeue(stNodeQueue* q);

uint16_t NodeQueue_getSize(stNodeQueue* q);
#endif
