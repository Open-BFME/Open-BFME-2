// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "ascii_string.h"

// ?rva003B66D8@Rva003B573E@@QAEXH@Z @0x003B66D8 (131B): remove record at index
// from the 0x14-stride ScriptList subrecord. Same object as the rowed search
// 0x003B573E (thiscall on same this): dec references at +0xE, mark released
// at +0xC, return while nodes at +0x10 remain; else locate sorted position via
// search, unlink prev/next with tail at +0x1C, push to free list at +0x18,
// release the name buffer, erase the sorted entry. Evidence: chain from
// 0x003B573E, record shape from Rva003B675BRecord, subrecord layout of two
// vectors plus two ints from ScriptListSubrecordCtor.

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

void __cdecl operator delete(void *block);

class BfmeNodeZ
{
public:
	~BfmeNodeZ();
	BfmeNodeZ *m_next;
};

class Rva003B448C
{
public:
	~Rva003B448C();
	Rva003B448C *m_next;
};

class Rva003B573E
{
public:
	int rva003B573E(const StringBase<char> &key);
	int rva003B6633(const StringBase<char> &key);
	void rva003B66D8(int index);
	int rva003B7C47(const StringBase<char> &key);
	int rva003B7F8E(Rva003B573E *other, int index);
	int rva003B820D(Rva003B573E *other, int index);
	void rva003B7096(int index);
	void rva003B71B4(int index);
private:
	_STL::vector<void *> m_sorted; // +0x00
	_STL::vector<Rva003B675BRecord> m_records; // +0x0C
	int m_freeHead; // +0x18
	int m_tail; // +0x1C
};

void Rva003B573E::rva003B66D8(int index)
{
	Rva003B675BRecord *rec = &m_records[index];
	--rec->m_references;
	rec->m_released = 1;
	if (rec->m_nodes != 0)
		return;
	int pos = rva003B573E(*(const StringBase<char> *)&rec->m_name);
	if (rec->m_previous != -1)
		m_records[rec->m_previous].m_next = rec->m_next;
	if (rec->m_next != -1)
		m_records[rec->m_next].m_previous = rec->m_previous;
	else
		m_tail = rec->m_previous;
	rec->m_previous = m_freeHead;
	m_freeHead = index;
	rec->m_name.~AsciiString();
	m_sorted.erase(m_sorted.begin() + pos);
}

int Rva003B573E::rva003B6633(const StringBase<char> &key)
{
	int pos = rva003B573E(key);
	if ((unsigned int)pos < m_sorted.size()) {
		int idx = (int)m_sorted[pos];
		if ((*(const StringBase<char> *)&m_records[idx].m_name).compare(key) == 0)
			return idx;
	}
	return -1;
}

void Rva003B573E::rva003B71B4(int index)
{
	Rva003B675BRecord *rec = &m_records[index];
	BfmeNodeZ *nd = (BfmeNodeZ *)rec->m_nodes;
	rec->m_nodes = nd->m_next;
	delete nd;
	rva003B66D8(index);
}

// ?rva003B7096@Rva003B573E@@QAEXH@Z @0x003B7096 (52B): pop head node with the
// rowed Rva003B448C dtor then remove the record via rowed rva003B66D8. Twin of
// rowed rva003B71B4 which uses the pinned BfmeNodeZ dtor. Evidence: chain from
// 0x003B66D8, same 0x14-stride unlink plus delete plus tail remove shape,
// callers at 0x003B70F8 and 0x003B77F8.
void Rva003B573E::rva003B7096(int index)
{
	Rva003B675BRecord *rec = &m_records[index];
	Rva003B448C *nd = (Rva003B448C *)rec->m_nodes;
	rec->m_nodes = nd->m_next;
	delete nd;
	rva003B66D8(index);
}

// Native 0x003B7F8E..0x003B7FE0: transfer the first linked node from another
// instance's indexed 0x14-byte record to the local record with the same key.
// The key is at +8 and the node head at +0x10, as independently established
// by rva003B66D8. Method spelling is address-derived; identity unknown.
int Rva003B573E::rva003B7F8E(Rva003B573E *other, int index)
{
	Rva003B675BRecord *source = &other->m_records[index];
	int destination = rva003B7C47(*(const StringBase<char> *)&source->m_name);
	if (destination == -1)
		return -1;
	BfmeNodeZ *node = (BfmeNodeZ *)source->m_nodes;
	Rva003B675BRecord *target = &m_records[destination];
	source->m_nodes = node->m_next;
	node->m_next = (BfmeNodeZ *)target->m_nodes;
	target->m_nodes = node;
	other->rva003B66D8(index);
	return destination;
}

// Native 0x003B820D..0x003B825F: a separate transfer entry, called from
// 0x003B847B on the ScriptList subobject at +0x2C. Its native key, indexed
// record, node-link and removal operations independently agree with the
// +0x0C subobject entry above. Original class/method identities are unknown.
int Rva003B573E::rva003B820D(Rva003B573E *other, int index)
{
	Rva003B675BRecord *source = &other->m_records[index];
	int destination = rva003B7C47(*(const StringBase<char> *)&source->m_name);
	if (destination == -1)
		return -1;
	BfmeNodeZ *node = (BfmeNodeZ *)source->m_nodes;
	Rva003B675BRecord *target = &m_records[destination];
	source->m_nodes = node->m_next;
	node->m_next = (BfmeNodeZ *)target->m_nodes;
	target->m_nodes = node;
	other->rva003B66D8(index);
	return destination;
}
