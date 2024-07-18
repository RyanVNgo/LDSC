#include <LDSC_queue.h>
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

struct LDSC_queue {
  int length;
  LDSC_node* head;
  LDSC_node* tail;
};

LDSC_queue* LDSC_queue_init() {
  LDSC_queue* newQueue = (LDSC_queue*)malloc(sizeof(LDSC_queue));
  newQueue->length = 0;
  newQueue->head = NULL;
  newQueue->tail = NULL;
  return newQueue;
}

int LDSC_queue_length(LDSC_queue* queueIn) {
  if (!queueIn) return -1;
  return queueIn->length;
}

int LDSC_queue_isEmpty(LDSC_queue* queueIn) {
  if (!queueIn) return -1;
  if (!queueIn->length) return 1;
  return 0;
}

void LDSC_queue_enqueue(LDSC_queue* queueIn, void* dataPtrIn) {
  if (!queueIn || !dataPtrIn) return;
  LDSC_node* newNode = LDSC_node_init(dataPtrIn);
  if (!queueIn->head) {
    queueIn->head = newNode;
    queueIn->tail = newNode;
  } else {
    queueIn->tail->next = newNode;
    queueIn->tail = newNode;
  }
  queueIn->length++;
  return;
}

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

void* LDSC_queue_peek(LDSC_queue* queueIn) {
  if (!queueIn || !queueIn->head) return NULL;
  return queueIn->head->dataPtr;
}

