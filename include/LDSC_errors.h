#ifndef LDSC_ERRORS_H
#define LDSC_ERRORS_H

/**
 * The following enum defined all error types and associated codes for the LDSC library.
 * We suggest using the symbolic mnemonics in your code for better readability.
 */
typedef enum {
  /* STANDARD TYPES*/
  OK = 0,
  ERROR = -1,

  /* MALLOC TYPES */
  STRUCTURE_MALLOC = 1,
  PRIVATEDATA_MALLOC = 2,
  NODE_MALLOC = 3,
  DELETE_FAIL = 4,

  /* POINTER ERROR TYPES */
  NULL_SELF = 101,
  NULL_DATAPTR = 102,

  /* INDEX ERROR TYPES */
  LESS_THAN_INDEX = 201,
  GREATER_THAN_INDEX = 202

} LDSC_error;

#endif
