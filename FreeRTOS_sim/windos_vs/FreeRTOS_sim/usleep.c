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

//int usleep(int useconds)
//{
//	for (int i = 0; i < useconds; i++) { };
//
//	return 0;
//}
//
//#include "Windows.h"
//int sleep(int n){
//	Sleep(n);
//	return 0;
//}

#include "FreeRTOS.h"
#include "task.h"

int sleep(int secs) {
	vTaskDelay((secs * 1000) / ((TickType_t)1000 / configTICK_RATE_HZ));

	return 0;
}

int usleep(int usec) {
	vTaskDelay(usec / ((TickType_t)1000000 / configTICK_RATE_HZ));

	return 0;
}

