/** @file   LDSC.h
 *  @brief  Primary entry pointer for the LDSC library.
 *
 *  @author Ryan V. Ngo
 */

#ifndef LDSC_H
#define LDSC_H

/****************************** LDSC Codes ******************************/

#define LDSC_ERROR            -1
#define LDSC_INVALID_STRUCT   -2
#define LDSC_INVALID_INDEX    -3

/****************************** General Structure ******************************/

typedef struct LDSC_structure LDSC_structure;

/****************************** Generalized Methods ******************************/

/* attribute methods */

int LDSC_length(const LDSC_structure* structure); 
int LDSC_empty(const LDSC_structure* structure); 

/* add element methods */

int LDSC_append(LDSC_structure* structure, void* data_ptr); 
int LDSC_prepend(LDSC_structure* structure, void* data_ptr); 
int LDSC_insert(LDSC_structure* structure, void* data_ptr, int index);
int LDSC_push(LDSC_structure* structure, void* data_ptr);

/* remove element methods */

void* LDSC_remove(LDSC_structure* structure, int index);
void* LDSC_pop(LDSC_structure* structure);

/* get element methods */

void* LDSC_get(LDSC_structure* structure, int index);
void* LDSC_front(LDSC_structure* structure);
void* LDSC_back(LDSC_structure* structure);
void* LDSC_peek(LDSC_structure* structure);

/* wipe methods */

int LDSC_clear(LDSC_structure* structure);
void LDSC_delete(LDSC_structure* structure, void (*data_del)(void*));

/****************************** Unique Initialization ******************************/

LDSC_structure* LDSC_linked_list_init();

LDSC_structure* LDSC_queue_init();

LDSC_structure* LDSC_stack_init();

LDSC_structure* LDSC_array_init();

#endif 
