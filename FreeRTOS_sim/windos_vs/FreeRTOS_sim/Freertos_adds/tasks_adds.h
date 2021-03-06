/*
* Whitecat, tasks adds for whitecat
*
* Copyright (C) 2015 - 2016
* IBEROXARXA SERVICIOS INTEGRALES, S.L. & CSS IBÉRICA, S.L.
*
* Author: Jaume Olivé (jolive@iberoxarxa.com / jolive@whitecatboard.org)
*
* All rights reserved.
*
* Permission to use, copy, modify, and distribute this software
* and its documentation for any purpose and without fee is hereby
* granted, provided that the above copyright notice appear in all
* copies and that both that the copyright notice and this
* permission notice and warranty disclaimer appear in supporting
* documentation, and that the name of the author not be used in
* advertising or publicity pertaining to distribution of the
* software without specific, written prior permission.
*
* The author disclaim all warranties with regard to this
* software, including all implied warranties of merchantability
* and fitness.  In no event shall the author be liable for any
* special, indirect or consequential damages or any damages
* whatsoever resulting from loss of use, data or profits, whether
* in an action of contract, negligence or other tortious action,
* arising out of or in connection with the use or performance of
* this software.
*/

//static int _____errno; // Errno variable if scheluder is not started
#ifndef _TASK_ADDS_H__
#define _TASK_ADDS_H__

void enter_critical_section() {
	if (portIN_ISR()) {
		taskDISABLE_INTERRUPTS();
	}
	else {
		taskENTER_CRITICAL();
	}
}

void exit_critical_section() {
	if (portIN_ISR()) {
		taskENABLE_INTERRUPTS();
	}
	else {
		taskEXIT_CRITICAL();
	}
}

//void *GetErrnoRef (void) {
//    void *ref;
//    
//    enter_critical_section();
//    if (pxCurrentTCB) {
//        ref = &(pxCurrentTCB->errno);        
//    } else {
//        ref = &_____errno;
//    }
//    exit_critical_section();
//
//    return ref;
//}

UBaseType_t uxGetTaskId() {
	UBaseType_t uxTaskNumber;

	enter_critical_section();
	uxTaskNumber = pxCurrentTCB->uxTaskNumber;
	exit_critical_section();

	return uxTaskNumber;
}

UBaseType_t uxGetThreadId() {
	int threadid;

	enter_critical_section();
	threadid = pxCurrentTCB->threadid;
	exit_critical_section();

	return threadid;
}

void uxSetThreadId(UBaseType_t id) {
	enter_critical_section();
	pxCurrentTCB->threadid = id;
	exit_critical_section();
}

void uxSetLuaState(lua_State* L) {
	enter_critical_section();
	pxCurrentTCB->L = L;
	exit_critical_section();
}

lua_State* pvGetLuaState() {
	lua_State* L;

	enter_critical_section();
	L = pxCurrentTCB->L;
	exit_critical_section();

	return L;
}

uint32_t uxGetSignaled(TaskHandle_t h) {
	uint32_t signaled;

	enter_critical_section();
	signaled = ((TCB_t *)h)->signaled;
	exit_critical_section();

	return signaled;
}

void uxSetSignaled(TaskHandle_t h, int s) {
	enter_critical_section();
	((TCB_t *)h)->signaled |= (1 << s);
	exit_critical_section();
}

void uxClearSignaled(TaskHandle_t h, int s) {
	enter_critical_section();
	((TCB_t *)h)->signaled &= ~(1 << s);
	exit_critical_section();
}

TaskHandle_t xGetCurrentTask() {
	return (TaskHandle_t)pxCurrentTCB;
}

//add by lcj
UBaseType_t uxGetStack(TaskHandle_t h) {
	int thread_stack;

	enter_critical_section();
	thread_stack = ((TCB_t *)h)->thread_stackNum;
	exit_critical_section();

	return thread_stack;
}

void uxSetStack(UBaseType_t stack) {
	enter_critical_section();
	pxCurrentTCB->thread_stackNum = stack;
	exit_critical_section();
}
//add by lcj end

#endif