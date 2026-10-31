// cl: /DBFME_ASCII_DTOR_DECL /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ?init@PlayerTemplateStore@@UAEXXZ, retail 0x001FF223 (95 bytes): slot 1 of the
// subsystem vtable 0x007E1BB0 whose destructor is rowed in
// Rva001FDB55Dtor.cpp (vector of 0x1DC-byte Overridable records at +0x0C,
// the set at +0x18, the state word at +0x24). As Zero Hour's INI stores
// init: every record drops its INI overrides (Overridable::deleteOverrides
// 0x001E35ED), the vector is emptied (rowed erase 0x001FEFB9), the set is
// cleared (0x00072FE6) and the state returns to -1. Storage view: no
// constructor or destructor is defined here.
#include <vector>
#include <set>
#include <list>
#include "ascii_string.h"
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class INI;
class Image;
struct BfmeObject476 { virtual ~BfmeObject476(); unsigned char opaque[472]; BfmeObject476(); BfmeObject476(const BfmeObject476 &); BfmeObject476 &operator=(const BfmeObject476 &); };
extern template void _STL::vector<BfmeObject476>::push_back(const BfmeObject476 &);
namespace _STL { template <> vector<BfmeObject476>::~vector(); }
// bfme link decl-only BfmeObject476
namespace _STL { template <> BfmeObject476 * vector<BfmeObject476, allocator<BfmeObject476> >::erase(BfmeObject476 *, BfmeObject476 *); }

enum NameKeyType
{
	NAMEKEY_INVALID = -1,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};
class Overridable
{
public:
	Overridable *deleteOverrides();
	const Overridable *getFinalOverride() const;

	virtual ~Overridable();
	Overridable *m_nextOverride;
	bool m_isOverride;
    char pad09[3];
	int m_extra0C;
};
namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class A, class B> struct pair;
template <class K, class V, class C, class A> class map;
template <> class map<int, float, less<int>, allocator<pair<const int, float> > >
{
public:
	float &operator[](const int &key);
private:
	unsigned char m_tree[0xC];
};
template <> class map<int, int, less<int>, allocator<pair<const int, int> > >
{
public:
	int &operator[](const int &key);
private:
	unsigned char m_tree[0xC];
};
}
typedef _STL::map<int, float, _STL::less<int>, _STL::allocator<_STL::pair<const int, float> > > ProductionChangeMap;
typedef _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > ProductionVeterancyMap;
class Rva001FDE3F
{
public:
	float &rva001FDE3F(const AsciiString &key);
private:
	unsigned char m_table[0x14]; // +0x00
};
class PlayerTemplate : public Overridable
{
public:
	PlayerTemplate();
    virtual ~PlayerTemplate();
    static void parseStartMoney(INI *ini, void *instance, void *store, const void *userData);
    const Image *getFlagWaterMarkImage() const;
    const Image *getEnabledImage() const;
    int rva001FD234() const;
    const Image *rva001FD23F() const;
protected:
	static void parseProductionCostChange(INI *ini, void *instance, void *store, const void *userData);
	static void parseProductionTimeChange(INI *ini, void *instance, void *store, const void *userData);
	static void parseProductionVeterancyLevel(INI *ini, void *instance, void *store, const void *userData);
public:
    NameKeyType m_nameKey; // +0x10
    char display14[4];
    AsciiString side;
    char beforeF4[0xF4 - 0x1C];
    ProductionChangeMap m_productionCostChanges;
    Rva001FDE3F m_productionTimeChanges;
    ProductionVeterancyMap m_productionVeterancyLevels;
    char before150[0x150 - 0x120];
    bool flag150,flag151;
    char tail152[0x170 - 0x152];
    AsciiString m_170;
    AsciiString m_174;
    char m_pad178[0x1D8 - 0x178];
    AsciiString m_1D8;
};
class PlayerTemplateVector
{
public:
	PlayerTemplate &operator[](int index) { return m_first[index]; }
	unsigned size() const { return static_cast<unsigned>(m_last - m_first); }
	const PlayerTemplate &operator[](int index) const { return m_first[index]; }

	PlayerTemplate *m_first;
	PlayerTemplate *m_last;
    PlayerTemplate *m_capacity;
    void push_back(const PlayerTemplate &pt) { reinterpret_cast<_STL::vector<BfmeObject476> *>(this)->push_back(reinterpret_cast<const BfmeObject476 &>(pt)); }
};

// The store's index tree at +0x18: a set<int> whose destructor is the row 0x000730DE
// (not set<int>'s own 0x00073116) and whose clear is the row 0x00072FE6.
class Rva00072FE6 : public _STL::set<int>
{
public:
	~Rva00072FE6();
	void rva00072FE6();
};

class PlayerTemplateStore : public SubsystemInterface
{
public:
	PlayerTemplateStore();
	virtual ~PlayerTemplateStore();
	virtual void init();
	virtual void reset();
	bool rva001FD4E1(NameKeyType key, int *index);
	bool rva001FD367(int faction, int *outIndex) const;
	static void parsePlayerTemplateDefinition(INI *);
    const PlayerTemplate *findPlayerTemplate(NameKeyType namekey) const;
	const PlayerTemplate *getNthPlayerTemplate(int index) const;
	void getAllSideStrings(_STL::list<AsciiString> *outStringList);
    bool showReload() const { return m_flag; }
    PlayerTemplateVector &templates() { return *reinterpret_cast<PlayerTemplateVector *>(&m_playerTemplates); }
    const PlayerTemplateVector &templates() const { return *reinterpret_cast<const PlayerTemplateVector *>(&m_playerTemplates); }

    // +0x00: the vptr (retail table 0x00BE1BB0, installed at +0 by the ctor 0x001FDB55)
    _STL::vector<BfmeObject476> m_playerTemplates; // +0x0C
    Rva00072FE6 playableIndices; // +0x18
    int index24; // +0x24
};

void PlayerTemplateStore::init()
{
	for (unsigned int i = 0; i < templates().size(); ++i)
		templates()[i].deleteOverrides();
	m_playerTemplates.clear();
	playableIndices.rva00072FE6();
	index24 = -1;
}
