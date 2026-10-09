// ?ConstructHeroBlingList@CreateAHeroHero@@QAEXXZ
// partial score=0.74 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// CreateAHeroHero.cpp -- CreateAHeroHero members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names each function and
// its source file; retail supplies the bytes.
//
// Layout (target evidence): the hero's bling lists live in an STLport map
// whose header node pointer is at +0x74; each node keeps a vector of bling
// ids at +0x14/+0x18. The 31-byte lookup at 0x004079D5 (unnamed in WB) finds
// the node and reports whether it is not the end.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, Int line);	// 0x00234111
// Retail's __FILE__ for this unit; the call sites pass their original line.
#define CREATEAHEROHERO_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\CreateAHeroHero.cpp"

#include "ascii_string.h"

class CreateAHeroManager
{
public:
	class CreateAHeroSubClass {
    public:
        void *GetBlingGroupNameKey(unsigned int);
        unsigned int GetBlingIndex(int,unsigned int);
        char prefix[0x28]; unsigned groupCount;
    };
    const CreateAHeroSubClass *rva0021A1B6(unsigned int,unsigned int);
    bool FindBlingByUpgradeName(const AsciiString &,int*,int*);
    unsigned char m_pad00[0x1c0];
	Real m_rollChance;			// +0x1C0, percent
	unsigned char m_pad1C4[0x1dc - 0x1c4];
	AsciiString m_baseCommandSetName;	// +0x1DC
};

extern CreateAHeroManager *TheCreateAHeroManager;

struct CreateAHeroBlingNode
{
	unsigned char m_pad00[0x14];
	Int *m_idsStart;			// +0x14
	Int *m_idsFinish;			// +0x18
};

class CreateAHeroHero;

// Same witnessed STLport bit-vector ABI as the rowed award-reset provider.
// operator[] returns the eight-byte bit reference by value (native6BE1F).
#include <vector>
#include <map>
#include <algorithm>
class Rva0021937DTarget { public: void rva00407E94(); };
class Rva00406E7D { public: int rva00406E7D(); };
class Rva00406E8F { public: int rva00406E8F(unsigned int); };
struct BfmePod40;
class Rva0040AAD5 { public: BfmePod40 *rva0040AAD5(int); };
extern Rva0040AAD5 *g_00E02F74;
class InGameUI
{
public:
	void notifyHeroEarnedAward(CreateAHeroHero *, int);
};
extern InGameUI *TheInGameUI;
// Retain the timeline provider's existing scalar ABI spelling. Its ScienceType
// label is provisional: this call's word is the rowed GetAwardNameKey result,
// not independent evidence that award keys are science identifiers.
enum ScienceType { SCIENCE_FIRST = 0, SCIENCE_FORCE_LONG = 0x7fffffff };
void Rva005200C5Add(void *, ScienceType);

// The twelve-byte per-level button record (CreateAHeroElementCopy.cpp's
// BfmeHeroElement005C39DE): the button name, its experience level and a
// third word. SetButtonForLevel 0x0040737F stores one into the fifteen at
// +0x80.
struct BfmeHeroElement005C39DE
{
	AsciiString text;
	unsigned word4, word8;
	BfmeHeroElement005C39DE(const AsciiString &name, unsigned level, unsigned value);
	BfmeHeroElement005C39DE &operator=(const BfmeHeroElement005C39DE &);
};

// Target offsets read by native4078A8; WB names the command-button,
// special-power and upgrade paths. The two command values remain numeric.
class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
private:
	void *m_vtbl;
};
class SpecialPowerTemplate : public Overridable
{
public:
	unsigned char m_pad04[0x10 - 4];
	AsciiString m_name;
};
class UpgradeTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	unsigned char m_pad00[8];
	AsciiString m_name;
};
class CommandButton
{
public:
	const UpgradeTemplate *getNeededUpgrade() const { return m_neededBegin[0]; }
	unsigned char m_pad00[0x14];
	Int m_command;
	unsigned char m_pad18[4];
	UnsignedInt m_options;
	unsigned char m_pad20[8];
	const UpgradeTemplate **m_neededBegin, **m_neededEnd, **m_neededCapacity;
	unsigned char m_pad34[0x44 - 0x34];
	const SpecialPowerTemplate *m_power;
};
// The command set UpdateCommandSet builds, rowed under the address names
// its reset (0x00409F83, WB CommandSet::ResetCommandSet) and button setter
// (0x00409FA0, WB CommandSet::SetCommandButton; the ledger spells the button
// argument as an int) carry; ControlBar's 0x0031E8D5 returns it.
class Rva00409FFA
{
public:
	void rva00409F83();								// 0x00409F83
	void rva00409FA0(Int button, Int index);		// 0x00409FA0
};
class CommandSet
{
public:
	const CommandButton *getCommandButton(Int index) const;	// 0x00409EE8
};
// ControlBar's command-set lookup by name (0x0031D5F8), rowed under its
// address-named class.
class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *name);		// 0x0031D5F8
};
class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &);
	Rva00409FFA *rva0031E8D5(const AsciiString &name, Int create);	// 0x0031E8D5

	unsigned char m_pad00[0x28];
	Bool m_commandSetsChanged;		// +0x28
};
extern ControlBar *TheControlBar;
class Object
{
public:
	const AsciiString &rva00292330(const AsciiString &);

	unsigned char m_pad00[0x88];
	AsciiString m_templateName;			// +0x88
	unsigned char m_pad8C[0x41c - 0x8c];
	AsciiString m_commandSetStringOverride;	// +0x41C
};
class Rva004076EE { public: Object *rva004076EE(); };
class ExperienceLevelStore
{
public:
	Bool CreateNewExpLevel(const AsciiString &source, const AsciiString &name,
		const AsciiString &experience, const AsciiString &upgrades, const AsciiString &attributes);
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

// WorldBuilder's CAH_MAX_EXP_LEVELS (the SetButtonForLevel assert).
enum { CAH_MAX_EXP_LEVELS = 15 };

// Award record; 0x0040AA27 (unnamed in WB) tests every requirement against
// the hero.
class CreateAHeroAward
{
public:
	Bool rva0040AA27(const CreateAHeroHero *hero) const;	// 0x0040AA27
};

class CreateAHeroHero
{
public:
	void ConstructHeroBlingList();
	Bool HasEarnedAward(const CreateAHeroAward *award) const;
	Int GetBlingCount(Int blingKey) const;
	Int GetBlingId(Int blingKey, UnsignedInt index) const;
	Bool SetButtonForLevel(const AsciiString &button, UnsignedInt experienceLevel, UnsignedInt value);
	void UpdateAwardEarnedFlags();
	Bool AddCommandButtonLevel(UnsignedInt index, const AsciiString &source,
		const AsciiString &name, const AsciiString &experience);
	Bool UpdateCommandSet(UnsignedInt rank);

private:
	Bool rva004079D5(Int blingKey, CreateAHeroBlingNode **found) const;	// 0x004079D5

	unsigned char m_pad00[12];
    unsigned m_classIndex,m_subClassIndex;
    unsigned char m_pad14[0x38-0x14];
	UnsignedInt m_state38;
	unsigned char m_pad3C[0x4C - 0x3C];
	AsciiString m_className;				// +0x4C
	unsigned char m_pad50[0x5C - 0x50];
	_STL::vector<bool> m_awardEarnedFlags; // +0x5C
	Bool m_flag70, m_updateAwards; // +0x70, +0x71
	unsigned char m_pad72[2];
	_STL::map<int,_STL::vector<unsigned> > m_bling74; // +0x74
	BfmeHeroElement005C39DE m_buttons[CAH_MAX_EXP_LEVELS];	// +0x80
};

// WB10828C0 identifies this member; native407F05..407FB2 supplies the
// incremental award loop, state bit9 reset and both notification calls.
void CreateAHeroHero::UpdateAwardEarnedFlags()
{
	if (!m_updateAwards)
		return;
	if (m_state38 & 0x200)
	{
		m_state38 &= ~0x200;
		((Rva0021937DTarget *)this)->rva00407E94();
	}
	UnsignedInt count = ((Rva00406E7D *)this)->rva00406E7D();
	for (UnsignedInt i = 0; i < count; ++i)
	{
		if (m_awardEarnedFlags[i])
			continue;
		Int key = ((Rva00406E8F *)this)->rva00406E8F(i);
		BfmePod40 *award = g_00E02F74->rva0040AAD5(key);
		if (award && HasEarnedAward((const CreateAHeroAward *)award))
		{
			m_awardEarnedFlags[i] = true;
			if (TheInGameUI)
				TheInGameUI->notifyHeroEarnedAward(this, key);
			Rva005200C5Add(this, (ScienceType)key);
		}
	}
}

// CreateAHeroHero::HasEarnedAward, retail 0x00406EA7.
Bool CreateAHeroHero::HasEarnedAward(const CreateAHeroAward *award) const
{
	if (award == 0)
		return false;
	return award->rva0040AA27(this);
}

// CreateAHeroHero::GetBlingCount, retail 0x004079F4.
Int CreateAHeroHero::GetBlingCount(Int blingKey) const
{
	CreateAHeroBlingNode *node = 0;
	if (rva004079D5(blingKey, &node) && node != reinterpret_cast<CreateAHeroBlingNode *>(m_bling74.end()._M_node))
		return node->m_idsFinish - node->m_idsStart;
	return 0;
}

// CreateAHeroHero::GetBlingId, retail 0x00407A29.
Int CreateAHeroHero::GetBlingId(Int blingKey, UnsignedInt index) const
{
	CreateAHeroBlingNode *node = 0;
	if (rva004079D5(blingKey, &node) && node != reinterpret_cast<CreateAHeroBlingNode *>(m_bling74.end()._M_node)
		&& index < (UnsignedInt)(node->m_idsFinish - node->m_idsStart))
		return node->m_idsStart[index];
	return 0;
}

// Retail 0x00406DE3 (WorldBuilder pairs it unnamed, CreateAHeroHero.cpp line
// 160): a client-random percent roll against the manager's chance.
Bool rva00406DE3RollChance()
{
	Real roll = GetGameClientRandomValueReal(0.0f, 100.0f, CREATEAHEROHERO_FILE, 160);
	return roll <= TheCreateAHeroManager->m_rollChance;
}

// Retail 0x004071D7, 32 bytes (unnamed in WorldBuilder, called from
// SetButtonForLevel): the per-level record's constructor.
BfmeHeroElement005C39DE::BfmeHeroElement005C39DE(const AsciiString &name, unsigned level, unsigned value)
	: text(name), word4(level), word8(value)
{
}

// CreateAHeroHero::SetButtonForLevel, retail 0x0040737F (WorldBuilder,
// CreateAHeroHero.cpp line 1029; wb-name-unverified).
Bool CreateAHeroHero::SetButtonForLevel(const AsciiString &button, UnsignedInt experienceLevel, UnsignedInt value)
{
	if (experienceLevel < CAH_MAX_EXP_LEVELS)
	{
		BfmeHeroElement005C39DE record(button, experienceLevel, value);
		m_buttons[experienceLevel] = record;
	}
	return true;
}

// WB107E250 supplies the identity; native4078A8..4079D0 supplies this
// RET16 body and every field offset. CreateNewExpLevel's native28A473
// RET20 and WB BE9C10 show five string references: the third is pushed into
// vector<AsciiString>, and the last two go to SplitUpgrades/SplitString.
Bool CreateAHeroHero::AddCommandButtonLevel(UnsignedInt index, const AsciiString &source,
	const AsciiString &name, const AsciiString &experience)
{
	Object *object = ((Rva004076EE *)this)->rva004076EE();
	const CommandButton *button = TheControlBar->findCommandButton(m_buttons[index].text);
	if (!button)
		return false;
	if (button->m_command == 0x18 || button->m_command == 0x25)
	{
		const SpecialPowerTemplate *power = button->m_power;
		if (!power)
			return false;
		power = (const SpecialPowerTemplate *)power->friend_getFinalOverride();
		AsciiString upgradeName = object->rva00292330(power->m_name);
		if (upgradeName.isEmpty())
			return false;
		((ExperienceLevelStore *)TheExperienceLevelSystem)->CreateNewExpLevel(
			source, name, experience, upgradeName, AsciiString());
		return true;
	}
	if (button->m_options & 0x40)
	{
		if ((UnsignedInt)(button->m_neededEnd - button->m_neededBegin) != 1)
			return false;
		const AsciiString &upgradeName = button->getNeededUpgrade()->getName();
		if (((const StringBase<char> *)&upgradeName)->isEmpty())
			return false;
		((ExperienceLevelStore *)TheExperienceLevelSystem)->CreateNewExpLevel(
			source, name, experience, upgradeName, AsciiString());
		return true;
	}
	return false;
}

// CreateAHeroHero::UpdateCommandSet, retail 0x00407705 (WorldBuilder
// 0x0107DDF0, CreateAHeroHero.cpp lines 740..792; wb-name-unverified):
// names the hero object's command set after its template, the hero class and
// the rank, rebuilds it from the manager's base set, then lays each level
// button into its slot (a later level only while below the rank) and the
// attack-move button into slot 16.
Bool CreateAHeroHero::UpdateCommandSet(UnsignedInt rank)
{
	Object *object = ((Rva004076EE *)this)->rva004076EE();
	if (!object)
		return false;

	AsciiString commandSetName;
	commandSetName.format("CommandSet_%s_%s_rank_%d", object->m_templateName.str(), m_className.str(), rank);
	object->m_commandSetStringOverride = commandSetName;
	Rva00409FFA *commandSet = TheControlBar->rva0031E8D5(commandSetName, 1);
	commandSet->rva00409F83();

	const CommandSet *baseSet = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(
		&TheCreateAHeroManager->m_baseCommandSetName);
	if (baseSet)
	{
		for (UnsignedInt i = 0; i < 32; ++i)
		{
			const CommandButton *button = baseSet->getCommandButton(i);
			if (button)
				commandSet->rva00409FA0((Int)button, i);
		}
	}

	for (UnsignedInt slot = 0; slot < 32; ++slot)
	{
		Bool found = false;
		for (Int i = 0; !((const StringBase<char> *)&m_buttons[i].text)->isEmpty(); ++i)
		{
			UnsignedInt buttonSlot = m_buttons[i].word8;
			if (buttonSlot != slot)
				continue;
			if (found && m_buttons[i].word4 >= rank)
				continue;
			const CommandButton *button = TheControlBar->findCommandButton(m_buttons[i].text);
			if (!button)
				continue;
			found = true;
			commandSet->rva00409FA0((Int)button, buttonSlot);
		}
	}

	AsciiString attackMove("Command_AttackMove");
	const CommandButton *button = TheControlBar->findCommandButton(attackMove);
	if (button)
		commandSet->rva00409FA0((Int)button, 0x10);
	TheControlBar->m_commandSetsChanged = true;
	return true;
}

class Rva0021BC2C { public: int rva0021BC2C(int); };


struct BfmePod40;

extern Rva0040AAD5 *g_00E02F74;
class Rva0040AA27 { public: int rva0040AA27(int); };
class Rva0040A7F1 { public: int rva0040A7F1(int) const; };
class Rva004079D5 { public: char rva004079D5(int, int *); };
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator { public: const AsciiString &keyToName(NameKeyType); };
extern NameKeyGenerator *TheNameKeyGenerator;
struct HeroAwardBlingView {
    unsigned int unknown00;
    _STL::vector<int> upgradeKeys;
};
struct HeroBlingNodeView {
    unsigned char opaque00[0x14];
    _STL::vector<unsigned int> blingIds;
};
namespace _STL { template<> vector<unsigned int> &map<int, vector<unsigned int> >::operator[](const int &); }
// ?ConstructHeroBlingList@CreateAHeroHero@@QAEXXZ
void CreateAHeroHero::ConstructHeroBlingList()
{
    CreateAHeroManager::CreateAHeroSubClass *subClass = const_cast<CreateAHeroManager::CreateAHeroSubClass *>(TheCreateAHeroManager->rva0021A1B6(m_classIndex, m_subClassIndex));
    m_state38 &= ~0x80;
    if (subClass)
    {
        m_bling74.clear();
        for (unsigned int groupIndex = 0; groupIndex < subClass->groupCount; ++groupIndex)
        {
            int groupKey = reinterpret_cast<int>(subClass->GetBlingGroupNameKey(groupIndex));
            for (unsigned int index = 0; index < static_cast<unsigned int>(reinterpret_cast<Rva0021BC2C *>(subClass)->rva0021BC2C(groupKey)); ++index)
            {
                unsigned int blingId = subClass->GetBlingIndex(groupKey, index);
                m_bling74[groupKey].push_back(blingId);
            }
        }
        for (unsigned int awardIndex = 0; awardIndex < static_cast<unsigned int>(reinterpret_cast<Rva00406E7D *>(this)->rva00406E7D()); ++awardIndex)
        {
            BfmePod40 *award = g_00E02F74->rva0040AAD5(reinterpret_cast<Rva00406E8F *>(this)->rva00406E8F(awardIndex));
            if (!award || !static_cast<unsigned char>(reinterpret_cast<Rva0040AA27 *>(award)->rva0040AA27(reinterpret_cast<int>(this))))
                continue;
            HeroAwardBlingView *awardView = reinterpret_cast<HeroAwardBlingView *>(award);
            for (unsigned int upgradeIndex = 0; upgradeIndex < awardView->upgradeKeys.size(); ++upgradeIndex)
            {
                AsciiString upgradeName(TheNameKeyGenerator->keyToName(static_cast<NameKeyType>(reinterpret_cast<Rva0040A7F1 *>(award)->rva0040A7F1(upgradeIndex))));
                unsigned int blingId = 0;
                int groupKey = 0;
                int nodeBits = 0;
                if (TheCreateAHeroManager->FindBlingByUpgradeName(upgradeName, reinterpret_cast<int *>(&blingId), &groupKey) && reinterpret_cast<Rva004079D5 *>(this)->rva004079D5(groupKey, &nodeBits))
                {
                    _STL::vector<unsigned int> *ids = &reinterpret_cast<HeroBlingNodeView *>(nodeBits)->blingIds;
                    if (_STL::find(ids->begin(), ids->end(), blingId) == ids->end())
                        m_bling74[groupKey].push_back(blingId);
                }
            }
        }
    }
}
