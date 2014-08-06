#include "autogentestclassbindings.hpp"
#include "tclass.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_autogentestclassbindings_Tst_A_a(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_A* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"test.Tst_A",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Test::Tst_A*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_autogentestclassbindings_Tst_A_a'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        char* ret = cobj->a();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "a",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_A_a'.",&tolua_err);
#endif

    return 0;
}
int lua_autogentestclassbindings_Tst_A_set_number(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_A* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"test.Tst_A",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Test::Tst_A*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_autogentestclassbindings_Tst_A_set_number'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->set_number(arg0);
        return 0;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "set_number",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_A_set_number'.",&tolua_err);
#endif

    return 0;
}
int lua_autogentestclassbindings_Tst_A_get_number(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_A* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"test.Tst_A",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Test::Tst_A*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_autogentestclassbindings_Tst_A_get_number'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->get_number();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "get_number",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_A_get_number'.",&tolua_err);
#endif

    return 0;
}
int lua_autogentestclassbindings_Tst_A_constructor(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_A* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new Test::Tst_A();
        tolua_pushusertype(tolua_S,(void*)cobj,"test.Tst_A");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "Tst_A",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_A_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_autogentestclassbindings_Tst_A_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Tst_A)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Tst_A",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        Test::Tst_A* self = (Test::Tst_A*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_autogentestclassbindings_Tst_A(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"test.Tst_A");
    tolua_cclass(tolua_S,"Tst_A","test.Tst_A","",lua_autogentestclassbindings_Tst_A_finalize);

    tolua_beginmodule(tolua_S,"Tst_A");
        tolua_function(tolua_S,"new",lua_autogentestclassbindings_Tst_A_constructor);
        tolua_function(tolua_S,"a",lua_autogentestclassbindings_Tst_A_a);
        tolua_function(tolua_S,"set_number",lua_autogentestclassbindings_Tst_A_set_number);
        tolua_function(tolua_S,"get_number",lua_autogentestclassbindings_Tst_A_get_number);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(Test::Tst_A).name();
    g_luaType[typeName] = "test.Tst_A";
    g_typeCast["Tst_A"] = "test.Tst_A";
    return 1;
}

int lua_autogentestclassbindings_Tst_B_b(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_B* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"test.Tst_B",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Test::Tst_B*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_autogentestclassbindings_Tst_B_b'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        char* ret = cobj->b();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "b",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_B_b'.",&tolua_err);
#endif

    return 0;
}
int lua_autogentestclassbindings_Tst_B_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"test.Tst_B",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        Test::Tst_A* ret = Test::Tst_B::create();
        object_to_luaval<Test::Tst_A>(tolua_S, "test.Tst_A",(Test::Tst_A*)ret);
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_B_create'.",&tolua_err);
#endif
    return 0;
}
int lua_autogentestclassbindings_Tst_B_create_void(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"test.Tst_B",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        void* ret = Test::Tst_B::create_void();
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d\n ", "create_void",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_B_create_void'.",&tolua_err);
#endif
    return 0;
}
int lua_autogentestclassbindings_Tst_B_constructor(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_B* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new Test::Tst_B();
        tolua_pushusertype(tolua_S,(void*)cobj,"test.Tst_B");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "Tst_B",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_B_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_autogentestclassbindings_Tst_B_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Tst_B)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Tst_B",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        Test::Tst_B* self = (Test::Tst_B*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_autogentestclassbindings_Tst_B(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"test.Tst_B");
    tolua_cclass(tolua_S,"Tst_B","test.Tst_B","test.Tst_A",lua_autogentestclassbindings_Tst_B_finalize);

    tolua_beginmodule(tolua_S,"Tst_B");
        tolua_function(tolua_S,"new",lua_autogentestclassbindings_Tst_B_constructor);
        tolua_function(tolua_S,"b",lua_autogentestclassbindings_Tst_B_b);
        tolua_function(tolua_S,"create", lua_autogentestclassbindings_Tst_B_create);
        tolua_function(tolua_S,"create_void", lua_autogentestclassbindings_Tst_B_create_void);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(Test::Tst_B).name();
    g_luaType[typeName] = "test.Tst_B";
    g_typeCast["Tst_B"] = "test.Tst_B";
    return 1;
}

int lua_autogentestclassbindings_Tst_C_c(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_C* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"test.Tst_C",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Test::Tst_C*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_autogentestclassbindings_Tst_C_c'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        char* ret = cobj->c();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "c",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_C_c'.",&tolua_err);
#endif

    return 0;
}
int lua_autogentestclassbindings_Tst_C_constructor(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_C* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj = new Test::Tst_C(arg0);
        tolua_pushusertype(tolua_S,(void*)cobj,"test.Tst_C");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "Tst_C",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_C_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_autogentestclassbindings_Tst_C_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Tst_C)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Tst_C",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        Test::Tst_C* self = (Test::Tst_C*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_autogentestclassbindings_Tst_C(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"test.Tst_C");
    tolua_cclass(tolua_S,"Tst_C","test.Tst_C","test.Tst_B",lua_autogentestclassbindings_Tst_C_finalize);

    tolua_beginmodule(tolua_S,"Tst_C");
        tolua_function(tolua_S,"new",lua_autogentestclassbindings_Tst_C_constructor);
        tolua_function(tolua_S,"c",lua_autogentestclassbindings_Tst_C_c);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(Test::Tst_C).name();
    g_luaType[typeName] = "test.Tst_C";
    g_typeCast["Tst_C"] = "test.Tst_C";
    return 1;
}

int lua_autogentestclassbindings_Tst_E_get_pete(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_E* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"test.Tst_E",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Test::Tst_E*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_autogentestclassbindings_Tst_E_get_pete'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Test::Tst_E::Pete arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->get_pete(arg0);
        return 0;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "get_pete",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_E_get_pete'.",&tolua_err);
#endif

    return 0;
}
int lua_autogentestclassbindings_Tst_E_get_pointer(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_E* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"test.Tst_E",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Test::Tst_E*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_autogentestclassbindings_Tst_E_get_pointer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        void* arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR void*;
        if(!ok)
            return 0;
        cobj->get_pointer(arg0);
        return 0;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "get_pointer",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_E_get_pointer'.",&tolua_err);
#endif

    return 0;
}
int lua_autogentestclassbindings_Tst_E_set_ptr(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_E* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"test.Tst_E",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Test::Tst_E*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_autogentestclassbindings_Tst_E_set_ptr'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        void* arg0;

        #pragma warning NO CONVERSION TO NATIVE FOR void*;
        if(!ok)
            return 0;
        cobj->set_ptr(arg0);
        return 0;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "set_ptr",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_E_set_ptr'.",&tolua_err);
#endif

    return 0;
}
int lua_autogentestclassbindings_Tst_E_operator+(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_E* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"test.Tst_E",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Test::Tst_E*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_autogentestclassbindings_Tst_E_operator+'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Test::Tst_E arg0;

        ok &= luaval_to_object<Test::Tst_E>(tolua_S, 2, "test.Tst_E",&arg0);
        if(!ok)
            return 0;
        Test::Tst_E& ret = cobj->operator+(arg0);
        object_to_luaval<Test::Tst_E&>(tolua_S, "test.Tst_E",(Test::Tst_E&)ret);
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "operator+",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_E_operator+'.",&tolua_err);
#endif

    return 0;
}
int lua_autogentestclassbindings_Tst_E_pars(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_E* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"test.Tst_E",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Test::Tst_E*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_autogentestclassbindings_Tst_E_pars'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->pars();
        return 0;
    }
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->pars(arg0);
        return 0;
    }
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->pars(arg0, arg1);
        return 0;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "pars",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_E_pars'.",&tolua_err);
#endif

    return 0;
}
int lua_autogentestclassbindings_Tst_E_get_ptr(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_E* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"test.Tst_E",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Test::Tst_E*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_autogentestclassbindings_Tst_E_get_ptr'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        void* ret = cobj->get_ptr();
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "get_ptr",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_E_get_ptr'.",&tolua_err);
#endif

    return 0;
}
int lua_autogentestclassbindings_Tst_E_constructor(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_E* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj = new Test::Tst_E(arg0);
        tolua_pushusertype(tolua_S,(void*)cobj,"test.Tst_E");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "Tst_E",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_E_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_autogentestclassbindings_Tst_E_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Tst_E)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Tst_E",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        Test::Tst_E* self = (Test::Tst_E*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_autogentestclassbindings_Tst_E(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"test.Tst_E");
    tolua_cclass(tolua_S,"Tst_E","test.Tst_E","",lua_autogentestclassbindings_Tst_E_finalize);

    tolua_beginmodule(tolua_S,"Tst_E");
        tolua_function(tolua_S,"new",lua_autogentestclassbindings_Tst_E_constructor);
        tolua_function(tolua_S,"get_pete",lua_autogentestclassbindings_Tst_E_get_pete);
        tolua_function(tolua_S,"get_pointer",lua_autogentestclassbindings_Tst_E_get_pointer);
        tolua_function(tolua_S,"set_ptr",lua_autogentestclassbindings_Tst_E_set_ptr);
        tolua_function(tolua_S,"operator+",lua_autogentestclassbindings_Tst_E_operator+);
        tolua_function(tolua_S,"pars",lua_autogentestclassbindings_Tst_E_pars);
        tolua_function(tolua_S,"get_ptr",lua_autogentestclassbindings_Tst_E_get_ptr);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(Test::Tst_E).name();
    g_luaType[typeName] = "test.Tst_E";
    g_typeCast["Tst_E"] = "test.Tst_E";
    return 1;
}

int lua_autogentestclassbindings_Tst_Outside_constructor(lua_State* tolua_S)
{
    int argc = 0;
    Test::Tst_Outside* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new Test::Tst_Outside();
        tolua_pushusertype(tolua_S,(void*)cobj,"test.Tst_Outside");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    printf("%s has wrong number of arguments: %d, was expecting %d \n", "Tst_Outside",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_autogentestclassbindings_Tst_Outside_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_autogentestclassbindings_Tst_Outside_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Tst_Outside)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"Tst_Outside",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        Test::Tst_Outside* self = (Test::Tst_Outside*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_autogentestclassbindings_Tst_Outside(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"test.Tst_Outside");
    tolua_cclass(tolua_S,"Tst_Outside","test.Tst_Outside","",lua_autogentestclassbindings_Tst_Outside_finalize);

    tolua_beginmodule(tolua_S,"Tst_Outside");
        tolua_function(tolua_S,"new",lua_autogentestclassbindings_Tst_Outside_constructor);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(Test::Tst_Outside).name();
    g_luaType[typeName] = "test.Tst_Outside";
    g_typeCast["Tst_Outside"] = "test.Tst_Outside";
    return 1;
}
TOLUA_API int register_all_autogentestclassbindings(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_autogentestclassbindings_Tst_A(tolua_S);
	lua_register_autogentestclassbindings_Tst_B(tolua_S);
	lua_register_autogentestclassbindings_Tst_C(tolua_S);
	lua_register_autogentestclassbindings_Tst_E(tolua_S);
	lua_register_autogentestclassbindings_Tst_Outside(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

