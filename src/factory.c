/** @file   factory.c
 *  @brief  Definitions for making LDSC structures.
 *
 *  @author Ryan V. Ngo
 */

#include "factory.h"
#include "type_masks.h"

#include <stdlib.h>

/****************************** Unique Structures ******************************/

typedef struct DL_Node {
  void* data_ptr;
  struct DL_Node* next;
  struct DL_Node* prev;
} DL_Node;

typedef struct SL_Node {
  void* data_ptr;
  struct DL_Node* next;
} SL_Node;

typedef struct HeadTailStructure {
  int id;
  int size;
  Node* head;
  Node* tail;
} HeadTailStructure;

typedef struct HeadStructure {
  int id;
  int size;
  Node* head;
} HeadStructure;


/****************************** Factory Methods ******************************/

LDSC_structure* initialize_structure(int structure_id) {
  LDSC_structure* new_structure = NULL;

  if (structure_id == LinkedList_ID) {
    new_structure = malloc(sizeof(HeadTailStructure));
    new_structure->tail = NULL;
  } else if (structure_id == Queue_ID) {
    new_structure = malloc(sizeof(HeadTailStructure));
    new_structure->tail = NULL;
  } else {
    new_structure = malloc(sizeof(HeadStructure));
  }

  new_structure->id = structure_id;
  new_structure->length = 0;
  new_structure->head = NULL;

  return new_structure;
}

Node* node_init(int structure_id) {
  Node* new_node = NULL;

  if (structure_id & DOUBLY_LINKED_MASK) {
    new_node= malloc(sizeof(DL_Node));
    new_node->prev = NULL;
  } else {
    new_node= malloc(sizeof(SL_Node));
  }

  new_node->data_ptr = NULL;
  new_node->next = NULL;

  return new_node;
}

