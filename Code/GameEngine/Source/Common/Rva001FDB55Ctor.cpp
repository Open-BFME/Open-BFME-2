// cl: /DBFME_ASCII_DTOR_DECL /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ??0PlayerTemplateStore@@QAE@XZ @0x001FDB55 76B (WorldBuilder names its slot 5
// PlayerTemplateStore::attemptRefresh). Default ctor: base SubsystemInterface via
// the rowed ctor 0x001B4E63, vptr 0x007E1BB0, the vector at +0xC through the empty
// vector-base body 0x00211E58, the tree at +0x18 through the empty set body
// 0x000D3A71, and -1 at +0x24. Base layout (vptr + flag + value = 12B); element and
// member patterns from stlport_vector_e16_o1.cpp and stlport_asciistring_set_base.cpp.
// Retail arms early EH state 0 and state 1 for the base and the vector.
// Sole caller at 0x0022EA94. The destructor is rowed in PlayerTemplateStore.cpp.
#include <vector>
#include <set>
#include <list>
#include "ascii_string.h"
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#include "RTS/PlayerTemplateTreeView.h"

// Retail's tree destructors here keep the unwind state store before the free.
namespace _STL {
template <> inline void allocator<_Rb_tree_node<AsciiString> >::deallocate(_Rb_tree_node<AsciiString> *p, unsigned int) const { if (p != 0) PlayerTemplateTree::free(p); }
template <> inline void allocator<_Rb_tree_node<int> >::deallocate(_Rb_tree_node<int> *p, unsigned int) const { if (p != 0) PlayerTemplateTree::free(p); }
}

class INI;
class PlayerTemplate;
struct BfmeObject476 { virtual ~BfmeObject476(); unsigned char opaque[472]; BfmeObject476(); BfmeObject476(const BfmeObject476 &); BfmeObject476 &operator=(const BfmeObject476 &); };
namespace _STL { template <> vector<BfmeObject476>::~vector(); }
enum NameKeyType
{
	NAMEKEY_INVALID = -1,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};
// The store's index tree at +0x18: a set<int> whose destructor is the row 0x000730DE
// (not set<int>'s own 0x00073116) and whose clear is the row 0x00072FE6.
class Rva00072FE6 : public _STL::set<int>
{
public:
	~Rva00072FE6();
	void rva00072FE6();
};

// The seed's view of this class without its virtual init and reset: every copy of
// the vtable outside the merged unit has __purecall in slot 1, and the link keeps
// one copy of it.
class PlayerTemplateStore : public SubsystemInterface
{
public:
	PlayerTemplateStore();
	virtual ~PlayerTemplateStore();
	virtual void bfmeVtSlot1() = 0;
	bool rva001FD4E1(NameKeyType key, int *index);
	bool rva001FD367(int faction, int *outIndex) const;
	static void parsePlayerTemplateDefinition(INI *);
    const PlayerTemplate *findPlayerTemplate(NameKeyType namekey) const;
	const PlayerTemplate *getNthPlayerTemplate(int index) const;
	void getAllSideStrings(_STL::list<AsciiString> *outStringList);

    // +0x00: the vptr (retail table 0x00BE1BB0, installed at +0 by the ctor 0x001FDB55)
    _STL::vector<BfmeObject476> m_playerTemplates; // +0x0C
    Rva00072FE6 playableIndices; // +0x18
    int index24; // +0x24
};

// Retail 0x001FDB55, sole caller 0x0022EA94; WorldBuilder names vtable slot 5 PlayerTemplateStore::attemptRefresh.
// Base ctor 0x001B4E63, vptr 0x007E1BB0, vector at +0xC through _Vector_base's ctor 0x00211E58, set at +0x18 through its ctor 0x000D3A71, -1 at +0x24.
PlayerTemplateStore::PlayerTemplateStore()
{
	index24 = -1;
}

// The faction-set tree destructor 0x000589BE (rowed clear 0x00057B4B, then a null-checked free of the header).
bool operator<(const AsciiString &, const AsciiString &);
template _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, _STL::less<AsciiString>, _STL::allocator<AsciiString> >::~_Rb_tree();
