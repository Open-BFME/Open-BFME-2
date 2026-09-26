// cl: /O1 /DNDEBUG /MD /EHsc
//
// Element destroy loops at 0x003B678A and 0x003B713E (41B each): they
// drain the 0x14-byte string-record elements in [start,finish),
// stepping one record back per iteration. Each element is torn down in
// two calls: the node-list drain (rowed clearRva00359330Nodes at
// 0x003B578E for the 0x678A loop, rowed clearRva003B675BNodes at
// 0x003B675B for the 0x713E loop) plus the shared 8B name-string tail
// through the ?destroy@ScriptListElementName pin at 0x00577998,
// invoked as an explicit destructor call on the re-read finish pointer
// (the Iter precedent). The typed record pointers give the 0x14 stride
// (sub for the local, add-to-memory for the range update); the loop
// condition reads start first. Same /EHsc scheduling as the drains.

void __cdecl operator delete(void *block);

class BfmeNodeZ
{
public:
	~BfmeNodeZ();

	BfmeNodeZ *m_next;
};

struct Rva00359330Record
{
	int m_previous;
	int m_next;
	void *m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	BfmeNodeZ *m_nodes;
};

void clearRva00359330Nodes(Rva00359330Record *record);

class Rva003B448C
{
public:
	~Rva003B448C();

	Rva003B448C *m_next;
};

struct Rva003B675BRecord
{
	int m_previous;
	int m_next;
	void *m_name;
	unsigned char m_released;
	unsigned char m_pad;
	unsigned short m_references;
	Rva003B448C *m_nodes;
};

void clearRva003B675BNodes(Rva003B675BRecord *record);

class ScriptListElementName
{
public:
	~ScriptListElementName();
};

struct Rva003B678ARange
{
	Rva00359330Record *m_start;
	Rva00359330Record *m_finish;
};

struct Rva003B713ERange
{
	Rva003B675BRecord *m_start;
	Rva003B675BRecord *m_finish;
};

// ?destroyRva003B678ARange@@YAXPAURva003B678ARange@@@Z
void destroyRva003B678ARange(Rva003B678ARange *range)
{
	while (range->m_start != range->m_finish) {
		Rva00359330Record *last = range->m_finish - 1;
		clearRva00359330Nodes(last);
		range->m_finish -= 1;
		((ScriptListElementName *)range->m_finish)->~ScriptListElementName();
	}
}

// ?destroyRva003B713ERange@@YAXPAURva003B713ERange@@@Z
void destroyRva003B713ERange(Rva003B713ERange *range)
{
	while (range->m_start != range->m_finish) {
		Rva003B675BRecord *last = range->m_finish - 1;
		clearRva003B675BNodes(last);
		range->m_finish -= 1;
		((ScriptListElementName *)range->m_finish)->~ScriptListElementName();
	}
}
