#ifndef WHY_CONSTANTS_H
#define WHY_CONSTANTS_H

#include <limits.h>

#define HASH_ALPHABET_SIZE 71 //a prime close to the actual number of symbols; does it matter?
#define HASH_LARGE_PRIME 433494437

#define DEFAULT_ITEM_SIZE (int)sizeof(void *)

#define BUFFER_DBC (1 << 13)
#define BUFFER_DRS (1 << 13)

#define true 1
#define false 0

#define SUCCESS 0
#define FAILURE 1

#define DEFAULT 0

#define DIGITS "0123456789"
#define HEX_DIGITS "0123456789abcdef"

#define STRING_BUFFER_DC 1 << 10
#define VECTOR_DC 32

#define S_FUNCTIONS_DVS 16

#endif