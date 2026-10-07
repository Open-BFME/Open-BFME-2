// ?rva003B8141@Rva003B573E@@QAEHABV?$StringBase@D@@@Z
// partial score=0.93 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "ascii_string.h"

// ?rva003B8141@Rva003B573E@@QAEHABV?$StringBase@D@@@Z @0x003B8141 111B
// Searches the ScriptList subrecord by key and prepends a node to its record.
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

class Rva003B417E
{
public:
	Rva003B417E();
	char m_payload[0x54];
};

struct Rva003B8141Node
{
	Rva003B8141Node *m_next;
	Rva003B417E m_payload;
	Rva003B8141Node() : m_next(0), m_payload() {}
};

class Rva003B573E
{
public:
	int rva003B7C47(const StringBase<char> &key);
	int rva003B8141(const StringBase<char> &key);

private:
	_STL::vector<void *> m_sorted;
	_STL::vector<Rva003B675BRecord> m_records;
	int m_freeHead;
	int m_tail;
};

int Rva003B573E::rva003B8141(const StringBase<char> &key)
{
	int index = rva003B7C47(key);
	if (index != -1) {
		Rva003B675BRecord *record = &m_records[index];
		Rva003B8141Node *node = new Rva003B8141Node;
		node->m_next = (Rva003B8141Node *)record->m_nodes;
		record->m_nodes = node;
	}
	return index;
}
