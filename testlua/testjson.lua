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


	local response = '{	"result":0,		 \
				"cn":"我是中文",			\
				"token":"1d2eccd9f16d1db1",			\
				"uname":"0", \
				"lastGameServer":"",	\
				"en":"i am english",	\
				"uin":"0",	\
				"msg":"OK",	\
				"gameServers":[				\
				{											\
					"name":"1区月光宝地",						\
					"IP":"113.107.167.207:5001",			\
					"load":0,								\
					"ext":0									\
				},											\
				{											\
					"name":"2区圣火巢穴",						\
					"IP":"113.107.167.207:5002",			\
					"load":0,								\
					"ext":0									\
				},											\
				{											\
					"name":"3区水雾山脉",						\
					"IP":"113.107.167.207:5003",			\
					"load":0,								\
					"ext":0									\
				}											\
				]											\
			}'													
	print("response", json.decode(response))

	dump(json.decode(response))
	
end





return t