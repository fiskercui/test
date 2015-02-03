
function __G__TRACKBACK__(errorMessage)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(errorMessage) .. "\n")
    print(debug.traceback("", 2))
    print("----------------------------------------")
end

<<<<<<< HEAD
-- require("app.MyApp").new():run()

--comment by weihua.cui

require("samples.mvc.src.app.MyApp").new():run()

=======

-- require("mobdebug").start()

require("samples.mvc.src.app.MyApp").new():run()
>>>>>>> f81383bbd9d8a90c6ced933f4425d916b722237d
