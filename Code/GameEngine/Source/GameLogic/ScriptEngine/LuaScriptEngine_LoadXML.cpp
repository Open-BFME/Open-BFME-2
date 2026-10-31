// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfmealloc /Ireference/shims/bfmelist -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine
// ?LoadXML@LuaScriptEngine@@QAEXPBD_N@Z, retail 0x00338241, 214 bytes.
// Name: WorldBuilder's LuaScriptEngine.cpp:825-847 LoadXML (openFile, new[],
// lexer, ProcessSageElement loop, delete[]).
// BFME2 ParseTokenFile over LuaScriptEngine: openFile 3-arg plus size plus
// new[] plus read plus close plus Rva00542806 init plus finish loop plus
// ParseToken plus delete[]. Ported from Open-BFME-1
// LuaScriptEngineParseTokenFile.cpp (rva002EC840ParseTokenFile): BFME2 adds
// third openFile arg 0 plus Rva00542806/Rva0054288B for BfmeLexEAN ctor/dtor
// plus m_keepOpen at +0xD8. Evidence: sole callers 0x003387D4/0x00338997;
// callees rowed openFile 0x00600C34 plus List init 0x00542806 plus ParseToken
// 0x003381C4 plus thunk 0x0054288B plus new[]/delete[]; layout +0xD8 matches.

typedef int Int;
typedef bool Bool;

#include <new>

class File
{
public:
	virtual void fileVirtual00() = 0;
	virtual void fileVirtual01() = 0;
	virtual void close() = 0;
	virtual Int read(void *buffer, Int bytes) = 0;
	virtual void fileVirtual03() = 0;
	virtual void fileVirtual04() = 0;
	virtual void fileVirtual05() = 0;
	virtual void fileVirtual06() = 0;
	virtual void fileVirtual07() = 0;
	virtual void fileVirtual08() = 0;
	virtual void fileVirtual09() = 0;
	virtual Int size() = 0;
	virtual void fileVirtual12() = 0;
};

class FileSystem
{
public:
	class File *openFile(const char *filename, int access, int unk);
	bool doesFileExist(const char *filename) const;
};
extern FileSystem *TheFileSystem;

class Rva00542806
{
public:
	Rva00542806 *rva00542806(char *a1, int a2, int a3);
private:
	char *m_ptr;
	char m_pad4[8];
	int m_c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	unsigned char m_24;
	char m_pad25[3];
	int m_28;
	char m_buf[0x184];
};

class Rva0054288B
{
public:
	void rva0054288B();
};

struct ParserWrap : Rva00542806
{
	ParserWrap(char *source, int buffer, int bufferSize) { rva00542806(source, buffer, bufferSize); }
	~ParserWrap() { ((Rva0054288B *)this)->rva0054288B(); }
};

class XmlNameSlotList
{
public:
	int count();
	int finish();
	const char *tagAt(int);
	const char *nameAt(int);
};

class BfmeLexEAN;
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

void LuaScriptEngine::LoadXML(const char *filename, bool keepOpen)
{
	File *file = TheFileSystem->openFile(filename, 0x41, 0);
	if (file != 0)
	{
		Int size = file->size();
		char *source = (char *)operator new[](size + 10);
		file->read(source, size);
		source[size] = 0;
		file->close();
		char buffer[0x1000];
		m_keepOpen = keepOpen;
		ParserWrap parser(source, (int)buffer, 0xFFF);
		for (;;)
		{
			Int status = ((XmlNameSlotList *)&parser)->finish();
			if (status == 0)
				break;
			if (--status != 0)
				return;
			ProcessSageElement((BfmeLexEAN *)&parser);
		}
		m_keepOpen = 0;
		operator delete[](source);
	}
}
