// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine
// LuaScriptEngine::ProcessSageElement, BFME2 retail 0x003381C4 (donor name
// rva002EC770ParseToken after its BFME1 RVA 0x002EC770). The BFME2 name is
// WorldBuilder's: LuaScriptEngine.cpp:864-887 asserts in ProcessSageElement with
// the same SageLuaScriptSection / Events / EventList dispatch.
// Sibling of LuaScriptEngineParseTokenFile.cpp's rva002EC840ParseTokenFile,
// which calls this body once per XML tag through the
// ?j_0000ed95@@YAXXZ alternate name. `parser` is the same BfmeLexEAN the
// caller constructs; m_bfmeTailEAN (+0x1C) holds the tag name the lexer just
// consumed. The root element must read "SageLuaScriptSection" and
// XmlNameSlotList::finish() (already pinned to 0x0035EE70) must report 1;
// then the tag is re-read and dispatched to one of two sibling handlers --
// "Events" through the still-carved body at 0x002EA5D0 (thunk 0x0000668B)
// and "EventList" through the still-carved body at 0x002EC0A0 (thunk
// 0x0003ED33) -- before a final finish() == 1 check.

#include <string.h>

typedef int Int;
typedef bool Bool;

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

class __declspec(novtable) LuaScriptEngine
{
public:
	void ProcessSageElement(BfmeLexEAN *parser);
	void ProcessEventsElement(BfmeLexEAN *parser);
	void ProcessEventList(BfmeLexEAN *parser);	// 0x00337EAA

private:
	char m_pad00B4[0xB4];
	unsigned char m_keepOpen;
};

// getTailEAN (0x0030F2C7, rowed by LuaScriptEngineProcessEventList.cpp) and
// the EventList handler ProcessEventList (0x00337EAA) are called directly.


// ?ProcessSageElement@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
void LuaScriptEngine::ProcessSageElement(BfmeLexEAN *parser)
{
	char *tail = parser->getTailEAN();
	int cmp = strcmp(tail, "SageLuaScriptSection");
	if (cmp != 0)
		return;

	Int status = ((XmlNameSlotList *)parser)->finish();
	while (status != 0)
	{
		if (--status != 0)
			return;

		const char *tag = parser->getTailEAN();
		int cmpEvents = strcmp(tag, "Events");
		if (cmpEvents == 0)
		{
			ProcessEventsElement(parser);
		}
		else
		{
			int cmpEventList = strcmp(tag, "EventList");
			if (cmpEventList != 0)
				return;
			ProcessEventList(parser);
		}
		status = ((XmlNameSlotList *)parser)->finish();
	}
}
