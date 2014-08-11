local t = {}



--[[--

输出值的内容

### 用法示例

~~~ lua

local t = {comp = "chukong", engine = "quick"}

dump(t)

~~~

@param mixed value 要输出的值

@param [string desciption] 输出内容前的文字描述

@parma [integer nesting] 输出时的嵌套层级，默认为 3

]]
function dump(value, desciption, nesting)
    if type(nesting) ~= "number" then nesting = 3 end

    local lookupTable = {}
    local result = {}

    local function _v(v)
        if type(v) == "string" then
            v = "\"" .. v .. "\""
        end
        return tostring(v)
    end

    local traceback = string.split(debug.traceback("", 2), "\n")
    print("dump from: " .. string.trim(traceback[3]))

    local function _dump(value, desciption, indent, nest, keylen)
        desciption = desciption or "<var>"
        spc = ""
        if type(keylen) == "number" then
            spc = string.rep(" ", keylen - string.len(_v(desciption)))
        end
        if type(value) ~= "table" then
            result[#result +1 ] = string.format("%s%s%s = %s", indent, _v(desciption), spc, _v(value))
        elseif lookupTable[value] then
            result[#result +1 ] = string.format("%s%s%s = *REF*", indent, desciption, spc)
        else
            lookupTable[value] = true
            if nest > nesting then
                result[#result +1 ] = string.format("%s%s = *MAX NESTING*", indent, desciption)
            else
                result[#result +1 ] = string.format("%s%s = {", indent, _v(desciption))
                local indent2 = indent.."    "
                local keys = {}
                local keylen = 0
                local values = {}
                for k, v in pairs(value) do
                    keys[#keys + 1] = k
                    local vk = _v(k)
                    local vkl = string.len(vk)
                    if vkl > keylen then keylen = vkl end
                    values[k] = v
                end
                table.sort(keys, function(a, b)
                    if type(a) == "number" and type(b) == "number" then
                        return a < b
                    else
                        return tostring(a) < tostring(b)
                    end
                end)
                for i, k in ipairs(keys) do
                    _dump(values[k], k, indent2, nest + 1, keylen)
                end
                result[#result +1] = string.format("%s}", indent)
            end
        end
    end
    _dump(value, desciption, "- ", 1)

    for i, line in ipairs(result) do
        print(line)
    end
end

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

	local t = {
		testenv = "",
		testapk = ""
	}
	dump(t, "_G dump")
end

return t

