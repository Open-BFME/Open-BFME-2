// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// DataChunkInput::getChunkLabel, retail 0x003074D7, 51 bytes.
//
// Ported from the Zero Hour reference
// (GameEngine/Source/Common/System/DataChunk.cpp, getChunkLabel).
// Retail returns empty AsciiString when no chunk is open, otherwise the
// table name for the current chunk id via the rowed getName at 0x003070F1.
// Evidence: m_chunkStack at +0x1C with id at +8; empty "" via pinned
// AsciiString char ctor at 0x00037BA0; getName row 0x003070F1.

typedef unsigned int UnsignedInt;

#include "ascii_string.h"

struct InputChunk
{
	void *m_vtable; ///< retail +0x00
	void *m_next; ///< retail +0x04
	UnsignedInt m_id; ///< retail +0x08
};

class DataChunkTableOfContents
{
public:
	AsciiString getName(UnsignedInt id);

private:
	void *m_list; ///< retail this+0x00
	int m_listLength; ///< retail +0x04
	UnsignedInt m_nextID; ///< retail +0x08
	bool m_headerOpened; ///< retail +0x0C
};

class DataChunkInput
{
public:
	AsciiString getChunkLabel();

private:
	void *m_file; ///< retail this+0x00
	DataChunkTableOfContents m_contents; ///< retail this+0x04 (0x10 bytes)
	int m_fileposOfFirstChunk; ///< retail this+0x14
	void *m_parserList; ///< retail this+0x18
	InputChunk *m_chunkStack; ///< retail this+0x1C
};

AsciiString DataChunkInput::getChunkLabel()
{
	if (m_chunkStack == 0)
		return AsciiString("");
	return m_contents.getName(m_chunkStack->m_id);
}
