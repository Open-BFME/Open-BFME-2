// cl: /DNDEBUG /MD
//
// ?WriteGroupDataChunk@@YAXAAVDataChunkOutput@@PAVScriptList@@PAVScriptGroup@@@Z,
// retail 0x003B6975, 166 bytes. Dedicated TU.
//
// Free group writer in the ScriptEngine family (promoted from banked stash
// reverse/attempts/0x003b6975.cpp, already 166/166 with the ebx home as the
// sole wall): ZH ScriptGroup::WriteGroupDataChunk shape with BFME2
// adaptations (all retail-measured): v3 ScriptGroup chunk, opaque skip
// predicate (0x3B485A, true skips), capture helper (matched 0x3B40A1 row),
// group name via ScriptList table (index at input+4, base at list+0x18, 20B
// entries, AsciiString at +8) through matched writeAsciiString, actives at
// real+0x0C/+0x0D through matched writeByte, subgroup at real+4 via self
// recursion, scripts at real+8 via the 0x3B5994 pin, input walks via +0x00,
// open/close via matched rows. The skip call reads AL (alias QAE_N pin);
// the skip body row is the Int twin at the same address.

typedef int Int;
typedef unsigned char Byte;
typedef bool Bool;

class AsciiString;
class Script;
class ScriptList;
class ScriptGroup;

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short ver);
	void writeAsciiString(const AsciiString &str);
	void writeByte(Byte b);
	void closeDataChunk(void);
};

struct GroupNameEntry
{
	Byte m_pad[8];
	Byte m_name[8];
	Byte m_tail[4];
};

class ScriptListView
{
public:
	Byte m_pad[0x18];
	GroupNameEntry *m_groupNames;
};

class ScriptGroupInput
{
public:
	ScriptGroup *m_next;
	Int m_nameIndex;
};

class ScriptGroupReal
{
public:
	Byte m_pad0[4];
	ScriptGroup *m_firstSubgroup;
	Script *m_firstScript;
	Byte m_isGroupActive;
	Byte m_isGroupSubroutine;
};

class Rva003B485AHolder
{
public:
	Bool skipGroup(void *group);
};

class Rva003B40A1Holder
{
public:
	void *captureGroup(void *group);
};

void WriteScriptDataChunk(DataChunkOutput &chunkWriter, ScriptList *scriptList, Script *script);

// ?WriteGroupDataChunk@@YAXAAVDataChunkOutput@@PAVScriptList@@PAVScriptGroup@@@Z
void WriteGroupDataChunk(DataChunkOutput &chunkWriter, ScriptList *scriptList, ScriptGroup *scriptGroup)
{
	ScriptList *list = scriptList;
	ScriptGroupInput *input;
	for (input = (ScriptGroupInput *)(void *)scriptGroup; input; input = (ScriptGroupInput *)(void *)input->m_next) {
		if (((Rva003B485AHolder *)list)->skipGroup(input))
			continue;
		ScriptGroupReal *real = (ScriptGroupReal *)(void *)((Rva003B40A1Holder *)list)->captureGroup(input);
		chunkWriter.openDataChunk("ScriptGroup", 3);
		chunkWriter.writeAsciiString(*(const AsciiString *)&((ScriptListView *)list)->m_groupNames[input->m_nameIndex].m_name);
		chunkWriter.writeByte(real->m_isGroupActive);
		chunkWriter.writeByte(real->m_isGroupSubroutine);
		if (real->m_firstSubgroup)
			WriteGroupDataChunk(chunkWriter, list, real->m_firstSubgroup);
		if (real->m_firstScript)
			WriteScriptDataChunk(chunkWriter, list, real->m_firstScript);
		chunkWriter.closeDataChunk();
	}
}
