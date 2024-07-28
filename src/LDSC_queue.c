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
  if (!newNode) return NULL;

  newNode->dataPtr = dataPtr;
  newNode->next = NULL;
  return newNode;
}

/**
  * @brief Opaque container for private data.
  */
struct privateData {
  int length;
  Node* front;
  Node* back;
};

/**************************************************/
/* LDSC_queue */

/**
  * @brief Check is queue is empty.
  * @param self Queue pointer.
  * @param status Error pointer.
  * @return Integer where 1 = empty and 0 = not empty.
  */
int LDSC_queue_empty(LDSC_queue* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return ERROR;
  }

  return self->pd->length == 0;
}

/**
  * @brief Get length of the queue.
  * @param self Queue pointer.
  * @param status Error pointer.
  * @return Length of the stack as integer type.
  */
int LDSC_queue_length(LDSC_queue* self, LDSC_error* status) {
  if (status) *status = OK;
  
  if (!self) {
    if (status) *status = NULL_SELF;
    return ERROR;
  }

  return self->pd->length;
}

/**
  * @brief Add item to end of the queue.
  * @param self Queue pointer.
  * @param dataPtr Pointer to data.
  * @param status Error pointer.
  * @details
  * Keep note that enqueue performs a shallow copy of the data.
  */
void LDSC_queue_enqueue(LDSC_queue* self, void* dataPtr, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return;
  }

  if (!dataPtr) {
    if (status) *status = NULL_DATAPTR;
    return;
  }


  Node* newNode = Node_init(dataPtr);
  if (!newNode) {
    if (status) *status = NODE_MALLOC;
    return;
  }

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
  * @param status Error pointer.
  * @return Pointer to data at the front of the queue.
  */
void* LDSC_queue_dequeue(LDSC_queue* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return NULL;
  }

  if (!self->pd->front)
    return NULL;

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
  * @param status Error pointer.
  * @return Pointer to data at the front of the queue.
  */
void* LDSC_queue_peek(LDSC_queue* self, LDSC_error* status) {
  if (status) *status = OK;
  
  if (!self) {
    if (status) *status = NULL_SELF;
    return NULL;
  }

  if (!self->pd->front)
    return NULL;

  return self->pd->front->dataPtr;
}

/**
  * @brief Delete the queue.
  * @param self Queue pointer.
  * @param status Error pointer.
  */
void LDSC_queue_delete(LDSC_queue* self, LDSC_error* status) {
  if (status) *status = OK;

  if (!self) {
    if (status) *status = NULL_SELF;
    return;
  }

  while (self->pd->front) {
    self->dequeue(self, status);
  }

  free(self->pd);
  free(self);
  return;
}

/**
 * @brief Create a new queue
 * @return Pointer to a new queue
 * @param status Error pointer.
 */
LDSC_queue* LDSC_queue_init(LDSC_error* status) {
  if (status) *status = OK;

  LDSC_queue* newQueue = malloc(sizeof(LDSC_queue));
  if (!newQueue) {
    if (status) *status = STRUCTURE_MALLOC;
    return NULL;
  }


  newQueue->pd = malloc(sizeof(privateData));
  if (!newQueue->pd) {
    if (status) *status = PRIVATEDATA_MALLOC;
    free(newQueue);
    return NULL;
  }
  
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

