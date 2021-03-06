#ifndef WHY_PRINTF_CONSTANTS_H
#define WHY_PRINTF_CONSTANTS_H

#define PRINTF_INT_DBC 32
#define PRINTF_DOUBLE_DBC (1 << 6) //can this break on long doubles?
#define PRINTF_PRECISION_DEFAULT 5
#define PRINTF_EPSILON 1e-7
#define PRINTF_FLUSH_THRESHOLD (1 << 10)

#define PRINTF_SPECIAL_CHAR '%'
#define PRINTF_SPECIFIERS "dfspx"

#endif