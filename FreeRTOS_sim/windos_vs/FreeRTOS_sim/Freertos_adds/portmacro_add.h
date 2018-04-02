#ifndef PORT_MACRO_ADD_H_H_
#define PORT_MACRO_ADD_H_H_

#include "stdbool.h"
//#define BaseType_t portBASE_TYPE
//#define UBaseType_t portUBASE_TYPE
//#define StackType_t portSTACK_TYPE
//#define TickType_t portTickType
//#define xSemaphoreHandle SemaphoreHandle_t
//#define xQueueHandle QueueHandle_t
//#define xTaskHandle TaskHandle_t
//#define xTimerHandle TimerHandle_t
//
//#define bzero(s, n) memset((s), 0, (n))
#define bcopy(s1, s2, n) memcpy((s2), (s1), (n))

//#define pdTASK_CODE TaskFunction_t

// add by lcj
extern volatile UBaseType_t ulCriticalNesting;//windows用的是ulCriticalNesting
//extern volatile UBaseType_t uxInterruptNesting;//微处理器用的是uxInterruptNesting
#define portIN_ISR() (ulCriticalNesting > 0)
// add by lcj END

//#define portTICK_PERIOD_US			( ( TickType_t ) 1000000 / configTICK_RATE_HZ )
//#define portTICK_PERIOD_MS			( ( TickType_t ) 1000 / configTICK_RATE_HZ )

#endif

