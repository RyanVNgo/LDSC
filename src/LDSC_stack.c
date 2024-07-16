#include <LDSC_stack.h>
#include <stdlib.h>

typedef struct LDSC_node {
  void* dataPtr;
  struct LDSC_node* next;
} LDSC_node;

static LDSC_node* LDSC_node_init(void* dataPtrIn) {
  LDSC_node* newNode = (LDSC_node*)malloc(sizeof(LDSC_node));
  newNode->dataPtr = dataPtrIn;
  newNode->next = NULL;
  return newNode;
}

struct LDSC_stack {
  int length;
  LDSC_node* top;
};

LDSC_stack* LDSC_stack_init() {
  LDSC_stack* newStack = (LDSC_stack*)malloc(sizeof(LDSC_stack));
  newStack->length = 0;
  newStack->top = NULL;
  return newStack;
}
void LDSC_stack_push(LDSC_stack* stackIn, void* dataPtrIn) {
  // conditions for invalid parameters
  if (stackIn == NULL || dataPtrIn == NULL) return;

  // create new node and assign new node's next to current top
  LDSC_node* newNode = LDSC_node_init(dataPtrIn);
  newNode->next = stackIn->top;

  // set top of stack to new node
  stackIn->top = newNode;
  return;
}
void* LDSC_satck_pop(LDSC_stack* stackIn);
void* LDSC_stack_peek(LDSC_stack* stackIn);
int LDSC_stack_isEmpty(LDSC_stack* stackIn);
int LDSC_stack_size(LDSC_stack* stackIn);
