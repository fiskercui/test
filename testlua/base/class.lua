-- class() 的这种用法让我们可以在 C++ 对象基础上任意扩展行为。

-- 既然是继承，自然就可以覆盖 C++ 对象的方法：

-- ~~~ lua

-- function Toolbar:setPosition(x, y)
--     -- 由于在 Toolbar 继承类中覆盖了 CCNode 对象的 setPosition() 方法
--     -- 所以我们要用以下形式才能调用到 CCNode 原本的 setPosition() 方法
--     getmetatable(self).setPosition(self, x, y)

--     printf("x = %0.2f, y = %0.2f", x, y)
-- end

-- ~~~

-- **注意:** Lua 继承类覆盖的方法并不能从 C++ 调用到。也就是说通过 C++ 代码调用这个 CCNode 对象的 setPosition() 方法时，并不会执行我们在 Lua 中定义的 Toolbar:setPosition() 方法。

-- @param string classname 类名
-- @param [mixed super] 父类或者创建对象实例的函数

-- @return table

-- ]]
function class(classname, super)
    local superType = type(super)
    local cls

    if superType ~= "function" and superType ~= "table" then
        superType = nil
        super = nil
    end

    if superType == "function" or (super and super.__ctype == 1) then
        -- inherited from native C++ Object
        cls = {}

        if superType == "table" then
            -- copy fields from super
            for k,v in pairs(super) do cls[k] = v end
            cls.__create = super.__create
            cls.super    = super
        else
            cls.__create = super
            cls.ctor = function() end
        end

        cls.__cname = classname
        cls.__ctype = 1

        function cls.new(...)
            local instance = cls.__create(...)
            -- copy fields from class to native object
            for k,v in pairs(cls) do instance[k] = v end
            instance.class = cls
            instance:ctor(...)
            return instance
        end

    else
        -- inherited from Lua Object
        if super then
            cls = {}
            setmetatable(cls, {__index = super})
            cls.super = super
        else
            cls = {ctor = function() end}
        end

        cls.__cname = classname
        cls.__ctype = 2 -- lua
        cls.__index = cls

        function cls.new(...)
            local instance = setmetatable({}, cls)
            instance.class = cls
            instance:ctor(...)
            return instance
        end
    end

    return cls
end
