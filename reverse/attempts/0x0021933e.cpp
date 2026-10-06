// ?GetRequiredButton@CreateAHeroManager@@QAEPBVCommandButton@@I@Z
// partial score=0.85 date=2026-10-06
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

// The manager's required-button count, rowed under the placeholder
// Rva00219309 (unnamed in WB; its assert calls it GetRequiredButtonCount).
class Rva00219309
{
public:
	Int rva00219309();					// 0x00219309
};

class CreateAHeroManager
{
public:
	class CreateAHeroSubClass
	{
	public:
		Int rva0021BC2C(Int blingKey) const;		// 0x0021BC2C, bling count
		Int GetDefaultBlingId(Int blingKey) const;	// 0x0021BC53
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


	Int GetBlingCount(Int blingKey, const CreateAHeroHero *hero) const;
	Int GetSubClassDefaultBlingId(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex) const;
	const AsciiString &GetBlingNameTag(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	const AsciiString &GetBlingDescTag(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	const AsciiString &GetBlingUpgradeName(Int blingKey, const CreateAHeroHero *hero, UnsignedInt index);
	Bool FindBlingByUpgradeName(const AsciiString &upgradeName, Int *index, Int *blingId);
	void *GetBling(UnsignedInt blingId);			// 0x00219D85
	const CommandButton *GetRequiredButton(UnsignedInt buttonIndex);

private:
	Int rva00219309() const;				// 0x00219309, required-button count

	unsigned char m_pad00[0x14c];
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

// CreateAHeroManager::GetSubClassDefaultBlingId, retail 0x0021BF11.
Int CreateAHeroManager::GetSubClassDefaultBlingId(Int blingKey, UnsignedInt classIndex, UnsignedInt subClassIndex) const
{
	if (classIndex < m_classes.size())
		return m_classes[classIndex].GetSubClassDefaultBlingId(blingKey, subClassIndex);
	return 0;
}

// CreateAHeroManager::GetRequiredButton, retail 0x0021933E (50 bytes): WB
// asserts the index is below the required-button count; the button is the
// one at that index of the manager's command set, NULL when either is absent.
const CommandButton *CreateAHeroManager::GetRequiredButton(UnsignedInt buttonIndex)
{
	if (buttonIndex >= (UnsignedInt)((Rva00219309 *)this)->rva00219309())
		return 0;
	const CommandSet *commandSet = TheControlBar->findCommandSet(m_commandSetName);
	return commandSet ? commandSet->getCommandButton(buttonIndex) : 0;
}
