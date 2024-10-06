/** @file   factory.h
 *  @brief  Defines and prototypes for making LDSC structures.
 *
 *  @author Ryan V. Ngo
 */

#ifndef FACTORY_H
#define FACTORY_H

/****************************** Internal Structures ******************************/

typedef struct Node {
  void* data_ptr;
  struct Node* next;
  struct Node* prev;
} Node;

typedef struct LDSC_structure {
  int id;
  int length;
  Node* head;
  Node* tail;
} LDSC_structure;

/****************************** Factory Methods ******************************/

LDSC_structure* initialize_structure(int structure_id);

Node* node_init(int structure_id);

#endif
