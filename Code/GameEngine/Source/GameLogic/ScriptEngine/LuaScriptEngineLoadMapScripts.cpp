// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist
//
// ?rva003387DC@LuaScriptEngine@@QAEXABVAsciiString@@@Z, retail 0x003387DC
// (464 bytes, EH, RET 4): LuaScriptEngine's per-map script loader, called by
// GameLogic 0x002469A5 with the map name. Registers the script functions
// (0x00338317), then, for a non-empty map name, strips the file part of the
// map path (the pristine map name at TheGameState +0x2C when 0x002DC7C1 places
// the map in the save directory) and loads the folder's Scripts.lua
// (LoadScripts 0x003345BE) and ScriptEvents.xml (LoadXML 0x00338241, true).
// Donor: Open-BFME-1 LuaScriptEngineMapScriptPaths.cpp (0x002ECF40, same
// walk); the BFME 2 path walk is the one GameLogic::loadMapINI (0x0023E3CE,
// GameLogicInit.cpp) compiles. The method keeps its retail address name: the
// WB name is not proven by a string.
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"

class GameState
{
	char m_pad00[0x2c];
public:
	AsciiString m_pristineMapName;                                       // +0x2C
};

class Rva002DC7C1
{
public:
	bool rva002DC7C1(const UnicodeString &path) const;
};

class File;
class FileSystem
{
public:
	class File *openFile(const char *filename, int access, int unk);
	bool doesFileExist(const char *filename) const;
};

extern GameState *TheGameState;
extern FileSystem *TheFileSystem;

extern "C" int (__cdecl * const _imp__sprintf)(char *buffer, const char *format, ...);

class LuaScriptEngine
{
public:
	void rva003387DC(const AsciiString &mapName);
	void rva00338317RegisterScriptFunctions();
	void LoadXML(const char *filename, bool reload);
	void LoadScripts(const char *filename);
};

void LuaScriptEngine::rva003387DC(const AsciiString &mapName)
{
	rva00338317RegisterScriptFunctions();
	if (!mapName.isEmpty()) {
		char mapPath[260];
		char scriptPath[260];

		memset(mapPath, 0, 260);
		strcpy(mapPath, mapName.str());

		if (TheGameState && ((Rva002DC7C1 *)TheGameState)->rva002DC7C1(UnicodeString(AsciiString(mapPath))))
			strcpy(mapPath, TheGameState->m_pristineMapName.str());

		int length = strlen(mapPath);
		if (length < 4)
			return;

		char *end = mapPath + length - 4;
		while (end > mapPath && *end != '\\' && *end != '/')
			--end;
		*end = 0;

		int (__cdecl *format)(char *, const char *, ...) = _imp__sprintf;
		format(scriptPath, "%s\\Scripts.lua", mapPath);
		if (TheFileSystem->doesFileExist(scriptPath))
			LoadScripts(scriptPath);

		format(scriptPath, "%s\\ScriptEvents.xml", mapPath);
		if (TheFileSystem->doesFileExist(scriptPath))
			LoadXML(scriptPath, true);
	}
}
