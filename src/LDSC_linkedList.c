#include <LDSC_linkedList.h>
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

struct LDSC_linkedList {
  int length;
  LDSC_node* head;
  LDSC_node* tail;
};

LDSC_linkedList* LDSC_linkedList_init() {
  LDSC_linkedList* newLL = (LDSC_linkedList*)malloc(sizeof(LDSC_linkedList));
  newLL->length = 0;
  newLL->head = NULL;
  newLL->tail = NULL;
  return newLL;
}

LDSC_node* LDSC_linkedList_getNode(LDSC_linkedList* LLin, int index) {
  // conditions for invalid parameters
  if (index < 0 || index >= LLin->length) return NULL;

  // start at head node
  LDSC_node* returnNode = LLin->head;

  // move through list
  for (int i = 0; i < index; i++)
    returnNode = returnNode->next;

  // return node ptr
  return returnNode; 
}

int LDSC_linkedList_length(LDSC_linkedList* LLin) {return LLin->length;}

void* LDSC_linkedList_head(LDSC_linkedList* LLin) {
  if (LLin->length == 0) return NULL;
  return LLin->head->dataPtr;
}

void* LDSC_linkedList_tail(LDSC_linkedList* LLin) {
  if (LLin->length == 0) return NULL;
  return LLin->tail->dataPtr;
}

void LDSC_linkedList_append(LDSC_linkedList* LLin, void* dataPtrIn) {
  // conditions for invalid parameters
  if (!LLin || !dataPtrIn) return;

  // create new node
  LDSC_node* newNode = LDSC_node_init(dataPtrIn);

  // condition if list is empty, inferred by null head
  if (!LLin->head) {
    // set new node as new head and tail of list
    LLin->head = newNode;
    LLin->tail = newNode;

    // increment length of list
    LLin->length++;

    // append complete, early return
    return;
  }

  // set current tail's nest pointer to new node
  LLin->tail->next = newNode;
  
  // set new node as the new tail
  LLin->tail = newNode;

  // increment length of list
  LLin->length++;
  return;
}

void LDSC_linkedList_prepend(LDSC_linkedList* LLin, void* dataPtrIn) {
  // conditions for invalid parameters
  if (!LLin || !dataPtrIn) return;

  // create new node
  LDSC_node* newNode = LDSC_node_init(dataPtrIn);
  
  // condition if list is empty, inferred by nul head
  if (!LLin->head) {
    // set new node as new head and tail of list
    LLin->head = newNode;
    LLin->tail = newNode;

    // increment length of list
    LLin->length++;

    // append complete, early return
    return;
  }

  // set new node's next to the current head
  newNode->next = LLin->head;

  // set new node as the new head
  LLin->head = newNode;

  // increment length of list
  LLin->length++;
  return;
}

void* LDSC_linkedList_get(LDSC_linkedList* LLin, int index) {
  // conditions for invalid parameters
  if (!LLin || index < 0 || index >= LLin->length) return NULL;
  
  // return data of head if index == 0
  if (index == 0) return LLin->head->dataPtr;

  // return data of tail if index == length - 1
  if (index == LLin->length - 1) return LLin->tail->dataPtr;

  // get node of target index
  LDSC_node* targetNode = LDSC_linkedList_getNode(LLin, index);

  // return data of target node
  return targetNode->dataPtr;
}

void LDSC_linkedList_insert(LDSC_linkedList* LLin, void* dataPtrIn, int index) {
  // conditions for invalid parameters
  if (!LLin || !dataPtrIn || index < 0 || index > LLin->length) return;

  // if inserting at head, call preprend function and exit
  if (index == 0) {LDSC_linkedList_prepend(LLin, dataPtrIn); return;}
  
  // if inserting at tail, call append function and exit
  if (index == LLin->length) {LDSC_linkedList_append(LLin, dataPtrIn); return;}

  // retrieve the node that will come before the inserted node
  LDSC_node* prevNodeOfInsert = LDSC_linkedList_getNode(LLin, index-1);

  // create new node
  LDSC_node* newNode = LDSC_node_init(dataPtrIn);

  // set the new node's next to it's previous nodes next
  newNode->next = prevNodeOfInsert->next;

  // set the prev node's next to the new node
  prevNodeOfInsert->next = newNode;
  
  // increment length of list
  LLin->length++;
  return;
}

void* LDSC_linkedList_removeFirst(LDSC_linkedList* LLin) {
  // conditions for invalid parameters
  if (!LLin || !LLin->length) return NULL;

  // get current head node of list
  LDSC_node* oldHead = LLin->head;

  // extract data of current head
  void* firstDataPtr = oldHead->dataPtr;
  
  // set the new head to the current head's next
  LDSC_node* newHead = oldHead->next;

  // decrement length of list
  LLin->length--;

  // set the head of the list to the new head
  LLin->head = newHead;

  // free the old head
  free(oldHead);

  // return data from the old head
  return firstDataPtr;
}

void* LDSC_linkedList_removeLast(LDSC_linkedList* LLin) {
  // condition for invalid parameters
  if (!LLin || !LLin->length) return NULL;

  // condtion for a 1 element list
  // in a 1 element list, removeFirst == removeLast
  // removeFirst is called
  if (LLin->length == 1) return LDSC_linkedList_removeFirst(LLin);

  // get current tail node of list
  LDSC_node* oldTail = LLin->tail;

  // retrieve data ptr of curent tail
  void* lastDataPtr = oldTail->dataPtr;

  // get node ptr of new tail
  LDSC_node* newTail = LDSC_linkedList_getNode(LLin, LLin->length - 2);

  // decrement length of list
  LLin->length--;

  // set tail of list to new tail
  LLin->tail = newTail;

  // condition that if new length of list is = 1, set head to point to tail
  if (LLin->length == 1) LLin->head = newTail;

  // free the old tail
  free(oldTail);

  // return data from the old tail
  return lastDataPtr;
}

void* LDSC_linkedList_remove(LDSC_linkedList* LLin, int index) {
  // condition for invalid parameters
  if (!LLin || !LLin->length || index < 0 || index >= LLin->length) return NULL;

  // if removing head, call removeFirst and return;
  if (index == 0) return LDSC_linkedList_removeFirst(LLin);

  // if removing tail, call removeLast and return;
  if (index == LLin->length - 1) return LDSC_linkedList_removeLast(LLin);

  // get prev node ptr of node targeted for removal
  LDSC_node* prevNodeOfRemove = LDSC_linkedList_getNode(LLin, index - 1);

  // get node ptr of node targeted for removal
  LDSC_node* removeNode = prevNodeOfRemove->next;

  // set prev node's next to target node's next
  // targeted node for removal has been removed from links
  prevNodeOfRemove->next = removeNode->next;

  // decrement length of list
  LLin->length--;

  // retrieve data of removed node
  void* removeDataPtr = removeNode->dataPtr;

  // free removed node
  free(removeNode);

  // return data of removed node
  return removeDataPtr;
}

