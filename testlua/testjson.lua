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

	print("____________")
	local s = "%7B%22result%22%3A0%2C%22lastGameServer%22%3A%22%22%2C%22msg%22%3A%22ok%22%2C%22gameServers%22%3A%5B%7B%22gamezoneID%22%3A14%2C%22name%22%3A%22%3F%3F+++1%3F%22%2C%22IP%22%3A%22113.107.148.124%3A5001%22%2C%22load%22%3A0%2C%22ext%22%3A0%7D%2C%7B%22gamezoneID%22%3A25%2C%22name%22%3A%22%3F%3F+++2%3F%22%2C%22IP%22%3A%22113.107.148.124%3A5002%22%2C%22load%22%3A0%2C%22ext%22%3A0%7D%2C%7B%22gamezoneID%22%3A26%2C%22name%22%3A%22%3F%3F+++3%3F%22%2C%22IP%22%3A%22113.107.148.124%3A5003%22%2C%22load%22%3A0%2C%22ext%22%3A0%7D%2C%7B%22gamezoneID%22%3A27%2C%22name%22%3A%22%3F%3F+++4%3F%22%2C%22IP%22%3A%22113.107.167.235%3A5001%22%2C%22load%22%3A0%2C%22ext%22%3A0%7D%2C%7B%22gamezoneID%22%3A28%2C%22name%22%3A%22%3F%3F+++5%3F%22%2C%22IP%22%3A%22113.107.167.235%3A5002%22%2C%22load%22%3A0%2C%22ext%22%3A0%7D%2C%7B%22gamezoneID%22%3A29%2C%22name%22%3A%22%3F%3F+++6%3F%22%2C%22IP%22%3A%22113.107.167.235%3A5003%22%2C%22load%22%3A0%2C%22ext%22%3A0%7D%5D%7D"
	print(json.decode(s))
	
end





return t