#include <machine/syscall.h>
#include <sys/stat.h>
#include "semihost_syscall.h"

extern int _stat_common (int, struct stat *);
extern int _open (const char *, int, ...);
extern int _close (int);
