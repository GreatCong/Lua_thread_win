#ifndef _LUA_MODULES_H_
#define _LUA_MODULES_H_

#if LUA_USE_ROTABLE
#define LUA_REG_TYPE                luaR_entry
#define LSTRKEY                     LRO_STRKEY
#define LNUMKEY                     LRO_NUMKEY
#define LNILKEY                     LRO_NILKEY
#define LFUNCVAL                    LRO_FUNCVAL
#define LUDATA                      LRO_LUDATA
#define LNUMVAL                     LRO_NUMVAL
#define LINTVAL                     LRO_INTVAL
#define LROVAL                      LRO_ROVAL
#define LNILVAL                     LRO_NILVAL
#define LREGISTER(L, name, table)\
  return 0
#else
#define LUA_REG_TYPE                luaL_Reg
#define LSTRKEY(x)                  x
#define LNILKEY                     NULL
#define LFUNCVAL(x)                 x
#define LNILVAL                     NULL
#define LNUMVAL(x)					x
#define LINTVAL(x)					x
#define LROVAL(x)					x

#define LREGISTER(L, name, table)\
  luaL_register(L, name, table);\
  return 1
#endif

/* module */
#define PUT_IN_SECTION(s) __attribute__((used,unused,section(s)))

// Macros for concatenate 2 tokens
#define LIB_PASTER(x,y) x##y
#define LIB_EVALUATOR(x,y) LIB_PASTER(x,y)
#define LIB_CONCAT(x,y) LIB_EVALUATOR(x,y)

// Macros for stringify a token
#define LIB_TOSTRING_PASTER(x) #x
#define LIB_TOSTRING_EVALUATOR(x) LIB_TOSTRING_PASTER(x)
#define LIB_TOSTRING(x) LIB_TOSTRING_EVALUATOR(x)

// Macros for register a library init function
#define LIB_USED(fname) LIB_CONCAT(LUA_USE_,fname)
#define LIB_SECTION(fname, section) LIB_CONCAT(section,LIB_USED(fname))

#define LIB_INIT(fname, lname, func) \
const PUT_IN_SECTION(LIB_TOSTRING(LIB_SECTION(fname,.lua_libs))) luaL_Reg LIB_CONCAT(lua_libs,LIB_CONCAT(_,LIB_CONCAT(lname,LIB_USED(fname)))) = {LIB_TOSTRING(lname), func}

#if LUA_USE_ROTABLE
#define LUA_OS_MODULE(fname, lname, map) \
const PUT_IN_SECTION(LIB_TOSTRING(LIB_SECTION(fname,.lua_rotable))) luaR_entry LIB_CONCAT(lua_rotable,LIB_CONCAT(_,LIB_CONCAT(lname,LIB_USED(fname)))) = {LSTRKEY(LIB_TOSTRING(lname)), LROVAL(map)}
#else
#define LUA_OS_MODULE(fname, lname, map)
#endif

/*
#define NODEMCU_MODULE(cfgname, luaname, map, initfunc) \
const LOCK_IN_SECTION(".lua_libs") \
luaL_Reg MODULE_PASTE_(lua_lib_,cfgname) = { luaname, initfunc }; \
const LOCK_IN_SECTION(".lua_rotable") \
luaR_table MODULE_EXPAND_PASTE_(cfgname,MODULE_EXPAND_PASTE_(_module_selected,MODULE_PASTE_(LUA_USE_MODULES_,cfgname))) \
= { luaname, map }
*/

#endif // !__LUA_MODULE_H_

