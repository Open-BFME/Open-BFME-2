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
#include <vector>
#include <map>
#include <algorithm>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

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
		Int GetBlingCount(Int blingKey, UnsignedInt subClassIndex) const;
		Int GetSubClassDefaultBlingId(Int blingKey, UnsignedInt subClassIndex) const;

	private:
		const CreateAHeroSubClass *rva00219B9E(UnsignedInt subClassIndex) const;	// 0x00219B9E

		unsigned char m_data[0x20];
	};


	// SubsystemInterface slots 0 and 1 (vtable 0x007E648C).
	virtual ~CreateAHeroManager();
	virtual void init();

	Int GetBlingCount(Int blingKey, const CreateAHeroHero *hero) const;
	Int rva0021BEE0(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex) const;
	Int GetSubClassDefaultBlingId(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex) const;
	const AsciiString &GetBlingNameTag(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	const AsciiString &GetBlingDescTag(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	const AsciiString &GetBlingUpgradeName(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	Bool FindBlingByUpgradeName(const AsciiString &upgradeName, Int *index, Int *blingId);
	void *GetBling(UnsignedInt blingId);			// 0x00219D85
	const CreateAHeroHero *GetHeroForPlayer(const Player *player);

private:
	Int rva00219309() const;				// 0x00219309, required-button count

	unsigned char m_pad04[0xc - 0x4];
	CreateAHeroHero m_localHero;				// +0x0C, used without a game
	unsigned char m_pad0D[0x14c - 0xd];
	std::vector<CreateAHeroClass> m_classes;		// +0x14C
	unsigned char m_pad158[0x15c - 0x158];
	std::vector<CreateAHeroBlingEntry> m_blings;		// +0x15C
	unsigned char m_pad168[0x1dc - 0x168];
	AsciiString m_commandSetName;				// +0x1DC
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

// CreateAHeroManager::CreateAHeroClass::GetBlingCount, retail 0x0021BE23.
Int CreateAHeroManager::CreateAHeroClass::GetBlingCount(Int blingKey, UnsignedInt subClassIndex) const
{
	const CreateAHeroSubClass *subClass = rva00219B9E(subClassIndex);
	if (subClass)
		return subClass->rva0021BC2C(blingKey);
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

// CreateAHeroManager::FindBlingByUpgradeName, retail 0x0021D4CE: the table
// index and id of the bling granted by an upgrade.
Bool CreateAHeroManager::FindBlingByUpgradeName(const AsciiString &upgradeName, Int *index, Int *blingId)
{
	CreateAHeroBlingEntry *it = rva0021D120(m_blings.begin(), m_blings.end(), upgradeName);
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
        std::map<int, std::vector<int> >::const_iterator ids = m_blingIds.find(blingKey);
        if (ids != m_blingIds.end()) {
            const std::vector<int> &list = ids->second;
            const int *it = std::find(list.begin(), list.end(), def->second);
            if (it != list.end())
                return it - list.begin();
        }
    }
    return 0;
}
