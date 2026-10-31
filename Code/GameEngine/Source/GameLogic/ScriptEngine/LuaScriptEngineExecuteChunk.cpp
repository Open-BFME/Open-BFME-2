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


__forceinline const char *GetStr003340C1(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
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
	struct lua_State *m_luaState;
};

void LuaScriptEngine::ExecuteChunk(char *buff, int size, const AsciiString &chunk)
{
	const char *name = GetStr003340C1(chunk);
	lua_dobuffer(m_luaState, buff, size, name);
	lua_settop(m_luaState, 0);
}

class File
{
public:
	virtual void fileVirtual00() = 0;
	virtual void fileVirtual01() = 0;
	virtual void close() = 0;
	virtual int read(void *buffer, int bytes) = 0;
	virtual void fileVirtual03() = 0;
	virtual void fileVirtual04() = 0;
	virtual void fileVirtual05() = 0;
	virtual void fileVirtual06() = 0;
	virtual void fileVirtual07() = 0;
	virtual void fileVirtual08() = 0;
	virtual void fileVirtual09() = 0;
	virtual int size() = 0;
	virtual void fileVirtual12() = 0;
};

class FileSystem
{
public:
	class File *openFile(const char *filename, int access, int unk);
	bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

void LuaScriptEngine::LoadScripts(const char *filename)
{
	File *file = TheFileSystem->openFile(filename, 0x41, 0);
	if (!file)
		return;
	int size = file->size();
	char *buff = new char[size + 10];
	file->read(buff, size);
	file->close();
	ExecuteChunk(buff, size, AsciiString(filename));
	delete[] buff;
}
