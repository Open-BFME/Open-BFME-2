// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva0002CB98@Rva0002CB98@@QBE_NABVAsciiString@@@Z @0x0002CB98 28B
// Wrapper that tests membership in a nocase AsciiString set member at +0x14.
// Evidence: calls the tree _M_find at 0x0002C751, whose body compares through
// the nocase AsciiString less at 0x0002C63C (Rva0002C63CAsciiNocaseLess), so
// the key is an AsciiString, not a BitFlags as this unit once declared; the
// sibling 0x0002CBB4 inserts into a nocase AsciiString set at the same +0x14.
// WorldBuilder's SidesList::linkLibraryMaps (wb 0xa86e40) and
// Win32LocalFileSystem::getFileListInDirectory (wb 0x1651780) call the same
// _M_find (wb 0x6cedf0) on their set<AsciiString> before set::insert 0x0002CA26.
// Host class opaque, so the honest-address name stays.
#define _STLP_NO_EXCEPTIONS 1
#include <set>

#include "ascii_string.h"

struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &a, const AsciiString &b) const;
};

class Rva0002CB98
{
	unsigned char m_pad[0x14];
public:
	_STL::set<AsciiString, BfmeStringNoCaseLess, _STL::allocator<AsciiString> > m_set;
	bool rva0002CB98(const AsciiString &a) const;
};

bool Rva0002CB98::rva0002CB98(const AsciiString &a) const
{
	return m_set.find(a) != m_set.end();
}
