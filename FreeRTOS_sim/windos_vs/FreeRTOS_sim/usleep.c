//这个函数仅仅在linux中使用
//int usleep(__useconds_t useconds)
//{
//	struct timespec ts;
//
//	ts.tv_sec = (long int)useconds / 1000000;
//	ts.tv_nsec = ((long int)useconds % 1000000) * 1000;
//	if (!nanosleep(&ts, &ts)) return 0;
//	if (errno == EINTR) return ts.tv_sec;
//	return -1;
//}

#include "stdint.h"

//#ifndef __useconds_t
//#define __useconds_t uint32_t
//#endif

int usleep(int useconds)
{
	for (int i = 0; i < useconds; i++) { };

	return 0;
}

#include "Windows.h"
int sleep(int n){
	Sleep(n);
	return 0;
}
