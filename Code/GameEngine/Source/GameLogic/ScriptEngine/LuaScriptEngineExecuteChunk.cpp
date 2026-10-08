// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /GX-
//
// ?ExecuteChunk@LuaScriptEngine@@QAEXPADHABVAsciiString@@@Z @0x003340C1 57B: Lua
// dobuffer helper calling lua_dobuffer then lua_settop 0. Evidence: GetStr via
// m_data+8 or g_Rva0107301CEmptyString, lua_dobuffer 0x0074DD00,
// lua_settop 0x00746F40, this+0xC lua_State, caller 0x003345BE passes
// buffer size and AsciiString chunkname.
// Names: WorldBuilder's LuaScriptEngine.cpp ExecuteChunk (:1331, lua_dobuffer
// then lua_settop) and LoadScripts (:352, openFile / new[] / ExecuteChunk).
#include "ascii_string.h"
#include <new>


__forceinline const char *GetStr003340C1(const AsciiString &s)
{
	char *t = *(char * *)(void *)&s;
	return t ? t + 8 : "";
}

struct lua_State;

extern "C" int __cdecl lua_dobuffer(struct lua_State *L, const char *buff, unsigned int size, const char *name);
extern "C" void __cdecl lua_settop(struct lua_State *L, int idx);

class LuaScriptEngine
{
public:
	void ExecuteChunk(char *buff, int size, const AsciiString &chunk);
	void LoadScripts(const char *filename);

private:
	unsigned char m_pad[0xC];
	struct lua_State *m_lua;
};

void LuaScriptEngine::ExecuteChunk(char *buff, int size, const AsciiString &chunk)
{
	const char *name = GetStr003340C1(chunk);
	lua_dobuffer(m_lua, buff, size, name);
	lua_settop(m_lua, 0);
}

class File
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void close();
	virtual int read(char *buff, int size);
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual int getSize();
};

class FileSystem
{
public:
	class File *openFile(const char *filename, int access, int unk);
};

extern FileSystem *TheFileSystem;

void LuaScriptEngine::LoadScripts(const char *filename)
{
	File *file = TheFileSystem->openFile(filename, 0x41, 0);
	if (!file)
		return;
	int size = file->getSize();
	char *buff = new char[size + 10];
	file->read(buff, size);
	file->close();
	AsciiString *chunk = new ((void *)&filename) AsciiString(filename);
	ExecuteChunk(buff, size, *chunk);
	chunk->~AsciiString();
	delete[] buff;
}
