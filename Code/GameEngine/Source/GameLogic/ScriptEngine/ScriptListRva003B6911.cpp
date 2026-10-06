// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "ascii_string.h"

// ?rva003B6911@ScriptList@@QAEPAXABV?$StringBase@D@@@Z @0x003B6911 (41B): lookup
// m_nodes+4 through the +0x2C subrecord. Same ScriptList with two 0x20-byte
// subrecords from ScriptListCtor (+0x0C/+0x2C); +0x38 is the second subrecord's
// sorted-records begin. Forwards key to rowed 0x003B6633 wrapper; -1 gives
// NULL else record m_nodes +4. Evidence: chain from just-landed 0x003B6633,
// ScriptListCtor layout, caller 0x00204F3B null-checks the result.

struct Rva003B675BRecord
{
	int m_previous; // +0x00
	int m_next; // +0x04
	AsciiString m_name; // +0x08
	unsigned char m_released; // +0x0C
	unsigned char m_pad; // +0x0D
	unsigned short m_references; // +0x0E
	void *m_nodes; // +0x10
};

class Rva003B573E
{
public:
	int rva003B6633(const StringBase<char> &key);
	_STL::vector<void *> m_sorted; // +0x00
	_STL::vector<Rva003B675BRecord> m_records; // +0x0C
	int m_freeHead; // +0x18
	int m_tail; // +0x1C
};

class ScriptList
{
public:
	void *rva003B68E8(const StringBase<char> &key);
	void *rva003B6911(const StringBase<char> &key);
private:
	void *m_vtable; // +0x00
	void *m_firstGroup; // +0x04
	void *m_firstScript; // +0x08
	Rva003B573E m_first; // +0x0C
	Rva003B573E m_second; // +0x2C
};

// 0x003B68E8 (41B): first ScriptList subrecord lookup, returning the node
// chain at record m_nodes + 4. The target reads subrecord +0x0C and record
// stride 0x14; identity/layout follow the ScriptList subrecord evidence above.
void *ScriptList::rva003B68E8(const StringBase<char> &key)
{
	int idx = m_first.rva003B6633(key);
	if (idx != -1)
		return (void *)((char *)m_first.m_records[idx].m_nodes + 4);
	return 0;
}

void *ScriptList::rva003B6911(const StringBase<char> &key)
{
	int idx = m_second.rva003B6633(key);
	if (idx != -1)
		return (void *)((char *)m_second.m_records[idx].m_nodes + 4);
	return 0;
}
