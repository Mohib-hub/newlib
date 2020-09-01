#include "semihost_fdtable.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef RISCV_MAX_OPEN_FILES
#define RISCV_MAX_OPEN_FILES 16
#endif

extern int errno;
extern int _open (const char *, int, ...);

static struct fdentry fdtable[RISCV_MAX_OPEN_FILES];

/* Initialize fdtable.  A handle of -1 denotes an empty entry.  */

void __attribute__((constructor))
init_semihosting ()
{
  int fd;

  for (int i=0; i<RISCV_MAX_OPEN_FILES; i++)
    fdtable[i].handle = -1;

  /* Set up std streams.  */
  /* stdin.  */
  fd = _open (":tt", O_RDONLY);
  fdtable[STDIN_FILENO].handle = fd;
  fdtable[STDIN_FILENO].pos = 0;

  /* stdout.  */
  fd = _open (":tt", O_WRONLY|O_CREAT|O_TRUNC);
  fdtable[STDOUT_FILENO].handle = fd;
  fdtable[STDOUT_FILENO].pos = 0;

  /* stderr.  */
  fd = _open (":tt", O_WRONLY|O_CREAT|O_APPEND);
  fdtable[STDERR_FILENO].handle = fd;
  fdtable[STDERR_FILENO].pos = 0;
}

int
_register_fd (int handle)
{
  for (int i=0; i<RISCV_MAX_OPEN_FILES; i++)
    if (fdtable[i].handle == -1)
      {
        fdtable[i].handle = handle;
        fdtable[i].pos = 0;
        return i;
      }
  /* Too many open files.  */
  errno = ENFILE;
  return -1;
}

/* Find an fd entry for handle.  Return NULL if not found.  */

struct fdentry *
_get_fdentry (int fd)
{
  if (fd<0 || fd>RISCV_MAX_OPEN_FILES || fdtable[fd].handle == -1)
    {
      errno = EBADF;
      return NULL;
    }
  return &fdtable[fd];
}

/* Remove entry from fdtable.  */

void
_deregister_fd (int fd)
{
  fdtable[fd].handle = -1;
}
