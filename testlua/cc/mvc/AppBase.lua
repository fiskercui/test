
local AppBase = class("AppBase")

AppBase.APP_ENTER_BACKGROUND_EVENT = "APP_ENTER_BACKGROUND_EVENT"
AppBase.APP_ENTER_FOREGROUND_EVENT = "APP_ENTER_FOREGROUND_EVENT"

function AppBase:ctor(appName, packageRoot)
    cc(self):addComponent("components.behavior.EventProtocol"):exportMethods()

<<<<<<< HEAD
    self.name = appName
    self.packageRoot = packageRoot or "app"

    -- add by weihua.cui
    self.packageRoot = packageRoot or "samples.mvc.src.app"

=======
    -- self.name = nil
    -- self.name.abc = {}

    self.name = appName
    self.packageRoot = packageRoot or "app"
    -- --add by weihua.cui
    -- self.packageRoot = "samples.mvc.src.app"

    print("AppBase name", self.name)

    print("AppBase packageRoot", packageRoot)
    print("AppBase packageRoot", self.packageRoot)

    --comment by weihua.cui
>>>>>>> f81383bbd9d8a90c6ced933f4425d916b722237d
    -- local eventDispatcher = cc.Director:getInstance():getEventDispatcher()
    -- local customListenerBg = cc.EventListenerCustom:create(cc.EVENT_COME_TO_BACKGROUND,
    --                             handler(self, self.onEnterBackground))
    -- eventDispatcher:addEventListenerWithFixedPriority(customListenerBg, 1)
    -- local customListenerFg = cc.EventListenerCustom:create(cc.EVENT_COME_TO_FOREGROUND,
    --                             handler(self, self.onEnterForeground))
    -- eventDispatcher:addEventListenerWithFixedPriority(customListenerFg, 1)
<<<<<<< HEAD

=======
>>>>>>> f81383bbd9d8a90c6ced933f4425d916b722237d
    self.snapshots_ = {}

    -- set global app
    app = self
end

function AppBase:run()
end

function AppBase:exit()
<<<<<<< HEAD
    cc.Director:getInstance():endToLua()
=======
    --comment by weihua.cui
    -- cc.Director:getInstance():endToLua()
>>>>>>> f81383bbd9d8a90c6ced933f4425d916b722237d
    if device.platform == "windows" or device.platform == "mac" then
        os.exit()
    end
end

function AppBase:enterScene(sceneName, args, transitionType, time, more)
    local scenePackageName = self. packageRoot .. ".scenes." .. sceneName
<<<<<<< HEAD
    print("scenePackageName", scenePackageName)
    local sceneClass = require(scenePackageName)
    local scene = sceneClass.new(unpack(checktable(args)))
=======
    print("scenePackageName:", scenePackageName)
    -- comment by weihua.cui 
    -- local sceneClass = require(scenePackageName)
    local sceneClass = require("samples.mvc.src.app.scenes.MainScene")

    print("args type", type(checktable(args)))
    -- print("args type", typeunpack(checktable(args)))

    print("args", unpack(checktable(args)))
    local scene = sceneClass.new(unpack(checktable(args)))

    print("AppBase enterScene")
>>>>>>> f81383bbd9d8a90c6ced933f4425d916b722237d
    display.replaceScene(scene, transitionType, time, more)
end

function AppBase:createView(viewName, ...)
    local viewPackageName = self. packageRoot .. ".views." .. viewName
    local viewClass = require(viewPackageName)
    return viewClass.new(...)
end

function AppBase:makeLuaVMSnapshot()
    self.snapshots_[#self.snapshots_ + 1] = LuaStackSnapshot()
    while #self.snapshots_ > 2 do
        table.remove(self.snapshots_, 1)
    end

    return self
end

function AppBase:checkLuaVMLeaks()
    assert(#self.snapshots_ >= 2, "AppBase:checkLuaVMLeaks() - need least 2 snapshots")
    local s1 = self.snapshots_[1]
    local s2 = self.snapshots_[2]
    for k, v in pairs(s2) do
        if s1[k] == nil then
            print(k, v)
        end
    end

    return self
end

function AppBase:onEnterBackground()
    self:dispatchEvent({name = AppBase.APP_ENTER_BACKGROUND_EVENT})
end

function AppBase:onEnterForeground()
    self:dispatchEvent({name = AppBase.APP_ENTER_FOREGROUND_EVENT})
end

return AppBase
