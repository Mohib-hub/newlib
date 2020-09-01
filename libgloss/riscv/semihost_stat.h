#include <sys/types.h>

#ifndef RISCV_SEMIHOST_STAT_H
#define RISCV_SEMIHOST_STAT_H

extern int _stat_common (int, struct stat *);
extern int _open (const char *, int, ...);
extern int _close (int);

#endif
