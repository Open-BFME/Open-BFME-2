// ?rva003B81C5@Rva003B573E@@QAEHHABV?$StringBase@D@@@Z
// partial score=0.944444 date=2026-10-07
// Fresh BFME1 1399ad37 BfmeConv1700 lead: native CMP/MOV/JE loads original index for failed lookup; return index is required.
// Byte-exact 72B with the existing callee pin; no C++ provider yet for 3B7C47, so linking is incomplete.
// ?rva003B81C5@Rva003B573E@@QAEHHABV?$StringBase@D@@@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "ascii_string.h"

// ?rva003B81C5@Rva003B573E@@QAEHHABV?$StringBase@D@@@Z @0x003B81C5 72B
// Same class and record model as ScriptListSubrecordRemove.cpp; target search
// uses the supplied key, then transfers one linked node and removes its source.
struct Rva003B675BRecord
{
	int m_previous;
	int m_next;
	AsciiString m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	void *m_nodes;
};

class BfmeNodeZ
{
public:
	BfmeNodeZ *m_next;
};

class Rva003B573E
{
public:
	int rva003B7C47(const StringBase<char> &key);
	void rva003B66D8(int index);
	int rva003B81C5(int index, const StringBase<char> &key);

private:
	_STL::vector<void *> m_sorted;
	_STL::vector<Rva003B675BRecord> m_records;
	int m_freeHead;
	int m_tail;
};

int Rva003B573E::rva003B81C5(int index, const StringBase<char> &key)
{
	int destination = rva003B7C47(key);
	if (destination == -1)
		return index;
	Rva003B675BRecord *source = &m_records[index];
	BfmeNodeZ *node = (BfmeNodeZ *)source->m_nodes;
	source->m_nodes = node->m_next;
	Rva003B675BRecord *target = &m_records[destination];
	node->m_next = (BfmeNodeZ *)target->m_nodes;
	target->m_nodes = node;
	rva003B66D8(index);
	return destination;
}
