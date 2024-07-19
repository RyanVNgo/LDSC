#include <LDSC_stack.h>
#include <stdlib.h>

// node definition
typedef struct LDSC_node {
  void* dataPtr;
  struct LDSC_node* next;
} LDSC_node;

// create and return a new stack node
static LDSC_node* LDSC_node_init(void* dataPtrIn) {
  LDSC_node* newNode = (LDSC_node*)malloc(sizeof(LDSC_node));
  newNode->dataPtr = dataPtrIn;
  newNode->next = NULL;
  return newNode;
}

// stack definition
struct LDSC_stack {
  int length;
  LDSC_node* top;
};

// create and return a new stack
LDSC_stack* LDSC_stack_init() {
  LDSC_stack* newStack = (LDSC_stack*)malloc(sizeof(LDSC_stack));
  newStack->length = 0;
  newStack->top = NULL;
  return newStack;
}

// return length of the stack
int LDSC_stack_length(LDSC_stack* stackIn) {
  if (!stackIn) return -1;
  return stackIn->length;
}

// check if the stack is empty
int LDSC_stack_isEmpty(LDSC_stack* stackIn) {
  if(!stackIn) return -1;
  if (!stackIn->length) return 1;
  return 0;
}

// push new data to the stack
void LDSC_stack_push(LDSC_stack* stackIn, void* dataPtrIn) {
  if (!stackIn || !dataPtrIn) return;

  LDSC_node* newNode = LDSC_node_init(dataPtrIn);
  newNode->next = stackIn->top;
  stackIn->top = newNode;

  stackIn->length++;
  return;
}

// return data on top of the stack
void* LDSC_stack_peek(LDSC_stack* stackIn) {
  if (!stackIn || !stackIn->top) return NULL;
  return stackIn->top->dataPtr;
}

// remove and return data on top of the stack
void* LDSC_stack_pop(LDSC_stack* stackIn) {
  if (!stackIn || !stackIn->top) return NULL;
  
  void* dataOutPtr = stackIn->top->dataPtr;
  LDSC_node* newTop = stackIn->top->next;
  
  free(stackIn->top);
  stackIn->top = newTop;

  return dataOutPtr;
}

