// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Split from CreateAHero.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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

#include "../../../Include/Common/CreateAHeroHero.h"

// The same hero object under the names its rowed copy and setter carry:
// operator= at 0x00409359 and the +4 setter at 0x00406E47.
#include "../../../Include/GameLogic/CreateAHeroData.h"

// A bling entry starts with its name and description string tags.
struct CreateAHeroBling
{
	AsciiString m_nameTag;					// +0x00
	AsciiString m_descTag;					// +0x04
	AsciiString m_upgradeName;				// +0x08
};

// The manager's bling table at +0x15C holds 16-byte entries with the bling
// id at +0x0C; the lookup by upgrade name is the rowed cdecl find at
// 0x0021D120 (unnamed in WB).
struct CreateAHeroBlingEntry
{
	unsigned char m_pad00[0xc];
	Int m_blingId;						// +0x0C
};

const CreateAHeroBlingEntry *Rva0021D120Find(const CreateAHeroBlingEntry *first, const CreateAHeroBlingEntry *last, const StringBase<char> *upgradeName);	// 0x0021D120

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

#include "../../../Include/GameNetwork/GameInfo.h"


extern GameInfo *TheGameInfo;

// init's INI load: the file goes through INI::loadFile with the subsystem
// list's xfer (+0x24) when TheSubsystemList (VA 0x00DFD940) exists.
class Xfer;

enum INILoadType { INI_LOAD_INVALID, INI_LOAD_OVERWRITE };

#include "../../../Include/Common/INI/FieldParse.h"

struct BlockFieldParse
{
	const char *name;
	void (*parse)(class INI *);
	const void *userData;
	int offset;
};

struct CreateAHeroSystemFieldParseTable
{
	BlockFieldParse blocks[3];
	FieldParse fields[23];
};

class INI
{
public:
	INI();							// 0x0002CDB0
	~INI();							// 0x0002CE5B
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer);	// 0x0002DC75: byte result (rowed in INI_loadFile.cpp)
	static void parseAsciiStringVectorAppend(INI *, void *, void *, const void *);
	static void parseAsciiString(INI *, void *, void *, const void *);
	static void parseInt(INI *, void *, void *, const void *);
	static void parseReal(INI *, void *, void *, const void *);
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
		friend class CreateAHeroManager;
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
	static void parseCreateAHeroSubClass(INI *, void *, void *, const void *);
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

// The manager's global at VA 0x00DFE344 is defined in CreateAHero.cpp.
extern CreateAHeroManager *TheCreateAHeroManager;

// CreateAHeroManager::CreateAHeroClass::GetBlingCount, retail 0x0021BE23.
Int CreateAHeroManager::CreateAHeroClass::GetBlingCount(Int blingKey, UnsignedInt subClassIndex) const
{
	const CreateAHeroSubClass *subClass = rva00219B9E(subClassIndex);
	if (subClass)
		return subClass->rva0021BC2C(blingKey);
	return 0;
}

// CreateAHeroManager::FindBlingByUpgradeName, retail 0x0021D4CE: the table
// index and id of the bling granted by an upgrade.
Bool CreateAHeroManager::FindBlingByUpgradeName(const AsciiString &upgradeName, Int *index, Int *blingId)
{
	const CreateAHeroBlingEntry *it = Rva0021D120Find(m_blings.begin(), m_blings.end(), (const StringBase<char> *)&upgradeName);
	if (it == m_blings.end())
		return false;
	*index = it - m_blings.begin();
	*blingId = it->m_blingId;
	return true;
}

// Target calls the matched CreateAHeroClass::GetBlingCount at 0x0021BE23.
// The original method name is not independently proven, so keep the RVA label.
Int CreateAHeroManager::rva0021BEE0(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex) const
{
	if (classIndex < m_classes.size())
		return m_classes[classIndex].GetBlingCount(blingKey, subClassIndex);
	return 0;
}

// iniParseCreateAHeroSystem's views. The CreateAHeroSystem block's field table
// (VA 0x00BE6888) names each manager field it fills; the stat names are
// checked by the 0x00219453 validator, which throws INIException.
extern "C" const CreateAHeroSystemFieldParseTable CreateAHeroSystemFieldParse;

bool Rva00219453Validate(int stat, const char *name);	// 0x00219453


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


extern "C" const FieldParse CreateAHeroClassFieldParse[];


// The native isEmpty call stays out of line; its visible body lets the compiler
// retain TheCreateAHeroManager across the call.
template <> __declspec(noinline) inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }

void CreateAHeroManager::parseCreateAHeroClassDefinition(INI *ini)
{
	CreateAHeroClass heroClass(AsciiString("None"), AsciiString("None"), AsciiString("None"), AsciiString("None"), AsciiString("None"));
	ini->initFromINI(&heroClass, CreateAHeroClassFieldParse);
	if (heroClass.m_upgradeName.isNone() || ((const StringBase<char> *)&heroClass.m_upgradeName)->isEmpty())
		throw INIException(3, "No upgrade name specified while parsing CreateAHeroClass.");
	if (TheUpgradeCenter->findUpgrade(heroClass.m_upgradeName) == 0)
		throw INIException(3, "Upgrade %s not found while parsing CreateAHeroClass.", heroClass.m_upgradeName.str());
	if (TheCreateAHeroManager->rva0021B31C(heroClass.m_upgradeName))
		throw INIException(3, "A Create-a-Hero Class with the upgrade %s already exists.", heroClass.m_upgradeName.str());
	TheCreateAHeroManager->rva0022020C(heroClass);
}

// CreateAHeroManager::iniParseCreateAHeroSystem, retail 0x0022044C (684
// bytes), the CreateAHeroSystem block parser (BlockParse node VA 0x00DB9D38).
// WB names it (CreateAHero.cpp:3270..3367): fill the manager from the block,
// require every stat, clamp the special-animation chance to [0, 100], require
// a weapon group and the three animation names, and drop a CanBuild upgrade
// name that no upgrade answers. The DEBUG reports are compiled out.
void CreateAHeroManager::iniParseCreateAHeroSystem(INI *ini)
{
	if (TheCreateAHeroManager == 0)
		return;

	ini->initFromINI(TheCreateAHeroManager, reinterpret_cast<const FieldParse *>(&CreateAHeroSystemFieldParse));

	Rva00219453Validate(TheCreateAHeroManager->m_stratigicDefeatStat, "StratigicDefeatStatName");
	Rva00219453Validate(TheCreateAHeroManager->m_stratigicVictoryStat, "StratigicVictoryStatName");
	Rva00219453Validate(TheCreateAHeroManager->m_stratigicMPDefeatStat, "StratigicMPDefeatStatName");
	Rva00219453Validate(TheCreateAHeroManager->m_stratigicMPVictoryStat, "StratigicMPVictoryStatName");
	Rva00219453Validate(TheCreateAHeroManager->m_skirmishDefeatStat, "SkirmishDefeatStatName");
	Rva00219453Validate(TheCreateAHeroManager->m_skirmishVictoryStat, "SkirmishVictoryStatName");
	Rva00219453Validate(TheCreateAHeroManager->m_openPlayDefeatStat, "OpenPlayDefeatStatName");
	Rva00219453Validate(TheCreateAHeroManager->m_openPlayVictoryStat, "OpenPlayVictoryStatName");

	TheCreateAHeroManager->m_specialAnimPercentChance = std::min(100.0f, TheCreateAHeroManager->m_specialAnimPercentChance);
	TheCreateAHeroManager->m_specialAnimPercentChance = std::max(0.0f, TheCreateAHeroManager->m_specialAnimPercentChance);

	static NameKeyType noneKey = TheNameKeyGenerator->nameToKey("None");
	static NameKeyType emptyKey = TheNameKeyGenerator->nameToKey("");
	if (TheCreateAHeroManager->m_weaponGroupName == NAMEKEY_INVALID
		|| TheCreateAHeroManager->m_weaponGroupName == noneKey
		|| TheCreateAHeroManager->m_weaponGroupName == emptyKey)
		throw INIException(3, "WeaponGroupName is not a valid in CreateAHeroSystem.ini.");

	if (TheCreateAHeroManager->m_selectedCheerAnimName.isNone() || ((const StringBase<char> *)&TheCreateAHeroManager->m_selectedCheerAnimName)->isEmpty())
		throw INIException(3, "SelectedCheerAninName is not a valid in CreateAHeroSystem.ini.");
	if (TheCreateAHeroManager->m_examineWeaponAnimName.isNone() || ((const StringBase<char> *)&TheCreateAHeroManager->m_examineWeaponAnimName)->isEmpty())
		throw INIException(3, "ExamineWeaponAninName is not a valid in CreateAHeroSystem.ini.");
	if (TheCreateAHeroManager->m_examineSelfAnimName.isNone() || ((const StringBase<char> *)&TheCreateAHeroManager->m_examineSelfAnimName)->isEmpty())
		throw INIException(3, "ExamineSelfAninName is not a valid in CreateAHeroSystem.ini.");

	if (!((const StringBase<char> *)&TheCreateAHeroManager->m_canBuildUpgradeName)->isEmpty())
	{
		if (TheUpgradeCenter->findUpgrade(TheCreateAHeroManager->m_canBuildUpgradeName) == 0)
			TheCreateAHeroManager->m_canBuildUpgradeName.clear();
	}
}

// Native 21AD88..21ADD9 is the cdecl comparator passed by the independently
// bounded sort wrapper21E673. The preceding43B member ends exactly at21AD88;
// the comparator returns at21ADD8 before the following member starts21ADD9.
// Each four-byte value selects a bling and its upgrade; only the unsigned
// word at upgrade+88 participates in ordering. Its original field and
// comparator names are unresolved. Ghidra omitted this standalone boundary.
bool Rva0021AD88Less(unsigned int first, unsigned int second);


typedef bool (*BlingIndexLess)(unsigned int, unsigned int);
namespace _STL {
template <> void sort<unsigned int *, BlingIndexLess>(unsigned int *, unsigned int *, BlingIndexLess);
}

namespace _STL {
template <> vector<unsigned int> &map<int, vector<unsigned int> >::operator[](const int &);
}

// Native substring builder and conversion use the same12-byte view ABI.
#include "../../../Include/Common/Rva000B6AF5Rec.h"
struct Rva000B6AA9Rec {
    operator AsciiString();
    AsciiString *m_string; int m_start; int m_len;
};
Rva000B6AF5Rec *__cdecl Rva000B6AF5Build(Rva000B6AF5Rec *, void **, int);

// Retail expands its nullable character accessor. The shared string header
// now calls an out-of-line accessor; this view keeps the proven one-pointer
// string layout and character data at buffer+8 without changing that header.
inline char BlingFirstChar(const AsciiString &string)
{
    const char *buffer=*reinterpret_cast<const char *const *>(&string);
    return buffer ? buffer[8] : 0;
}

// WB B801A0 names this FieldParse callback; native21EE37..21EF66 RET0
// parses the upgrade list and recognizes the leading default marker '@'.
// Its three EH states own the list, the current upgrade and the substring
// conversion result. Retail's builder and converter have a12-byte view ABI.
void CreateAHeroManager::parseHeroBlingUpgrades(INI *ini, void *instance, void *, const void *)
{
    std::vector<AsciiString> upgrades;
    INI::parseAsciiStringVectorAppend(ini,0,&upgrades,0);
    CreateAHeroSubClass *subClass=static_cast<CreateAHeroSubClass *>(instance);
    for (unsigned i=0;i<upgrades.size();++i) {
        int index=0;
        int blingId=0;
        AsciiString upgrade=upgrades[i];
        bool makeDefault=false;
        if (upgrade.getLength()>1 && BlingFirstChar(upgrade)=='@') {
            makeDefault=true;
            Rva000B6AF5Rec view;
            upgrade=*reinterpret_cast<Rva000B6AA9Rec *>(
                Rva000B6AF5Build(&view,reinterpret_cast<void **>(&upgrade),upgrade.getLength()-1));
        }
        if (TheCreateAHeroManager->FindBlingByUpgradeName(upgrade,&index,&blingId))
            subClass->AddBling(blingId,index,makeDefault);
    }
}

// Native21B474..21B5D6 and WB B7D7B0 establish the binding operation.
// The virtual interfaces below retain slot names where original names are
// unresolved: hero slot10 consumes update mask2FF; a behavior subobject at0C
// returns the power interface from slot20, whose slot54 result WB asserts.
// The Object prefix witnesses its ID74 and null-terminated module list244.
class Object {
public:
    Player *getControllingPlayer() const;
    unsigned char prefix[0x74]; unsigned id;
    unsigned char middle[0x244-0x78]; void **modules;
};

void parseCreateAHeroBlingDefinition(INI *);
void parseCreateAHeroBlingBinderDefinition(INI *);

// The block callbacks take INI alone; all entries share retail's four-word format.
extern "C" const CreateAHeroSystemFieldParseTable CreateAHeroSystemFieldParse =
{
	{
		{ "CreateAHeroBling", parseCreateAHeroBlingDefinition, 0, 0 },
		{ "CreateAHeroBlingBinder", parseCreateAHeroBlingBinderDefinition, 0, 0 },
		{ "CreateAHeroClass", CreateAHeroManager::parseCreateAHeroClassDefinition, 0, 0 }
	},
	{
		{ "CreateAHeroMapModeUpgradeName", INI::parseAsciiString, 0, 0x188 },
		{ "CreateAHeroGameModeUpgradeName", INI::parseAsciiString, 0, 0x18C },
		{ "CanBuildCreateAHeroUpgradeName", INI::parseAsciiString, 0, 0x190 },
		{ "CommandSetTemplate", INI::parseAsciiString, 0, 0x1DC },
		{ "StratigicDefeatStatName", NameKeyGenerator::parseStringAsNameKeyType, 0, 0x194 },
		{ "StratigicVictoryStatName", NameKeyGenerator::parseStringAsNameKeyType, 0, 0x198 },
		{ "StratigicMPDefeatStatName", NameKeyGenerator::parseStringAsNameKeyType, 0, 0x19C },
		{ "StratigicMPVictoryStatName", NameKeyGenerator::parseStringAsNameKeyType, 0, 0x1A0 },
		{ "SkirmishDefeatStatName", NameKeyGenerator::parseStringAsNameKeyType, 0, 0x1A4 },
		{ "SkirmishVictoryStatName", NameKeyGenerator::parseStringAsNameKeyType, 0, 0x1A8 },
		{ "OpenPlayDefeatStatName", NameKeyGenerator::parseStringAsNameKeyType, 0, 0x1AC },
		{ "OpenPlayVictoryStatName", NameKeyGenerator::parseStringAsNameKeyType, 0, 0x1B0 },
		{ "StratigicCampainDefeatStatName", NameKeyGenerator::parseStringAsNameKeyType, 0, 0x1B4 },
		{ "StratigicCampainVictoryStatName", NameKeyGenerator::parseStringAsNameKeyType, 0, 0x1B8 },
		{ "WeaponGroupName", NameKeyGenerator::parseStringAsNameKeyType, 0, 0x1BC },
		{ "SpecialAnimPercentChance", INI::parseReal, 0, 0x1C0 },
		{ "SelectedCheerAninName", INI::parseAsciiString, 0, 0x1C4 },
		{ "ExamineWeaponAninName", INI::parseAsciiString, 0, 0x1C8 },
		{ "ExamineSelfAninName", INI::parseAsciiString, 0, 0x1CC },
		{ "ExamineAnimTweakValue", INI::parseInt, 0, 0x1E4 },
		{ "ModelSwapFadeDown", INI::parseAsciiString, 0, 0x1E8 },
		{ "ModelSwapFadeUp", INI::parseAsciiString, 0, 0x1EC },
		{ 0, 0, 0, 0 }
	}
};

extern "C" const FieldParse CreateAHeroClassFieldParse[] =
{
	{ "UpgradeName", INI::parseAsciiString, 0, 0x10 },
	{ "NameTag", INI::parseAsciiString, 0, 0 },
	{ "DescriptionTag", INI::parseAsciiString, 0, 4 },
	{ "PowersDescTag", INI::parseAsciiString, 0, 8 },
	{ "IconImage", INI::parseAsciiString, 0, 0x0C },
	{ "SubClass", CreateAHeroManager::parseCreateAHeroSubClass, 0, 0x14 },
	{ 0, 0, 0, 0 }
};

// INI block registration (LINK-236). Each unit links its own 12-byte BlockParse nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the link; MSVC 7.1
// builds token and parse in .data, so the node's .text$yc initializer is only the 21-byte
// link (retail .CRT$XCU 0x007ADAD2, node 0x00DB9D38). Retail's CreateAHero unit run is its
// Drawable.h copy 0x007ADAA5 (static after TheCreateAHeroManager), a vector 0x007ADAB5, this
// node, then the pool-init marker 0x007ADAE7; this fragment defines the node's callback.
typedef void (*INIBlockParse)( INI *ini );
extern struct BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse ) : next(theBlockParseList), token(token), parse(parse)
	{
		theBlockParseList = this;
	}
};

BlockParse theCreateAHeroSystemBlockParse( "CreateAHeroSystem", CreateAHeroManager::iniParseCreateAHeroSystem );
