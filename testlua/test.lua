
require('base.class')
-- require('pack')

local tests = {
	-- "testdebug",
	-- "testmetatable",
	-- "testserialize",
	-- "testenv",
	-- "testtable",
	-- "testfunction",
	-- "teststring",
	"testbytearray"
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