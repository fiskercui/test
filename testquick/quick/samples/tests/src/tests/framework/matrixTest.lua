
local MatrixTestScene = game.createSceneClass("MatrixTestScene")

function MatrixTestScene:ctor()
    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "Matrix",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function MatrixTestScene:beforeRunTest()
    printf("MatrixTestScene beforeRunTest")
end

function MatrixTestScene:MatrixTest()
    local a = "123"
    printf("********MatrixTest a = %xs", a);

    local t = { 1, 2,3, 4, 5,6,7,8,9,10, 11, 12,13,14,15,16}
        local abc = cc.Director:getInstance():loadMatrix(1, t);
    dump(getmetatable(cc.Mat4), "cc.Mat4")
    -- local aMatrix = cc.Mat4:new("cc.Mat4")

    local aString = "123"
    local bString = "456"
    local testSchdule = cc.Scheduler:new(aString, bString)
    -- local aMatrix = cc.Mat4:new{t}
    -- local abc = cc.Director:getInstance():loadMatrix(1, t);
    -- local mat = cc.Mat4:new()
    -- debug(mat)

end

return MatrixTestScene
