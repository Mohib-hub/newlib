#include <machine/syscall.h>
#include <sys/types.h>
#include "semihost_syscall.h"

/* Read from a file.  */
ssize_t _read(int file, void *ptr, size_t len)
{
  long data_block[] = {file, (long) ptr, len};
  long bytes_not_read = syscall_errno (SEMIHOST_read, data_block);
  if (bytes_not_read >= 0)
    return len - bytes_not_read;
  return -1;
}
