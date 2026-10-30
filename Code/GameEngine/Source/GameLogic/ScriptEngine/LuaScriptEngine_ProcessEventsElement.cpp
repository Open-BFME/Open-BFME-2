// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine
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
class LuaScriptEngine
{
public:
	void ProcessEventsElement(BfmeLexEAN *parser);
	void ProcessInternalEvent(XmlNameSlotList *xml);
	void rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *parser);
	void ProcessScriptedEvent(XmlNameSlotList *xml);
	void rva002E9680ParseModelConditionEvent(BfmeLexEAN *parser);

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
