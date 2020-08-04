#include <machine/syscall.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include "semihost_syscall.h"

extern int errno;

/* Set position in a file.  */
off_t
_lseek(int file, off_t offset, int dir)
{
  long data_block[] = {file, 0};
  long flen;
  long res;
  off_t abs_pos;

  if (file == STDOUT_FILENO || file == STDERR_FILENO || file == STDIN_FILENO)
    return 0;

  flen = syscall_errno (SEMIHOST_flen, data_block);

  switch (dir)
    {
      case SEEK_SET:
        abs_pos = offset;
        break;
      case SEEK_END:
        abs_pos = flen + offset;
        break;
      default:
        /* The semihosting seek syscall only works with absolute values.  The
           current position of each open file would need to be tracked to
           support SEEK_CUR.  */
        errno = EINVAL;
        return -1;
    }

  if (abs_pos < 0)
    {
      errno = EINVAL;
      return -1;
    }

  data_block[1] = abs_pos;
  res = syscall_errno (SEMIHOST_seek, data_block);
  if (res == 0)
    return abs_pos;
  return res;
}
