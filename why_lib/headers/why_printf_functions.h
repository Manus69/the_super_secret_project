#ifndef WHY_PRINTF_FUNCTIONS_H
#define WHY_PRINTF_FUNCTIONS_H

int why_printf(const char *format, ... );
char *why_sprintf(const char *format, ...);
int why_fprintf(const char *format, const char *file_name, int mode, ...);

#endif