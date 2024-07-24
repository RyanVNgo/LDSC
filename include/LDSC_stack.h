#ifndef LDSC_STACK_H
#define LDSC_STACK_H

typedef struct {
  int length;
  void* top;
  int (*getLength)(const void* self);
} LDSC_stack;

LDSC_stack* LDSC_stack_init();

#endif
