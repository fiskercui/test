
require('pack')

local t =  {}

function t:test( ... )
	print("string test")
	local __s = "123"
	print("string sub", string.sub(__s, 1,2))
	print("string sub", __s:sub(2,2))


	local __pack = string.pack("<bihP2", 0x59, 11, 1101, "", "中文")
	-- local __pack = string.pack("hello",1)
	print("pack type", type(__pack))
	for i=1, #__pack do
		print ("string ", i, string.sub(__pack, i,i))
	end
	print("pack", __pack)


	local tbl = {
		"hello",
		"wrold",
	}
	local __unpack = {unpack(tbl)}
	print("unpack type", type(__unpack))
	print("unpack", __unpack[1], __unpack[2])
end


return t
