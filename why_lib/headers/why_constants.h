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

#define EPSILON 1e-6
#define NAN __DBL_MIN__

#define STRING_BUFFER_DC 1 << 10
#define VECTOR_DC 32

#define S_FUNCTIONS_DVS 16

#define FILE_MODE_READ 00
#define FILE_MODE_WRITE 01
#define FILE_MODE_READ_WRITE 02
#define FILE_MODE_TRUNCATE 01000
#define FILE_MODE_APPEND 02000

#endif