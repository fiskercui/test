
require('pack')

local t =  {}

local sprite_fs = [[
varying vec2 v_texcoord;
varying vec4 v_color;
uniform sampler2D texture0;
uniform vec3 additive;

void main() {
	vec4 tmp = texture2D(texture0, v_texcoord);
	gl_FragColor.xyz = tmp.xyz * v_color.xyz;
	gl_FragColor.w = tmp.w;
	gl_FragColor *= v_color.w;
	gl_FragColor.xyz += additive.xyz * tmp.w;
}
]]

local node_fs =[[
abc=123
]]
-- z : zero-terminated string 
-- p : string preceded by length byte 
-- P : string preceded by length word 
-- a : string preceded by length size_t 
-- A : string 
-- f : float 
-- d : double 
-- n : Lua number 
-- c : char 
-- b : byte (unsigned char) 
-- h : short 
-- H : unsigned short 
-- i : int 
-- I : unsigned int 
-- l : long 
-- L : unsigned long

-- < : little endian 
-- > : big endian 
-- = : native endian
function t:test( ... )
	print("string test")
	print("sprite_fs type", type(sprite_fs))
	print("sprite_fs string", sprite_fs)
	print("node_fs string", node_fs)
	
	local __s = "123"
	print("string sub", string.sub(__s, 1,2))
	print("string sub", __s:sub(2,2))


	local __pack = string.pack("<bihP2", 0x59, 11, 1101, "", "中文")
	-- local __pack = string.pack("hello",1)
	print("pack type", type(__pack))
	for i=1, #__pack do
		-- print ("string ", i, string.sub(__pack, i,i))
	end
	print("pack", __pack)


	local tbl = {
		"hello",
		"wrold",
	}
	local __unpack = {unpack(tbl)}
	print("unpack type", type(__unpack))
	print("unpack", __unpack[1], __unpack[2])
end


return t
