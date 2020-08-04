#include <machine/syscall.h>
#include <sys/stat.h>
#include "semihost_syscall.h"

int
_isatty(int file)
{
  long data_block[] = {file};
  return syscall_errno (SEMIHOST_istty, data_block);
}
