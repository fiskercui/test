local t = {}


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
end

return t


