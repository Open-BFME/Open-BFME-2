// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003023B8@PlayerPosition@@QAEXABVAsciiString@@@Z @0x003023B8 114B.
// Evidence: PlayerPosition layout (three uchars plus int plus set at +8) proven
// by the default ctor 0x302805 and copy 0x302CE2 in MapMetaDataCopy.cpp;
// set insert at this+8 via rowed 0x5897D; Faction prefix normalization via
// startsWith 0x2BE9C plus set 0x55F5 plus concat 0x6987; caller 0x59E8F3 loops
// an INI ascii-vector and inserts each element.
#include <set>

typedef bool Bool;
typedef int Int;

#include "../../Include/Common/BfmeStringData.h"

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

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
template <> pair<Lk6AsciiSetTree::iterator, bool> Lk6AsciiSetTree::insert_unique(const AsciiString&);
template <> Lk6AsciiSetTree::iterator Lk6AsciiSetTree::insert_unique(Lk6AsciiSetTree::iterator, const AsciiString&);
template <> _Rb_tree_node<AsciiString> *Lk6AsciiSetTree::_M_create_node(const AsciiString&);
}

#include "../../Include/Common/PlayerPosition.h"

// ?rva003023B8@PlayerPosition@@QAEXABVAsciiString@@@Z
void PlayerPosition::rva003023B8(const AsciiString &name)
{
	AsciiString tmp(name);
	if (!name.startsWith("Faction")) {
		((StringBase<char> *)&tmp)->set("Faction");
		((StringBase<char> *)&tmp)->concat(*(const StringBase<char> *)&name);
	}
	factions.insert(tmp);
}
