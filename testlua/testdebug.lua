local t = {}

function t:test( ... )
	print("testdebug")

	function traceback ()
		local level = 1
		while true do
			local info = debug.getinfo(level, "Sl")
			if not info then break end
			if info.what == "C" then -- is a C function?
				print(level, "C function")
				print(info)
			else -- a Lua function
				print(string.format("[%s]:%d",info.short_src, info.currentline))
				print(info)
			end
		level = level + 1
		end
	end
	traceback()


	--testhook
	print("turn on the hock")
	debug.sethook(print, "l")
	--上面这一行代码，简单的将print函数作为hook函数，并指示Lua当line事件发生时调用print函数。可以使用getinfo将当前正在执行的文件名信息加上去，使得跟踪器稍微精致点的
	function trace(event, line)
		-- body
		local  s  = debug.getinfo(2).short_src
		print(s .. ":" .. line)
	end
	debug.sethook(trace, "l")

	print ("hello world")
	print (tostring(1234567890))

	debug.sethook()
	print("turn off the hock")
end

return t

