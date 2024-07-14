#ifndef LDS_H
#define LDS_H

typedef struct LDSC_linkedList LDSC_linkedList;
typedef struct LDSC_node LDSC_node;

LDSC_linkedList* LDSC_linkedList_init();
int LDSC_linkedList_length(LDSC_linkedList*);
LDSC_node* LDSC_linkedList_head(LDSC_linkedList*);
LDSC_node* LDSC_linkedList_tail(LDSC_linkedList*);

#endif
