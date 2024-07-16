#include <stdlib.h>

#include "test_linkedLists.h"
#include <LDSC.h>
#include <check.h>

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE CORE START

// Ensure that the attributes of a new linked list are initialized properly
START_TEST(linkedList_init) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  // attributes should be initialize as follows:
  // length == 0
  // head == NULL
  // tail == NULL 
  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  free(myLL);
} END_TEST

// TEST CASE CORE END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE APPEND START

// Calling the append function with a null list input should return with no error
START_TEST(linkedList_null_list_append) {
  int testData = 17;
  LDSC_linkedList_append(NULL, (void*)&testData);
} END_TEST

// Attempting to append with null data should return with no error and no change to the linked list
START_TEST(linkedList_null_data_append) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  
  // append attempt
  LDSC_linkedList_append(myLL, NULL);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  // attributes should be initialize as follows:
  // length == 0
  // head == NULL
  // tail == NULL 
  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  free(myLL);
} END_TEST

// Appending to an empty list
START_TEST(linkedList_empty_append) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  
  // append attempt
  LDSC_linkedList_append(myLL, (void*)&testData);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  // Check if:
  // length == 1
  // head != NULL
  // tail != NULL
  // head == tail
  // dereferenced head == testData
  ck_assert_int_eq(length, 1);
  ck_assert_ptr_nonnull(head);
  ck_assert_ptr_nonnull(tail);
  ck_assert_ptr_eq(head, tail);
  ck_assert_int_eq(*(int*)head, testData);

  free(myLL);
} END_TEST

// Appending to a non empty list
START_TEST(linkedList_nonempty_append) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};

  // Start with a single append of testData[0]
  // Should be passed by previous test
  LDSC_linkedList_append(myLL, (void*)&testData[0]);
  
  // remember initial head and tail which head == tail
  void* initHead = LDSC_linkedList_head(myLL);
  void* initTail = LDSC_linkedList_tail(myLL);

  // append the remaining items in testData
  for (int i = 1; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  // Check if:
  // length == length of testData
  // head != tail ; the head and tail should not be equal at this point
  // initHead == head ; the head should still be the same as the initial head
  // initTail != tail ; the tail should not be the same as the initial tail
  ck_assert_int_eq(length, nodeCount);
  ck_assert_ptr_ne(head, tail);
  ck_assert_ptr_eq(initHead, head);
  ck_assert_ptr_ne(initTail, tail);

  free(myLL);
} END_TEST

// TEST CASE APPEND END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE PREPEND START

// Calling the prepend function with a null list input should return with no error
START_TEST(linkedList_null_list_prepend) {
  int testData = 17;
  LDSC_linkedList_prepend(NULL, (void*)&testData);
} END_TEST

// Attempting to prepend with null data should return with no error and no change to the linked list
START_TEST(linkedList_null_data_prepend) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  
  // prepend attempt
  LDSC_linkedList_prepend(myLL, NULL);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  // Check if:
  // length == 0
  // head == NULL
  // tail == NULL
  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  free(myLL);
} END_TEST

// Prepending to an empty list
START_TEST(linkedList_empty_prepend) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  
  // prepend attempt
  LDSC_linkedList_prepend(myLL, (void*)&testData);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  // Check if:
  // length == 1
  // head != NULL
  // tail != NULL
  // head == tail
  // dereferenced head == testData
  ck_assert_int_eq(length, 1);
  ck_assert_ptr_nonnull(head);
  ck_assert_ptr_nonnull(tail);
  ck_assert_ptr_eq(head, tail);
  ck_assert_int_eq(*(int*)head, testData);

  free(myLL);
} END_TEST

START_TEST(linkedList_nonempty_prepend) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};

  // Start with a single prepend of testData[0]
  // Should be passed by previous test
  LDSC_linkedList_prepend(myLL, (void*)&testData[0]);
  
  // remember initial head and tail which head == tail
  void* initHead = LDSC_linkedList_head(myLL);
  void* initTail = LDSC_linkedList_tail(myLL);

  // prepend the remaining items in testData
  for (int i = 1; i < nodeCount; i++)
    LDSC_linkedList_prepend(myLL, (void*)&testData[i]);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  // Check if:
  // length == length of testData
  // head != tail ; the head and tail should not be equal at this point
  // initHead != head ; the head should not be the same as the initial head
  // initTail == tail ; the tail should still be the same as the initial tail
  ck_assert_int_eq(length, nodeCount);
  ck_assert_ptr_ne(head, tail);
  ck_assert_ptr_ne(initHead, head);
  ck_assert_ptr_eq(initTail, tail);

  free(myLL);
} END_TEST

// TEST CASE PREPEND END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE GET START

// Calling the get function with an empty list should fail and return with no error
START_TEST(linkedList_null_list_get) {
  int index = 0;
  // get attempt
  void* dataPtrOut = LDSC_linkedList_get(NULL, index);

  // dataPtrOut should be NULL
  ck_assert_ptr_null(dataPtrOut);
} END_TEST

// Calling get with a negative index should fail and return with no error
START_TEST(linkedList_neg_index_get) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_append(myLL, (void*)&testData);

  // get attempt with a negative index value
  int index = -1;
  void* dataPtrOut = LDSC_linkedList_get(myLL, index);

  // dataPtrOut should be null
  ck_assert_ptr_null(dataPtrOut);

  free(myLL);
} END_TEST

// Calling get with an index equal to the length of the list or greater
// should fail and return with no error
START_TEST(linkedList_greater_index_get) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_append(myLL, (void*)&testData);

  // get attempt with an out of range index value (>)
  int index = LDSC_linkedList_length(myLL);
  void* dataPtrOut = LDSC_linkedList_get(myLL, index);

  // dataPtrOut should be null
  ck_assert_ptr_null(dataPtrOut);

  free(myLL);
} END_TEST

// Check if calling get for every valid index returns correctly
START_TEST(linkedList_get) {
  // initialize the linked list
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};
  int i;
  for (i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  // Store return values of every get call
  int dataOut[nodeCount];
  for (i = 0; i < nodeCount; i++)
    dataOut[i] = *(int*)LDSC_linkedList_get(myLL, i);

  // Check if each return value matches with the testData
  for (i = 0; i < nodeCount; i++)
    ck_assert_int_eq(testData[i], dataOut[i]);

  free(myLL);
} END_TEST

// TEST CASE GET END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE INSERT START

// Calling insert with an empty list should fail and return with no error
START_TEST(linkedList_null_list_insert) {
  int testData = 17, index = 0;
  LDSC_linkedList_insert(NULL, (void*)&testData, index);
} END_TEST

// Calling insert with null data should fail and return with no error
START_TEST(linkedList_null_data_insert) {
  // initialize an empty list
  LDSC_linkedList* myLL = LDSC_linkedList_init();

  // attempt to insert
  int index = 0;
  LDSC_linkedList_insert(myLL, NULL, index);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  // Check if:
  // length == 0
  // head == NULL
  // tail == NULL
  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  free(myLL);
} END_TEST

// Calling insert with a negative index should fail and return with no error
START_TEST(linkedList_neg_index_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();

  // attempet to insert
  int testData = 17, index = -1;
  LDSC_linkedList_insert(myLL, (void*)&testData, index);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  // Check if:
  // length == 0
  // head == NULL
  // tail == NULL
  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  free(myLL);
} END_TEST

// Calling insert with an index greater than the length of the list
// should fail and return with no error
START_TEST(linkedList_greater_index_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  // attempt to insert
  int testDataInsert = 22, index = LDSC_linkedList_length(myLL) + 1;
  LDSC_linkedList_insert(myLL, (void*)&testDataInsert, index);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);

  // Check if length == nodeCount
  ck_assert_int_eq(length, nodeCount);

  free(myLL);
} END_TEST

// Should insert equivalent to prepend
START_TEST(linkedList_zero_index_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);
  
  // remember initial head and tail
  void* initHead = LDSC_linkedList_head(myLL);
  void* initTail = LDSC_linkedList_tail(myLL);

  // insert data
  int testDataInsert = 22, index = 0;
  LDSC_linkedList_insert(myLL, (void*)&testDataInsert, index);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* newHead = LDSC_linkedList_head(myLL);
  void* newTail = LDSC_linkedList_tail(myLL);

  // Check if:
  // length == nodeCount + 1
  // initHead != newHead
  // initTail == newTail
  ck_assert_int_eq(nodeCount + 1, length);
  ck_assert_ptr_ne(initHead, newHead);
  ck_assert_ptr_eq(initTail, newTail);

  free(myLL);
} END_TEST

// Should insert equivalent to append
START_TEST(linkedList_length_index_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);
  
  // remember initial head and tail
  void* initHead = LDSC_linkedList_head(myLL);
  void* initTail = LDSC_linkedList_tail(myLL);

  // insert data
  int testDataInsert = 22, index = nodeCount;
  LDSC_linkedList_insert(myLL, (void*)&testDataInsert, index);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* newTail = LDSC_linkedList_tail(myLL);
  void* newHead = LDSC_linkedList_head(myLL);

  // check f:
  // length == nodeCount + 1
  // initTail != newTail
  // initHead == newHead
  ck_assert_int_eq(nodeCount + 1, length);
  ck_assert_ptr_ne(initTail, newTail);
  ck_assert_ptr_eq(initHead, newHead);

  free(myLL);
} END_TEST

//
START_TEST(linkedList_other_index_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  // remember initial head and tail
  void* initHead = LDSC_linkedList_head(myLL);
  void* initTail = LDSC_linkedList_tail(myLL);

  // insert data
  int testDataInsert = 22, index = 2;
  LDSC_linkedList_insert(myLL, (void*)&testDataInsert, index);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* newHead = LDSC_linkedList_head(myLL);
  void* newTail = LDSC_linkedList_tail(myLL);

  // Check if:
  // length == nodeCount + 1
  // initHead == newHead
  // initTail == newTail
  ck_assert_int_eq(length, nodeCount + 1);
  ck_assert_ptr_eq(initHead, newHead);
  ck_assert_ptr_eq(initTail, newTail);

  free(myLL);
} END_TEST

// TEST CASE INSERT END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE REMOVEFIRST START

// Calling removeFirst with a null list should fail and return with no error
START_TEST(linkedList_null_list_removeFirst) {
  void* dataOutPtr = LDSC_linkedList_removeFirst(NULL);
  ck_assert_ptr_null(dataOutPtr);
} END_TEST

// Calling removeFirst with an empty list should return NULL
START_TEST(linkedList_empty_list_removeFirst) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  
  // attempt to remove and return first item
  void* dataOutPtr = LDSC_linkedList_removeFirst(myLL);
  
  // check if dataOutPtr is NULL
  ck_assert_ptr_null(dataOutPtr);

  free(myLL);
} END_TEST

// Calling removeFirst on a single item list
START_TEST(linkedList_single_item_list_removeFirst) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_append(myLL, (void*)&testData);

  // attempt to remove and return first item
  int dataOut = *(int*)LDSC_linkedList_removeFirst(myLL);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  // Check if:
  // length is 0
  // head is NULL
  // tail is NULL
  // data was properly returned
  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);
  ck_assert_int_eq(testData, dataOut);

  free(myLL);
} END_TEST

// Calling removeFirst for a > 1 item list
START_TEST(linkedList_removeFirst) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  // attempt to remove and return first item
  int dataOut = *(int*)LDSC_linkedList_removeFirst(myLL);
  
  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);

  // head should not be NULL
  ck_assert_ptr_nonnull(head);

  // length should be equal to nodeCount - 1
  ck_assert_int_eq(nodeCount - 1, length);

  // returned data should equal first element of testData
  ck_assert_int_eq(testData[0], dataOut);

  free(myLL);
} END_TEST

// TEST CASE REMOVEFIRST END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE REMOVELAST START

// Calling removeLast on a NULL list should fail and return with no error
START_TEST(linkedList_null_list_removeLast) {
  // attempt to remove and return last item
  void* dataOutPtr = LDSC_linkedList_removeLast(NULL);

  // dataOutPtr should be NULL
  ck_assert_ptr_null(dataOutPtr);
} END_TEST

// Calling removeLast on an empty list should fail and return with no error
START_TEST(linkedList_empty_list_removeLast) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();

  // attempt to remove and return the last item
  void* dataOutPtr = LDSC_linkedList_removeLast(myLL);

  // dataOutPtr should be NULL
  ck_assert_ptr_null(dataOutPtr);

  free(myLL);
} END_TEST

// Calling removeLast on a single item list
START_TEST(linkedList_single_item_list_removeLast) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_append(myLL, (void*)&testData);

  // attempt to remove and return the last item
  int dataOut = *(int*)LDSC_linkedList_removeLast(myLL);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  // list should be empty
  // head should be NULL
  // tail should be NULL
  // returned data should equal the testData
  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);
  ck_assert_int_eq(testData, dataOut);

  free(myLL);
} END_TEST

// Calling removeLast on a > 1 item list
START_TEST(linkedList_removeLast) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  // attempt to remove and return the last item
  int dataOut = *(int*)LDSC_linkedList_removeLast(myLL);

  // retrieve all attribute data
  int length = LDSC_linkedList_length(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  // tail should not be NULL
  ck_assert_ptr_nonnull(tail);
  
  // length should be equal to nodeCount -1
  ck_assert_int_eq(nodeCount - 1, length);

  // returned data should equal the last item in testData
  ck_assert_int_eq(testData[nodeCount - 1], dataOut);

  free(myLL);
} END_TEST

// TEST CASE REMOVELAST END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE REMOVE START

// Calling remove on a NULL list should fail and return with no error
START_TEST(linkedList_null_list_remove) {
  // attempt to remove and return item at index
  int index = 1;
  void* dataOutPtr = LDSC_linkedList_remove(NULL, index);
  
  // dataOutPtr should be NULL
  ck_assert_ptr_null(dataOutPtr);

} END_TEST

// Calling remove on an empty list should fail and return with no error
START_TEST(linkedList_empty_list_remove) {
  LDSC_linkedList* myLL = LDSC_linkedList_init(); 
  int index = 0;
  
  // attempt to remove and return item at index
  void* dataOutPtr = LDSC_linkedList_remove(myLL, index);

  // dataOutPtr should be NULL
  ck_assert_ptr_null(dataOutPtr);

  free(myLL);
} END_TEST

// Calling remove with a negative index shoudl fail and return with no error
START_TEST(linkedList_neg_index_remove) {
  LDSC_linkedList* myLL = LDSC_linkedList_init(); 
  int index = -1;

  // attempt to remove and return item at index
  void* dataOutPtr = LDSC_linkedList_remove(myLL, index);

  // dataOutPtr should be NULL
  ck_assert_ptr_null(dataOutPtr);

  free(myLL);
} END_TEST

// Calling remove with a index >= to the length of the list
// should fail and return with no error
START_TEST(linkedList_greater_index_remove) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  // attempt to remove and return item at index
  int index = nodeCount;
  void* dataOutPtr = LDSC_linkedList_remove(myLL, index);
  
  // dataOutPtr should be NULL
  ck_assert_ptr_null(dataOutPtr);

  // length of list should equal the nodeCount
  int length = LDSC_linkedList_length(myLL);
  ck_assert_int_eq(length, nodeCount);

  free(myLL);
} END_TEST

// Calling remove with a index of zero should be equal to removeFirst
START_TEST(linkedList_zero_index_remove) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  // attempt to remove and return item at index
  int index = 0;
  void* dataOutPtr = LDSC_linkedList_remove(myLL, index);

  // retrieve attribute data
  int length = LDSC_linkedList_length(myLL);
  void* headDataOutPtr = LDSC_linkedList_head(myLL); 

  // dataOutPtr should not be NULL
  ck_assert_ptr_nonnull(dataOutPtr);

  // removed data should be equal to the first element of testData
  ck_assert_int_eq(*(int*)dataOutPtr, testData[index]);

  // head data should now equal the second element of testData
  ck_assert_int_eq(*(int*)headDataOutPtr, testData[index+1]);

  // length should be equal to nodeCount - 1
  ck_assert_int_eq(length, nodeCount - 1);

  free(myLL);
} END_TEST

// Calling remove with an index equal to the list length should
// be equal to removeLast
START_TEST(linkedList_length_index_remove) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  // attempt to remove and return item at index
  int index = nodeCount - 1;
  void* dataOutPtr = LDSC_linkedList_remove(myLL, index);

  // retrieve attribute data
  int length = LDSC_linkedList_length(myLL);
  void* tailDataOutPtr = LDSC_linkedList_tail(myLL); 

  // dataOutPtr should not be NULL
  ck_assert_ptr_nonnull(dataOutPtr);

  // removed data should be equal to the last element of testData
  ck_assert_int_eq(*(int*)dataOutPtr, testData[index]);

  // tail data should now equal the second to last element of testData
  ck_assert_int_eq(*(int*)tailDataOutPtr, testData[nodeCount - 2]);

  // length should be equal to nodeCount - 1
  ck_assert_int_eq(length, nodeCount - 1);

  free(myLL);
} END_TEST

// Calling remove with a valid index that does not equal 0 or
// the length of the list
START_TEST(linkedList_remove) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  // attempt to remove and return item at index
  int index = 1;
  void* dataOutPtr = LDSC_linkedList_remove(myLL, index);

  // retrieve attribute data
  int length = LDSC_linkedList_length(myLL);
  void* headDataOutPtr = LDSC_linkedList_head(myLL); 
  void* tailDataOutPtr = LDSC_linkedList_tail(myLL); 

  // dataOutPtr should not be NULL
  ck_assert_ptr_nonnull(dataOutPtr);

  // removed data should equal the data at testData[index]
  ck_assert_int_eq(*(int*)dataOutPtr, testData[index]);

  // head data should equal the first element of testData
  ck_assert_int_eq(*(int*)headDataOutPtr, testData[0]);

  // tail data should equal the last element of testData
  ck_assert_int_eq(*(int*)tailDataOutPtr, testData[nodeCount - 1]);

  // length should be equal to nodeCount - 1
  ck_assert_int_eq(length, nodeCount - 1);

  free(myLL);
} END_TEST

// TEST CASE REMOVE END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// SUITE DEFINITION

Suite* LDSC_linkedList_suite() {
  Suite *s;
  s = suite_create("LDSC_linkedList");

  TCase* tc_core = tcase_create("core");
  tcase_add_test(tc_core, linkedList_init);
  suite_add_tcase(s, tc_core);

  TCase* tc_append= tcase_create("append");
  tcase_add_test(tc_append, linkedList_null_list_append);
  tcase_add_test(tc_append, linkedList_null_data_append);
  tcase_add_test(tc_append, linkedList_empty_append);
  tcase_add_test(tc_append, linkedList_nonempty_append);
  suite_add_tcase(s, tc_append);

  TCase* tc_prepend = tcase_create("prepend");
  tcase_add_test(tc_prepend, linkedList_null_list_prepend);
  tcase_add_test(tc_prepend, linkedList_null_data_prepend);
  tcase_add_test(tc_prepend, linkedList_empty_prepend);
  tcase_add_test(tc_prepend, linkedList_nonempty_prepend);
  suite_add_tcase(s, tc_prepend);

  TCase* tc_get = tcase_create("get");
  tcase_add_test(tc_get, linkedList_null_list_get);
  tcase_add_test(tc_get, linkedList_neg_index_get);
  tcase_add_test(tc_get, linkedList_greater_index_get);
  tcase_add_test(tc_get, linkedList_get);
  suite_add_tcase(s, tc_get);

  TCase* tc_insert = tcase_create("insert");
  tcase_add_test(tc_insert, linkedList_null_list_insert);
  tcase_add_test(tc_insert, linkedList_null_data_insert);
  tcase_add_test(tc_insert, linkedList_neg_index_insert);
  tcase_add_test(tc_insert, linkedList_greater_index_insert);
  tcase_add_test(tc_insert, linkedList_zero_index_insert);
  tcase_add_test(tc_insert, linkedList_length_index_insert);
  tcase_add_test(tc_insert, linkedList_other_index_insert);
  suite_add_tcase(s, tc_insert);

  TCase* tc_removeFirst = tcase_create("removeFirst");
  tcase_add_test(tc_removeFirst, linkedList_null_list_removeFirst);
  tcase_add_test(tc_removeFirst, linkedList_empty_list_removeFirst);
  tcase_add_test(tc_removeFirst, linkedList_single_item_list_removeFirst);
  tcase_add_test(tc_removeFirst, linkedList_removeFirst);
  suite_add_tcase(s, tc_removeFirst);

  TCase* tc_removeLast = tcase_create("removeLast");
  tcase_add_test(tc_removeLast, linkedList_null_list_removeLast);
  tcase_add_test(tc_removeLast, linkedList_empty_list_removeLast);
  tcase_add_test(tc_removeLast, linkedList_single_item_list_removeLast);
  tcase_add_test(tc_removeLast, linkedList_removeLast);
  suite_add_tcase(s, tc_removeLast);

  TCase* tc_remove = tcase_create("remove");
  tcase_add_test(tc_remove, linkedList_null_list_remove);
  tcase_add_test(tc_remove, linkedList_empty_list_remove);
  tcase_add_test(tc_remove, linkedList_neg_index_remove);
  tcase_add_test(tc_remove, linkedList_greater_index_remove);
  tcase_add_test(tc_remove, linkedList_zero_index_remove);
  tcase_add_test(tc_remove, linkedList_length_index_remove);
  tcase_add_test(tc_remove, linkedList_remove);
  suite_add_tcase(s, tc_remove);

  return s;
}

