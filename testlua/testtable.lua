
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
	for key,value in pairs(t.tbltest) do
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
end


return t
