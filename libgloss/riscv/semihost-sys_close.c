#include <machine/syscall.h>
#include "semihost_syscall.h"

/* Close a file.  */
int
_close(int file)
{
  long data_block[] = {file};
  return syscall_errno (SEMIHOST_close, data_block);
}
