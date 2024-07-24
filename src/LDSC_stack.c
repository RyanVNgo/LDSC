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

int LDSC_stack_length(const void* self) {
  return ((LDSC_stack*)(self))->length;
}

LDSC_stack* LDSC_stack_init() {
  LDSC_stack* newStack = malloc(sizeof(LDSC_stack));
  newStack->length = 0;
  newStack->top = NULL;
  newStack->getLength = &LDSC_stack_length;
  return newStack;
}
