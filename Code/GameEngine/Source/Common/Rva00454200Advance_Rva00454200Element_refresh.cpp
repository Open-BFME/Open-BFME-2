// cl: /Ireference/shims/bfme2_ascii_common /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfmealloc /D_CRTIMP=
//
// ?refresh@Rva00454200Element@@QAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z
// retail 0x00302823, 206 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/Rva00454200Advance.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// stlport

#include <set>

#include "ascii_string.h"

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
template <> pair<Lk6AsciiSetTree::iterator, bool> Lk6AsciiSetTree::insert_unique(const AsciiString&);
template <> _Rb_tree_node<AsciiString> *Lk6AsciiSetTree::_M_create_node(const AsciiString&);
}

bool operator<(const AsciiString &left, const AsciiString &right);

#include "../../Include/Common/DataChunk.h"

struct DataChunkInfo
{
	char m_label[8];
	unsigned short m_version;
};

struct Rva00454200Element
{
	void refresh();
	bool refresh(DataChunkInput &file, DataChunkInfo *info);

private:
	unsigned char m_firstFlag;
	unsigned char m_secondFlag;
	unsigned char m_thirdFlag;
	char m_padding;
	int m_value;
	std::set<AsciiString> m_strings;
};

class Rva00454200Cursor
{
public:
	void advance();

private:
	char m_padding[0x0C];
	Rva00454200Element *m_elements;
	unsigned int m_index;
};

bool Rva00454200Element::refresh(DataChunkInput &file, DataChunkInfo *info)
{
	m_firstFlag = file.readByte() ? true : false;
	m_secondFlag = file.readByte() ? true : false;
	if (info->m_version >= 1)
	{
		m_thirdFlag = file.readByte() ? true : false;
		m_value = file.readInt();
	}
	else
	{
		m_thirdFlag = true;
		m_value = -1;
	}

	std::set<AsciiString> strings;
	int count = file.readInt();
	while (count > 0)
	{
		strings.insert(file.readAsciiString());
		--count;
	}
	m_strings.swap(strings);
	return true;
}
