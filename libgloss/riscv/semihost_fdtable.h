#include <sys/types.h>

#ifndef RISCV_SEMIHOST_FDTABLE_H
#define RISCV_SEMIHOST_FDTABLE_H

extern void __attribute__((constructor)) init_semihosting ();
extern int _register_fd (int);
extern struct fdentry * _get_fdentry (int);
extern void _deregister_fd (int);

struct fdentry
{
  int handle;
  off_t pos;
};

#endif
