#include <machine/syscall.h>
#include <sys/timeb.h>
#include "semihost_syscall.h"

/* Get the current time.  Only relatively correct.  */
int
_ftime(struct timeb *tp)
{
  tp->time = syscall_errno (SEMIHOST_time, 0);
  tp->millitm = 0;
  return 0;
}
