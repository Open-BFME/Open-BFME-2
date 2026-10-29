// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <map>
#include <algorithm>
// Bind vector<unsigned int>::push_back to the kept retail copy (0x004DFCB0).
namespace _STL { template <> void vector<unsigned int, allocator<unsigned int> >::push_back(const unsigned int &); }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::end() { return this->_M_finish; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::begin() { return this->_M_start; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void vector<unsigned int,allocator<unsigned int> >::push_back(unsigned int const &); }

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t);
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
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
	Int GetBlingCount(Int blingKey) const;			// 0x004079F4
	Int GetBlingId(Int blingKey, UnsignedInt index) const;	// 0x00407A29
	// 0x004098BE (WorldBuilder places it in CreateAHeroHero.cpp): takes a
	// file name and a flag; rva0021A428 hands it "MyHero.dat".
	Bool rva004098BE(const AsciiString &fileName, Bool flag);
};

// The same hero object under the names its rowed copy and setter carry:
// operator= at 0x00409359 and the +4 setter at 0x00406E47.
class CreateAHeroData
{
public:
	CreateAHeroData &operator=(const CreateAHeroData &that);
    unsigned char prefix[0x0c]; unsigned classIndex; unsigned subClassIndex;
};

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

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int i) const;	// 0x00409EE8
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);	// 0x0031D5F8
};

extern ControlBar *TheControlBar;

// GetHeroForPlayer's views. A game slot keeps the name compared with the
// player's key at +0x34 and its created hero at +0x64, valid when the byte
// at +0x60 is set; the player's name key is at +0x50.
enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);		// 0x0009FA65
	NameKeyType nameToKey(const char *name);		// 0x00148E1A
};

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
	void loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer);	// 0x0002DC75
	static void parseAsciiStringVectorAppend(INI *, void *, void *, const void *);
	void initFromINI(void *what, const FieldParse *parseTable);	// 0x0002DE78

private:
	unsigned char m_data[0x87c];
};

class SubsystemInterfaceList
{
public:
	Xfer *getXfer() const { return m_xfer; }

private:
	unsigned char m_pad00[0x24];
	Xfer *m_xfer;						// +0x24
};

extern SubsystemInterfaceList *TheSubsystemList;

// The dword at VA 0x00DFE348 (ColdGlobalDwordGetters.cpp) gates init's load.
extern int g_Va00DFE348;

class Player
{
public:
	NameKeyType getPlayerNameKey() const { return m_playerNameKey; }

private:
	unsigned char m_pad00[0x50];
	NameKeyType m_playerNameKey;				// +0x50
};

class CreateAHeroManager
{
public:
	class CreateAHeroSubClass
	{
	public:
		Int rva0021BC2C(Int blingKey) const;		// 0x0021BC2C, bling count
		Int GetDefaultBlingId(Int blingKey) const; // 0x0021BC53
        void AddBling(Int blingKey, UnsignedInt index, Bool makeDefault);
    private:
        // WB lookup and retail node+14/+18 prove the vector mapped value.
        // Retail map headers are at +24 and +48.
        unsigned char m_pad00[0x24];
        std::map<int, std::vector<unsigned int> > m_blingIds;
        unsigned char m_pad30[0x48-0x30];
        std::map<int, int> m_defaultBlingIds;
	};

	class CreateAHeroClass
	{
	public:
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

	Int GetBlingCount(Int blingKey, const CreateAHeroHero *hero) const;
	Int rva0021BEE0(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex) const;
	Int GetSubClassDefaultBlingId(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex) const;
	const AsciiString &GetBlingNameTag(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	const AsciiString &GetBlingDescTag(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	const AsciiString &GetBlingUpgradeName(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	Bool FindBlingByUpgradeName(const AsciiString &upgradeName, Int *index, Int *blingId);
    static void parseHeroBlingUpgrades(INI *, void *, void *, const void *);
	const CreateAHeroSubClass *rva0021A1B6(UnsignedInt, UnsignedInt);
    Bool GetAvailableHeroesForFaction(std::vector<unsigned int> *, int);
	void *GetBling(UnsignedInt blingId);			// 0x00219D85
	const CreateAHeroHero *GetHeroForPlayer(const Player *player);
	CreateAHeroClass *rva0021B31C(const AsciiString &upgradeName);
	void rva0021A428(const CreateAHeroData &hero);

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
	unsigned char m_pad168[0x174 - 0x168];
    std::vector<CreateAHeroData *> m_userHeroes;
    unsigned char m_pad180[0x188-0x180];
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
};

// The manager's global: GameEngine::init registers the subsystem under the
// name "TheCreateAHeroManager" (call site 0x0022FC2F) into VA 0x00DFE344;
// matched references place it there (retail .data initial value 0).
extern CreateAHeroManager *TheCreateAHeroManager;

// iniParseCreateAHeroSystem's views. The CreateAHeroSystem block's field table
// (VA 0x00BE6888) names each manager field it fills; the stat names are
// checked by the 0x00219453 validator, which throws INIException.
extern "C" const FieldParse CreateAHeroSystemFieldParse[];

bool Rva00219453Validate(int stat, const char *name);	// 0x00219453

class INIException
{
public:
	INIException(int argCount, const char *format, ...);	// 0x0002F681
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};

class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;	// 0x0026F26D
};

extern UpgradeCenter *TheUpgradeCenter;

// isEmpty was header-defined: MSVC keeps the call out of line (0x00001E2F) but,
// knowing the body, does not reload TheCreateAHeroManager across it.
template <> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }

// Native 21AD88..21ADD9 is the cdecl comparator passed by the independently
// bounded sort wrapper21E673. The preceding43B member ends exactly at21AD88;
// the comparator returns at21ADD8 before the following member starts21ADD9.
// Each four-byte value selects a bling and its upgrade; only the unsigned
// word at upgrade+88 participates in ordering. Its original field and
// comparator names are unresolved. Ghidra omitted this standalone boundary.
struct BlingUpgradeOrderView { char unknown00[0x88]; unsigned int word88; };
typedef bool (*BlingIndexLess)(unsigned int, unsigned int);
namespace _STL {
template <> void sort<unsigned int *, BlingIndexLess>(unsigned int *, unsigned int *, BlingIndexLess);
}
namespace _STL {
template <> vector<unsigned int> &map<int, vector<unsigned int> >::operator[](const int &);
}
// Native substring builder and conversion use the same12-byte view ABI.
struct Rva000B6AF5Rec { void *p; int a; int b; };
struct Rva000B6AA9Rec {
    operator AsciiString();
    AsciiString *m_string; int m_start; int m_len;
};
Rva000B6AF5Rec *__cdecl Rva000B6AF5Build(Rva000B6AF5Rec *, void **, int);
// Retail expands the old nullable character accessor. The canonical
// string header's current getCharAt deliberately calls a different body.
inline char BlingFirstChar(const AsciiString &string)
{
    const char *buffer=*reinterpret_cast<const char *const *>(&string);
    return buffer ? buffer[8] : 0;
}

class Rva0040A3F9 { public: CreateAHeroData *rva0040A32F(int); };
class Rva002196A9 { public: int rva002196A9(unsigned); };
Bool CreateAHeroManager::GetAvailableHeroesForFaction(std::vector<unsigned int> *result, int faction)
{
    const unsigned count=m_userHeroes.size();
    // The native clear is the rowed ICF erase 0x0031BD55 shared by every 4-byte element
    // vector; calling it through the void-pointer view resolves to that body.
    ((_STL::vector<void *> *)result)->clear();
    for (unsigned i=0;i<count;++i) {
        CreateAHeroData *hero=reinterpret_cast<Rva0040A3F9 *>(&m_userHeroes)->rva0040A32F(i);
        if (!hero) continue;
        const CreateAHeroSubClass *sub=rva0021A1B6(hero->classIndex,hero->subClassIndex);
        if (!sub) continue;
        if (faction==-1 || static_cast<unsigned char>(reinterpret_cast<Rva002196A9 *>(const_cast<CreateAHeroSubClass *>(sub))->rva002196A9(faction)))
            result->push_back(i);
    }
    return result->size()>0;
}
