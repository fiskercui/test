testmoudle
-- 打印参数
for i = 1, select('#', ...) do
     print(select(i, ...))
end
 
local M = {}    -- 局部的变量
_G[moduleName] = M     -- 将这个局部变量最终赋值给模块名
 

 
-- //方案1
-- function M.new(r, i) return {r = r, i = i} end
-- M.i = M.new(0, 1)
-- function M.add(c1, c2)
--     return M.new(c1.r + c2.r, c1.i + c2.i)
-- end
-- function M.sub(c1, c2)
--     return M.new(c1.r - c2.r, c1.i - c2.i)
-- end


-- 方案二
--声明这个模块将会用到的全局函数，因为在setfenv之后将无法再访问他们，
--因此需要在设置之前先用本地变量获取。
-- local sqrt = mat.sqrt
-- local io = io

-- --在这句话之后就不再需要外部访问了。
-- setfenv(1,M)

-- --后面的函数和常量定义都无需模块限定符了。
-- i = {r = 0, i = 1}
-- function new(r,i) return {r = r, i = i} end
-- function add(c1,c2) 
--     return new(c1.r + c2.r,c1.i + c2.i)
-- end
 
-- function sub(c1,c2)
--     return new(c1.r - c2.r,c1.i - c2.i)
-- end

--方案三
package.loaded[modname] = M
--[[
和普通Lua程序块一样声明外部函数。
--]]
setfenv(1,M)

return complex  -- 返回模块的table	
