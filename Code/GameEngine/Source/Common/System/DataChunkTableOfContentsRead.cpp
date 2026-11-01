// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?read@DataChunkTableOfContents@@QAEXAAVChunkInputStream@@@Z @0x003071E9 301B via BFME1 donor DataChunkTableOfContents.cpp
// Evidence: pinned name; caller DataChunkInput ctor 0x307351; donor game/GameEngine/Source/Common/System/DataChunkTableOfContents.cpp read plus DataChunk.cpp; retail inlines tag CkMp check and the 0x10-byte mapping new (as allocateID) with StringBase getBufferForRead row.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Byte;

// DataChunk.cpp's views: the stream, the output stream, the 0x10-byte mapping
// (Mapping, and the concrete object retail news, whose table 0x00807EAC the
// ledger also names ??_7Rva0030714F@@6B@) and the table of contents.
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

class Rva0030714F
{
public:
	Rva0030714F() {}
	virtual ~Rva0030714F();
private:
	char m_pad04[4];
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

class OutputStream
{
public:
    virtual int write(const void *data, int count) = 0;
};

// Zero Hour's ChunkInputStream: read is vslot 0, eof vslot 3.
class ChunkInputStream
{
public:
	virtual int read(void *buf, int numBytes) = 0;
	virtual unsigned int tell(void) = 0;
	virtual bool absoluteSeek(unsigned int pos) = 0;
	virtual bool eof(void) = 0;
};

#include <new>

// The read() consumer naturally emits the unsigned-reference instantiation.
// Its complete native leaf is 0x9FDE5..0x9FDF5 (16B): load two referents,
// unsigned compare, select the second address when first<=second, RET0.
// The previous minimum leaf ends at 0x9FDE4 and the following function starts
// at 0x9FDF5. BFME1 9cbfb551fe20dae985f91f2319d8997287b6a705's Common
// donor sweep agrees under O1/SSE/G7. Native proves this reference/tie contract;
// the global template name comes from the already compiled semantic provider.
template <typename T>
inline const T &max(const T &a, const T &b)
{
	return a > b ? a : b;
}

void DataChunkTableOfContents::read(ChunkInputStream &s)
{
	Int count, i;
	UnsignedInt maxID = 0;
	unsigned char len;
	Mapping *m;

	Byte tag[4] = {'x', 'x', 'x', 'x'};
	s.read(tag, sizeof(tag));
	if (tag[0] != 'C' || tag[1] != 'k' || tag[2] != 'M' || tag[3] != 'p')
		return;

	s.read((char *)&count, sizeof(Int));

	for (i = 0; i < count; i++)
	{
		m = (Mapping *)new Rva0030714F;
		s.read((char *)&len, sizeof(unsigned char));

		if (len > 0)
		{
			char *str = ((StringBase<char> *)&m->m_name)->getBufferForRead(len);
			s.read(str, len);
			str[len] = '\0';
		}

		s.read((char *)&m->m_id, sizeof(UnsignedInt));
		m->m_next = m_list;
		m_list = m;
		m_listLength++;

		if (m->m_id > maxID)
			maxID = m->m_id;
	}

	m_headerOpened = count > 0 && !s.eof();
	m_nextID = max(m_nextID, maxID + 1);
}

// ?write@DataChunkTableOfContents@@QAEXAAVOutputStream@@@Z
// BFME1 donor: 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/System/DataChunkTableOfContents.cpp.
// Retail 0x0030715D..0x003071E8 is the complete 140-byte RET 4 body:
// it writes CkMp, the count at +4, then each node's byte length, text, and
// id. The native list walk proves next +4, string +8, id +C; its virtual
// stream calls use slot zero. Donor supplies the writer's semantic name;
// those offsets and the canonical string header are target evidence.
// Native caller 0x003076A5 passes [esi] as stream and esi+8 as the table;
// the following code closes the output's temporary FILE at receiver+4.
void DataChunkTableOfContents::write(OutputStream &s)
{
	Mapping *m;
	unsigned char len;
	Byte tag[4] = {'C', 'k', 'M', 'p'};
	s.write(tag, sizeof(tag));
	s.write((void *)&m_listLength, sizeof(Int));
	for (m = m_list; m; m = m->m_next)
	{
		len = m->m_name.getLength();
		s.write((char *)&len, sizeof(unsigned char));
		s.write(m->m_name.str(), len);
		s.write((char *)&m->m_id, sizeof(UnsignedInt));
	}
}
