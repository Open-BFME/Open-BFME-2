// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Four EH-framed STLport _Rb_tree destructors, 56 bytes each, twins of the
// map<int, vector<unsigned> > tree destructor rowed at 0x0021E0FC
// (CreateAHeroDataDtor.cpp, whose flags this unit copies): each differs from
// it only in its clear call and its own __ehhandler, and each clear call lands
// on a tree clear rowed for the type named here.
//
//   0x004D21B4  map<int, Rva004D1B38Mapped>          clear 0x004D1EF1 (stlport_tree_erase_004D1B38.cpp)
//   0x0051097F  map<AsciiString, TreeHintRef0051030C> clear 0x0051024F (stlport_rb_tree_hint_005109b7.cpp)
//   0x005C6BF5  set<Rva0027EA49>                     clear 0x005C6B83 (stlport_rb_tree_rva0027EA49_erase.cpp)
//   0x005E4670  map<int, SBServer>                   clear 0x005E43A8 (stlport_map_int_sbserver.cpp)
//
// The value views are copied from those units. Their own units build without
// EH frames, which gives a 52-byte destructor that is not retail's. clear is
// an inline member, so it is emitted here too and equals retail's. _M_erase is
// declared extern (an MSVC extension) so that this unit calls the rowed
// _M_erase of each tree rather than emitting another copy of it.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include "ascii_string.h"

struct Rva004D1B38Mapped
{
	AsciiString m_name;
};
typedef _STL::pair<const int, Rva004D1B38Mapped> Rva004D1B38Pair;
typedef _STL::_Rb_tree<int, Rva004D1B38Pair, _STL::_Select1st<Rva004D1B38Pair>, _STL::less<int>, _STL::allocator<Rva004D1B38Pair> > Rva004D1B38Tree;

struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef0051030C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef0051030C(const TreeHintRef0051030C &other);
	~TreeHintRef0051030C();
};
typedef _STL::pair<const AsciiString, TreeHintRef0051030C> TreeHintPair0051030C;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair0051030C, _STL::_Select1st<TreeHintPair0051030C>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair0051030C> > TreeHint0051030C;

struct Rva0027EA49
{
	~Rva0027EA49();
	int m_00;
	TargetRef00217D4C *m_04;
};
bool operator<(const Rva0027EA49 &a, const Rva0027EA49 &b);
typedef _STL::_Rb_tree<Rva0027EA49, Rva0027EA49, _STL::_Identity<Rva0027EA49>, _STL::less<Rva0027EA49>, _STL::allocator<Rva0027EA49> > Rva0027EA49Tree;

struct SBServer
{
	void *m_handle;
	SBServer();
	SBServer(const SBServer &src);
	~SBServer();
};
typedef _STL::pair<const int, SBServer> SBServerPair;
typedef _STL::_Rb_tree<int, SBServerPair, _STL::_Select1st<SBServerPair>, _STL::less<int>, _STL::allocator<SBServerPair> > SBServerTree;

extern template void Rva004D1B38Tree::_M_erase(Rva004D1B38Tree::_Link_type);
extern template void TreeHint0051030C::_M_erase(TreeHint0051030C::_Link_type);
extern template void Rva0027EA49Tree::_M_erase(Rva0027EA49Tree::_Link_type);
extern template void SBServerTree::_M_erase(SBServerTree::_Link_type);

template Rva004D1B38Tree::~_Rb_tree();
template TreeHint0051030C::~_Rb_tree();
template Rva0027EA49Tree::~_Rb_tree();
template SBServerTree::~_Rb_tree();
