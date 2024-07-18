#ifndef LDSC_QUEUE_H
#define LDSC_QUEUE_H

typedef struct LDSC_queue LDSC_queue;

LDSC_queue* LDSC_queue_init();
int LDSC_queue_length(LDSC_queue*);
void LDSC_queue_enqueue(LDSC_queue*, void*);
void* LDSC_queue_dequeue(LDSC_queue*);
void* LDSC_queue_peek(LDSC_queue*);

#endif
