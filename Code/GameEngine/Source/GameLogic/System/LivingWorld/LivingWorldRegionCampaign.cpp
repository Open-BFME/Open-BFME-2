// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// LivingWorldRegionCampaign.cpp -- the "LivingWorldRegionCampaign" INI block:
// its block parse (retail 0x00210A14, registered by the block-parse node at
// VA 0x00DB993C with that token) and the campaign constructor it calls
// (retail 0x0021076F). The field table the parse applies (VA 0x00BE4120)
// names the members: Region, RegionBonusArmy/Resource/Legendary,
// HeroOnly/Small/MediumArmyCommandPoints, ArmyPlacementPos, ArmyRetreatRounds,
// ArmyCarryoverPoints, RegionConqueredSound, RegionEffectsManagerName and
// ConcurrentRegionBonus. The destructor is rowed in
// LivingWorldRegionManager.cpp under its deleting dtor's placeholder
// (Rva002109F8); the member layout here is the constructor's own.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <hash_map>
#include <vector>

#include "ascii_string.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL {
// end() and the fill insert(pos, n, x) are taken inline, as retail's
// hashtable::_M_initialize_buckets does (59 bytes: it reads _M_finish and
// calls the rowed _M_fill_insert); dllimport + forceinline emits no copy.
template <> __declspec(dllimport) __forceinline void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline void vector<void*>::insert(void **pos, size_t n, void *const &x)
{ _M_fill_insert(pos, n, x); }
}
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
// bfme link decl-only end

typedef int Int;

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);					// 0x0002DF97
	void initFromINI(void *what, const FieldParse *parseTable);	// 0x0002DE78
	static void parseInt(INI *, void *, void *, const void *);
	static void parseAsciiString(INI *, void *, void *, const void *);
	static void Rva002F592_ParseArmyPlacementPos(INI *, void *, void *, const void *);
};

// ArmyPlacementPos elements: the Coord2D INI::Rva002F592_ParseArmyPlacementPos
// appends, spelled BfmeE8 as that unit does.
struct BfmeE8
{
	float x;
	float y;
};

// The +0x38 table's element, as StlSweepW5Rva0021072A.cpp spells it (its
// default ctor 0x0021072A is rowed there).
struct Rva0021072AElement
{
	Rva0021072AElement();
	Rva0021072AElement(const Rva0021072AElement &);
	Rva0021072AElement &operator=(const Rva0021072AElement &);
	~Rva0021072AElement() {}
	char bytes[8];
	bool operator==(const Rva0021072AElement &) const;
};

// The 0x30-byte object the constructor allocates at +0x4C (rowed ctor).
class Rva003EF77E
{
public:
	Rva003EF77E();

private:
	unsigned char m_bytes[0x30];
};

class Rva0020E89C;
class Rva002105A6;

class LivingWorldRegionCampaign
{
public:
	LivingWorldRegionCampaign(const AsciiString &name);

	AsciiString m_name;										// +0x00
	AsciiString m_regionBonusArmy;							// +0x04
	AsciiString m_regionBonusResource;						// +0x08
	AsciiString m_regionBonusLegendary;						// +0x0C
	Int m_heroOnlyArmyCommandPoints;						// +0x10
	Int m_smallArmyCommandPoints;							// +0x14
	Int m_mediumArmyCommandPoints;							// +0x18
	Int m_armyCarryoverPoints;								// +0x1C
	_STL::vector<BfmeE8> m_armyPlacementPos;				// +0x20
	_STL::vector<Rva0020E89C *> m_regions;					// +0x2C
	_STL::hash_map<int, Rva0021072AElement> m_table;		// +0x38
	Rva003EF77E *m_owned;									// +0x4C
	AsciiString m_regionConqueredSound;						// +0x50
	AsciiString m_regionEffectsManagerName;					// +0x54
	Int m_armyRetreatRounds;								// +0x58
	_STL::vector<Rva002105A6 *> m_rules;					// +0x5C
};

LivingWorldRegionCampaign::LivingWorldRegionCampaign(const AsciiString &name) :
	m_name(name),
	m_heroOnlyArmyCommandPoints(0),
	m_smallArmyCommandPoints(20),
	m_mediumArmyCommandPoints(50),
	m_armyCarryoverPoints(50),
	m_regionConqueredSound(),
	m_regionEffectsManagerName(),
	m_armyRetreatRounds(10)
{
	m_regions.clear();
	m_owned = new Rva003EF77E;
}

// The campaign's post-parse pass, rowed under its placeholder owner.
class Rva002103B6
{
public:
	void rva002106D6();										// 0x002106D6
};

class LivingWorldRegionManagerCampaigns
{
public:
	unsigned char m_pad00[0x34];
	_STL::vector<LivingWorldRegionCampaign *> m_campaigns;	// +0x34
};

class LivingWorldLogic
{
public:
	unsigned char m_pad00[0xB0];
	LivingWorldRegionManagerCampaigns *m_regionManager;		// +0xB0
};
extern LivingWorldLogic *TheLivingWorldLogic;

struct FieldParse
{
	const char *token;
	void (*parse)(INI *, void *, void *, const void *);
	const void *userData;
	int offset;
};

class LivingWorldRegionManager
{
public:
	static void rva00210620(INI *, void *, void *, const void *);
};

class LivingWorldRegionBonusRule
{
public:
	static void ParseINI(INI *, void *, void *, const void *);
};

// Campaign fields at native 0x00BE4120, including its null sentinel.
extern const FieldParse Rva00210A14FieldParseTable[] =
{
	{"Region", LivingWorldRegionManager::rva00210620, 0, 0x00},
	{"RegionBonusArmy", INI::parseAsciiString, 0, 0x04},
	{"RegionBonusResource", INI::parseAsciiString, 0, 0x08},
	{"RegionBonusLegendary", INI::parseAsciiString, 0, 0x0C},
	{"HeroOnlyArmyCommandPoints", INI::parseInt, 0, 0x10},
	{"SmallArmyCommandPoints", INI::parseInt, 0, 0x14},
	{"MediumArmyCommandPoints", INI::parseInt, 0, 0x18},
	{"ArmyPlacementPos", INI::Rva002F592_ParseArmyPlacementPos, 0, 0x20},
	{"ArmyRetreatRounds", INI::parseInt, 0, 0x58},
	{"ArmyCarryoverPoints", INI::parseInt, 0, 0x1C},
	{"RegionConqueredSound", INI::parseAsciiString, 0, 0x50},
	{"RegionEffectsManagerName", INI::parseAsciiString, 0, 0x54},
	{"ConcurrentRegionBonus", LivingWorldRegionBonusRule::ParseINI, 0, 0x00},
	{0, 0, 0, 0}
};

void parseLivingWorldRegionCampaignDefinition(INI *ini)
{
	LivingWorldRegionManagerCampaigns *manager = TheLivingWorldLogic->m_regionManager;
	const char *name = ini->getNextToken();
	LivingWorldRegionCampaign *campaign = new LivingWorldRegionCampaign(AsciiString(name));
	ini->initFromINI(campaign, Rva00210A14FieldParseTable);
	((Rva002103B6 *)campaign)->rva002106D6();
	manager->m_campaigns.push_back(campaign);
}
