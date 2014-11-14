local t = {}

local CURRENT_MODULE_NAME = ...

cc = cc or {}
cc.PACKAGE_NAME = string.sub(CURRENT_MODULE_NAME, 1, -6)
cc.VERSION = "3.3 RC0"
cc.FRAMEWORK_NAME = "quick-cocos2d-x"

function t:test( ... )
	print("testcomponent")
	require("cc.init")
	require("samples.mvc.src.main")
end


return t

