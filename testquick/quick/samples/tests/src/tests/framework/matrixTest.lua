
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
    printf("MatrixTest a = %s", a);
end

return MatrixTestScene
