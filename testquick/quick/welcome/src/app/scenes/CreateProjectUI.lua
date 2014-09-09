--
-- FILE: CreateProjectUI.lua
-- DATE: 2014-08-21
--

local EditBoxLite = import(".EditBoxLite")
local eventDispatcher = cc.Director:getInstance():getEventDispatcher()

local CreateProjectUI = class("CreateProjectUI", function()
        return cc.LayerColor:create(cc.c4b(56, 56, 56, 250))
    end)

-- settings
local font = "Monaco"
local fontSize = 25
local images = {
    normal = "#ButtonNormal.png",
    pressed = "#ButtonPressed.png",
    disabled = "#ButtonDisabled.png",
}
local checkboxImages = {
    off = "CheckBoxButton2Off.png",
    on = "CheckBoxButton2On.png",
}

--
function CreateProjectUI:ctor()
    self:addNodeEventListener(cc.NODE_EVENT, function(e) 
            if e.name == "enter" then self:onEnter() 
            elseif e.name == "exit" then 
                eventDispatcher:removeEventListener(self.eventListenerCustom_)
            end 
        end)
end

function CreateProjectUI:onEnter()
    
    -- project location:
    ui.newTTFLabel({
        text = "Choose Project Location:",
        size = fontSize,
        font = font,
        color = display.COLOR_WHITE,
        x = 40,
        y = display.top - 55,
        align = ui.TEXT_ALIGN_LEFT,
        })
    :addTo(self)

    local t = {
        image = "#ButtonNormal.png",
        size = cc.size(display.width-250, 40),
        x = 40,
        y = display.top - 120,
    }
    local locationEditbox
    if device.platform == "windows" then
        locationEditbox = ui.newEditBox(t)
    elseif device.platform == "mac" then
        locationEditbox = EditBoxLite.new(t)
    end

    locationEditbox:setAnchorPoint(0,0)
    self:addChild(locationEditbox)

    local selectButton = cc.ui.UIPushButton.new(images, {scale9 = true})
    selectButton:setAnchorPoint(0,0)
    selectButton:setButtonSize(150, 40)
    :setButtonLabel("normal", ui.newTTFLabel({
            text = "Select",
            size = fontSize,
            font = font,
        }))
    :pos(display.right - 170, display.top - 120)
    :addTo(self)
    :onButtonClicked(function()
        local filedialog = PlayerProtocol:getInstance():getFileDialogService()
        local locationDirectory = filedialog:openDirectory("Choose Localtion", "")
        if string.len(locationDirectory) > 0 then
            locationEditbox:setText(locationDirectory)
        end
    end)


    -- package name:

    ui.newTTFLabel({
        text = "Project package name: (etc: com.mycomp.games.mygame)",
        size = fontSize,
        font = font,
        color = display.COLOR_WHITE,
        x = 40,
        y = display.top - 155,
        align = ui.TEXT_ALIGN_LEFT,
        })
    :addTo(self)

    local packageEditbox = ui.newEditBox({
        image = "#ButtonNormal.png",
        size = cc.size(display.width-250, 40),
        x = 40,
        y = display.top - 220,
    })
    packageEditbox:setAnchorPoint(0,0)
    self:addChild(packageEditbox)

    -- screen direction:

    ui.newTTFLabel({
        text = "Screen Direction:",
        size = fontSize,
        font = font,
        color = display.COLOR_WHITE,
        x = 40,
        y = display.top - 255,
        align = ui.TEXT_ALIGN_LEFT,
        })
    :addTo(self)

    local portaitCheckBox = 
    cc.ui.UICheckBoxButton.new(checkboxImages)
        :setButtonLabel(cc.ui.UILabel.new({text = "Portait", size = fontSize,  color = display.COLOR_WHITE}))
        :setButtonLabelOffset(70, 0)
        :setButtonLabelAlignment(display.CENTER)
        :align(display.LEFT_CENTER, 40, display.cy)
        :onButtonClicked(function() self.landscapeCheckBox:setButtonSelected(not self.portaitCheckBox:isButtonSelected()) end)
        :addTo(self)

    local landscapeCheckBox = 
    cc.ui.UICheckBoxButton.new(checkboxImages)
        :setButtonLabel(cc.ui.UILabel.new({text = "Landscape", size = fontSize,  color = display.COLOR_WHITE}))
        :setButtonLabelOffset(100, 0)
        :setButtonLabelAlignment(display.CENTER)
        :align(display.LEFT_CENTER, 200, display.cy)
        :onButtonClicked(function() self.portaitCheckBox:setButtonSelected(not self.landscapeCheckBox:isButtonSelected()) end)
        :addTo(self)

    portaitCheckBox:setButtonSelected(true)
    self.portaitCheckBox = portaitCheckBox
    self.landscapeCheckBox = landscapeCheckBox


    -- ok or cancel

    local button = cc.ui.UIPushButton.new(images, {scale9 = true})
    button:setAnchorPoint(0,0)
    button:setButtonSize(150, 40)
    :setButtonLabel("normal", ui.newTTFLabel({
            text = "Cancel",
            size = fontSize,
            font = font,
        }))
    :pos(40, 30)
    :addTo(self)
    :onButtonClicked(function()
        self:removeFromParent(true)
    end)

    local createProjectbutton = cc.ui.UIPushButton.new(images, {scale9 = true})
    createProjectbutton.currState = 1
    createProjectbutton:setAnchorPoint(0,0)
    createProjectbutton:setButtonSize(250, 40)
    :setButtonLabel("normal", ui.newTTFLabel({
            text = "Create Project",
            size = fontSize,
            font = font,
        }))
    :pos(display.right - 270, 30)
    :addTo(self)
    :onButtonClicked(function()
        if createProjectbutton.currState == 1 then
            if locationEditbox:getText() and packageEditbox:getText() then
                local t = packageEditbox:getText():splitBySep('.')
                self.projectFolder = locationEditbox:getText() .. '/' .. t[#t]

                local projectConfig = ProjectConfig:new()
                projectConfig:setProjectDir(self.projectFolder)
                projectConfig:changeFrameOrientationToPortait()
                self.projectConfig = projectConfig

                local scriptPath = cc.player.quickRootPath .. "quick/bin/create_project.sh"
                if device.platform == "windows" then
                    scriptPath = cc.player.quickRootPath .. "quick/bin/create_project.bat"
                end

                local screenDirection = " -r portrait "
                if self.landscapeCheckBox:isButtonSelected() then
                    projectConfig:changeFrameOrientationToLandscape()
                    screenDirection = " -r landscape "
                end
                local arguments = " -p " .. packageEditbox:getText() .. " -f " .. " -o " .. self.projectFolder .. screenDirection
                local taskId = tostring(os.time())
                local task = PlayerProtocol:getInstance():getTaskService():createTask(taskId, scriptPath, arguments)
                eventDispatcher:addEventListenerWithFixedPriority(cc.EventListenerCustom:create(taskId, 
                            function()
                                if task:getResultCode() == 0 then
                                    createProjectbutton:setButtonLabelString("normal", "Open ...")
                                    createProjectbutton.currState = 2
                                end
                            end), 
                           1)
                task:run()
            else
                local messageBox = PlayerProtocol:getInstance():getMessageBoxService()
                messageBox:showMessageBox("player v3", "please fill all infomation..")
            end
        else
            PlayerProtocol:getInstance():openNewPlayerWithProjectConfig(self.projectConfig)
        end
    end)

    -- keyboard event
    local event = function(e)
        local data = json.decode(e:getDataString())
        if data == nil then return end

        -- esc keyc = 6
        if data.data == 6 then self:removeFromParent(true) end
    end
    self.eventListenerCustom_ = cc.EventListenerCustom:create("APP.EVENT", event)
    eventDispatcher:addEventListenerWithFixedPriority(self.eventListenerCustom_, 1)
end


return CreateProjectUI