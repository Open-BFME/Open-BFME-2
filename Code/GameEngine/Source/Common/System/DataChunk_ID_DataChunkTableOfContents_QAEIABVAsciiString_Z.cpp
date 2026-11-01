// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?getID@DataChunkTableOfContents@@QAEIABVAsciiString@@@Z, retail 0x00307A53
// (23 bytes): Zero Hour's DataChunkTableOfContents::getID. findMapping
// (0x00307A2C) on the name, then the mapping's id at +0x0C or zero; Zero Hour's
// DEBUG_CRASH is compiled out. Spelled on DataChunk.cpp's Mapping and table of
// contents views, the TU retail built it in; it replaces the Zero Hour donor
// compile (Common/DataChunk.h through PreRTS.h) this body was first placed with.
#include "ascii_string.h"

class ChunkInputStream;
class OutputStream;

class Mapping
{
public:
	virtual void *deleteInstance(int flags);

	Mapping *m_next;			// +0x04
	AsciiString m_name;			// +0x08
	unsigned int m_id;			// +0x0C
};

class DataChunkTableOfContents
{
public:
    DataChunkTableOfContents() : m_list(0), m_nextID(1), m_listLength(0), m_headerOpened(false) {}
    ~DataChunkTableOfContents();
    void read(ChunkInputStream &s);
    void write(OutputStream &stream);
    unsigned int allocateID(const AsciiString &name);
    unsigned int getID(const AsciiString &name);
    AsciiString getName(unsigned int id);

    Mapping *m_list;
    int m_listLength;
    unsigned int m_nextID;
    bool m_headerOpened;

private:
    Mapping *findMapping(const AsciiString &name);
};

unsigned int DataChunkTableOfContents::getID(const AsciiString &name)
{
	Mapping *mapping = findMapping(name);

	if (mapping)
		return mapping->m_id;

	return 0;
}
