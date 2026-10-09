// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
//
// ?rva003B8141@Rva003BRefSubrecord@@QAEHABV?$StringBase@D@@@Z,
// retail 0x003B8141..0x003B81C5 (132B: 111B body plus the 21B catch funclet),
// thiscall ret 4.
//
// Payload-less sibling of Rva003B573E::rva003B80B8: key lookup
// (rva003B7C47), a 0x58-byte new-expression whose node clears +0 inline and
// default-constructs the payload at +4 through the pinned 0x003B417E, pushed
// onto the record's node list at +0x10; the catch funclet drops the
// reference (rva003B66D8) and rethrows. The method sits on the pinned class
// Rva003BRefSubrecord, modelled as deriving the lookup/release owner
// Rva003B573E (base layout identical). Names are address-derived.
#include "ascii_string.h"


class Rva003B417E
{
public:
	Rva003B417E() throw();
	char m_data[0x54];
};

// 0x58-byte list node: next link then the default-constructed payload at +4.
class Rva003B8141Node
{
public:
	Rva003B8141Node() : m_next(0) {}

	Rva003B8141Node *m_next;	// +0x00
	Rva003B417E m_payload;		// +0x04
};

struct Rva003B675BRecord
{
	int m_previous;		// +0x00
	int m_next;		// +0x04
	AsciiString m_name;	// +0x08
	unsigned char m_released;	// +0x0C
	unsigned char m_pad;	// +0x0D
	unsigned short m_references;	// +0x0E
	Rva003B8141Node *m_nodes;	// +0x10
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

class Rva003BRefSubrecord : public Rva003B573E
{
public:
	int rva003B8141(const StringBase<char> &key);
};

int Rva003BRefSubrecord::rva003B8141(const StringBase<char> &key)
{
	int index = rva003B7C47(key);
	if (index != -1)
	{
		Rva003B675BRecord *records = m_records;
		try
		{
			Rva003B675BRecord *rec = &records[index];
			Rva003B8141Node *node = new Rva003B8141Node;
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
