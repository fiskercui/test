
local tests = {
	-- "testdebug",
	-- "testmetatable",
	-- "testserialize",
	-- "testenv",
	-- "testtable"
	"testfunction"
}

print(table.maxn(tests))
print(#tests)

function  startAllTests()
	print("-----------initAllTests")
	-- for i=1,10 do
	-- 	print(i)
	-- end
	for i=1, #tests do 
		local t = require(tests[i])
		t:test()
	end
end

startAllTests()