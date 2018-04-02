/*
* Whitecat, main program
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
#include "myBoardDef.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portable.h"
#include "timers.h"
//#include "lua.h"

//#include <machine/pic32mz.h>
//#include <machine/machConst.h>
//#include <sys/drivers/gpio.h>
//#include <sys/drivers/uart.h>
//#include <sys/syslog.h>
#include "sys/panic_sys.h"
//#include <drivers/network/network.h>
//#include <drivers/lora/lora.h>
//#include <utils/delay.h>

#include <stdio.h>
//#include <fcntl.h>

//#include <stdio.h>
//#include <sys/param.h>
//#include <sys/stat.h>
//#include <unistd.h>
//#include <errno.h>
//#include <stdlib.h>
//#include <string.h>
//#include <syslog.h>
//#include <stdarg.h>
//#include <dirent.h>
//#include <time.h>
//#include <setjmp.h>

#include "pthread.h"
#include <stdlib.h>
//#include <sys/delay.h>
#include <sys/debug.h>

extern const char *__progname;

// #include "math.h"

//add by lcj
#ifndef luaTaskStack
#define luaTaskStack 192 * 5
#endif 
//add by lcj END

int luaos_main(void);

void *lua_start(void *arg) {
	for (;;) {
		luaos_main();
		//printf("ok ");
		//vTaskDelay(100);
	}

	return NULL;
}

//extern char *normalize_path(const char *path);
//extern double nmea_geoloc_to_decimal(char *token);

//add by lcj
//extern void mach_dev();
//extern void _clock_init();
//extern void _syscalls_init();
extern void _pthread_init();
//extern void _console_init();
//extern void _lora_init();
//extern void _signal_init();
extern void _mtx_init();

void mach_init() {
	//resource_init();
	_mtx_init();
	_pthread_init();
	/*_clock_init();
	_syscalls_init();
	_console_init();
	_signal_init();*/

//#if LUA_USE_LORA
//	_lora_init();
//#endif
//
//	mach_dev();
}
//add by lcj end

void user_init(void) {
#if LED_ACT
	// Init leds
	gpio_pin_output(LED_ACT);
	gpio_pin_clr(LED_ACT);
#endif

	pthread_attr_t attr;
	pthread_t thread;
	int res;

	mach_init();

	debug_free_mem_begin(lua_main_thread);//lua_main_thread是表示返回值，是对堆的检查

	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, luaTaskStack);

	res = pthread_create(&thread, &attr, lua_start, NULL);
	if (res) {
		panic("Cannot start lua");
	}

	debug_free_mem_end(lua_main_thread, NULL);
}

