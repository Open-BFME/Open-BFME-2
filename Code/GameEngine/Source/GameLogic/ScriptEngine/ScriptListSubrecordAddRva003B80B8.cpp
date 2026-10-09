// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD /EHsc
//
// ?rva003B80B8@Rva003B573E@@QAEHABV?$StringBase@D@@PAH@Z,
// retail 0x003B80B8..0x003B8141 (137B: 116B body plus the 21B catch funclet),
// thiscall ret 8.
//
// Same shape as Rva003B573E::rva003B7E39 (ScriptListSubrecordAddRva003B7E39.cpp)
// with an int* payload: key lookup (rva003B7C47), a 0x58-byte new-expression
// built by the rowed 0x003B770B constructor (int* argument), pushed onto the
// record's node list at +0x10; the catch funclet drops the reference again
// (rva003B66D8) and rethrows. Structural twin only; the class and the node
// type name are address-derived.
#include "ascii_string.h"


// 0x58-byte list node: next link then the payload copy at +4.
class Rva003B770B
{
public:
	Rva003B770B(int *other);

	Rva003B770B *m_next;	// +0x00
	char m_payload[0x54];	// +0x04 (embedded 0x003B7448 object)
};

struct Rva003B675BRecord
{
	int m_previous;		// +0x00
	int m_next;		// +0x04
	AsciiString m_name;	// +0x08
	unsigned char m_released;	// +0x0C
	unsigned char m_pad;	// +0x0D
	unsigned short m_references;	// +0x0E
	Rva003B770B *m_nodes;	// +0x10
};

class Rva003B573E
{
public:
	void rva003B66D8(int index);
	int rva003B7C47(const StringBase<char> &key);
	int rva003B80B8(const StringBase<char> &key, int *value);

private:
	void *m_sorted[3];		// +0x00
	Rva003B675BRecord *m_records;	// +0x0C
};

int Rva003B573E::rva003B80B8(const StringBase<char> &key, int *value)
{
	int index = rva003B7C47(key);
	if (index != -1)
	{
		Rva003B675BRecord *records = m_records;
		try
		{
			Rva003B675BRecord *rec = &records[index];
			Rva003B770B *node = new Rva003B770B(value);
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
