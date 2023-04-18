#ifndef LALUA_H
#define LALUA_H

#include "lua.h"
#include <stdio.h>
#include <stdbool.h>

//very much a work in progress!

#ifdef __cplusplus
extern "C" {
#endif

    static inline void luaClear(lua_State* L) {
        if (L != NULL) {
            lua_settop(L, 0);
            lua_gc(L, LUA_GCCOLLECT, 0);
        }
    }

    static inline int luaRunScript(lua_State* L, const char* script) {
        int result = 0;
        if (L != NULL) {
            luaClear(L);
            int luaFile = luaL_loadfile(L, script);
            luaFile = lua_pcall(L, 0, LUA_MULTRET, 0);
            if (luaFile != 0) {
                const char* errorMessage = lua_tostring(L, -1);
                printf(errorMessage);
                result = 1;
            }
        }
        else {
            result = 1;
        }
        return result;
    }
    
    //Easy way, to call lua functions from inside you program 
    //e.g if you have something like a game loop

    static inline void luaFnSetup(lua_State* L) {
        if (L == NULL) { return; }
        lua_getglobal(L, "setup");
        if (lua_pcall(L, 0, 0, 0) != 0) {
            const char* errorMessage = lua_tostring(L, -1);
            printf(errorMessage);
        }
    }

    static inline void luaFnUpdate(lua_State* L) {
        if (L == NULL) { return; }
        lua_getglobal(L, "update");
        if (lua_pcall(L, 0, 0, 0) != 0) {
            const char* errorMessage = lua_tostring(L, -1);
            printf(errorMessage);
        }
    }

    static inline int luaFnExit(lua_State* L) {
        int result = 0;
        if (L == NULL) { return 1; }
        lua_getglobal(L, "exit");
        if (lua_pcall(L, 0, 0, 0) != 0) {
            const char* errorMessage = lua_tostring(L, -1);
            printf(errorMessage);
            result = 1;
        }
        return result;
    }

    static inline int luaExists(lua_State* L, const char* name) {
        if (L != NULL) {
            lua_getglobal(L, name);
            int type = lua_type(L, -1);
            lua_pop(L, 1);
            return type != LUA_TNIL;
        }
        else {
            return 0;
        }
    }

    static inline void luaSetGlobalBool(lua_State* L, const char* var, bool val) {
        if (L != NULL) {
            lua_pushglobaltable(L);
            lua_pushboolean(L, val);
            lua_setfield(L, -2, var);
            lua_pop(L, 1);
        }
    }

    static inline void luaSetGlobalNumber(lua_State* L, const char* var, float val) {
        if (L != NULL) {
            lua_pushglobaltable(L);
            lua_pushnumber(L, val);
            lua_setfield(L, -2, var);
            lua_pop(L, 1);
        }
    }

    static inline void luaSetBool(lua_State* L, const char* var, bool val) {
        if (L != NULL) {
            lua_pushboolean(L, val);
            lua_setglobal(L, var);
        }
    }

    static inline void luaSetNumber(lua_State* L, const char* var, float val) {
        if (L != NULL) {
            lua_pushnumber(L, val);
            lua_setglobal(L, var);
        }
    }

#ifdef __cplusplus
}
#endif

#endif /* LALUA_H */
