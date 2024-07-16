#ifndef LDSC_STACK_H
#define LDSC_STACK_H

typedef struct LDSC_stack LDSC_stack;

LDSC_stack* LDSC_stack_init();
void LDSC_stack_push(LDSC_stack*, void*);
void* LDSC_satck_pop(LDSC_stack*);
void* LDSC_stack_peek(LDSC_stack*);
int LDSC_stack_isEmpty(LDSC_stack*);
int LDSC_stack_size(LDSC_stack*);

#endif
