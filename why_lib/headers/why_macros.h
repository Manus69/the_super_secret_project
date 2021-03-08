#ifndef WHY_MACROS_H
#define WHY_MACROS_H

#define ABS(x) (((x) < 0) ? (-x) : (x))

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define SWAP(array, type, li, ri) {type _store = array[li]; array[li] = array[ri]; array[ri] = _store;}

#endif