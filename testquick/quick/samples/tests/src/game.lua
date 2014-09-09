
require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    cc.FileUtils:getInstance():addSearchPath("res/")

    game.enterMainScene()
end

function game.createMenu(items, callback)
    local node = display.newNode()
    local baseY = display.cy - 100
    for i, item in ipairs(items) do
        local label = cc.ui.UIPushButton.new()
            :setButtonLabel(
                cc.ui.UILabel.new({
                    text = item, size = 40,
                    color = display.COLOR_BLUE}))
        :onButtonPressed(function(event)
            event.target:getButtonLabel():setColor(display.COLOR_RED)
        end)
        :onButtonRelease(function(event)
            event.target:getButtonLabel():setColor(display.COLOR_BLUE)
        end)
        :onButtonClicked(function(event)
            callback(item)
        end)
        :align(display.LEFT_CENTER, 0, baseY - 60*i)
        :addTo(node)
    end

    node:setPosition(display.cx, display.cy)

    return node
end

function game.exit()
    os.exit()
end

function game.enterMainScene()
    display.replaceScene(require("scenes.MainScene").new(), "fade", 0.6, display.COLOR_WHITE)
end

function game.createSceneClass(name)
    local cls = class(name, function()
        return display.newScene(name)
    end)

    function cls:prepare(args)
        cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = "RETURN",
                color = cc.c3b(255, 0, 0)}))
            :align(display.CENTER, display.right - 80, display.bottom + 30)
            :onButtonClicked(function()
                display.replaceScene(require("scenes.MainScene").new())
                end)
            :addTo(self)

        cc.ui.UIPushButton.new()
            :setButtonLabel(cc.ui.UILabel.new({text = "====   " .. cls.__cname .. "   ====",
                color = cc.c3b(0, 255, 0)}))
            :align(display.CENTER, display.cx, display.top - 30)
            :addTo(self)

        if args and args.description then
            cc.ui.UIPushButton.new()
                :setButtonLabel(cc.ui.UILabel.new({text = args.description,
                    size = 20,
                    color = cc.c3b(0, 160, 0)}))
                :align(display.CENTER, display.cx, display.top - 60)
                :addTo(self)
        end
    end


    function cls:runTest(name)
        printf("----------------------------------------")
        printf("-- run test %s", name)
        print("--")
        name = string.gsub(name, " ", "_")
        if self.beforeRunTest then self:beforeRunTest() end
        local m = self[name .. "Test"]
        m(self)
    end

    return cls
end

function bin2hex(bin)
    local t = {}
    for i = 1, string.len(bin) do
        local c = string.byte(bin, i, i)
        t[#t + 1] = string.format("%02x", c)
    end
    return table.concat(t, " ")
end
