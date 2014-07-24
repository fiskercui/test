#include <stdio.h>
#include <string.h>
#include <complex>
using std::complex;

extern "C"
{
  #include <lua.h>
  #include <lauxlib.h>
  #include <lualib.h>
}

void testExchangeData()
{
  char buff[256];
  int error;

  const char* szLua_code = "r = string.gsub(c_Str, c_Mode, c_Tag)"
                    "u = string.upper(r)";
  printf("szLua_code=%s\n", szLua_code);
  const char* szMode = "(%w+)%s*=%s*(%w+)";
  const char* szStr = "key1 = value1 key2 = value2";
  const char* szTag = "<%1>%2<%1>";

  lua_State *L = lua_open();   /* opens Lua */
  luaL_openlibs(L);             /* opens the basic library */

  lua_pushstring(L, szMode);
  lua_setglobal(L, "c_Mode");
  lua_pushstring(L, szTag);
  lua_setglobal(L, "c_Tag");
  lua_pushstring(L, szStr);
  lua_setglobal(L, "c_Str");

  bool err = luaL_loadbuffer(L, szLua_code, strlen(szLua_code), "demo") || lua_pcall(L, 0, 0, 0);
  if (err)
  {
    fprintf(stderr, "%s", lua_tostring(L, -1));
    lua_pop(L, 1); 
  }
  else
  {
    lua_getglobal(L, "r");
    printf("r=%s\n", lua_tostring(L, -1));
    lua_pop(L, 1);

    lua_getglobal(L, "u");
    printf("u=%s\n", lua_tostring(L, -1));
    lua_pop(L,1);
  }

  lua_close(L);
}

void testLua()
{
  char buff[256];
  int error;

  lua_State *L = lua_open();   /* opens Lua */
  luaL_openlibs(L);             /* opens the basic library */

  while (fgets(buff, sizeof(buff), stdin) != NULL) {
    error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
            lua_pcall(L, 0, 0, 0);
    if (error) {
      fprintf(stderr, "%s", lua_tostring(L, -1));
      lua_pop(L, 1);   //pop error message from the stack 
    }
  }
  lua_close(L);
}

void testTable()
{
  char* szLua_code =
    "x = {}"
    "x[1], x[2] = string.gsub(c.Str, c.Mode, c.Tag)"
    "print(c.Str, c.Mode, c.Tag)"
    "x.u = string.upper(x[1])"
    ;
  // 一下结果为非法，加注释后似乎有问题
  // char* szLua_code =
  //   "x = {}  --结果集合"
  //   "x[1], x[2] = string.gsub(c.Str, c.Mode, c.Tag)"
  //   "print(c.Str, c.Mode, c.Tag)"
  //   "x.u = string.upper(x[1])"
  //   ;

  const char* szMode = "(%w+)%s*=%s*(%w+)";
  const char* szStr = "key1 = value1 key2 = value2";
  const char* szTag = "<%1>%2<%1>";

  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  //把一个table 送给lua
  lua_newtable(L);  //新建一个table并压入栈顶
  lua_pushstring(L, "Mode"); //key
  lua_pushstring(L, szMode); //value
  //设置newtable[Mode] = szMode
  //由于上面两次牙栈、现在table元素排在栈顶往下数第三的的位置
  lua_settable(L, -3);
// void lua_settable (lua_State *L, int index);
// Does the equivalent to t[k] = v, where t is the value at the given valid index, v is the value at the top of the stack, and k is the value just below the top.

// This function pops both the key and the value from the stack. As in Lua, this function may trigger a metamethod for the "newindex" event (see §2.8).

  lua_pushstring(L, "Tag");
  lua_pushstring(L, szTag);
  lua_settable(L, -3);

  lua_pushstring(L, "Str");
  lua_pushstring(L, szStr);
  lua_settable(L, -3);

  lua_setglobal(L, "c");
  bool err = luaL_loadbuffer(L, szLua_code, strlen(szLua_code), "demo") || lua_pcall(L, 0, 0, 0);
  if (err)
  {
    fprintf(stderr, "%s", lua_tostring(L, -1));
    lua_pop(L, 1);   //pop error message from the stack 
  }
  else
  {
    lua_getglobal(L, "x");

    if(lua_istable(L, -1))
    {
      lua_pushstring(L, "u") ;  //Key
      lua_gettable(L, -2);
      printf("x.u == %s\n", lua_tostring(L, -1));
      lua_pop(L, 1);


      for(int i = 1; i<=2; i++)
      {
        lua_pushnumber(L, i );
        lua_gettable(L, -2);
        printf("x[%d]=%s\n", i, lua_tostring(L, -1));
        lua_pop(L, 1);
      }
    }
    lua_pop(L,1); //pop top stack 'x'
  }
  lua_close(L);
}

void testLuaFunction()
{
  char* szLua_code = 
      "function gsub(Str, Mode, Tag)\n"
      "    a, b = string.gsub(Str, Mode, Tag)\n"
      "    c = string.upper(a)\n"
      "    return a,b,c \n"
      "end"
      ;

  printf("szLua_code=%s\n", szLua_code);

  const char* szMode = "(%w+)%s*=%s*(%w+)";
  const char* szStr = "key1 = value1 key2 = value2";
  const char* szTag = "<%1>%2<%1>";

  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  bool err = luaL_loadbuffer(L, szLua_code, strlen(szLua_code), "demo") || lua_pcall(L, 0, 0, 0);
  if (err)
  {
      fprintf(stderr, "%s", lua_tostring(L, -1));
      lua_pop(L, 1);   //pop error message from the stack 
  }
  else
  {
    lua_getglobal(L, "gsub");
    if(lua_isfunction(L, -1))
    {
      lua_pushstring(L, szStr);
      lua_pushstring(L, szMode);
      lua_pushstring(L, szTag);
      if (0 != lua_pcall(L ,3, 2, 0))
      {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);   //pop error message from the stack   
      }
      else
      {
        printf("a = %s\n", lua_tostring(L, -2));
        printf("b = %s\n", lua_tostring(L, -1));
        lua_pop(L, 2);
      }
    }
    else
    {
        lua_pop(L, 1);
    }
  }
  lua_close(L);

}

int calcComplex(lua_State *L)
{
  double r = luaL_checknumber(L, 1);
  double i = luaL_checknumber(L, 2);
  complex<double> c(r, i);
  lua_pushnumber(L, abs(c));
  lua_pushnumber(L, arg(c)*180/3.14159);
  return 2;
}

void testCppFunction()
{
  char* szLua_code = "v, a = calcComplex(3, 4)\n"
                    "print(v,a)\n";

  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  lua_pushcfunction(L, calcComplex);
  lua_setglobal(L, "calcComplex");

  bool err = luaL_loadstring(L, szLua_code) || lua_pcall(L, 0, 0, 0);
  if (err)
  {
    fprintf(stderr, "%s", lua_tostring(L, -1));
    lua_pop(L, 1);   //pop error message from the stack  
  }
  lua_close(L);
}


int main (void) 
{
  // testTable();
  // testExchangeData();
  // testLua();
  testCppFunction();
  return 0;
}