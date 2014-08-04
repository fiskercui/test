local url={parsed={}} --存储decode出来的key-value

--private
local function escape(w)
    pattern="[^%w%d%._%-%* ]"
    s=string.gsub(w,pattern,function(c)
        local c=string.format("%%%02X",string.byte(c))
        return c
    end)
    s=string.gsub(s," ","+")
    return s
end

local function detail_escape(w)
    local t={}
    for i=1,#w do
        c = string.sub(w,i,i)
        b,e = string.find(c,"[%w%d%._%-'%* ]")
        if not b then
            t[#t+1]=string.format("%%%02X",string.byte(c))
        else
            t[#t+1]=c
        end
    end
    s = table.concat(t)
    s = string.gsub(s," ","+")
    return s
end

local function unescape(w)
    s=string.gsub(w,"+"," ")
    s,n = string.gsub(s,"%%(%x%x)",function(c)
        return string.char(tonumber(c,16))
    end)
    return s
end

---[=[
--public function
function url:new()
    local u={}    --对象
    u.old= nil    --上一次decode 字符串的值
    u.de = nil    --decode字符串后的结果值
    u.en = nil    --encode字符串后的结果值
    u.enold = nil --上一次encode 字符串的值
    u.len = 0     --记录parsed map的长度


    --设置metatable
    setmetatable(u,{__index=self})
    return u
end

function url:decode(line)
    assert(line == nil or type(line) == "string")
    if self.old == line then return print("url:decode have cache") ,self.de end
    if not line then return self.de end

    self.parsed=nil
    self.len = 0
    self.parsed={}
    for k,v in string.gmatch(line,"([^&=]+)=([^&=]+)") do
        self.len = self.len + 1
        self.parsed[k] = unescape(v)
    end

    if  self.len == 0 then return nil  end

    local r={}
    for k,v in pairs(self.parsed) do
        r[#r+1] = k.."="..v
    end
    self.de=table.concat(r,"&")
    self.old=line
    return self.de
end

function url:encode(t)
    if(type(t) == "string") then
            if t == self.enold then
                print("url:encode have cache")
                return self.en
            end

            local r={}
            for k,v in string.gmatch(t,"([^&=]+)=([^&=]+)") do
                r[#r+1] = escape(k) .."=".. escape(v)
            end
            self.en = table.concat(r,"&")
            self.enold = t
            return self.en
    elseif type(t) ~= "table" then return nil
    else
        local r = {}
        for k , v in pairs(t) do
            r[#r+1] = escape(k) .."=".. escape(v)

        end
        self.en = table.concat(r,"&")

        return self.en
    end
end

function url:parse(line)
    assert(line == nil or type(line) == "string")
    if not line then
        if self.len == 0 then return nil
        else return self.parsed end
    end
    if url:decode(line) == nil then return nil end
    return self.parsed
end

function url:get(k)
    if self.len > 0 then
        return self.parsed[k]
    else
        return nil
    end
end

--测试私有函数
test="泰囧<>2a+b=c.*!^()"
test2="tn=baiduhome_pg&ie=utf-8&bs=lua%26%3D+%E5%8C%B9%E9%85%8D%E6%B1%89%E5%AD%97&f=8&rsv_bp=1&rsv_spt=1&wd=%E6%B3%B0%E5%9B%A7%3C%3E2a%2Bb+%3D+c.*%21%5E%28%29&rsv_n=2&rsv_sug3=1&rsv_sug1=1&rsv_sug4=168&inputT=897"
test2="%7B%22result%22%3A0%2C%22lastGameServer%22%3A%22%22%2C%22msg%22%3A%22ok%22%2C%22gameServers%22%3A%5B%7B%22gamezoneID%22%3A14%2C%22name%22%3A%22%3F%3F+++1%3F%22%2C%22IP%22%3A%22113.107.148.124%3A5001%22%2C%22load%22%3A0%2C%22ext%22%3A0%7D%2C%7B%22gamezoneID%22%3A25%2C%22name%22%3A%22%3F%3F+++2%3F%22%2C%22IP%22%3A%22113.107.148.124%3A5002%22%2C%22load%22%3A0%2C%22ext%22%3A0%7D%2C%7B%22gamezoneID%22%3A26%2C%22name%22%3A%22%3F%3F+++3%3F%22%2C%22IP%22%3A%22113.107.148.124%3A5003%22%2C%22load%22%3A0%2C%22ext%22%3A0%7D%2C%7B%22gamezoneID%22%3A27%2C%22name%22%3A%22%3F%3F+++4%3F%22%2C%22IP%22%3A%22113.107.167.235%3A5001%22%2C%22load%22%3A0%2C%22ext%22%3A0%7D%2C%7B%22gamezoneID%22%3A28%2C%22name%22%3A%22%3F%3F+++5%3F%22%2C%22IP%22%3A%22113.107.167.235%3A5002%22%2C%22load%22%3A0%2C%22ext%22%3A0%7D%2C%7B%22gamezoneID%22%3A29%2C%22name%22%3A%22%3F%3F+++6%3F%22%2C%22IP%22%3A%22113.107.167.235%3A5003%22%2C%22load%22%3A0%2C%22ext%22%3A0%7D%5D%7D"

---[[
local u = url:new()
d=u:decode(test2)
print("decode test2 ret:",test2);
print("decode test2 ret:",d);
--]=]

local hex_to_char = function(x)
  return string.char(tonumber(x, 16))
end

local unescape = function(url)
  return url:gsub("%%(%x%x)", hex_to_char)
end


print(unescape(test2)) 

function urlencode(str)
   if (str) then
      str = string.gsub (str, "\n", "\r\n")
      str = string.gsub (str, "([^%w ])",
         function (c) return string.format ("%%%02X", string.byte(c)) end)
      str = string.gsub (str, " ", "+")
   end
   return str    
end

test3="{\"result\":0,\"lastGameServer\":\"\",\"msg\":\"ok\",\"gameServers\":[{\"gamezoneID\":14,\"name\":\"混服   1区\",\"IP\":\"113.107.148.124:5001\",\"load\":0,\"ext\":0},{\"gamezoneID\":25,\"name\":\"混服   2区\",\"IP\":\"113.107.148.124:5002\",\"load\":0,\"ext\":0},{\"gamezoneID\":26,\"name\":\"混服   3区\",\"IP\":\"113.107.148.124:5003\",\"load\":0,\"ext\":0},{\"gamezoneID\":27,\"name\":\"混服   4区\",\"IP\":\"113.107.167.235:5001\",\"load\":0,\"ext\":0},{\"gamezoneID\":28,\"name\":\"混服   5区\",\"IP\":\"113.107.167.235:5002\",\"load\":0,\"ext\":0},{\"gamezoneID\":29,\"name\":\"混服   6区\",\"IP\":\"113.107.167.235:5003\",\"load\":0,\"ext\":0}]}"

local decodeURI
do
    local char, gsub, tonumber = string.char, string.gsub, tonumber
    local function _(hex) return char(tonumber(hex, 16)) end

    function decodeURI(s)
        s = gsub(s, '%%(%x%x)', _)
        return s
    end
end


local  function test_string(s, orgin, replace)
    local new_string = ""
    for i=1,#s do
        local c = string.sub(s, i, i)
        if c == orgin then
            new_string = new_string .. replace
        else
            new_string = new_string .. c
        end
    end
    return new_string
end


s = test_string(test2, '.', '%2E')
print("sssss",s)
decode_s = decodeURI(s)
print("decode",decode_s)


