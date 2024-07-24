#include <LDSC_stack.h>
#include <stdlib.h>

typedef struct LDSC_node {
  void* dataPtr;
  struct LDSC_node* next;
} LDSC_node;

/** create and return a new stack node
static LDSC_node* LDSC_node_init(void* dataPtrIn) {
  LDSC_node* newNode = (LDSC_node*)malloc(sizeof(LDSC_node));
  newNode->dataPtr = dataPtrIn;
  newNode->next = NULL;
  return newNode;
}
*/

struct stackPrivate {
  int length;
  LDSC_node* top;
};

int LDSC_stack_length(LDSC_stack* self) {
  return ((LDSC_stack*)(self))->pd->length;
}

void* LDSC_stack_peek(LDSC_stack* self) {
  LDSC_stack* stack = (LDSC_stack*)self;
  if (!stack->pd->top) return NULL;
  return stack->pd->top->dataPtr;
}

LDSC_stack* LDSC_stack_init() {
  LDSC_stack* newStack = malloc(sizeof(LDSC_stack));

  newStack->pd = malloc(sizeof(stackPrivate));
  newStack->pd->length = 0;
  newStack->pd->top = NULL;

  newStack->getLength = &LDSC_stack_length;
  newStack->peek = &LDSC_stack_peek;

  return newStack;
}
