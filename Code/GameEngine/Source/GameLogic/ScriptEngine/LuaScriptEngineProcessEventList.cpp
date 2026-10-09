// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?ProcessEventList@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
// retail 0x00337EAA..0x003381C4 (794 bytes, ret 4).
// LuaScriptEngine::ProcessEventList: WorldBuilder's twin (va 0xC01930) is
// named by LuaScriptEngine.cpp's own asserts (lines 1233..1256) and runs the
// same Name/Inherit attribute scan / EventHandler loop with EventName
// ScriptFunctionName and DebugSingleStep attributes / lua_getglobal plus
// lua_type checks / merge-or-push_back into the event-list vector. Its only
// caller is the matched ProcessSageElement (0x003381C4) for the "EventList"
// tag beside its sibling ProcessEventsElement; the parser type BfmeLexEAN
// follows those two rows. WB's "Method ... in event list" debug output and
// the item==ELEM_END assert are compiled out of retail (the first finish()
// result after an EventHandler is discarded).
// Engine layout from retail accesses: lua_State at +0x0C / dirty flag at
// +0xAC / vector of 20-byte event lists at +0xB0 / keep-open flag at +0xD8.
// Callee spellings follow their rows or pins: record ctor 0x003323AD /
// base assign 0x003323D2 / add handler 0x0033269B / dtor 0x003372B7 /
// assign 0x003372EC / push_back 0x00337CEA / lookup 0x00337DEF; handler
// entry dtor 0x0029D7C2 (pinned ??1Rva002DFC30) is reached from the unwind
// funclet.

#include <vector>
#include "ascii_string.h"

struct lua_State;
extern "C" void lua_getglobal(lua_State *L, const char *name);
extern "C" int lua_type(lua_State *L, int index);
extern "C" void lua_settop(lua_State *L, int index);

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class XmlNameSlotList
{
public:
	int count();
	const char *tagAt(int index);
	const char *nameAt(int index);
	int finish();
};

class BfmeLexEAN
{
public:
	char *getTailEAN();
};

// One event handler: key / Lua function name / single-step flag (12 bytes).
class Rva002DFC30
{
public:
	NameKeyType m_key;
	AsciiString m_function;
	unsigned char m_debugSingleStep;
};

struct BfmeStringRecord000331962;

class Rva0033269B
{
public:
	void rva0033269B(const BfmeStringRecord000331962 &rec);
};

class Rva002E17F0
{
public:
	void operator=(const Rva002E17F0 &other);
};

// Event list record (20 bytes: name / flag / handler vector).
class Rva003323AD
{
public:
	Rva003323AD(const StringBase<char> &name);

private:
	char m_data[0x14];
};

class Rva003371B1 : public Rva003323AD
{
public:
	Rva003371B1(const AsciiString &name) : Rva003323AD(*(const StringBase<char> *)&name) {}
	~Rva003371B1();
	Rva003371B1 &operator=(const Rva003371B1 &other);
};

namespace _STL
{
template <> void vector<Rva003371B1, allocator<Rva003371B1> >::push_back(const Rva003371B1 &);
}

struct Rva00336283Element;

class __declspec(novtable) LuaScriptEngine
{
public:
	void ProcessEventList(BfmeLexEAN *parser);
	Rva00336283Element *rva00337DEF(const AsciiString &name);

private:
	char m_pad00[0x0C];
	lua_State *m_luaState;
	char m_pad10[0xAC - 0x10];
	unsigned char m_eventListsDirty;
	char m_padAD[3];
	_STL::vector<Rva003371B1> m_eventLists;
	char m_padBC[0xD8 - 0xBC];
	unsigned char m_keepOpen;
};

void LuaScriptEngine::ProcessEventList(BfmeLexEAN *parser)
{
	XmlNameSlotList *xml = (XmlNameSlotList *)parser;
	AsciiString name;
	AsciiString inherit;
	for (int i = 0; i < xml->count(); ++i)
	{
		const char *value = xml->nameAt(i);
		if (strcmp(xml->tagAt(i), "Name") == 0)
			name = value;
		else if (strcmp(xml->tagAt(i), "Inherit") == 0)
			inherit = value;
	}

	Rva003371B1 record(name);
	int item = xml->finish();
	Rva00336283Element *base = rva00337DEF(inherit);
	if (base)
		*(Rva002E17F0 *)&record = *(Rva002E17F0 *)base;

	bool done = false;
	while (!done && item != 0)
	{
		switch (item)
		{
		case 1:
		{
			const char *element = parser->getTailEAN();
			if (strcmp(element, "EventHandler") != 0)
				return;
			{
				AsciiString eventName;
				AsciiString functionName;
				bool debugSingleStep = false;
				for (int i = 0; i < xml->count(); ++i)
				{
					const char *value = xml->nameAt(i);
					if (strcmp(xml->tagAt(i), "EventName") == 0)
						eventName = value;
					else if (strcmp(xml->tagAt(i), "ScriptFunctionName") == 0)
						functionName = value;
					else if (strcmp(xml->tagAt(i), "DebugSingleStep") == 0)
						debugSingleStep = strcmp(value, "true") == 0;
				}
				if (!eventName.isEmpty() && !functionName.isEmpty())
				{
					lua_getglobal(m_luaState, functionName.str());
					if (lua_type(m_luaState, -1) != 5)
					{
						AsciiString error;
						if (lua_type(m_luaState, -1) == 1)
							error = " is not defined.";
						else
							error = " is not a lua function.";
					}
					lua_settop(m_luaState, -2);
					Rva002DFC30 entry;
					entry.m_key = TheNameKeyGenerator->nameToKey(eventName);
					entry.m_function = functionName;
					entry.m_debugSingleStep = debugSingleStep;
					((Rva0033269B *)&record)->rva0033269B(*(const BfmeStringRecord000331962 *)&entry);
				}
				item = xml->finish();
			}
			break;
		}
		case 2:
			done = true;
			break;
		default:
			return;
		}
		if (!done)
			item = xml->finish();
	}

	m_eventListsDirty = 0;
	if (m_keepOpen)
	{
		for (Rva003371B1 *it = m_eventLists.begin(); it != m_eventLists.end(); ++it)
		{
			if (((const StringBase<char> *)&record)->compare(*(const StringBase<char> *)it) == 0)
			{
				*it = record;
				return;
			}
		}
	}
	m_eventLists.push_back(record);
}
