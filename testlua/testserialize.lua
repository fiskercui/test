local t = {}

local function table_size(tt)
  if type(tt) ~= "table" then
    return 0
  end

  local count = 0
  for k,v in pairs(tt) do
    count = count + 1
  end
  return count
end


local function serialize_obj(obj)
  local lua = ""
  local t = type(obj)
  -- print("sserialize_java type", t)
  if t == "number" or t == "boolean" then
    local sizesize = string.len(tostring(obj))
    -- print("number size size", sizesize)
    lua = lua .. sizesize .. tostring(obj)
  elseif t == "string" then
    local size = string.len(obj)
    local sizesize = string.len(tostring(size)) 
    lua = lua .. sizesize .. size .. obj
  elseif t == "table" then
  
    local tabelsize = table_size(obj)
    -- print("tablesize", tabelsize)
    lua = lua .. serialize_obj(tabelsize)
    -- print("tableSize", lua)
    for k,v in pairs(obj) do
      lua = lua .. serialize_obj(k) .. serialize_obj(v)
    end
  end
  return lua
end

local function  unserialize_string(ss, index)
  -- print("unserialize_string index:", ss, index)
  local sizesize = tonumber(string.sub(ss, index, index))
  -- print("index size size", sizesize)
  index = index + 1
  local size = tonumber(string.sub(ss, index, index+sizesize-1))
  -- print("222index size size",index, size, index+sizesize-1)
  index = index + sizesize
  local s =  string.sub(ss, index, index+size-1)
  -- print("3333index size size",index, index+index-1)
  index = index + size
  return s, index
end

local function  unserialize_number(ss, index)
  local sizesize = tonumber(string.sub(ss, index, index))
  index = index + 1
  local sizess = string.sub(ss, index, index+sizesize-1)
  index = index + sizesize
  -- print("iindex ------", index)
  return tonumber(sizess), index
end


local function  unserialize_table(lua)
  local index = 1

  local tablelua = {}
  local t = type(lua)
  if t=="nil" or lua == "" then
    return nil
  elseif t == "string" then
    local tableSize,index = unserialize_number(lua, index);
    -- print("heheheheheheh", tableSize)
    -- print("tableIndex", index)
    for i = 1, tableSize do
      sKeyString, index = unserialize_string(lua, index)
      -- print("tableIndex key", index)
      sValueString, index = unserialize_string(lua, index)
    -- print("tableIndex value", index)
      tablelua[sKeyString] = sValueString
    end
    return tablelua
  end
end

local function  print_table(obj)
    local t = type(obj)
    if t=="nil" or obj == "" then return nil end
    for k,v in pairs(obj) do
        print("",k,v)
    end
end


function t:test(...)
  print("serialize test")
  local productInfo = {}
  productInfo["appid"] = "真的没有关系"
  productInfo["appsecret"] = "**********"
  productInfo["描述"] = "sdfjdlsfj"
  productInfo["12我都是开放回家的考虑是否还多久开始发货家口"] = "hsdjkfhjkhjkhsdjfhk"
  productInfo["why123wehy"] = "hehehehe "
  local s  = serialize_obj(productInfo)
  print(s)

  print_table(unserialize_table(s))
end

return t



