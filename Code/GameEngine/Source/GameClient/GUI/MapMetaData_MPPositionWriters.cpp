// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?write@Rva00300912Holder@@QAEXPAVDataChunkOutput@@@Z,
// retail 0x00300912 (134 bytes). Dedicated TU.
//
// MPPositionInfo chunk writer: opens "MPPositionInfo" v1, writes three
// flag bytes as comparisons (retail cmp-mem-bl + setne, no xor wall),
// two ints (the second is the name map's own count via size()) and the
// map keys, then closes. All callees are matched rows (openDataChunk,
// writeByte, writeInt, writeAsciiString, closeDataChunk, _M_increment).
// The element is 20 bytes (stride proven by the 0x300998 list writer's
// add-esi-0x14 loop); the class keeps the retail address token because no
// caller names it (parser-registration precedent).

#pragma optimize("t", on)
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#pragma optimize("", on)

#include "ascii_string.h"


class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short ver);
	void writeAsciiString(const AsciiString &textValue);
	void writeByte(unsigned char value);
	void writeInt(int value);
	void closeDataChunk();
};

typedef std::map<AsciiString, int> PositionNameMap;

struct Rva00300912Holder
{
	unsigned char flag0; // +0x00
	unsigned char flag1; // +0x01
	unsigned char flag2; // +0x02
	int value; // +0x04
	PositionNameMap names; // +0x08 (count at +0x0C)
	void write(DataChunkOutput *writer);
};

// ?write@Rva00300912Holder@@QAEXPAVDataChunkOutput@@@Z
void Rva00300912Holder::write(DataChunkOutput *writer)
{
	unsigned char noFlags = 0;
	writer->openDataChunk("MPPositionInfo", 1);
	writer->writeByte(flag0 != noFlags);
	writer->writeByte(flag1 != noFlags);
	writer->writeByte(flag2 != noFlags);
	writer->writeInt(value);
	writer->writeInt((int)names.size());
	for (PositionNameMap::iterator it = names.begin(); it != names.end(); ++it)
		writer->writeAsciiString(it->first);
	writer->closeDataChunk();
}

struct Rva00300998Holder
{
	Rva00300912Holder infos[8]; // +0x00
	void writeList(DataChunkOutput *writer);
};

// ?writeList@Rva00300998Holder@@QAEXPAVDataChunkOutput@@@Z
void Rva00300998Holder::writeList(DataChunkOutput *writer)
{
	writer->openDataChunk("MPPositionList", 0);
	Rva00300912Holder *info = infos;
	int remaining = 8;
	do {
		info->write(writer);
		info++;
	} while (--remaining);
	writer->closeDataChunk();
}
