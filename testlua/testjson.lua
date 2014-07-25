local t = {}

local json = require('base.json')


local function dump(tb)
	if type(tb) ~= "table" then return end
	for k,v in pairs(tb) do
		print(k,v)
		if type(v) == "table" then	
			dump(v)
		end
	end
end


function t:test(...)
	print("json test")
	local t = {
		a = 1,
		b = 2,
		c = 3,
	}
	print(json.encode(t))


	local s = '{ "result":1, "msg":"its not ok", "token":"abc", \
			"gameServers":                   \
			[                   \
				{                   \
					"ip":"10.10.3.123:5001",                   \
					"name":"1 区月光宝地",                   \
					"load":50,                   \
					"ext":0                   \
				},                   \
				{                   \
					"ip":"10.10.3.223:5001",                   \
					"name":"2 区圣火巢穴",                   \
					"load":70,                   \
					"ext":0                   \
				}				                   \
			]}'        
	local ts = json.decode(s)
	DEBUG=1
	dump(ts)


	local tb = json.decode('{"a":1,"b":"ss","c":{"c1":1,"c2":2},"d":[10,11],"1":100}')
	print("tb",tb)

	dump(tb)
	
end





return t