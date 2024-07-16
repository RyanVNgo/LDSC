#ifndef LDSC_STACK_H
#define LDSC_STACK_H

typedef struct LDSC_stack LDSC_stack;

LDSC_stack* LDSC_stack_init();
int LDSC_stack_length(LDSC_stack*);
int LDSC_stack_isEmpty(LDSC_stack*);
void LDSC_stack_push(LDSC_stack*, void*);
void* LDSC_stack_peek(LDSC_stack*);
void* LDSC_stack_pop(LDSC_stack*);

#endif
