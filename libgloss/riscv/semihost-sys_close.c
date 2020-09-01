#include <machine/syscall.h>
#include "semihost_syscall.h"
#include "semihost_fdtable.h"

/* Close a file.  */
int
_close(int file)
{
  struct fdentry *fd = _get_fdentry (file);
  long data_block[1];

  if (fd == NULL)
    return -1;

  data_block[0] = fd->handle;
  return syscall_errno (SEMIHOST_close, data_block);
}
