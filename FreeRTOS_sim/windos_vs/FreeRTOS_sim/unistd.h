/** This file is part of the Mingw32 package.
*  unistd.h maps     (roughly) to io.h
*/
#ifndef _UNISTD_H
#define _UNISTD_H
#include <io.h>
#include <process.h>

extern int usleep(int useconds);
extern int sleep(int n);

#endif /* _UNISTD_H */