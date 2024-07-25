#include <LDSC_queue.h>
#include <stdlib.h>

/** node structure */
typedef struct Node {
  void* dataPtr;
  struct Node* next;
} Node;

/** create and return a new queue node */
static Node* Node_init(void* dataPtr) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->dataPtr = dataPtr;
  newNode->next = NULL;
  return newNode;
}

/**
  * @brief Opaque container for private data.
  */
struct stackPrivate {
  int length;
  Node* front;
  Node* back;
};

/**
  * @brief Check is queue is empty.
  * @param self Queue pointer.
  * @return Integer where 1 = empty and 0 = not empty.
  */
int LDSC_queue_empty(LDSC_queue* self) {
  if (!self) return -1;
  return self->pd->length == 0;
}

/**
  * @brief Get length of the queue.
  * @param self Queue pointer.
  * @return Length of the stack as integer type.
  */
int LDSC_queue_length(LDSC_queue* self) {
  if (!self) return -1;
  return self->pd->length;
}

/**
  * @brief Add item to end of the queue.
  * @param self Queue pointer.
  * @param dataPtr Pointer to data.
  * @details
  * Keep note that enqueue performs a shallow copy of the data.
  */
void LDSC_queue_enqueue(LDSC_queue* self, void* dataPtr) {
  if (!self || !dataPtr) return;
  Node* newNode = Node_init(dataPtr);
  if (!self->pd->back) {
    self->pd->front = newNode;
  } else {
    self->pd->back->next = newNode;
  }
  self->pd->back = newNode;
  self->pd->length++;
  return;
}

/**
  * @brief Remove item from fron of the queue.
  * @param self Queue pointer.
  * @return Pointer to data at the front of the queue.
  */
void* LDSC_queue_dequeue(LDSC_queue* self) {
  if (!self || !self->pd->front) return NULL;
  Node* oldFront = self->pd->front;
  void* dataFront = oldFront->dataPtr;
  self->pd->front = oldFront->next;
  self->pd->length--;
  free(oldFront);
  return dataFront;
}

/**
  * @brief Peek item at the front of the queue.
  * @param self Queue pointer.
  * @return Pointer to data at the front of the queue.
  */
void* LDSC_queue_peek(LDSC_queue* self) {
  if (!self || !self->pd->front) return NULL;
  return self->pd->front->dataPtr;
}

/**
  * @brief Delete the queue.
  * @param self Queue pointer.
  */
void LDSC_queue_delete(LDSC_queue* self) {
  if (!self) return;
  while (self->pd->front) {
    self->dequeue(self);
  }
  free(self->pd);
  free(self);
  return;
}

/**
 * @brief Create a new queue
 * @return Pointer to a new queue
 */
LDSC_queue* LDSC_queue_init() {
  LDSC_queue* newQueue = malloc(sizeof(LDSC_queue));

  newQueue->pd = malloc(sizeof(stackPrivate));
  newQueue->pd->length = 0;
  newQueue->pd->front = NULL;
  newQueue->pd->back = NULL;

  newQueue->empty = &LDSC_queue_empty;
  newQueue->length = &LDSC_queue_length;
  newQueue->enqueue = &LDSC_queue_enqueue;
  newQueue->dequeue = &LDSC_queue_dequeue;
  newQueue->peek = &LDSC_queue_peek;
  newQueue->delete = &LDSC_queue_delete;

  return newQueue;
}

