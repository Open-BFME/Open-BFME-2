// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_CRTIMP= -D_STLP_USE_STATIC_LIB -EHs -MD -Ireference/shims/subsystem_bfme2
// The +15C/+168 vector destructors require the retail free-backed allocator
// and /EHs: both complete 63-byte bodies retain the unwind state through free.
// Constructor421B and its complete15-state EH graph match retail.
// Storage is established by rowed32B class record copy/dtor and16/20B bling records.
// Native state5 calls40A603 after constructor40A530 on the pointer vector at174.
// Native56B destructor40A603 clears the owned pointer vector through40A59B
// and frees its first pointer; its own EH cleanup7854A8 reaches base7FAB3.
// The older tree-shaped donor row is not evidence of the target container type.
// WB B7EE40 names LoadMyHeroList; retail21F47E..21F5E3 supplies extent and layout.
// Complete357B instruction sequence with three unresolved calls: 408A55 data refresh;
// 21F19B file vector construction; 4099CA file load with one-byte mode argument.
// Existing registered 4099CA helper uses an int prototype; do not fake its pin.
// Qualified ::delete is required by native vslot0(flags0) then global delete.
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
#include "unicode_string.h"
#include <vector>
#include <map>
#include <algorithm>
#include <stdlib.h>

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

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
#include "subsystem_interface.h"

class CreateAHeroHero
{
public:
	Int GetBlingCount(Int blingKey) const;			// 0x004079F4
	Int GetBlingId(Int blingKey, UnsignedInt index) const;	// 0x00407A29
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

class INI
{
public:
	INI();							// 0x0002CDB0
	~INI();							// 0x0002CE5B
	void loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer);	// 0x0002DC75

private:
	unsigned char m_data[0x87c];
};

class CreateAHeroSubsystemListView
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


class CreateAHeroData
{
public:
    CreateAHeroData(int, int, int, const UnicodeString &, int, int, int);
    virtual ~CreateAHeroData();
    bool rva00408A55();
    bool rva004099CA(AsciiString *filename, bool mode);
    unsigned char m_pad04[0x134-4];
    unsigned int m_crc;
    unsigned char m_pad138[8];
};
class Rva0040A3F9
{
public:
	__forceinline ~Rva0040A3F9() { if (m_begin) free(m_begin); }
    CreateAHeroData **m_begin;
    CreateAHeroData **m_end;
    CreateAHeroData **m_capacity;
    bool m_flag;
    unsigned int size() const { return m_end - m_begin; }
    CreateAHeroData *rva0040A32F(int index);
};
class ModuleData;
class Rva00423A68
{
public:
    void rva00423A68(const ModuleData *p);
};
struct CreateAHeroFileEntry
{
    AsciiString filename;
    bool system;
};
struct Rva0021DB35
{
    Rva0021DB35(); // native21F19B fills a vector of file-name / flag pairs
    ~Rva0021DB35();
    CreateAHeroFileEntry *m_begin;
    CreateAHeroFileEntry *m_end;
    CreateAHeroFileEntry *m_capacity;
};
class Debug
{
public:
	static bool SkipNext(bool skip);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual Debug &slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(int report);
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual Debug &slot6C(int first, int second, int third);
};

extern Debug *theDebug;


void _bfme_debugRecordCallsite(int kind);

class Rva0040A530 : public Rva0040A3F9
{
public:
    Rva0040A530(bool flag);
    __declspec(noinline) ~Rva0040A530();
};

// Retail copy/destruction providers establish these storage element views.
// Their application identities remain represented by the existing ledger names.

struct BfmeStringRecord002199C8
{
    ~BfmeStringRecord002199C8();
    AsciiString text0, text1, text2;
    unsigned int word;
};
struct BfmeStringRecord00219A68
{
    ~BfmeStringRecord00219A68();
    unsigned int word0;
    AsciiString text0, text1;
    unsigned int word1, word2;
};
class CreateAHeroManager : public SubsystemInterface
{
public:
	class CreateAHeroSubClass
	{
	public:
		Int rva0021BC2C(Int blingKey) const;		// 0x0021BC2C, bling count
		Int GetDefaultBlingId(Int blingKey) const; // 0x0021BC53
    private:
        // WB lookup and retail node+14/+18 prove the vector mapped value.
        // Retail map headers are at +24 and +48.
        unsigned char m_pad00[0x24];
        std::map<int, std::vector<int> > m_blingIds;
        unsigned char m_pad30[0x48-0x30];
        std::map<int, int> m_defaultBlingIds;
	};

	class CreateAHeroClass
	{
	public:
		~CreateAHeroClass();
		Int GetBlingCount(Int blingKey, UnsignedInt subClassIndex) const;
		Int GetSubClassDefaultBlingId(Int blingKey, UnsignedInt subClassIndex) const;

	private:
		const CreateAHeroSubClass *rva00219B9E(UnsignedInt subClassIndex) const;	// 0x00219B9E

		unsigned char m_data[0x20];
	};


	// SubsystemInterface native vtable 0x00BE648C: slot 2 is a `return true`
	// loadIniFilesFromLegend (0x0050B5C6), slots 9/10 reset and update the
	// folded empty body 0x000B3FD0; Rva0021FFEEDtor.cpp holds the same view.
    CreateAHeroManager();
	// ?loadIniFilesFromLegend@CreateAHeroManager present-unmatched
	virtual Bool loadIniFilesFromLegend() { return true; }
	// ?reset@CreateAHeroManager present-unmatched
    virtual void reset() {}
	// ?update@CreateAHeroManager present-unmatched
    virtual void update() {}
	virtual ~CreateAHeroManager();
	virtual void init();

	Int GetBlingCount(Int blingKey, const CreateAHeroHero *hero) const;
	Int rva0021BEE0(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex) const;
	Int GetSubClassDefaultBlingId(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex) const;
	const AsciiString &GetBlingNameTag(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	const AsciiString &GetBlingDescTag(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	const AsciiString &GetBlingUpgradeName(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	void LoadMyHeroList();
	Bool FindBlingByUpgradeName(const AsciiString &upgradeName, Int *index, Int *blingId);
	void *GetBling(UnsignedInt blingId);			// 0x00219D85
	const CreateAHeroHero *GetHeroForPlayer(const Player *player);

private:
	Int rva00219309() const;				// 0x00219309, required-button count

	CreateAHeroData m_localHero;				// +0x0C, used without a game
	std::vector<CreateAHeroClass> m_classes;		// +0x14C
	int m_numSystemHeroes;
	std::vector<BfmeStringRecord002199C8> m_blings;		// +0x15C
	std::vector<BfmeStringRecord00219A68> m_vector168; // WB bling binder list; stride20
    Rva0040A530 m_myHeroList; // +174
    bool m_flag184;
    AsciiString m_text188, m_text18C, m_text190;
    unsigned int m_word194, m_word198, m_word19C, m_word1A0, m_word1A4, m_word1A8, m_word1AC, m_word1B0, m_word1B4, m_word1B8, m_word1BC;
    float m_float1C0;
    AsciiString m_text1C4, m_text1C8, m_text1CC;
    unsigned int m_word1D0, m_word1D4;
    bool m_refreshList;
    unsigned char m_pad1D9[3];
	AsciiString m_commandSetName;				// +0x1DC
    unsigned int m_word1E0, m_word1E4;
    AsciiString m_fadeDown, m_fadeUp;
    unsigned int m_systemHeroCRC;
};

// The manager's global: GameEngine::init registers the subsystem under the
// name "TheCreateAHeroManager" (call site 0x0022FC2F) into VA 0x00DFE344;
// matched references place it there (retail .data initial value 0).
extern CreateAHeroManager *TheCreateAHeroManager;

CreateAHeroManager::CreateAHeroManager()
 : m_localHero(0,0,0,UnicodeString::TheEmptyString,-1,0xff707070,-1),
   m_numSystemHeroes(0), m_myHeroList(false), m_flag184(false),
   m_word194(0), m_word198(0), m_word19C(0), m_word1A0(0), m_word1A4(0), m_word1A8(0), m_word1AC(0), m_word1B0(0), m_word1B4(0), m_word1B8(0), m_word1BC(0),
   m_float1C0(50.0f), m_word1D0(0), m_word1D4(0), m_refreshList(false), m_word1E0(0), m_word1E4(0),
   m_fadeDown("FadeCreateAHeroScreenDown"), m_fadeUp("FadeCreateAHeroScreenUp"), m_systemHeroCRC(0)
{
    if (g_Va00DFE348) {
        _bfme_debugRecordCallsite(1);
        theDebug->slot60();
        theDebug->slot6C(0,0,0).slot38("Instance of CreateAHeroManager already exists!!").slot4C(1);
    }
    g_Va00DFE348 = (int)this;
}

class Rva0040A59B { public: void rva0040A59B(); };
Rva0040A530::~Rva0040A530() { reinterpret_cast<Rva0040A59B *>(this)->rva0040A59B(); }
