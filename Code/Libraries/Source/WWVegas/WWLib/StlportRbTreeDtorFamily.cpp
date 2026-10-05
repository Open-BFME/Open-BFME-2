// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport _Rb_tree<...>::~_Rb_tree (56 bytes: EH frame, clear(), then free
// the header node) for trees whose clear() is already rowed. Every member is
// the same-shape sibling of the WaypointTree destructor at 0x0022D7FC
// (WaypointTreeCleanup.cpp, whose flags these are): only the clear REL32
// differs, and it reads the address the ledger names for that tree's clear.
// Value types are declared with just the destructor clear() needs.
//
//   ~_Rb_tree   clear       tree (clear row's unit)
//   0x00384E28  0x00383F13  AsciiString -> PlayerInfo, AsciiComparator (PeerDefs.cpp)
//   0x0021D61F  0x0021CFD1  set<BfmeStringRecord0021A940> (stlport_rb_tree_bfme0021A940_erase.cpp)
//   0x0032C36B  0x0032BEBF  pair<AsciiString, AsciiString> -> int (SidesListTeamsInfoRecClear.cpp)
#include <map>
#include "ascii_string.h"

class PlayerInfo
{
public:
	~PlayerInfo();
private:
	char m_data[0x30];
};
struct AsciiComparator
{
	bool operator()(AsciiString s1, AsciiString s2) const;
};
typedef _STL::pair<const AsciiString, PlayerInfo> PlayerInfoMapValue;
typedef _STL::_Rb_tree<AsciiString, PlayerInfoMapValue, _STL::_Select1st<PlayerInfoMapValue>, AsciiComparator, _STL::allocator<PlayerInfoMapValue> > PlayerInfoMapTree;
template PlayerInfoMapTree::~_Rb_tree();

struct BfmeStringRecord0021A940
{
	~BfmeStringRecord0021A940();
	unsigned char m_data[20];
};
typedef _STL::_Rb_tree<BfmeStringRecord0021A940, BfmeStringRecord0021A940, _STL::_Identity<BfmeStringRecord0021A940>, _STL::less<BfmeStringRecord0021A940>, _STL::allocator<BfmeStringRecord0021A940> > BfmeStringRecord0021A940SetTree;
template BfmeStringRecord0021A940SetTree::~_Rb_tree();

typedef _STL::pair<AsciiString, AsciiString> AsciiStringPairKey;
typedef _STL::pair<const AsciiStringPairKey, int> AsciiStringPairIntValue;
typedef _STL::_Rb_tree<AsciiStringPairKey, AsciiStringPairIntValue, _STL::_Select1st<AsciiStringPairIntValue>, _STL::less<AsciiStringPairKey>, _STL::allocator<AsciiStringPairIntValue> > AsciiStringPairIntTree;
template AsciiStringPairIntTree::~_Rb_tree();
