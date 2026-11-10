// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// CreateAHero.cpp -- CreateAHeroManager forwarding accessors recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names each
// function and its nesting (CreateAHeroManager::CreateAHeroClass, ::
// CreateAHeroSubClass); retail supplies the bytes.
//
// Layout (target evidence): the manager keeps a vector of 32-byte hero classes
// at +0x14C and the command-set name at +0x1DC; a class's out-of-line
// bounds-checked subclass accessor (0x00219B9E, unnamed in WB) returns NULL
// for a bad index.
#include "ascii_string.h"
#include <vector>
#include <map>
#include <algorithm>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const  { return x < y; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void vector<unsigned int,allocator<unsigned int> >::push_back(unsigned int const &); }
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree<int, pair<int const, vector<unsigned int, allocator<unsigned int> > >, _Select1st<pair<int const, vector<unsigned int, allocator<unsigned int> > > >, less<int>, allocator<pair<int const, vector<unsigned int, allocator<unsigned int> > > > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator++(); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--(); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_empty_initialize(); }
namespace _STL { template <> void vector<unsigned int, allocator<unsigned int> >::_M_insert_overflow(unsigned int *, unsigned int const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<unsigned int, allocator<unsigned int> >::_M_set(unsigned int *, unsigned int *, unsigned int *); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::clear(); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(pair<int const, int> const &); }
// Call retail's hinted insert_unique (0x00422EC0) instead of emitting this unit's own copy.
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, pair<int const, int> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??0?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$a:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::_Rb_tree(const less<int> &, const allocator<pair<const int, int> > &); }
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> pair<_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::iterator, bool> _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::insert_unique(const pair<const int, int> &); }
// Keep native node comparisons local; the incidental tree-base copy
// differs from the selected out-of-line provider.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

// Native2DFCF6 releases trivial index storage with a conditional game free.
// The generic header leaves cleanup out of line for this instantiation;
// this specialization keeps the same trivial destruction and allocator
// semantics, using the independently verified17B game-free provider.
void Rva00030830GameFree(void *);
namespace _STL {
template <> inline void vector<unsigned int>::_M_clear()
{
    if (this->_M_start) Rva00030830GameFree(this->_M_start);
}
}

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// Retain the already rowed signed-vector tree lookup while the native bling
// index table uses unsigned elements. Both are real STLport instantiations;
// the key-only search is independently verified at retail's folded body.
typedef _STL::pair<const int, _STL::vector<int> > SignedBlingPair;
typedef _STL::_Rb_tree<int, SignedBlingPair,
    _STL::_Select1st<SignedBlingPair>, _STL::less<int>,
    _STL::allocator<SignedBlingPair> > SignedBlingTree;
template SignedBlingTree::_Link_type SignedBlingTree::_M_find<int>(const int &) const;

class CreateAHeroHero
{
public:
	void ConstructHeroBlingList(); // WB1082260; native409A76, unconverted455B
	Bool RegisterExperienceLevels(); // WB107E870; native408150, unconverted687B; returns AL
	Int GetBlingCount(Int blingKey) const;			// 0x004079F4
	Int GetBlingId(Int blingKey, UnsignedInt index) const;	// 0x00407A29
	// 0x004098BE (WorldBuilder places it in CreateAHeroHero.cpp): takes a
	// file name and a flag; rva0021A428 hands it "MyHero.dat".
	Bool rva004098BE(const AsciiString &fileName, Bool flag);
};

// The same hero object under the names its rowed copy and setter carry:
// operator= at 0x00409359 and the +4 setter at 0x00406E47.
#include "../../../Include/GameLogic/CreateAHeroData.h"

class Rva00406E47
{
public:
	Bool rva00406E47(Int value);
};

// A bling entry starts with its name and description string tags.
struct CreateAHeroBling
{
	AsciiString m_nameTag;					// +0x00
	AsciiString m_descTag;					// +0x04
	AsciiString m_upgradeName;				// +0x08
};

// The manager's bling table at +0x15C holds 16-byte entries with the bling
// id at +0x0C; the lookup by upgrade name is the unrowed cdecl find at
// 0x0021D120 (unnamed in WB).
struct CreateAHeroBlingEntry
{
	unsigned char m_pad00[0xc];
	Int m_blingId;						// +0x0C
};

CreateAHeroBlingEntry *rva0021D120(CreateAHeroBlingEntry *first, CreateAHeroBlingEntry *last, const AsciiString &upgradeName);	// 0x0021D120

class CommandButton;

#include "../../../Include/GameClient/CommandSet.h"

#include "../../../Include/GameClient/ControlBar.h"

extern ControlBar *TheControlBar;

// GetHeroForPlayer's views. A game slot keeps the name compared with the
// player's key at +0x34 and its created hero at +0x64, valid when the byte
// at +0x60 is set; the player's name key is at +0x50.
enum NameKeyType { NAMEKEY_INVALID = 0 };

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

class GameSlot
{
public:
	const AsciiString &getPlayerName() const { return m_playerName; }
	const CreateAHeroHero *getHero() const { return m_hasHero ? &m_hero : 0; }

private:
	unsigned char m_pad00[0x34];
	AsciiString m_playerName;				// +0x34
	unsigned char m_pad38[0x60 - 0x38];
	Bool m_hasHero;						// +0x60
	unsigned char m_pad61[0x64 - 0x61];
	CreateAHeroHero m_hero;					// +0x64
};

class GameInfo
{
public:
	GameSlot *getSlot(Int index);				// 0x003FF29F
};

extern GameInfo *TheGameInfo;

// init's INI load: the file goes through INI::loadFile with the subsystem
// list's xfer (+0x24) when TheSubsystemList (VA 0x00DFD940) exists.
class Xfer;

enum INILoadType { INI_LOAD_INVALID, INI_LOAD_OVERWRITE };

struct FieldParse;

class INI
{
public:
	INI();							// 0x0002CDB0
	~INI();							// 0x0002CE5B
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer);	// 0x0002DC75: byte result (rowed in INI_loadFile.cpp)
	static void parseAsciiStringVectorAppend(INI *, void *, void *, const void *);
	void initFromINI(void *what, const FieldParse *parseTable);	// 0x0002DE78

private:
	unsigned char m_data[0x87c];
};

#include "../../../Include/Common/SubsystemInterfaceList.h"

extern SubsystemInterfaceList *TheSubsystemList;

// The dword at VA 0x00DFE348 (ColdGlobalDwordGetters.cpp) gates init's load.
extern int g_Va00DFE348;

#include "../../../Include/Common/Player.h"


enum FactionType { FACTION_UNKNOWN=-1 };
template<int NUM_BITS,class BitTag>class BitFlags {
public: BitFlags() throw();
private: unsigned words[(NUM_BITS+31)/32];
};
class Rva002195E6 {
public: Rva002195E6() throw();
private: unsigned char data[108];
};
struct AttributeBlingBounds {
    // Target accessors21BDAB/21BDD3/21BDFB pass strings at+4/+8/+C to
    // GetBlingIndex; parser compares the leading NameKey with upgrade+84.
    // Field purposes are inferred; the three string representations are proven.
    NameKeyType group;
    AsciiString minimum, maximum, defaultBling;
};

class CreateAHeroManager
{
public:
	class CreateAHeroSubClass
	{
	public:
		CreateAHeroSubClass(const AsciiString &,const AsciiString &,const AsciiString &,const AsciiString &);
		Int rva0021BC2C(Int blingKey) const;		// 0x0021BC2C, bling count
		Int GetDefaultBlingId(Int blingKey) const; // 0x0021BC53
        void AddBling(Int blingKey, UnsignedInt index, Bool makeDefault);
    private:
        // Native199B constructor21E793 proves the complete216B layout.
        // WB supplies subclass identity and faction mask template; the names
        // of the color-like words and the trailing108B record remain unknown.
        AsciiString m_nameTag,m_descriptionTag,m_iconName,m_emptyString;
        unsigned m_word10,m_word14,m_word18;
        int m_spendablePoints;
        AsciiString m_upgradeName;
        std::map<int, std::vector<unsigned int> > m_blingIds;
        std::vector<NameKeyType> m_keys30,m_keys3C;
        std::map<int, int> m_defaultBlingIds;
        std::map<int,AttributeBlingBounds> m_attributes;
        bool m_flag60;
        FactionType m_preferredFaction;
        BitFlags<7,FactionType> m_factionMask;
        Rva002195E6 m_trailing;
	};

	class CreateAHeroClass
	{
	public:
		CreateAHeroClass(const AsciiString &, const AsciiString &, const AsciiString &, const AsciiString &, const AsciiString &);
		~CreateAHeroClass();
		Int GetBlingCount(Int blingKey, UnsignedInt subClassIndex) const;
		Int GetSubClassDefaultBlingId(Int blingKey, UnsignedInt subClassIndex) const;

		const AsciiString &getUpgradeName() const { return m_upgradeName; }

	private:
		const CreateAHeroSubClass *rva00219B9E(UnsignedInt subClassIndex) const;	// 0x00219B9E

		// Field table 0x00DBA0D8 (CreateAHeroClass block): NameTag,
		// DescriptionTag, PowersDescTag, IconImage, UpgradeName, SubClass.
		AsciiString m_nameTag;					// +0x00
		AsciiString m_descriptionTag;				// +0x04
		AsciiString m_powersDescTag;				// +0x08
		AsciiString m_iconImage;				// +0x0C
		AsciiString m_upgradeName;				// +0x10
		unsigned char m_subClasses[0xc];			// +0x14
	};


	// SubsystemInterface slots 0 and 1 (vtable 0x007E648C).
	virtual ~CreateAHeroManager();
	virtual void init();

	static void iniParseCreateAHeroSystem(INI *ini);
	static void parseCreateAHeroClassDefinition(INI *ini);
	CreateAHeroClass *rva0022020C(CreateAHeroClass &heroClass);	// 0x0022020C, adds a parsed class

	Int GetBlingCount(Int blingKey, const CreateAHeroHero *hero) const;
	Int rva0021BEE0(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex) const;
	Int GetSubClassDefaultBlingId(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex) const;
	const AsciiString &GetBlingNameTag(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	const AsciiString &GetBlingDescTag(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	const AsciiString &GetBlingUpgradeName(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	Bool FindBlingByUpgradeName(const AsciiString &upgradeName, Int *index, Int *blingId);
	static void parseHeroBlingUpgrades(INI *, void *, void *, const void *);
	void *GetBling(UnsignedInt blingId);			// 0x00219D85
	const CreateAHeroHero *GetHeroForPlayer(const Player *player);
	CreateAHeroClass *rva0021B31C(const AsciiString &upgradeName);
	void rva0021A428(const CreateAHeroData &hero);
	void BindHeroToObjectAndUpdate(class Object *);

private:
	Int rva00219309() const;				// 0x00219309, required-button count

	unsigned char m_pad04[0xc - 0x4];
	CreateAHeroHero m_localHero;				// +0x0C, used without a game
	unsigned char m_pad0D[0x58 - 0xd];
	AsciiString m_localHeroName;				// +0x58 (local hero +0x4C)
	unsigned char m_pad5C[0x14c - 0x5c];
	std::vector<CreateAHeroClass> m_classes;		// +0x14C
	unsigned char m_pad158[0x15c - 0x158];
	std::vector<CreateAHeroBlingEntry> m_blings;		// +0x15C
	unsigned char m_pad168[0x188 - 0x168];
	AsciiString m_mapModeUpgradeName;			// +0x188
	AsciiString m_gameModeUpgradeName;			// +0x18C
	AsciiString m_canBuildUpgradeName;			// +0x190
	NameKeyType m_stratigicDefeatStat;			// +0x194
	NameKeyType m_stratigicVictoryStat;			// +0x198
	NameKeyType m_stratigicMPDefeatStat;			// +0x19C
	NameKeyType m_stratigicMPVictoryStat;			// +0x1A0
	NameKeyType m_skirmishDefeatStat;			// +0x1A4
	NameKeyType m_skirmishVictoryStat;			// +0x1A8
	NameKeyType m_openPlayDefeatStat;			// +0x1AC
	NameKeyType m_openPlayVictoryStat;			// +0x1B0
	NameKeyType m_stratigicCampainDefeatStat;		// +0x1B4
	NameKeyType m_stratigicCampainVictoryStat;		// +0x1B8
	NameKeyType m_weaponGroupName;				// +0x1BC
	float m_specialAnimPercentChance;			// +0x1C0
	AsciiString m_selectedCheerAnimName;			// +0x1C4
	AsciiString m_examineWeaponAnimName;			// +0x1C8
	AsciiString m_examineSelfAnimName;			// +0x1CC
	unsigned char m_pad1D0[0x1dc - 0x1d0];
	AsciiString m_commandSetName;				// +0x1DC
	CreateAHeroHero *m_boundHero;				// +0x1E0
};

// The manager's global: GameEngine::init registers the subsystem under the
// name "TheCreateAHeroManager" (call site 0x0022FC2F) into VA 0x00DFE344;
// matched references place it there (retail .data initial value 0).
CreateAHeroManager *TheCreateAHeroManager = 0;

// CreateAHeroManager::GetBlingCount, retail 0x00219239.
Int CreateAHeroManager::GetBlingCount(Int blingKey, const CreateAHeroHero *hero) const
{
	if (hero)
		return hero->GetBlingCount(blingKey);
	return 0;
}

// CreateAHeroManager::CreateAHeroClass::GetSubClassDefaultBlingId, retail
// 0x0021BEA2.
Int CreateAHeroManager::CreateAHeroClass::GetSubClassDefaultBlingId(Int blingKey, UnsignedInt subClassIndex) const
{
	const CreateAHeroSubClass *subClass = rva00219B9E(subClassIndex);
	if (subClass)
		return subClass->GetDefaultBlingId(blingKey);
	return 0;
}

// CreateAHeroManager::GetBlingNameTag, retail 0x00219DAA. WB asserts the hero
// exists and the index is in range; retail answers the empty string.
const AsciiString &CreateAHeroManager::GetBlingNameTag(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index)
{
	if (hero && index < (UnsignedInt)hero->GetBlingCount(blingKey))
	{
		CreateAHeroBling *bling = (CreateAHeroBling *)GetBling(hero->GetBlingId(blingKey, index));
		if (bling)
			return bling->m_nameTag;
	}
	return AsciiString::TheEmptyString;
}

// CreateAHeroManager::GetBlingDescTag, retail 0x00219DEA.
const AsciiString &CreateAHeroManager::GetBlingDescTag(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index)
{
	if (hero && index < (UnsignedInt)hero->GetBlingCount(blingKey))
	{
		CreateAHeroBling *bling = (CreateAHeroBling *)GetBling(hero->GetBlingId(blingKey, index));
		if (bling)
			return bling->m_descTag;
	}
	return AsciiString::TheEmptyString;
}

// CreateAHeroManager::GetBlingUpgradeName, retail 0x00219E2F.
const AsciiString &CreateAHeroManager::GetBlingUpgradeName(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index)
{
	if (hero && index < (UnsignedInt)hero->GetBlingCount(blingKey))
	{
		CreateAHeroBling *bling = (CreateAHeroBling *)GetBling(hero->GetBlingId(blingKey, index));
		if (bling)
			return bling->m_upgradeName;
	}
	return AsciiString::TheEmptyString;
}

// CreateAHeroManager::GetSubClassDefaultBlingId, retail 0x0021BF11.
Int CreateAHeroManager::GetSubClassDefaultBlingId(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex) const
{
	if (classIndex < m_classes.size())
		return m_classes[classIndex].GetSubClassDefaultBlingId(blingKey, subClassIndex);
	return 0;
}

// CreateAHeroManager::GetHeroForPlayer, retail 0x0021B5D6 (154 bytes): WB
// names it and asserts a slot was found for the controlling player. Without a
// game the manager's own hero answers; otherwise the hero of the first slot
// whose player name keys to the player's.
const CreateAHeroHero *CreateAHeroManager::GetHeroForPlayer(const Player *player)
{
	if (TheGameInfo)
	{
		GameSlot *slot = 0;
		for (UnsignedInt i = 0; slot == 0 && i < 8; ++i)
		{
			AsciiString playerName = TheGameInfo->getSlot(i)->getPlayerName();
			NameKeyType key = TheNameKeyGenerator->nameToKey(playerName);
			if (player->getPlayerNameKey() == key)
				slot = TheGameInfo->getSlot(i);
		}
		if (slot == 0)
			return 0;
		return slot->getHero();
	}
	return &m_localHero;
}

// CreateAHeroManager::init, retail 0x0021A3B7 (113 bytes), vtable slot 1: WB
// names it; when the gate at 0x00DFE348 is set the create-a-hero system INI
// is loaded.
void CreateAHeroManager::init()
{
	if (g_Va00DFE348)
	{
		INI ini;
		ini.loadFile(AsciiString("Data\\INI\\CreateAHeroSystem.ini"), INI_LOAD_OVERWRITE, TheSubsystemList ? TheSubsystemList->getXfer() : 0);
	}
}

Int CreateAHeroManager::CreateAHeroSubClass::GetDefaultBlingId(Int blingKey) const
{
    std::map<int, int>::const_iterator def = m_defaultBlingIds.find(blingKey);
    if (def != m_defaultBlingIds.end()) {
        std::map<int, std::vector<unsigned int> >::const_iterator ids = m_blingIds.find(blingKey);
        if (ids != m_blingIds.end()) {
            const std::vector<unsigned int> &list = ids->second;
            // The existing native search uses the corresponding signed
            // alias of these four-byte indices. Equality consumes the same
            // bits, preserving its already verified const-int provider.
            const int *it = std::find(reinterpret_cast<const int *>(list.begin()),
                reinterpret_cast<const int *>(list.end()), def->second);
            if (it != reinterpret_cast<const int *>(list.end()))
                return it - reinterpret_cast<const int *>(list.begin());
        }
    }
    return 0;
}

// iniParseCreateAHeroSystem's views. The CreateAHeroSystem block's field table
// (VA 0x00BE6888) names each manager field it fills; the stat names are
// checked by the 0x00219453 validator, which throws INIException.
extern "C" const FieldParse CreateAHeroSystemFieldParse[];

bool Rva00219453Validate(int stat, const char *name);	// 0x00219453

#include "../../../Include/Common/INI/FieldParse.h"

class UpgradeTemplate;

#include "../../../Include/Common/Upgrade.h"

extern UpgradeCenter *TheUpgradeCenter;

// The CreateAHeroClass block parser, retail 0x002202BF (396 bytes), beside
// iniParseCreateAHeroSystem; its name is unknown (address-derived). It
// parses a class record (the 0x20-byte CreateAHeroClass: five strings and
// the subclass vector; constructor 0x0021F804, destructor 0x0021F8F3)
// through field table 0x00DBA0D8, requires an upgrade name that
// TheUpgradeCenter knows and that no class already uses (rowed
// 0x0021B31C), and hands the record to the manager (0x0022020C).
// The out-of-line StringBase<char>::isEmpty 0x00001E2F under an existing
// pin spelling (this unit's inline specialization would expand it here).
class BfmeStringPresenceValue
{
public:
	bool isEmpty() const;
};



extern "C" const FieldParse CreateAHeroClassFieldParse[];


// isEmpty was header-defined: MSVC keeps the call out of line (0x00001E2F) but,
// knowing the body, does not reload TheCreateAHeroManager across it.
template <> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }

// Retail 0x0021B31C: the hero class granted by an upgrade, or NULL. The class
// parser (0x002202BF) refuses a second class with the same upgrade through it.
CreateAHeroManager::CreateAHeroClass *CreateAHeroManager::rva0021B31C(const AsciiString &upgradeName)
{
	for (UnsignedInt i = 0; i < m_classes.size(); i++) {
		if (upgradeName.compareNoCase(m_classes[i].getUpgradeName()) == 0)
			return &m_classes[i];
	}
	return 0;
}

// Retail 0x0021A428 (callers AptSkirmish::InitCreateAHeroOnStartGame and the
// two hero-box Run handlers): copies the hero into the local hero, clears its
// +4 field through the rowed setter, and when the local hero has a name passes
// "MyHero.dat" to 0x004098BE.
void CreateAHeroManager::rva0021A428(const CreateAHeroData &hero)
{
	*(CreateAHeroData *)&m_localHero = hero;
	((Rva00406E47 *)&m_localHero)->rva00406E47(0);
	if (!((const StringBase<char> *)&m_localHeroName)->isEmpty())
		m_localHero.rva004098BE(AsciiString("MyHero.dat"), false);
}

// Native 21AD88..21ADD9 is the cdecl comparator passed by the independently
// bounded sort wrapper21E673. The preceding43B member ends exactly at21AD88;
// the comparator returns at21ADD8 before the following member starts21ADD9.
// Each four-byte value selects a bling and its upgrade; only the unsigned
// word at upgrade+88 participates in ordering. Its original field and
// comparator names are unresolved. Ghidra omitted this standalone boundary.
struct BlingUpgradeOrderView { char unknown00[0x88]; unsigned int word88; };
bool Rva0021AD88Less(unsigned int first, unsigned int second)
{
    const BlingUpgradeOrderView *blingUpgradeOrderView = reinterpret_cast<const BlingUpgradeOrderView *>(
        TheUpgradeCenter->findUpgrade(static_cast<CreateAHeroBling *>(
            TheCreateAHeroManager->GetBling(first))->m_upgradeName));
    const BlingUpgradeOrderView *b = reinterpret_cast<const BlingUpgradeOrderView *>(
        TheUpgradeCenter->findUpgrade(static_cast<CreateAHeroBling *>(
            TheCreateAHeroManager->GetBling(second))->m_upgradeName));
    return blingUpgradeOrderView->word88 < b->word88;
}

typedef bool (*BlingIndexLess)(unsigned int, unsigned int);
namespace _STL {
template <> void sort<unsigned int *, BlingIndexLess>(unsigned int *, unsigned int *, BlingIndexLess);
}
// Native21E673..21E68A supplies the verified comparator and the unsigned
// index vector's complete range to the recursively proven value-sort fold.
void Rva0021E673Sort(std::vector<unsigned int> *values)
{
    std::sort(values->begin(), values->end(), Rva0021AD88Less);
}

namespace _STL {
template <> vector<unsigned int> &map<int, vector<unsigned int> >::operator[](const int &);
}
// WB B770E0 names AddBling; native21E954..21E9D8 RET12 fixes the map
// offsets24/48. The four-byte index selects a bling through the comparator
// above; the integer key groups indices. New groups receive default index0,
// existing groups may replace it, and unique appended indices are sorted.
void CreateAHeroManager::CreateAHeroSubClass::AddBling(Int blingKey, UnsignedInt index, Bool makeDefault)
{
    if (!g_Va00DFE348) return;
    if (m_defaultBlingIds.find(blingKey) == m_defaultBlingIds.end())
        m_defaultBlingIds[blingKey] = 0;
    else if (makeDefault)
        m_defaultBlingIds[blingKey] = index;
    std::vector<unsigned int> &ids = m_blingIds[blingKey];
    unsigned int *finish = ids.end();
    if (std::find(ids.begin(), finish, index) == finish) {
        ids.push_back(index);
        Rva0021E673Sort(&ids);
    }
}

// Native substring builder and conversion use the same12-byte view ABI.
#include "../../../Include/Common/Rva000B6AF5Rec.h"
Rva000B6AF5Rec *__cdecl Rva000B6AF5Build(Rva000B6AF5Rec *, void **, int);

// Retail expands its nullable character accessor. The shared string header
// now calls an out-of-line accessor; this view keeps the proven one-pointer
// string layout and character data at buffer+8 without changing that header.
inline char BlingFirstChar(const AsciiString &string)
{
    const char *buffer=*reinterpret_cast<const char *const *>(&string);
    return buffer ? buffer[8] : 0;
}

// Native21B474..21B5D6 and WB B7D7B0 establish the binding operation.
// The virtual interfaces below retain slot names where original names are
// unresolved: hero slot10 consumes update mask2FF; a behavior subobject at0C
// returns the power interface from slot20, whose slot54 result WB asserts.
// The Object prefix witnesses its ID74 and null-terminated module list244.
class HeroUpdateInterfaceView {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(unsigned);
};
class HeroPowerStateView { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3c();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4c();
 virtual void slot50();
 virtual bool slot54();
};
class HeroBehaviorInterfaceView { public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual HeroPowerStateView *slot20();
};

class Object {
public:
    Player *getControllingPlayer() const;
    unsigned char prefix[0x74]; unsigned id;
    unsigned char middle[0x244-0x78]; void **modules;
};
void CreateAHeroManager::BindHeroToObjectAndUpdate(Object *object)
{
    if (!object) return;
    Player *controlling=0;
    CreateAHeroHero *hero;
    bool local;
    if (TheGameInfo) {
        Player *player=object->getControllingPlayer();
        GameSlot *slot=0;
        for (unsigned i=0;!slot && i<8;++i) {
            AsciiString name=TheGameInfo->getSlot(i)->getPlayerName();
            NameKeyType key=TheNameKeyGenerator->nameToKey(name);
            if (player->getPlayerNameKey()==key) slot=TheGameInfo->getSlot(i);
        }
        if (!slot) hero=0; else hero=const_cast<CreateAHeroHero *>(slot->getHero());
        local=player->isLocalPlayer() && hero;
        controlling=player;
    } else {
        hero=&m_localHero;
        local=true;
    }
    if (hero) {
        hero->ConstructHeroBlingList();
        reinterpret_cast<CreateAHeroData *>(hero)->rva00408A55();
        reinterpret_cast<Rva00406E47 *>(hero)->rva00406E47(object->id);
        hero->RegisterExperienceLevels();
        reinterpret_cast<HeroUpdateInterfaceView *>(hero)->slot10(0x2ff);
        if (controlling) {
            const UpgradeTemplate *upgrade=TheUpgradeCenter->findUpgrade(m_canBuildUpgradeName);
            controlling->removeUpgrade(upgrade,1);
        }
        if (local) m_boundHero=hero;
        for (void **module=object->modules;*module;++module) {
            HeroPowerStateView *power=reinterpret_cast<HeroBehaviorInterfaceView *>(static_cast<char *>(*module)+0x0c)->slot20();
            if (power) power->slot54();
        }
    }
}

// WB B76120 constructor callsite lead; target21E793..21E85A (RET16).
// Native member initialization and reference-taking ABI are independent
// target evidence; container folds require whole bodies and all relocations.
CreateAHeroManager::CreateAHeroSubClass::CreateAHeroSubClass(
    const AsciiString &upgrade,const AsciiString &name,
    const AsciiString &description,const AsciiString &icon)
    : m_nameTag(name),m_descriptionTag(description),m_iconName(icon),
      m_word10(0xff00ffff),m_word14(0xff00ffff),m_word18(0xff00ffff),
      m_spendablePoints(20),m_upgradeName(upgrade),
      m_flag60(false),m_preferredFaction(static_cast<FactionType>(6))
{}
