
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
    printf("********MatrixTest a = %s", a);

    local t = { 1, 2,3, 4, 5,6,7,8,9,10, 11, 12,13,14,15,16}
    local abc = cc.Director:getInstance():loadMatrix(1, t);
    -- local mat = cc.Mat4:new()
    -- debug(mat)

end

return MatrixTestScene
