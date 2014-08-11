local t = {}


local function print_table(tbl, flag, depth)
--- pairs 而不是 ipairs
	flag = flag or "**"
	depth = depth or 1
	for key,value in pairs(tbl) do
		print(flag .. "    " .. key, value)
		if type(value) == 'table' then
			flag = flag .. "**"
			depth = depth + 1
			if depth < 10 then
				print_table(value, flag, depth)
			end
		end
	end
end

function t:test( ... )
	print("testenv")

	print("**********current env", getfenv()) 
	print_table(getfenv())


	-- print("*******_G")
	-- print_table(getfenv()._G)

	local f=function (t,i) return os.getenv(i) end
	setmetatable(getfenv(),{__index=f})

	-- print(os.getenv("USERDOMAIN"))
	-- print(os.getenv("SystemRoot"))
	-- print(os.getenv("Os2LibPath"))
	-- print(os.getenv("ProgramFiles" ))
	-- print(os.getenv("APPDATA" ))
	-- print(os.getenv("ALLUSERSPROFILE" ))
	-- print(os.getenv("CommonProgramFiles" ))
	-- print(os.getenv("COMPUTERNAME" ))
	-- print(os.getenv("USERNAME"))
	-- print(os.getenv("USERPROFILE" ))
	-- print(os.getenv("ComSpec"))
	-- print(os.getenv("LOGONSERVER" ))
	-- print(os.getenv("NUMBER_OF_PROCESSORS" ))
	-- print(os.getenv("OS"))
	-- print(os.getenv("PATHEXT" ))
	-- print(os.getenv("PROCESSOR_ARCHITECTURE" ))
	-- print(os.getenv("PROCESSOR_IDENTIFIER" ))
	-- print(os.getenv("PROCESSOR_LEVEL" ))
	-- print(os.getenv("PROCESSOR_REVISION" ))
	-- print(os.getenv("USERDOMAIN"))
	-- print(os.getenv("SystemRoot" ))
	-- print(os.getenv("TEMP"))
	-- print (getfenv().__index)
	print(TEMP,USER,PATH)
end


return t