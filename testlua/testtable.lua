
local t =  {}


t.tbltest = {
	[1] = "hehe",
	[2] = "hehe",
	["apple"] = "hehe",
	["banana"] = "hehe",
	["fruit"] = "hehe",
}

t.printTable = function(tbl)
	print ("print table")
--- pairs 而不是 ipairs
	for key,value in pairs(tbl) do
		print(key, value)
	end
end

function t:test( ... )
	print("table test")

	tbl = {"alpha", "beta", "gamma"}
	table.insert(tbl, "delta")
	table.insert(tbl, "epsilon")
	print(table.concat(tbl, ", "))

	table.insert(tbl,3,"zeta")
	print(table.concat(tbl,":"))

	t.printTable(tbl)

	local SDKAndroid = {}
	SDKAndroid.CALLBACK_RESULT = "result"
	SDKAndroid.CALLBACK_MSG = "msg"
	SDKAndroid.CALLBACK_GAMESERVER = "gameServer"
	local response = {
	  [SDKAndroid.CALLBACK_RESULT] = "hello",
	   SDKAndroid.CALLBACK_MSG = "World",
	  -- SDKAndroid."",CALLBACK_GAMESERVER = 
	}
	print(response[SDKAndroid.CALLBACK_RESULT])

	local t = {
		result = nil,
		msg = nil,
	}
	--注意两个差距
	print(t["result"])
	print(t[result])
	print(t.result)
end


return t
