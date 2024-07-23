#include <LDSC_queue.h>
#include <stdlib.h>

typedef struct LDSC_node {
  void* dataPtr;
  struct LDSC_node* next;
} LDSC_node;

// create and return a new node
static LDSC_node* LDSC_node_init(void* dataPtrIn) {
  LDSC_node* newNode = (LDSC_node*)malloc(sizeof(LDSC_node));
  newNode->dataPtr = dataPtrIn;
  newNode->next = NULL;
  return newNode;
}

struct LDSC_queue {
  int length;
  LDSC_node* head;
  LDSC_node* tail;
};

/**
 * @brief Create a new queue
 * @return Pointer to a new queue
 */
LDSC_queue* LDSC_queue_init() {
  LDSC_queue* newQueue = (LDSC_queue*)malloc(sizeof(LDSC_queue));
  newQueue->length = 0;
  newQueue->head = NULL;
  newQueue->tail = NULL;
  return newQueue;
}

/**
 * @brief Return length of the queue
 * @param queueIn Pointer to LDSC_queue
 * @return Integer representing number of items in the queue
 */
int LDSC_queue_length(LDSC_queue* queueIn) {
  if (!queueIn) return -1;
  return queueIn->length;
}

/**
 * @brief Enqueue item to queue
 * @param queueIn Pointer to LDSC_queue
 * @param dataPtr Pointer of data to store
 */
void LDSC_queue_enqueue(LDSC_queue* queueIn, void* dataPtrIn) {
  if (!queueIn || !dataPtrIn) return;
  LDSC_node* newNode = LDSC_node_init(dataPtrIn);

  if (!queueIn->head) {
    queueIn->head = newNode;
  } else {
    queueIn->tail->next = newNode;
  }
  
  queueIn->tail = newNode;
  queueIn->length++;
  return;
}

/**
 * @brief Dequeue item from queue
 * @param queueIn Pointer to LDSC_queue
 * @return Pointer to item at front of the queue
 */
void* LDSC_queue_dequeue(LDSC_queue* queueIn) {
  if (!queueIn || !queueIn->length) return NULL;

  LDSC_node* oldHead = queueIn->head;
  void* dataPtrOut = oldHead->dataPtr;
  queueIn->head = oldHead->next;

  if (!queueIn->head)
    queueIn->tail = NULL;

  queueIn->length--;
  free(oldHead);
  return dataPtrOut;
}

/**
 * @brief Get item at front of the queue
 * @param queueIn Pointer to LDSC_queue
 * @return Pointer to data stored at the front of the queue
 */
void* LDSC_queue_peek(LDSC_queue* queueIn) {
  if (!queueIn || !queueIn->head) return NULL;
  return queueIn->head->dataPtr;
}

