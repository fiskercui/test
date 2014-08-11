local t = {}

local function  testarg( ... )
	-- print("testarg", arg.n)


	print("参数个数 : ", select("#",...))

	local str = ""
	for k, v in ipairs{...} do
	str = str .. tostring(v) .. " "
	end
	print("参数所有值 : ",str)


	print(unpack{...})
end


local function testcallfunc(listener)
	print(type(listener))
	listener("123", "1", "hahah")
end

function t:test (...)
	print ("function call test")
	testcallfunc(
		function (code, ret , msg)
			print("callback",code, ret, msg)
		end)


	testarg(3,5)
end

return t


