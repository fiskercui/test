
local PlayDuelController = import("..controllers.PlayDuelController")

-- local MainScene = class("MainScene", function()
<<<<<<< HEAD
--     return display.newScene("MainScene")
=======
--     -- return display.newScene("MainScene")
>>>>>>> f81383bbd9d8a90c6ced933f4425d916b722237d
-- end)

local MainScene = class("MainScene")

<<<<<<< HEAD
function MainScene:ctor()
    -- display.newColorLayer(cc.c4b(255, 255, 255, 255)):addTo(self)
=======

function MainScene:ctor()
    display.newColorLayer(cc.c4b(255, 255, 255, 255)):addTo(self)
>>>>>>> f81383bbd9d8a90c6ced933f4425d916b722237d

    -- add controller
    self:addChild(PlayDuelController.new())

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonSize(200, 80)
        :setButtonLabel(cc.ui.UILabel.new({text = "REFRESH"}))
        :onButtonPressed(function(event)
            event.target:setScale(1.1)
        end)
        :onButtonRelease(function(event)
            event.target:setScale(1.0)
        end)
        :onButtonClicked(function()
            app:enterScene("MainScene", nil, "flipy")
        end)
        :pos(display.cx, display.bottom + 100)
        :addTo(self)
end

function MainScene:onEnter()
end

function MainScene:onExit()
end

return MainScene
