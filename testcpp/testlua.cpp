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

static void stackDump(lua_State* L){
    cout<<"\nbegin dump lua stack"<<endl;
    int i = 0;
    int top = lua_gettop(L);
    for (i = 1; i <= top; ++i) {
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING:
            {
                printf("'%s' ", lua_tostring(L, i));
            }
                break;
            case LUA_TBOOLEAN:
            {
                printf(lua_toboolean(L, i) ? "true " : "false ");
            }break;
            case LUA_TNUMBER:
            {
                printf("%g ", lua_tonumber(L, i));
            }
                break;
            default:
            {
                printf("%s ", lua_typename(L, t));
            }
                break;
        }
    }
    printf("\nend dump lua stack\n");
}

void testExchangeData()
{
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
  const char* szLua_code =
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
  const char* szLua_code =
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

/*
lua call cpp function
*/
void testCppFunction()
{
  const char* szLua_code = "v, a = calcComplex(3, 4)\n"
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





int count(lua_State* L)
{
   //得到UpValue
  double m_ = lua_tonumber(L, lua_upvalueindex(1));
  //更改UpValue
  lua_pushnumber(L, ++m_);
  lua_replace(L, lua_upvalueindex(1));
  //返回结果（直接复制一份UpValue作为结果）
  lua_pushvalue(L, lua_upvalueindex(1));
  return 1;
}

int newCount(lua_State* L)
{
 //计数器初值（即UpValue）
  lua_pushnumber(L,0);
 //放入计算函数，告诉它与这个函数相关联的数据个数
  lua_pushcclosure(L, count, 1);
  return 1; //一个结果,即函数体
}

void testClosure()
{
    const char *szLua_code =
           "c1 = NewCount() "
           "c2 = NewCount() "
           "for i=1,5 do print(c1()) end "
           "for i=1,5 do print(c2()) end";
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L,"NewCount",newCount);
    bool err = luaL_loadstring(L, szLua_code) || lua_pcall(L, 0, 0, 0);
    if (err)
    {
      fprintf(stderr, "%s", lua_tostring(L, -1));
      lua_pop(L, 1);   //pop error message from the stack  
    }
    lua_close(L);
}



//test index 
void testGlobalIndex()
{
    const char *szLua_code =
           "a = 10 "
           "b=\"hello\" "
           "c=true ";

    lua_State *L = luaL_newstate();
    luaL_openlibs(L); 
    bool err = luaL_loadstring(L, szLua_code) || lua_pcall(L, 0, 0, 0);
    if (err)
    {
      fprintf(stderr, "%s", lua_tostring(L, -1));
      lua_pop(L, 1);   //pop error message from the stack  
    }
    else
    {
      lua_pushnil(L);
      while(0 !=  lua_next(L, LUA_GLOBALSINDEX))
      {
        lua_pushvalue(L, -2);
        printf("**%s-%s\n", lua_tostring(L, -1), lua_typename(L, lua_type(L,-2)));
        lua_pop(L, 2);
      }
    }
    lua_close(L);

}



/*
  test class
*/
class Window
{
public:
  Window()
  {
    m_a = 123;
    printf("new window\n");
  }

  ~Window()
  {
    printf("delete window\n");
  }

  void setPos(int posx, int posy, int width, int height)
  {
    printf("set postion:%d, %d, %d, %d\n", posx, posy, width, height);
  }

  void show()
  {
    printf("show\n");
  }
    
  void display()
  {
      printf("display:%d\n",m_a);
  }
public:
  int m_a;
};

int lua_newWindow(lua_State* L)
{
  // Window* window = NULL;
  // if(lua_isuserdata(L,1))
  // {
  //   window = *(Window*)luaL_checkudata(L, 1, "MyWindow");
  // }

//ps:lua_newuserdata 的内存会被lua自己回收， Window**的形式
  printf("lua_newWindow\n");
  Window** pWindowUserData = (Window**) lua_newuserdata(L, sizeof(Window));
  printf("lua_newWindow Addr no init::%lX\n", *pWindowUserData);
  *pWindowUserData =new Window;
  printf("lua_newWindow Addr::%lX\n", *pWindowUserData);
  printf("windows data m_a:%d\n", (*pWindowUserData)->m_a);
  luaL_getmetatable(L, "MyWindow");
  lua_setmetatable(L, -2);
  return 1;
}

int lua_delWindow(lua_State* L)
{
  printf("lua_delWindow\n");

  Window** window = (Window**)luaL_checkudata(L, 1 , "MyWindow");
    printf("windows data m_a:%d\n", (*window)->m_a);
  if(window != nullptr)
  {
      printf("windows has start delete\n");
      delete* window;
      printf("windows has end delete\n");
  }
  return 0;
}

int lua_showWindow(lua_State* L)
{
  Window* window = (Window*) luaL_checkudata(L, 1, "MyWindow");
  printf("lua_showWindow Addr::%lX\n", window);
    if(window)
  {
    window->show();
  }
  else
  {
    printf("lua_showWindow is null\n");
  }
  return 0;
}

int lua_setWindowPos(lua_State* L)
{
  Window* window = *(Window**) luaL_checkudata(L,1 ,"MyWindow");
  printf("lua_setWindowPos Addr::%lX\n", window);
  if(window)
  {
    window->setPos(luaL_checkint(L, 2), luaL_checkint(L, 3), 
                  luaL_checkint(L, 4), luaL_checkint(L, 5));
    window->display();
  }
  else
  {
    printf("lua_setPosWindow is null\n");
  }
  return 0;
}

static const struct  luaL_reg lib_Window[] = {
  {"new", lua_newWindow},
  {"del", lua_delWindow},
  {"pos", lua_setWindowPos},
  {"show", lua_showWindow},
  {NULL, NULL}
};

int luaopen_Window(lua_State* L)
{
  luaL_newmetatable(L, "MyWindow");

  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");//table.index = table

  lua_pushcfunction(L, lua_showWindow);
  lua_setfield(L, -2, "show");

  lua_pushcfunction(L, lua_setWindowPos);
  lua_setfield(L, -2, "pos");

  // lua_pushcfunction(L, lua_delWindow);
  // lua_setfield(L, -2, "del");

  lua_pushcfunction(L, lua_delWindow);
  lua_setfield(L, -2, "__gc");

  // lua_pushcfunction(L, lua_setWindowPos);
  // lua_setfield(L, -2, "pos");


  // lua 5.2 改动为luaL_newlib
  luaL_register(L, "Window", lib_Window);


  return 1;
}

void testCppObjectLua()
{
    const char* szLua_code=
        "local window = Window.new(); "    //在fm上建立一个按钮btn
        "for key,value in pairs( Window) do "
        "  print(\"window\", key, value) "
        "end "
        "local __mt = getmetatable(window) "
        "for key,value in pairs( __mt.__index) do "
        "  print(\"index\", key, value) "
        "end "
        "window:pos(100, 40, 150, 63); "
        "window:show(); ";
        // "Window.del(window);";

    lua_State *L = luaL_newstate();
    luaL_openlibs(L); 
    luaopen_Window(L);
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
  // testCppFunction();
  // testClosure();
  // testGlobalIndex();
  testCppObjectLua();
  return 0;
}