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

class CreateAHeroHero;
class CreateAHeroManager
{
public:
	const AsciiString &GetBlingUpgradeName(Int blingKey, const CreateAHeroHero *hero, UnsignedInt id);
	const AsciiString &GetClassUpgradeName(UnsignedInt heroClass);
	const AsciiString &GetSubClassUpgradeName(UnsignedInt heroClass, UnsignedInt heroSubclass);

	unsigned char m_pad00[0x184];
	Bool m_active;						// +0x184
	unsigned char m_pad185[3];
	AsciiString m_upgradeOn;			// +0x188
	AsciiString m_upgradeOff;			// +0x18C
	unsigned char m_pad190[0x1bc - 0x190];
	Int m_fullBlingKey;					// +0x1BC
	Real m_rollChance;			// +0x1C0, percent
	unsigned char m_pad1C4[4];
	AsciiString m_shortAnimation;		// +0x1C8
	AsciiString m_fullAnimation;		// +0x1CC
	unsigned char m_pad1D0[0x1dc - 0x1d0];
	AsciiString m_baseCommandSetName;	// +0x1DC
	unsigned char m_pad1E0[4];
	UnsignedInt m_animationFrameOffset;	// +0x1E4
};

extern CreateAHeroManager *TheCreateAHeroManager;
// Update reads its manager through the dword at VA 0x00DFE348 (the ledger's
// ColdGlobalDwordGetters.cpp name), which the manager's init sets to itself;
// the frame offset at +0x1E4 is read through TheCreateAHeroManager.
extern int g_Va00DFE348;
// Retail's int at VA 0x00DBA4E4 (initial value 5), the animation frame scale.
extern int g_Va00DBA4E4;

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

namespace _STL {
template<class T, class L, class R>
static inline bool operator!=(const _Rb_tree_iterator<T,L> &a, const _Rb_tree_iterator<T,R> &b) { return a._M_node != b._M_node; }
template <> vector<AsciiString,allocator<AsciiString> >::~vector();
// Branch-form int overloads: this TU's flags compile the generic max/min ?:
// to cmov, but retail's out-of-line copies use a branch (row 57 family-LK3).
inline const int &(max)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pa < *__pb) return __b; return __a; }
inline const int &(min)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pb < *__pa) return __b; return __a; }
}

// Reads the operand through a volatile view: retail reloads the bling id
// from the map node on both arms of Update's id select.
template<class T> static __forceinline T BlingOperand(const T &v) { return *(const volatile T *)&v; }
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
enum ModelConditionFlagType { MODEL_CONDITION_UNKNOWN = -1 };
class Drawable;
class Object
{
public:
	const AsciiString &rva00292330(const AsciiString &);
	Drawable *getDrawable() const;
	void rva00293077(const void *upgrade);
	void rva00290D42(const UpgradeTemplate *upgrade);
	void setSpecialModelConditionState(ModelConditionFlagType type, UnsignedInt frames);

	unsigned char m_pad00[0x88];
	AsciiString m_templateName;			// +0x88
	unsigned char m_pad8C[0x264 - 0x8c];
	class Rva004074B6 *m_experience;		// +0x264
	unsigned char m_pad268[0x41c - 0x268];
	AsciiString m_commandSetStringOverride;	// +0x41C
};
class Rva004076EE { public: Object *rva004076EE(); void rva00407AE6(ModelConditionFlagType type, UnsignedInt frames); };
class UpgradeCenter { public: const UpgradeTemplate *findUpgrade(const AsciiString &name) const; };
extern UpgradeCenter *TheUpgradeCenter;
class Rva0021BFD8 { public: Bool rva0021BFD8(const StringBase<char> &name); };
// The hero colour record Update hands the drawable (0x00406D67 fills it).
class Rva00406D67 { public: Rva00406D67 *rva00406D67(unsigned red, unsigned green, unsigned blue); unsigned data[4]; };
class Drawable
{
public:
	void rva00274176(bool);
	void rva0027248A(int color, int names);
	int rva00272709();
	int rva0027272B();
};
// The drawable's null-terminated draw-module array (rowed get 0x002B224B).
class Rva002B224BDwordField
{
public:
	int get() const;
};
// Draw-module and draw-interface views: only the virtual slots the two
// animation helpers call are named.
class CreateAHeroAnimInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08();
	virtual int v24();
	virtual AsciiString v28(int unused);
	virtual void v11(); virtual void v12(); virtual void v13();
	virtual bool v38(void *animation, void *frameCount);
};
class CreateAHeroDrawModule
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41();
	virtual CreateAHeroAnimInterface *vA8();
};
class ExperienceLevelStore
{
public:
	Bool CreateNewExpLevel(const AsciiString &source, const AsciiString &name,
		const AsciiString &experience, const AsciiString &upgrades, const AsciiString &attributes);
};
class ExperienceLevelSystem;
class Rva004074B6 { public: void rva004074B6(const AsciiString &); };
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString &); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva0028951F { public: const Overridable *rva0028951F(int); };
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
	Bool HasEarnedAward(const CreateAHeroAward *award) const;
	Int GetBlingCount(Int blingKey) const;
	Int GetBlingId(Int blingKey, UnsignedInt index) const;
	Bool SetButtonForLevel(const AsciiString &button, UnsignedInt experienceLevel, UnsignedInt value);
	void UpdateAwardEarnedFlags();
	Bool AddCommandButtonLevel(UnsignedInt index, const AsciiString &source,
		const AsciiString &name, const AsciiString &experience);
	Bool UpdateCommandSet(UnsignedInt rank);
	Bool RegisterExperienceLevels();
	Bool Update(Int flags);
	AsciiString rva004073DC(const Rva002B224BDwordField *drawable);
	Bool GetAnimationFameCount(const Rva002B224BDwordField *drawable, void *animation, void *frameCount);

private:
	Bool rva004079D5(Int blingKey, CreateAHeroBlingNode **found) const;	// 0x004079D5

	unsigned char m_pad00[0x0C];
	UnsignedInt m_heroClass;				// +0x0C
	UnsignedInt m_heroSubclass;				// +0x10
	_STL::map<Int, Int> m_bling;			// +0x14
	_STL::map<Int, Int> m_priorBling;		// +0x20
	UnsignedInt m_red, m_green, m_blue;		// +0x2C
	UnsignedInt m_state38;
	unsigned char m_pad3C[0x4C - 0x3C];
	AsciiString m_className;				// +0x4C
	unsigned char m_pad50[0x5C - 0x50];
	_STL::vector<bool> m_awardEarnedFlags; // +0x5C
	Bool m_flag70, m_updateAwards; // +0x70, +0x71
	unsigned char m_pad72[2];
	CreateAHeroBlingNode *m_blingHeader;	// +0x74, map end node
	unsigned char m_pad78[0x80 - 0x78];
	BfmeHeroElement005C39DE m_buttons[CAH_MAX_EXP_LEVELS];	// +0x80
	unsigned char m_pad134[4];
	Int m_animationState;					// +0x138
	Int m_animationState2;					// +0x13C
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

// CreateAHeroHero::GetAnimationFameCount, retail 0x00406F51 75B (WorldBuilder
// 0x0107FA30 names it and asserts frameCount at CreateAHeroHero.cpp line
// 1150; Update's call at 0x0040877A sets ECX, the body ignores it). Asks each
// draw module's interface (slot 42) for the animation's frame count (slot 14).
Bool CreateAHeroHero::GetAnimationFameCount(const Rva002B224BDwordField *drawable, void *animation, void *frameCount)
{
	if (frameCount == 0)
		return false;
	CreateAHeroDrawModule **modules = (CreateAHeroDrawModule **)drawable->get();
	for (; *modules; ++modules) {
		CreateAHeroDrawModule *module = *modules;
		CreateAHeroAnimInterface *di = module->vA8();
		if (!di)
			continue;
		if (di->v38(animation, frameCount))
			return true;
	}
	return false;
}

// CreateAHeroHero::GetBlingCount, retail 0x004079F4.
Int CreateAHeroHero::GetBlingCount(Int blingKey) const
{
	CreateAHeroBlingNode *node = 0;
	if (rva004079D5(blingKey, &node) && node != m_blingHeader)
		return node->m_idsFinish - node->m_idsStart;
	return 0;
}

// CreateAHeroHero::GetBlingId, retail 0x00407A29.
Int CreateAHeroHero::GetBlingId(Int blingKey, UnsignedInt index) const
{
	CreateAHeroBlingNode *node = 0;
	if (rva004079D5(blingKey, &node) && node != m_blingHeader
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

// Retail 0x004073DC 177B (unnamed in WorldBuilder; its twin 0x0107F910 moves
// ECX into this, and Update's sole call at 0x004086D2 sets ECX): the first
// non-empty animation name a draw module's interface reports (slot 9 test,
// slot 10 name by value). Retail's unwind map tracks the return slot, the
// local result and the by-value temporary.
AsciiString CreateAHeroHero::rva004073DC(const Rva002B224BDwordField *drawable)
{
	AsciiString result;
	CreateAHeroDrawModule **cursor = (CreateAHeroDrawModule **)drawable->get();
	while (result.isEmpty() && *cursor)
	{
		CreateAHeroAnimInterface *thing = (*cursor)->vA8();
		if (thing && thing->v24())
			result = thing->v28(0);
		++cursor;
	}
	return result;
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

Bool CreateAHeroHero::RegisterExperienceLevels()
{
 Object *object = ((Rva004076EE *)this)->rva004076EE();
 if (!object) return false;
 AsciiString source;
 source.format("%s_%s", "CreateAHero", m_className.str());
 object->m_experience->rva004074B6(source);
 unsigned int index = 0;
 AsciiString level;
 level.format("CreateAHeroLevel%d", index+1);
 const Overridable *info = ((Rva0028951F *)TheExperienceLevelSystem)->rva0028951F(TheNameKeyGenerator->nameToKey(level));
 _STL::map<unsigned int, bool> completed;
 do {
  ++index;
  level.format("CreateAHeroLevel%d", index);
  info = ((Rva0028951F *)TheExperienceLevelSystem)->rva0028951F(TheNameKeyGenerator->nameToKey(level));
  if (info) completed[index] = false;
 } while(info);
 index = 0;
 while (!((const StringBase<char> *)&m_buttons[index].text)->isEmpty()) {
  AsciiString name;
  level.format("CreateAHeroLevel%d", index+1);
  name.format("%s_%s", level.str(), m_className.str());
  if (AddCommandButtonLevel(index, level, name, source)) completed[index+1] = true;
  ++index;
  level.format("CreateAHeroLevel%d", index);
 }
 for (_STL::map<unsigned int,bool>::iterator it=completed.begin();it!=completed.end();++it) {
  if (!it->second) {
   level.format("CreateAHeroLevel%d", it->first);
   AsciiString name;
   name.format("%s_%s", level.str(), m_className.str());
   ((ExperienceLevelStore *)TheExperienceLevelSystem)->CreateNewExpLevel(level,name,source,AsciiString(),AsciiString());
  }
 }
 return true;
}

// CreateAHeroHero::Update, retail 0x004083FF..0x00408839 1082B (WorldBuilder
// 0x01081810 by callgraph; CreateAHeroHero.cpp lines 1446..1531): applies the
// manager's on/off upgrades, the changed bling upgrades (state bit 2), the
// class and subclass upgrades (bits 0-1), the colour rebuild (bit 3) and the
// award refresh (bit 9), then rolls a bling animation and records the
// drawable's animation state. An unsigned frame count converts with the
// 2^32 fix-up; the float product promoted to double keeps retail's fmul
// before the fimul by the frame scale.
Bool CreateAHeroHero::Update(Int flags)
{
	CreateAHeroManager *manager = (CreateAHeroManager *)g_Va00DFE348;
	Object *object = 0;
	if (manager) object = ((Rva004076EE *)this)->rva004076EE();
	if (!object) return false;
	AsciiString on = manager->m_upgradeOn;
	AsciiString off = manager->m_upgradeOff;
	const UpgradeTemplate *onUpgrade = TheUpgradeCenter->findUpgrade(on);
	const UpgradeTemplate *offUpgrade = TheUpgradeCenter->findUpgrade(off);
	Drawable *drawable = object->getDrawable();
	Bool useShort = false, useFull = false;
	if (onUpgrade && offUpgrade) {
		if (manager->m_active) { object->rva00293077(onUpgrade); object->rva00290D42(offUpgrade); }
		else { object->rva00293077(offUpgrade); object->rva00290D42(onUpgrade); }
	}
	Int changes = 0;
	m_state38 |= flags;
	if (m_state38 & 4) {
		for (_STL::map<Int, Int>::iterator it = m_bling.begin(); it != m_bling.end(); it++) {
			UnsignedInt id = (TheUpgradeCenter ? BlingOperand(it->second) : BlingOperand(it->second));
			Int key = it->first;
			AsciiString upgrade = manager->GetBlingUpgradeName(key, this, id);
			object->rva00293077(TheUpgradeCenter->findUpgrade(upgrade));
			if (m_priorBling[key] != id) {
				m_priorBling[key] = id;
				++changes;
				if (changes == 1) { if (manager->m_fullBlingKey == key) useFull = true; else useShort = true; }
				else if (changes > 1) { useShort = false; useFull = false; }
			}
		}
		m_state38 &= ~4;
		m_state38 |= 8;
	}
	if (m_state38 & 3) {
		AsciiString classUpgradeName = manager->GetClassUpgradeName(m_heroClass);
		const UpgradeTemplate *classUpgrade = TheUpgradeCenter->findUpgrade(classUpgradeName);
		if (classUpgrade) {
			object->rva00293077(classUpgrade);
			AsciiString subclassUpgradeName = manager->GetSubClassUpgradeName(m_heroClass, m_heroSubclass);
			const UpgradeTemplate *subclassUpgrade = TheUpgradeCenter->findUpgrade(subclassUpgradeName);
			if (subclassUpgrade) object->rva00293077(subclassUpgrade);
		}
		if (drawable) drawable->rva00274176(false);
		m_state38 &= ~3;
		m_state38 |= 0x80;
		if (manager->m_active) {
			useFull = useShort = false;
			Object *object = ((Rva004076EE *)this)->rva004076EE();
			if (object) object->setSpecialModelConditionState((ModelConditionFlagType)0x20f, 1);
		}
	}
	if ((m_state38 & 8) && drawable) {
		Rva00406D67 color;
		color.rva00406D67(m_red, m_green, m_blue);
		_STL::vector<AsciiString> names;
		m_state38 &= ~8;
		drawable->rva0027248A((int)&color, (int)&names);
		if (changes == 0) useShort = true;
	}
	if (m_state38 & 0x200) {
		m_state38 &= ~0x200;
		((Rva0021937DTarget *)this)->rva00407E94();
	}
	AsciiString current = rva004073DC((const Rva002B224BDwordField *)drawable);
	if (manager->m_active) {
		if (((Rva0021BFD8 *)manager)->rva0021BFD8(*(const StringBase<char> *)&current)) return true;
		if (m_state38 & 0x100) m_state38 &= ~0x100;
		else if (rva00406DE3RollChance() && (useShort || useFull)) {
			AsciiString animation("#(MODEL)");
			Int frames = 0;
			Int condition;
			if (useShort) { condition = 0x224; animation.concat(manager->m_fullAnimation); }
			else { animation.concat(manager->m_shortAnimation); condition = 0x226; }
			if (GetAnimationFameCount((const Rva002B224BDwordField *)drawable, &animation, &frames)) {
				frames -= TheCreateAHeroManager->m_animationFrameOffset;
				frames = (Int)((double)(float)((float)(UnsignedInt)frames * (1.0f / 30.0f)) * g_Va00DBA4E4);
				frames = _STL::max(0, frames);
				((Rva004076EE *)this)->rva00407AE6((ModelConditionFlagType)condition, frames);
			}
		}
	}
	if (drawable) { m_animationState = drawable->rva00272709(); m_animationState2 = drawable->rva0027272B(); }
	return true;
}
