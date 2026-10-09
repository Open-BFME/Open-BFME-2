// ?rva003B7EC2@Rva003B573E@@QAEHABV?$StringBase@D@@@Z
// partial score=0.95 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
//
// ?rva003B7EC2@Rva003B573E@@QAEHABV?$StringBase@D@@@Z,
// retail 0x003B7EC2..0x003B7F31 (111B: 91B body plus the 20B catch funclet
// 0x003B7F31), thiscall ret 4.
//
// Sibling of rva003B7E39: looks up or allocates the 0x14-stride record for
// the key (rva003B7C47), then pushes a default-constructed 0x14-byte list
// node onto the record's node list at +0x10. If building the node throws,
// the record reference is dropped again (rva003B66D8) and the exception is
// rethrown. Returns the record index or -1.
//
// Evidence (target): callees read at the retail REL32s: 0x003B7C47 (pinned
// rva003B7C47 on this class), operator new 0x0002FDA0 (0x14 bytes), the
// payload constructor 0x003B40DF (rowed Rva00352900 default ctor, called at
// node+4 after the link word at +0 is zeroed) and in the catch funclet
// 0x003B66D8 (rowed rva003B66D8) followed by _CxxThrowException(0 0).
// Record layout as in ScriptListSubrecordAddRva003B7E39.cpp. The method name
// stays address-derived.
#include "ascii_string.h"

// Payload constructed in place by the rowed 0x003B40DF default constructor
// (R3ScalarFieldConstructors1.cpp); spelled inline here so the compiler sees
// its register use, as in the original unit.
extern int Gen00C1F470;

class Rva00352900
{
public:
	__declspec(noinline) Rva00352900()
	{
		m_04 = 0;
		m_08 = 0;
		m_00 = &Gen00C1F470;
		m_0C = 1;
		m_0D = 0;
		m_0E = 0;
	}
	int *m_00;
	int m_04, m_08;
	char m_0C, m_0D, m_0E;
};

// 0x14-byte list node: next link then the default-constructed payload.
class Rva003B7EC2Node
{
public:
	Rva003B7EC2Node() : m_next(0) {}

	Rva003B7EC2Node *m_next;	// +0x00
	Rva00352900 m_payload;		// +0x04
};

struct Rva003B675BRecord
{
	int m_previous;		// +0x00
	int m_next;		// +0x04
	AsciiString m_name;	// +0x08
	unsigned char m_released;	// +0x0C
	unsigned char m_pad;	// +0x0D
	unsigned short m_references;	// +0x0E
	Rva003B7EC2Node *m_nodes;	// +0x10
};

class Rva003B573E
{
public:
	void rva003B66D8(int index);
	int rva003B7C47(const StringBase<char> &key);
	int rva003B7EC2(const StringBase<char> &key);

private:
	void *m_sorted[3];		// +0x00
	Rva003B675BRecord *m_records;	// +0x0C
};

int Rva003B573E::rva003B7EC2(const StringBase<char> &key)
{
	int index = rva003B7C47(key);
	if (index != -1)
	{
		Rva003B675BRecord *records = m_records;
		try
		{
			Rva003B675BRecord *rec = &records[index];
			Rva003B7EC2Node *node = new Rva003B7EC2Node;
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
