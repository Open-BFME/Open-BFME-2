// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
//
// ?rva003B7EC2@Rva003B7EC2View@@QAEHH@Z, retail 0x003B7EC2..0x003B7F46
// (132B: 111B body plus the 21B catch funclet at 0x003B7F31), thiscall ret 4.
//
// Sibling of Rva003BRefSubrecord::rva003B8141 with the 0x14-byte node whose
// payload at +4 is the rowed default ctor 0x003B40DF (Rva00352900): key
// lookup (rva003B7C47), new node pushed onto the record's list at +0x10,
// catch funclet releases the reference (rva003B66D8) and rethrows. The pin
// spells the parameter as int; retail passes the incoming argument slot
// straight to the lookup (a reference there), so it is forwarded as such.
// Names are address-derived.
#include "ascii_string.h"


extern int Gen00C1F470;

class Rva00352900
{
public:
	Rva00352900();
	int *m_00;
	int m_04, m_08;
	char m_0C, m_0D, m_0E;
};

// Defined ahead of its caller so the compiler sees which registers it uses
// (retail keeps the new-expression result in edx across the call).
Rva00352900::Rva00352900()
{
	m_04 = 0;
	m_08 = 0;
	m_00 = &Gen00C1F470;
	m_0C = 1;
	m_0D = 0;
	m_0E = 0;
}

// 0x14-byte list node: next link then the default-constructed payload at +4.
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

protected:
	void *m_sorted[3];		// +0x00
	Rva003B675BRecord *m_records;	// +0x0C
};

class Rva003B7EC2View : public Rva003B573E
{
public:
	int rva003B7EC2(int key);
};

int Rva003B7EC2View::rva003B7EC2(int key)
{
	int index = rva003B7C47(*reinterpret_cast<const StringBase<char> *>(key));
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
