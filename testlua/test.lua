require('base.function')
require('base.class')
require('base.json')


-- require('pack')

local tests = {
	-- "testdebug",
	-- "testmetatable",
	-- "testutf8",
	-- "testserialize",
	-- "testenv",
	-- "testtable",
	-- "testimport",
	-- "testfunction",
	"testmvc",
	-- "testfunction",
	-- "teststring",
	-- "testjson"
	-- "testbytearray"
}

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