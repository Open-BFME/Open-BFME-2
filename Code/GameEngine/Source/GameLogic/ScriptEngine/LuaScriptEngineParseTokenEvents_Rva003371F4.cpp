// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine
//
// ?ProcessEventsElement@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
// retail 0x003371F4, 195 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameLogic/ScriptEngine/LuaScriptEngineParseTokenEvents.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here.
// RVA 0x002EA5D0 (donor): Events dispatch reached from matched LuaScriptEngineParseToken.cpp.
// The retail backedge at +0xE9 repeats the status==1 check at +0x40.
// Retail string/call pairs establish InternalEvent -> 002E2970, ScriptedEvent
// -> 002E9590, ModelConditionEvent -> 002E9680, ObjectStatusEvent -> 002E9AA0.
// All receive the unchanged engine ECX and parser stack argument; each returns ret 4.
// BFME2 names from WorldBuilder's LuaScriptEngine.cpp: ProcessEventsElement
// (:904-932, same Events / InternalEvent / ScriptedEvent / ModelConditionEvent /
// ObjectStatusEvent dispatch) and ProcessInternalEvent for 0x00332C7A.
typedef int Int;

extern "C" int strcmp(const char *, const char *);

class XmlNameSlotList
{
public:
	Int finish();
};

class BfmeLexEAN
{
public:
	char *getTailEAN();
};

// InternalEvent dispatch uses the established event-flag host ABI at the same this.
class __declspec(novtable) LuaScriptEngine
{
public:
	void ProcessEventsElement(BfmeLexEAN *parser);
	void ProcessInternalEvent(XmlNameSlotList *xml);
	void rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *parser);
	void rva002E9590ParseScriptedEvent(BfmeLexEAN *parser);
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
			rva002E9590ParseScriptedEvent(parser);
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
