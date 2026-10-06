// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?ParseOrConditionDataChunk@OrCondition@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z retail 0x003B7587 151B OrCondition list append plus Condition parser registration offset 0x30

#include "ascii_string.h"

// Retail vtable VA 0x00C1F3F4 (data 0x0081F3F4): OrCondition list node.
// Packet annotates: no name yet, so use g_ stopgap per linking rules.
extern const void *const g_00C1F3F4[];

class OrConditionAllocation
{
public:
	__forceinline OrConditionAllocation()
	{
		m_vtable = (unsigned int)g_00C1F3F4;
		m_next = 0;
		m_first = 0;
	}
private:
	unsigned int m_vtable;
public:
	OrConditionAllocation *m_next;
private:
	void *m_first;
};

struct DataChunkInfo { AsciiString label; };
class DataChunkInput;
class UserParser;
typedef bool (__cdecl *ChunkParser)(DataChunkInput &, DataChunkInfo *, void *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DataChunk.h
class DataChunkInput
{
public:
	UserParser *registerParser(const AsciiString &name, const AsciiString &parent, ChunkParser parser, void *user_data);
	bool parse(void *instance);
};

class ScriptLayout
{
public:
	unsigned char m_prefix[0x30];
	OrConditionAllocation *m_or_condition;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Condition
{
public:
	static bool __cdecl ParseConditionDataChunk(DataChunkInput &, DataChunkInfo *, void *);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class OrCondition
{
public:
	static bool __cdecl ParseOrConditionDataChunk(DataChunkInput &, DataChunkInfo *, void *);
};

bool __cdecl OrCondition::ParseOrConditionDataChunk(DataChunkInput &file, DataChunkInfo *info, void *user_data)
{
	OrConditionAllocation *condition = new OrConditionAllocation;
	ScriptLayout *script = (ScriptLayout *)user_data;
	OrConditionAllocation *last = script->m_or_condition;
	while (last && last->m_next)
		last = last->m_next;
	if (last)
		last->m_next = condition;
	else
		script->m_or_condition = condition;
	{
		AsciiString name("Condition");
		file.registerParser(name, info->label, Condition::ParseConditionDataChunk, 0);
	}
	return file.parse(condition);
}
