// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
// Reuse the non-owning x86 address word and its verified deque providers from
// BfmeOwnerZKRelink.cpp. Here each word holds a node address, not ownership.
struct BfmeScriptSlotAddress { unsigned int address; };
namespace _STL {
template<> struct __type_traits<BfmeScriptSlotAddress> : __type_traits_aux<1> {};
}
#include <deque>
namespace _STL {
// Keep the independently compiled base destructor as the selected provider.
// Its definition in this unit would let MSVC remove the final unwind-state
// update, although the native deep-copy bodies retain that update.
template<> _Deque_base<BfmeScriptSlotAddress, allocator<BfmeScriptSlotAddress> >::~_Deque_base();
}
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

class Rva003B7EC2View
{
public:
	int rva003B7EC2(int key);
};

struct Rva003B8337Node
{
	Rva003B8337Node() : m_data(0), m_index(-1), m_refs(0) {}
	void *m_data;
	int m_index;
	int m_refs;
};

class Rva003B573E
{
public:
	Rva003B8337Node *rva003B8337(int key);
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

Rva003B8337Node *Rva003B573E::rva003B8337(int key)
{
	int index = reinterpret_cast<Rva003B7EC2View *>(&m_records)->rva003B7EC2(key);
	if (index != -1)
	{
		Rva003B8337Node *node = new Rva003B8337Node;
		node->m_index = index;
		node->m_refs = *reinterpret_cast<const short *>(m_freeHead + index * 20 + 0xe);
		return node;
	}
	return 0;
}

// The existing record-assignment provider's measured 0x14-byte view. Its
// name remains address-derived; the WorldBuilder lead does not establish the
// original template argument spelling for this retail instantiation.
class Rva003B32E5
{
public:
	Rva003B32E5 &operator=(const Rva003B32E5 &other);
	int previous;
	int next;
	AsciiString name;
	unsigned char released;
	unsigned short references;
	void *nodes;
};

// Native new(0x14), link at +0 and the verified pointer-copy constructor
// 0x003B44AB establish this complete storage extent. Payload identity is not
// inferred from the WorldBuilder ScriptGroup template name.
class Rva003B44AB
{
public:
	Rva003B44AB(const Rva003B44AB *other);
	Rva003B44AB *next;
	char payload[16];
};

void clearRva003B675BNodes(Rva003B675BRecord *record);

// WorldBuilder AB33E0 supplies the ScriptSetBase<ScriptGroup>::deepCopy
// algorithm: assign the record, collect its nodes, copy in reverse order,
// and drain the destination on a throwing copy. Retail's complete extent is
// 003B7FE0..003B80B8, including its catch and epilogue; the 171-byte Ghidra
// fragment alone omits both. All provider names below already have verified
// bodies. The local deque holds borrowed addresses of nodes.
void rva003B7FE0(Rva003B32E5 *destination, const Rva003B32E5 *source)
{
	*destination = *source;
	destination->nodes = 0;
	_STL::deque<BfmeScriptSlotAddress> nodes;
	BfmeScriptSlotAddress node;
	node.address = reinterpret_cast<unsigned int>(source->nodes);
	for (; node.address; node.address = reinterpret_cast<unsigned int>(reinterpret_cast<Rva003B44AB *>(node.address)->next))
		nodes.push_back(node);
	try {
		while (!nodes.empty()) {
			Rva003B44AB *copy = new Rva003B44AB(reinterpret_cast<const Rva003B44AB *>(nodes.back().address));
			nodes.pop_back();
			copy->next = static_cast<Rva003B44AB *>(destination->nodes);
			destination->nodes = copy;
		}
	} catch (...) {
		clearRva003B675BNodes(reinterpret_cast<Rva003B675BRecord *>(destination));
		throw;
	}
}

class Rva003B76EF
{
public:
	// Preserve the already verified provider's argument spelling. Its native
	// constructor copies from source+4 into this+4, with link word at +0.
	Rva003B76EF(int *other);
	Rva003B76EF *next;
	char payload[84];
};

struct Rva00359330Record;
void clearRva00359330Nodes(Rva00359330Record *record);

// WB AB4D60 is the Script specialization's independent deep-copy entry.
// Native 003B825F..003B8337 allocates 0x58-byte nodes, calls 003B76EF,
// and drains through 003B578E on failure. The rest of the whole body and
// EH graph independently agree with the record/borrowed-deque algorithm.
void rva003B825F(Rva003B32E5 *destination, const Rva003B32E5 *source)
{
	*destination = *source;
	destination->nodes = 0;
	_STL::deque<BfmeScriptSlotAddress> nodes;
	BfmeScriptSlotAddress node;
	node.address = reinterpret_cast<unsigned int>(source->nodes);
	for (; node.address; node.address = reinterpret_cast<unsigned int>(reinterpret_cast<Rva003B76EF *>(node.address)->next))
		nodes.push_back(node);
	try {
		while (!nodes.empty()) {
			Rva003B76EF *copy = new Rva003B76EF(reinterpret_cast<int *>(nodes.back().address));
			nodes.pop_back();
			copy->next = static_cast<Rva003B76EF *>(destination->nodes);
			destination->nodes = copy;
		}
	} catch (...) {
		clearRva00359330Nodes(reinterpret_cast<Rva00359330Record *>(destination));
		throw;
	}
}
