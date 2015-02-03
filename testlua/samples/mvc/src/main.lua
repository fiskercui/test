
function __G__TRACKBACK__(errorMessage)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(errorMessage) .. "\n")
    print(debug.traceback("", 2))
    print("----------------------------------------")
end

-- require("app.MyApp").new():run()

--comment by weihua.cui

require("samples.mvc.src.app.MyApp").new():run()

