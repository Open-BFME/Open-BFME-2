// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfmealloc /Ireference/shims/bfmelist -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine
//
// ?ProcessEventsElement@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
// retail 0x003371F4, 195 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineParseTokenEvents.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here.
// RVA 0x002EA5D0 (donor): Events dispatch reached from matched LuaScriptEngineParseToken.cpp.
// Retail string/call pairs establish InternalEvent -> 00332C7A, ScriptedEvent
// -> 00336BE4, ModelConditionEvent -> 00336C5D, ObjectStatusEvent -> 00336EB0.
// All receive the unchanged engine ECX and parser stack argument; each returns ret 4.
// BFME2 names from WorldBuilder's LuaScriptEngine.cpp: ProcessEventsElement
// (:904-932, same Events / InternalEvent / ScriptedEvent / ModelConditionEvent /
// ObjectStatusEvent dispatch) and ProcessInternalEvent for 0x00332C7A.

#include <string.h>

typedef int Int;

class XmlNameSlotList
{
public:
	int count();
	int finish();
	const char *tagAt(int);
	const char *nameAt(int);
};

class BfmeLexEAN
{
public:
	char *getTailEAN();
	BfmeLexEAN(char *text, char *buffer, int limit);
	~BfmeLexEAN();
	char *m_bfmePosEAN; // +0x00
	char *m_bfmeLineEAN; // +0x04
	char *m_bfmeSourceEAN; // +0x08
	int m_bfmeLineNumberEAN; // +0x0C
	int m_bfmeTagEAN; // +0x10
	char *m_bfmeBufEAN; // +0x14
	int m_bfmeLimitEAN; // +0x18
	char *m_tail; // +0x1C
	int m_bfmeDepthEAN; // +0x20
	unsigned char m_bfmeSeenEAN; // +0x24
	char m_pad25[0x3];
	int m_bfmeMarkEAN; // +0x28
	int m_bfmeStackEAN[0x61]; // +0x2C
};

// InternalEvent dispatch uses the established event-flag host ABI at the same this.
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


void LuaScriptEngine::ProcessEventsElement(BfmeLexEAN *parser)
{
	char *tail = parser->getTailEAN();
	int cmpEvents = strcmp(tail, "Events");
	if (cmpEvents != 0)
		return;

	Int status = ((XmlNameSlotList *)parser)->finish();
	while (status != 0)
	{
		if (--status != 0)
			return;

		const char *tag = parser->getTailEAN();
		int cmp;

		cmp = strcmp(tag, "InternalEvent");
		if (cmp == 0)
		{
			ProcessInternalEvent((XmlNameSlotList *)parser);
			goto checkFinish;
		}

		cmp = strcmp(tag, "ScriptedEvent");
		if (cmp == 0)
		{
			// The recovered provider uses the same parser view as finish/InternalEvent.
			ProcessScriptedEvent((XmlNameSlotList *)parser);
			goto checkFinish;
		}

		cmp = strcmp(tag, "ModelConditionEvent");
		if (cmp == 0)
		{
			rva002E9680ParseModelConditionEvent(parser);
			goto checkFinish;
		}

		cmp = strcmp(tag, "ObjectStatusEvent");
		if (cmp != 0)
			return;

		rva002E9AA0ParseObjectStatusEvent(parser);

	checkFinish:
		status = ((XmlNameSlotList *)parser)->finish();
	}
}
