// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
//
// ?rva003B7E39@Rva003B573E@@QAEHABV?$StringBase@D@@PBVRva003529B0@@@Z,
// retail 0x003B7E39..0x003B7EC2 (137B: 116B body plus the 21B catch funclet
// 0x003B7EAD), thiscall ret 8.
//
// Looks up or allocates the 0x14-stride record for the key (rva003B7C47),
// then pushes a new 0x14-byte list node holding a copy of the payload onto
// the record's node list at +0x10. If building the node throws, the record
// reference is dropped again (rva003B66D8) and the exception is rethrown.
// Returns the record index or -1.
//
// Evidence (target): callees read at the retail REL32s: 0x003B7C47 (pinned
// rva003B7C47 on this class), operator new 0x0002FDA0 (0x14 bytes), the node
// constructor 0x003B44C7 (its only caller is this new-expression: tmp kept at
// [ebp-0x18] under EH state 1 and the ctor's eax result used as the node) and
// in the catch funclet 0x003B66D8
// (rowed rva003B66D8, ScriptListSubrecordRemove.cpp) followed by
// _CxxThrowException(0 0). Record layout (+0x10 node head) as rowed by
// rva003B66D8 and rva003B7F8E. WorldBuilder twin 0xAB2080 (score 0.5)
// names the key lookup ScriptSetBase<ScriptGroup>::allocateEntry and builds
// the node in place (Rva003529B0 copy at node +4). The method name stays
// address-derived.
#include "ascii_string.h"

class Rva003529B0;

// 0x14-byte list node: next link then the payload copy at +4.
class Rva003B44AB
{
public:
	Rva003B44AB(const Rva003529B0 *other);

	Rva003B44AB *m_next;	// +0x00
	char m_payload[0x10];	// +0x04
};

struct Rva003B675BRecord
{
	int m_previous;		// +0x00
	int m_next;		// +0x04
	AsciiString m_name;	// +0x08
	unsigned char m_released;	// +0x0C
	unsigned char m_pad;	// +0x0D
	unsigned short m_references;	// +0x0E
	Rva003B44AB *m_nodes;	// +0x10
};

class Rva003B573E
{
public:
	void rva003B66D8(int index);
	int rva003B7C47(const StringBase<char> &key);
	int rva003B7E39(const StringBase<char> &key, const Rva003529B0 *value);

private:
	void *m_sorted[3];		// +0x00
	Rva003B675BRecord *m_records;	// +0x0C
};

int Rva003B573E::rva003B7E39(const StringBase<char> &key, const Rva003529B0 *value)
{
	int index = rva003B7C47(key);
	if (index != -1)
	{
		Rva003B675BRecord *records = m_records;
		try
		{
			Rva003B675BRecord *rec = &records[index];
			Rva003B44AB *node = new Rva003B44AB(value);
			node->m_next = rec->m_nodes;
			rec->m_nodes = node;
		}
		catch (...)
		{
			rva003B66D8(index);
			throw;
		}
	}
	return index;
}
