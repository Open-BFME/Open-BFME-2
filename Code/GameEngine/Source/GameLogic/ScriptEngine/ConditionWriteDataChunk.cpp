// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// Condition::WriteConditionDataChunk, retail 0x003B428C (183 bytes).
// Ported from the exact BFME1 reconstruction
// (Code/GameEngine/Source/GameLogic/ScriptEngine/ConditionWriteDataChunk.cpp),
// which matches ZH Scripts.cpp unchanged, with two BFME2 deltas proven by
// the retail body:
// - chunk version 6 (push 6, retail 0x3B42A0), ZH/BFME1 use version 4;
// - two trailing byte fields at Condition+0x4C/+0x4D, each movzx-pushed
//   through DataChunkOutput::writeInt (retail 0x3B4314-0x3B432B), absent in
//   BFME1 (160 bytes vs 183).
// Field offsets from the retail body: m_conditionType at +4, m_numParms at
// +8, m_parms array at +0x0C (12 pointers, MAX_PARMS), m_nextAndCondition at
// +0x3C, extra bytes at +0x4C/+0x4D (Condition : MemoryPoolObject, vtable
// at +0). ConditionTemplate carries m_internalNameKey at +0x10 (vtable +
// three AsciiString slots), read at retail 0x3B42CA.
// Callees openDataChunk/closeDataChunk/writeInt/writeNameKey (DataChunkOutput),
// WriteParameter (Parameter), getConditionTemplate (ScriptEngine) and
// nameToKey (NameKeyGenerator, for NAMEKEY Bogus) are pinned in
// reverse/symbols.csv from this call site's argument shapes; nameToKey is
// already matched at 0x148E1A.

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject() {}
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct BfmeStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

class AsciiString;
#include "ascii_string.h"


class Mapping;
class DataChunkTableOfContents
{
public:
	unsigned int allocateID(const AsciiString &name);
private:
	Mapping *m_list;
	int m_listLength;
	unsigned int m_nextID;
	bool m_headerOpened;
};

class OutputStream;
class OutputChunk
{
public:
	OutputChunk();
	virtual ~OutputChunk() {}
	OutputChunk *next;
	unsigned int id;
	int filepos;
};
// ??0OutputChunk@@QAE@XZ @0x00306C62 9B: the default constructor, storing the
// class's own vtable (VA 0x00C07E80) and returning this.
OutputChunk::OutputChunk()
{
}

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short ver);
	void writeInt(int value);
	void writeNameKey(NameKeyType key);
	void closeDataChunk(void);

private:
	OutputStream *m_pOut;
	void *m_tmp_file;
	DataChunkTableOfContents m_contents;
	OutputChunk *m_chunkStack;
};

extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buf, unsigned int size, unsigned int count, void *stream);
extern "C" __declspec(dllimport) int __cdecl ftell(void *stream);
extern "C" __declspec(dllimport) int __cdecl fseek(void *stream, long offset, int origin);

void __cdecl operator delete(void *ptr);

enum { SEEK_SET_ = 0 };

class ConditionTemplate
{
public:
	virtual ~ConditionTemplate() {}

	unsigned char m_pad[0x0C];
	NameKeyType m_internalNameKey;
};

class ScriptEngine
{
public:
	const ConditionTemplate *getConditionTemplate(int ndx);
};

extern ScriptEngine *TheScriptEngine;

class Parameter
{
public:
	void WriteParameter(DataChunkOutput &chunkWriter);
};

enum { K_SCRIPT_CONDITION_DATA_VERSION_6 = 6 };
enum { MAX_CONDITION_PARMS = 12 };

class Condition : public MemoryPoolObject
{
public:
	static void WriteConditionDataChunk(DataChunkOutput &chunkWriter, Condition *pCondition);
	Condition *getNext(void) { return m_nextAndCondition; }

	int m_conditionType;
	int m_numParms;
	Parameter *m_parms[MAX_CONDITION_PARMS];
	Condition *m_nextAndCondition;
	int m_hasWarnings;
	int m_customData;
	unsigned int m_customFrame;
	unsigned char m_extraFlagA;
	unsigned char m_extraFlagB;
};

void Condition::WriteConditionDataChunk(DataChunkOutput &chunkWriter, Condition *pCondition)
{
	while (pCondition) {
		chunkWriter.openDataChunk("Condition", K_SCRIPT_CONDITION_DATA_VERSION_6);
		chunkWriter.writeInt(pCondition->m_conditionType);
		const ConditionTemplate *condTemplate = TheScriptEngine->getConditionTemplate(pCondition->m_conditionType);
		if (condTemplate) {
			chunkWriter.writeNameKey(condTemplate->m_internalNameKey);
		} else {
			chunkWriter.writeNameKey(TheNameKeyGenerator->nameToKey("Bogus"));
		}
		chunkWriter.writeInt(pCondition->m_numParms);
		int parmIndex;
		for (parmIndex = 0; parmIndex < pCondition->m_numParms; parmIndex++) {
			pCondition->m_parms[parmIndex]->WriteParameter(chunkWriter);
		}
		chunkWriter.writeInt(pCondition->m_extraFlagA);
		chunkWriter.writeInt(pCondition->m_extraFlagB);
		chunkWriter.closeDataChunk();
		pCondition = pCondition->getNext();
	}
}

// ?openDataChunk@DataChunkOutput@@QAEXPADG@Z
void DataChunkOutput::openDataChunk(char *name, unsigned short version)
{
	unsigned int id;
	{
		const AsciiString &chunkName = AsciiString(name);
		id = m_contents.allocateID(chunkName);
	}

	OutputChunk *chunk = new OutputChunk;
	chunk->next = m_chunkStack;
	m_chunkStack = chunk;
	chunk->id = id;

	fwrite(&id, sizeof(id), 1, m_tmp_file);
	fwrite(&version, sizeof(version), 1, m_tmp_file);
	chunk->filepos = ftell(m_tmp_file);

	int dummy = 0xffff;
	fwrite(&dummy, sizeof(dummy), 1, m_tmp_file);
}

// ?closeDataChunk@DataChunkOutput@@QAEXXZ
// Retail 0x00306C88 (119 bytes). ZH DataChunk.cpp port (GeneralsMD): same
// head (null check, ftell, rewind, size, store, seek back, pop), but ZH ends
// with c->deleteInstance() (pooled) while retail emits a global ::delete
// (flag-0 virtual dtor call plus separate operator delete), matching the
// plain new in openDataChunk above. The trailing null check needs no outer
// if: ::delete on a nullable pointer emits it (xor/cmp/je over the dtor,
// delete-if-null still called since free(0) no-ops).
void DataChunkOutput::closeDataChunk(void)
{
	if (m_chunkStack == 0)
	{
		return;
	}

	int here = ftell(m_tmp_file);

	fseek(m_tmp_file, m_chunkStack->filepos, SEEK_SET_);

	int size = here - m_chunkStack->filepos - sizeof(int);

	fwrite(&size, sizeof(int), 1, m_tmp_file);

	fseek(m_tmp_file, here, SEEK_SET_);

	OutputChunk *c = m_chunkStack;
	m_chunkStack = m_chunkStack->next;
	::delete c;
}
