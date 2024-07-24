#ifndef LDSC_STACK_H
#define LDSC_STACK_H

typedef struct LDSC_stack LDSC_stack;
typedef struct stackPrivate stackPrivate;

struct LDSC_stack {
  int (*getLength)(LDSC_stack* self);
  void* (*peek)(LDSC_stack* self);
  stackPrivate* pd;
} ;

LDSC_stack* LDSC_stack_init();

#endif
