// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2 DataChunkInput version getter, transferred from the exact BFME1
// reconstruction (Code/GameEngine/Source/Common/System/DataChunk.cpp).
// Retail BFME2 keeps the same shape: null chunk stack reads zero, otherwise
// the version word at chunk+0xC with the stack head at this+0x1C.

#include "ascii_string.h"

struct InputChunk
{
	virtual void *deleteInstance(int flags);	// vtable slot 0 (MemoryPoolObject pattern)

	InputChunk *m_next;			// +0x04
	unsigned int m_id;			// +0x08
	unsigned short m_version;	// +0x0C
};

class DataChunkInput
{
public:
	unsigned short getChunkVersion();
	void clearChunkStack();

private:
	unsigned char m_pre[0x1C];
	InputChunk *m_chunkStack;	// +0x1C
};

// ?getChunkVersion@DataChunkInput@@QAEGXZ
unsigned short DataChunkInput::getChunkVersion()
{
	if (m_chunkStack == 0)
		return 0;

	return m_chunkStack->m_version;
}

// Table of contents for the chunk-name registry. Layout mirrors the ZH
// DataChunkTableOfContents (list head, entry count, next ID allocator,
// header-open flag); declaration order is what the bytes prove: retail
// stores NULL, 0, 1, false in that order.
class Mapping
{
public:
	virtual void *deleteInstance(int flags);

	Mapping *m_next;			// +0x04
	AsciiString m_name;			// +0x08
};

void operator delete(void *ptr);

class DataChunkTableOfContents
{
public:
	DataChunkTableOfContents();
	~DataChunkTableOfContents();

	Mapping *m_list;			// +0x00
	int m_listLength;			// +0x04
	unsigned int m_nextID;		// +0x08
	bool m_headerOpened;		// +0x0C

private:
	Mapping *findMapping( const AsciiString& name );
};

// ??0DataChunkTableOfContents@@QAE@XZ
DataChunkTableOfContents::DataChunkTableOfContents() :
	m_list(0),
	m_nextID(1),
	m_listLength(0),
	m_headerOpened(false)
{
}

// Retail 0x00306D5C (31B): frees every Mapping in the list head at +0 via
// the MemoryPoolObject pattern (MessageStreamListCtors.cpp precedent):
// next at +4, deleteInstance(0) through vtable slot 0, then operator
// delete on the returned block. ZH DataChunk.cpp donor proves the loop
// (next = m->next; m->deleteInstance()); BFME2's deleteInstance takes the
// int flag and returns the block. Caller is DataChunkInput teardown at
// 0x00306F41 (lea ecx,[edi+4]).
DataChunkTableOfContents::~DataChunkTableOfContents()
{
	Mapping *mapping, *next;
	for (mapping = m_list; mapping; mapping = next)
	{
		next = mapping->m_next;
		::operator delete(mapping->deleteInstance(0));
	}
}

// Retail 0x00306DA4 (40B): drains the InputChunk stack at +0x1C with the
// same deleteInstance(0)/operator-delete loop, then NULLs the head. ZH
// DataChunk.cpp donor proves the name and shape (next = c->next;
// c->deleteInstance(); m_chunkStack = NULL); BFME2's deleteInstance takes
// the int flag and returns the block. Callers are DataChunkInput teardown
// at 0x00306F16 and 0x00306DCC.
void DataChunkInput::clearChunkStack()
{
	InputChunk *chunk, *next;
	for (chunk = m_chunkStack; chunk; chunk = next)
	{
		next = chunk->m_next;
		::operator delete(chunk->deleteInstance(0));
	}
	m_chunkStack = 0;
}

// ?findMapping@DataChunkTableOfContents@@AAEPAVMapping@@ABVAsciiString@@@Z
// Retail 0x00307A2C (39B): Zero Hour's DataChunk.cpp lookup of a chunk name
// in the mapping list (name at Mapping +0x08; AsciiString compare 0x000069D6).
Mapping *DataChunkTableOfContents::findMapping( const AsciiString& name )
{
	Mapping *m;

	for( m=m_list; m; m=m->m_next )
		if (name == m->m_name )
			return m;

	return 0;
}
