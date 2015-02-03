
local t = {}


function t:test( ... )
	print("import test")

	local beginTime = os.clock()
	for i=1,10000 do
		require("base.function")
	end
	print("require module cost ", os.clock() - beginTime)

	local beginTime = os.clock()
	for i=1,10000 do
		require("base.function")
	end
	print("import module cost ", os.clock() - beginTime)

	local beginTime = os.clock()
	for i=1,10000 do
		import(".base.function", ...)
	end
	print("import no module cost ", os.clock() - beginTime)

end



return t