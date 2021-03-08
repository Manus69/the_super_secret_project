#ifndef WHY_PRINT_FUNCTIONS_H
#define WHY_PRINT_FUNCTIONS_H

//it prints pointers as if the addresses fit into an unsigned int variable (might brick on high pointers)
int why_printf(const char *format, ... );

#endif