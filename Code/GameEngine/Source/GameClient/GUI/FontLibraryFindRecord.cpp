// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva002186A6@FontLibrary@@QAEPAXPBVAsciiString@@M@Z, retail 0x002186A6, 69 bytes.
// FontLibrary record lookup called by pinned getFont at 0x002189E1.
// BFME1 donor (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/FontLibraryBFMERetail_getFont.cpp:
// bfmeFindRecord): AsciiString table find, int sizeKey from float, int-map find,
// default-record fallback, second-pointer return. BFME2 deltas (all retail-measured):
// table map lives at this+0x14, size-table records at table+0x0C with default at +0x08,
// float-to-int via cvttss2si (/arch:SSE). True member types are
// map<AsciiString,BfmeFontSizeTable*> and map<int,UnsignedInt>; they are spelled
// map<AsciiString,AsciiString> and map<int,int> so the emitted _M_find calls name
// the rowed workers at 0x001F8437 and 0x00388F63 (identical tree mechanics;
// LocomotorStoreFindTemplate precedent), the stored pointer recast from second.

#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

typedef int Int;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

struct BfmeFontSizeTable
{
	unsigned char m_pad[8];
	void *m_defaultRecord;
	_STL::map<int, int> m_records;
};

class GameFont;

struct BfmeFontRecord
{
	unsigned char m_pad[8];
	bool m_flag08; // +0x08
};

class FontLibrary
{
public:
	void *rva002186A6(const AsciiString *name, float size);
	GameFont *getFont(const AsciiString *name, float size, bool bold);
	GameFont *rva0021857E(const AsciiString *name, float size, bool bold, int style);
private:
	char m_pad[0x14];
	_STL::map<AsciiString, AsciiString> m_tables;
};

void *FontLibrary::rva002186A6(const AsciiString *name, float size)
{
	_STL::map<AsciiString, AsciiString>::iterator table = m_tables.find(*name);
	if (table == m_tables.end())
		return 0;
	int sizeKey = (int)size;
	BfmeFontSizeTable *sizes = *(BfmeFontSizeTable **)&table->second;
	_STL::map<int, int>::iterator record = sizes->m_records.find(sizeKey);
	if (record == sizes->m_records.end())
		return sizes->m_defaultRecord;
	return (void *)record->second;
}

// ?getFont@FontLibrary@@QAEPAVGameFont@@PBVAsciiString@@M_N@Z, retail
// 0x002189E1 (66B). BFME 2's getFont looks the name/size record up (above)
// to choose a style, 4 when the record's +8 flag is set or no record exists,
// else 1, and hands everything to the styled lookup 0x0021857E (pinned).
GameFont *FontLibrary::getFont(const AsciiString *name, float size, bool bold)
{
	bool flag = true;
	BfmeFontRecord *record = (BfmeFontRecord *)rva002186A6(name, size);
	if (record)
		flag = record->m_flag08;
	return rva0021857E(name, size, bold, flag ? 4 : 1);
}
