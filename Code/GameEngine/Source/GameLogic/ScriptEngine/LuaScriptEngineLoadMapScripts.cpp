// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfmealloc /Ireference/shims/bfmelist -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine
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

typedef unsigned char Bool;
#include <stdlib.h>
#include "subsystem_interface.h"
struct lua_State;
class Object;
class BfmeLexEAN;
class XmlNameSlotList;
struct LuaDrawableLink;
struct Rva003378D0
{
	~Rva003378D0();
	char m_pad[12];
};

template <class T> struct Rva00337AA8Buf
{
	void *m_ptr;
	~Rva00337AA8Buf()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
};
class LuaScriptEngine : public SubsystemInterface
{
public:
	LuaScriptEngine();
	virtual ~LuaScriptEngine();
 virtual void init();
 virtual void reset();
 virtual void update() {}
 virtual void slot14() {}
 virtual const char *GetSnapshotName() const; virtual void DoXfer(Xfer *);

 void ExecuteChunk(char *buff, int size, const AsciiString &chunk);
 void LoadScripts(const char *filename);
 void DispatchEvent(int *key, Object *object, void *parameters);
 void DispatchSpyEvent(int key, void *object, void *spy, void *parameters);
 void PushObjectTable(lua_State *state, Object *object);
 static int ObjectDescription(lua_State *state);
 static int ObjectModifyUpgrade(lua_State *state, bool grant);
 static int HordeBroadcastEventToMembers(lua_State *state);
 void ProcessEventsElement(BfmeLexEAN *parser);
 void ProcessInternalEvent(XmlNameSlotList *xml);
 void rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *parser);
 void ProcessScriptedEvent(XmlNameSlotList *xml);
 void rva002E9680ParseModelConditionEvent(BfmeLexEAN *parser);
 void ProcessSageElement(BfmeLexEAN *parser);
 void ProcessEventList(BfmeLexEAN *parser);
 void LoadXML(const char *filename, bool keepOpen);
 void rva003387DC(const AsciiString &mapName);
 void rva00338317RegisterScriptFunctions();
private:
	lua_State *m_luaState;
	lua_State *m_lua10;
	char m_pad14[0x9C - 0x14];
public:
	LuaDrawableLink *m_drawable;
private:
	Rva00337AA8Buf<void> m_bufA0;
	char m_padA4[0xAC - 0xA4];
	bool m_flagAC; char m_padAD[3];
	Rva003378D0 m_vecB0;
	Rva00337AA8Buf<void> m_bufBC;
	char m_padC0[0xC8 - 0xC0];
	// C8 is explicitly released by the dtor body; BC/A0 are automatic.
	void *m_bufC8; void *m_endCC, *m_limitD0;
 int m_depth; // +0xD4
 unsigned char m_keepOpen; // +0xD8
 char m_padD9[3];
 int m_singleStepKey; // +0xDC
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
