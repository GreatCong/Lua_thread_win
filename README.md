# FreeRTOS-Simulator
It can be used in Windows and Linux

## Change
Here,I add thread function for lua to the Simulator, which is from Lua RTOS.

### Lua-RTOS
In their wiki, https://github.com/whitecatboard/Lua-RTOS-ESP32/wiki, you have more information about Lua-RTOS.

### Thread management functions
###### Thread management functions
* thread.list([table, monitor, all])
* thread.start(function, [stack, priority, cpu, name])
* thread.suspend([thread id])
* thread.resume([thread id])
* thread.stop([thread id])
* thread.status(thread id)

###### Thread control functions
* thread.sleep(seconds)
* thread.sleepms(milliseconds)
* thread.sleepus(useconds)

## Note
###### VS version supported
* VS2013
* VS2015
* others(not tested)

###### Platform supported
* win32(x86)


