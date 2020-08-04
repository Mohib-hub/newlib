#include <machine/syscall.h>
#include <sys/types.h>
#include "semihost_syscall.h"

/* Write to a file.  */
ssize_t
_write(int file, const void *ptr, size_t len)
{
  long data_block[] = {file, (long) ptr, len};
  long bytes_not_written = syscall_errno (SEMIHOST_write, data_block);
  if (bytes_not_written >= 0)
    return len - bytes_not_written;
  return -1;
}
