
<<<<<<< HEAD
require("samples.mvc.src.config")

require("cc.init")
-- require("framework.shortcodes")
require("cc.init")
=======
-- require("config")
-- require("framework.init")
-- require("framework.shortcodes")
-- require("framework.cc.init")
>>>>>>> f81383bbd9d8a90c6ced933f4425d916b722237d

local MyApp = class("MyApp", cc.mvc.AppBase)

function MyApp:ctor()
<<<<<<< HEAD
=======
    print("self" ,cc.mvc.AppBase)
    print("MyApp super",MyApp.super)
    print("MyApp super ctor", MyApp.super.ctor)
>>>>>>> f81383bbd9d8a90c6ced933f4425d916b722237d
    MyApp.super.ctor(self)
    self.objects_ = {}
end

function MyApp:run()
<<<<<<< HEAD
    --comment by weihua.cui
=======
    -- comment by weihua.cui
>>>>>>> f81383bbd9d8a90c6ced933f4425d916b722237d
    -- cc.FileUtils:getInstance():addSearchPath("res/")
    -- display.addSpriteFrames(GAME_TEXTURE_DATA_FILENAME, GAME_TEXTURE_IMAGE_FILENAME)
    self:enterScene("MainScene")
end

function MyApp:setObject(id, object)
    assert(self.objects_[id] == nil, string.format("MyApp:setObject() - id \"%s\" already exists", id))
    self.objects_[id] = object
end

function MyApp:getObject(id)
    assert(self.objects_[id] ~= nil, string.format("MyApp:getObject() - id \"%s\" not exists", id))
    return self.objects_[id]
end

function MyApp:isObjectExists(id)
    return self.objects_[id] ~= nil
end

return MyApp
