-- author: weihua.cui
-- date: 2015.5.25

local t = {}

function t:test()
	print("start test coroutine")
	local co = coroutine.create(function ()
		-- body

		print("hi")
		-- print(coroutine.status(co))
	end)

	print(co)
	print("co status", coroutine.status(co))
	print("co resume ",coroutine.resume(co))
	print("co status",coroutine.status(co))


	local co2 = coroutine.create(
		function ()
			for i =1, 10 do
				print("ci",i)
				coroutine.yield()
			end
		end
	)

	coroutine.resume(co2)
	print("co status", coroutine.status(co2))
	coroutine.resume(co2)
	coroutine.resume(co2)
	coroutine.resume(co2)
	coroutine.resume(co2)
	coroutine.resume(co2)
	coroutine.resume(co2)
	coroutine.resume(co2)
	coroutine.resume(co2)
	coroutine.resume(co2)
	coroutine.resume(co2)
	coroutine.resume(co2)
	print("co2 return status:", coroutine.resume(co2))


	print("end test coroutine")
end











return t 