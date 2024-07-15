#ifndef LDSC_LINKEDLIST_H
#define LDSC_LINKEDLIST_H

typedef struct LDSC_linkedList LDSC_linkedList;

LDSC_linkedList* LDSC_linkedList_init();
int LDSC_linkedList_length(LDSC_linkedList*);
void* LDSC_linkedList_head(LDSC_linkedList*);
void* LDSC_linkedList_tail(LDSC_linkedList*);

void LDSC_linkedList_append(LDSC_linkedList*, void*);
void LDSC_linkedList_prepend(LDSC_linkedList*, void*);
void* LDSC_linkedList_get(LDSC_linkedList*, int);
void LDSC_linkedList_insert(LDSC_linkedList*, void*, int);
void* LDSC_linkedList_removeFirst(LDSC_linkedList*);

#endif
