// WB B7EE40 names LoadMyHeroList; retail21F47E..21F5E3 supplies extent and layout.
// Complete357B instruction sequence with three unresolved calls: 408A55 data refresh;
// 21F19B file vector construction; 4099CA file load with one-byte mode argument.
// 4099CA takes the flag as one byte (the spilled flag's dword is pushed whole);
// its row (CreateAHeroDataDtor.cpp) and the 21F19B ctor row carry these names.
// Qualified ::delete is required by native vslot0(flags0) then global delete.
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
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
#include "unicode_string.h"
#include <vector>
#include <stdlib.h>
#include <map>
#include <algorithm>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class AsciiString;
class CreateAHeroHero
{
public:
	int GetBlingCount(int blingKey) const; // 0x004079F4
	int GetBlingId(int blingKey, unsigned int index) const; // 0x00407A29
	bool rva004098BE(const AsciiString &file, bool system);
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
	int m_blingId;						// +0x0C
};

CreateAHeroBlingEntry *rva0021D120(CreateAHeroBlingEntry *first, CreateAHeroBlingEntry *last, const AsciiString &upgradeName);	// 0x0021D120

class CommandButton;

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;	// 0x00409EE8
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
	GameSlot *getSlot(int index);				// 0x003FF29F
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
	char m_storage04[0x130];
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
	CreateAHeroData *rva0040A5CF(const AsciiString &name);
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
struct BfmePod216 { int a[54]; };

struct Rva0021DA18
{
	~Rva0021DA18();
	char m_storage[12];
};

struct Rva0021DA57
{
	~Rva0021DA57();
	char m_storage[12];
};

class Rva0040A530 : public Rva0040A3F9
{
public:
	Rva0040A530(bool flag);
	__declspec(noinline) ~Rva0040A530();
};

#include "../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"

class CreateAHeroManager : public SubsystemInterface
{
public:
	// The named, independently rowed 00219C1F accessor views the same 32B class
	// record and its 216B subclass range. Keep the existing container spelling.
	class CreateAHeroClass
	{
	public:
		int GetAwardCount(unsigned int subClassIndex);
		CreateAHeroClass(const CreateAHeroClass &);
		~CreateAHeroClass();
		AsciiString m_strings[5];
		_STL::vector<BfmePod216> m_subclasses;
	};

	virtual ~CreateAHeroManager();
	virtual void init();
	virtual Bool loadIniFilesFromLegend();
	virtual void reset();
	virtual void update();
	CreateAHeroClass *rva0022020C(CreateAHeroClass &entry);
	void LoadMyHeroList();
	void rva0021F5F8();
private:
	CreateAHeroData m_hero0C;
	_STL::vector<CreateAHeroClass> m_vector14C;
	int m_158;
	Rva0021DA18 m_vector15C;
	Rva0021DA57 m_vector168;
	Rva0040A530 m_tree174;
	char m_pad180[4]; // +184; the pointer-vector view includes its +180 flag.
	AsciiString m_text188, m_text18C, m_text190;
	char m_pad194[0x30];
	AsciiString m_text1C4, m_text1C8, m_text1CC;
	int m_1D0;
	unsigned int m_maxAwards1D4;
	bool m_1D8;
	unsigned char m_pad1D9[3];
	AsciiString m_text1DC;
	int m_state1E0;
	int m_1E4;
	AsciiString m_text1E8, m_text1EC;
	unsigned int m_systemHeroCRC;
};

// The manager's global: GameEngine::init registers the subsystem under the
// name "TheCreateAHeroManager" (call site 0x0022FC2F) into VA 0x00DFE344;
// matched references place it there (retail .data initial value 0).
extern CreateAHeroManager *TheCreateAHeroManager;

// CreateAHeroManager::GetBlingCount, retail 0x00219239.

void CreateAHeroManager::LoadMyHeroList()
{
    if (m_tree174.size()) {
        if (m_1D8) {
            for (unsigned int i = 0; i < m_tree174.size(); ++i) {
                CreateAHeroData *hero = m_tree174.rva0040A32F(i);
                if (hero) hero->rva00408A55();
            }
            m_1D8 = false;
        }
    } else {
        Rva0021DB35 files;
        unsigned int crc = 0;
        m_158 = 0;
        for (CreateAHeroFileEntry *it = files.m_begin; it != files.m_end; ++it) {
            CreateAHeroData *hero = new CreateAHeroData(0,0,0,UnicodeString::TheEmptyString,-1,0xff707070,-1);
            bool system = it->system;
            if (hero->rva004099CA(&it->filename, system)) {
                ((Rva00423A68 *)&m_tree174)->rva00423A68((const ModuleData *)hero);
                if (system && !m_systemHeroCRC) {
                    ++m_158;
                    crc += hero->m_crc;
                    crc = (crc << 1) | (crc >> 31);
                }
            } else {
                ::delete hero;
            }
        }
        if (!m_systemHeroCRC) m_systemHeroCRC = crc;
    }
}
