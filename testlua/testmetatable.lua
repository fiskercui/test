local t = {}

t.testIndex =  function (...)
	print("index test")
	Window = {}
	Window.prototype = {x = 0 ,y = 0 ,width = 100 ,height = 100,}
	Window.mt = {}

	function Window.new(o)
		setmetatable(o ,Window.mt)
		return o
	end
	--是否写入index 元方法
	wt = Window.new({})
	print("before index", Window.mt.__index)
	print("before index Window width", wt.width)
	print("before index Window height", wt.height)
	print("before index Window x", wt.window)

	Window.mt.__index = function (table, key)
      return Window.prototype[key]
    end

	print("after index", Window.mt.__index)
	print("after index Window width", wt.width)
	print("after index Window height", wt.height)
	print("after index Window x", wt.window)

	-- Window.mt.__index = Window.prototype
	Window.mt.__index = function (table, key)
		return 1000
	end

	Window.mt.__newindex = function (table ,key ,value)
		if key == "wangbin" then
			rawset(table ,"wangbin" ,"yes,i am")
		end
	end
	w = Window.new{x = 10 ,y = 20}
	w.wangbin = "55"
	print(w.wangbin)
end

function t:test(...)
	print("metatable test")

	Window_Prototype = {x=0, y=0, width=100, height=100}
	MyWin = {title="Hello"}
	setmetatable(MyWin, {__index = Window_Prototype})
	print("MyWin", MyWin.x, MyWin.y, MyWin.width, MyWin.height, MyWin.title)

	t.testIndex()

	local __mt = getmetatable(MyWin)
	for key,value in pairs( __mt.__index) do
		print("index", key, value)
	end
end


return t