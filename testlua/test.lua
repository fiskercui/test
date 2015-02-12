require('base.function')
require('base.class')
require('base.json')

-- require('pack')
require('base.debug')-- require('pack')
require('base.string')

local tests = {
	-- "testdebug",
	"testmetatable",
	-- "testutf8",
	-- "testserialize",
	-- "testenv",
	-- "testtable",
	-- "testimport",
	-- "testfunction",
	-- "testmvc",
	-- "testcomponent",
	-- "testimport",
	-- "testfunction",
	-- "teststring",
	-- "testjson"
	-- "testbytearray"
}

-- local a = {1,2,3}
-- local a1, b1, c1 = unpack(a)

-- print a1
-- print b1
-- print c1


function  testLeap(...)
	
end

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