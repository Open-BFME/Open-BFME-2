// cl: /DBFME_ASCII_DTOR_DECL /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ??1Rva001FDB55@@UAE@XZ @0x001FDBA1 74B: dtor via vtable 0x007E1BB0, set at +0x18 via rowed 0x000730DE, vector at +0xC via rowed 0x001FD882, base 0x001B4E74; evidence callees rowed, caller 0x001FDD64, ctor 0x001FDB55.
// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
// This destructor is a header inline in the copier unit.
#include <vector>
#include <set>
#include <list>
#include "ascii_string.h"
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

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

PlayerTemplateStore::~PlayerTemplateStore()
{
}
