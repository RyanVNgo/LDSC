/** @file   type_masks.h
 *  @brief  Defines for function masks and structure IDs.
 *
 *  @author Ryan V. Ngo
 */

/****************************** Method Masks ******************************/

#define DOUBLY_LINKED_MASK    16384
#define HEAD_TAIL_MASK        32768

#define LENGTH_MASK     1
#define EMPTY_MASK      2

#define APPEND_MASK     4
#define PREPEND_MASK    8
#define INSERT_MASK     16
#define ENQUEUE_MASK    32
#define PUSH_MASK       64

#define REMOVE_MASK     128
#define POP_MASK        256
#define DEQUEUE_MASK    512

#define GET_MASK        1024
#define FRONT_MASK      2048
#define BACK_MASK       4096
#define PEEK_MASK       8192

/****************************** Structure ID ******************************/

enum StructureId {
  LinkedList_ID = 
    HEAD_TAIL_MASK + 
    LENGTH_MASK +
    EMPTY_MASK +
    APPEND_MASK +
    PREPEND_MASK + 
    INSERT_MASK + 
    REMOVE_MASK +
    GET_MASK +
    FRONT_MASK + 
    BACK_MASK
  ,

  Queue_ID =
    DOUBLY_LINKED_MASK +
    HEAD_TAIL_MASK + 
    LENGTH_MASK +
    EMPTY_MASK +
    ENQUEUE_MASK +
    DEQUEUE_MASK + 
    FRONT_MASK + 
    BACK_MASK
  ,
  
  Stack_ID =
    LENGTH_MASK +
    EMPTY_MASK +
    PUSH_MASK +
    POP_MASK +
    PEEK_MASK
};

