// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?read@DataChunkTableOfContents@@QAEXAAVChunkInputStream@@@Z @0x003071E9 301B via BFME1 donor DataChunkTableOfContents.cpp
// Evidence: pinned name; caller DataChunkInput ctor 0x307351; donor game/GameEngine/Source/Common/System/DataChunkTableOfContents.cpp read plus DataChunk.cpp; retail inlines tag CkMp check and Mapping new 0x10 with StringBase getBufferForRead row.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Byte;

class ChunkInputStream
{
public:
	virtual int read(void *pData, int numBytes);
	virtual unsigned int tell(void);
	virtual bool absoluteSeek(unsigned int pos);
	virtual bool eof(void);
};

class OutputStream
{
public:
	virtual Int write(const void *pData, Int numBytes) = 0;
};

struct Mapping
{
	virtual ~Mapping();
	Mapping *next;
	AsciiString name;
	UnsignedInt id;
};

// ??1Mapping@@UAE@XZ present-unmatched
Mapping::~Mapping() {}

void *__cdecl operator new(unsigned int size);

class DataChunkTableOfContents
{
public:
	void read(ChunkInputStream &s);
	void write(OutputStream &s);

private:
	Mapping *m_list;
	Int m_listLength;
	UnsignedInt m_nextID;
	bool m_headerOpened;
};

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
		m = new Mapping;
		s.read((char *)&len, sizeof(unsigned char));

		if (len > 0)
		{
			char *str = ((StringBase<char> *)&m->name)->getBufferForRead(len);
			s.read(str, len);
			str[len] = '\0';
		}

		s.read((char *)&m->id, sizeof(UnsignedInt));
		m->next = m_list;
		m_list = m;
		m_listLength++;

		if (m->id > maxID)
			maxID = m->id;
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
	for (m = m_list; m; m = m->next)
	{
		len = m->name.getLength();
		s.write((char *)&len, sizeof(unsigned char));
		s.write(m->name.str(), len);
		s.write((char *)&m->id, sizeof(UnsignedInt));
	}
}
