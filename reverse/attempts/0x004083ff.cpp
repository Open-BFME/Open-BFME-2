// ?Update@CreateAHeroHero@@QAE_NH@Z
// partial score=1.0 date=2026-10-10
template<class T> static __forceinline T p4Operand(const T &v) { return *(const volatile T*)&v; }
// ?Update@CreateAHeroHero@@QAE_NH@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// CreateAHeroHero::Update, native0x004083FF..0x00408839, full1082B.
// Identity: WorldBuilder callgraph lead in reverse/wb_name_leads.csv names
// CreateAHeroHero::Update; existing hero members and native receiver/state
// accesses corroborate the owner. The two anonymous animation helpers are
// members by caller MOV ECX,ESI at4086D2/40877A; their bodies ignore ECX.
// Target facts: state38, animation fields138/13C; runtime
// globalDFE348 differs from TheCreateAHeroManager atDFE344. Its field labels
// below describe this body's use, without asserting original declarations.
// The complete prior bank is the reconstruction lead, not byte proof.
// Explicit unsigned conversion preserves FILD/FADD2^32; a double cast of
// the rounded float product keeps native FMUL32 before FIMUL32. Every body,
// literal and unwind row must pass the normal matcher independently.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

class CreateAHeroHero;
class Rva002B224BDwordField;
#include "ascii_string.h"
Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, Int line);	// 0x00234111
// Retail's __FILE__ for this unit; the call sites pass their original line.
#define CREATEAHEROHERO_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\CreateAHeroHero.cpp"

class CreateAHeroManager
{
public:
	const AsciiString &GetBlingUpgradeName(Int, const CreateAHeroHero *, UnsignedInt);
 const AsciiString &GetClassUpgradeName(UnsignedInt);
 const AsciiString &GetSubClassUpgradeName(UnsignedInt, UnsignedInt);
 unsigned char m_pad00[0x184];
 Bool active;
 unsigned char pad185[3];
 AsciiString upgradeOn, upgradeOff;
 unsigned char pad190[0x1BC-0x190];
 Int fullBling;
	Real m_rollChance; // +1C0
 unsigned char rest[4];
 AsciiString shortAnimation, fullAnimation;
};

extern CreateAHeroManager *TheCreateAHeroManager;

struct CreateAHeroBlingNode
{
	unsigned char m_pad00[0x14];
	Int *m_idsStart;			// +0x14
	Int *m_idsFinish;			// +0x18
};

class CreateAHeroHero;

// The inherited owner view retains the witnessed STLport bit-vector ABI.
// operator[] returns the eight-byte bit reference by value (native6BE1F).
#include <vector>
#include <map>

namespace _STL {
template<class T, class L, class R>
static inline bool operator!=(const _Rb_tree_iterator<T,L> &a,const _Rb_tree_iterator<T,R> &b) { return a._M_node != b._M_node; }
}

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
#include "ascii_string.h"
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
class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &);
};
extern ControlBar *TheControlBar;
enum ModelConditionFlagType { MODEL_CONDITION_UNKNOWN=-1 };
class Drawable;
class Object
{
public:
	const AsciiString &rva00292330(const AsciiString &);
 Drawable *getDrawable() const;
 void rva00293077(const void *);
 void rva00290D42(const UpgradeTemplate *);
 void setSpecialModelConditionState(ModelConditionFlagType, UnsignedInt);
 unsigned char pad000[0x264];
 class Rva004074B6 *m_experience;
};
class Rva004076EE { public: Object *rva004076EE(); void rva00407AE6(ModelConditionFlagType,UnsignedInt); };
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
	Bool HasEarnedAward(const CreateAHeroAward *award) const;
	Int GetBlingCount(Int blingKey) const;
	Int GetBlingId(Int blingKey, UnsignedInt index) const;
	Bool SetButtonForLevel(const AsciiString &button, UnsignedInt experienceLevel, UnsignedInt value);
	void UpdateAwardEarnedFlags();
 Bool Update(Int);
 AsciiString rva004073DC(const Rva002B224BDwordField*);
 Bool rva00406F51(const Rva002B224BDwordField*,void*,void*);
	Bool AddCommandButtonLevel(UnsignedInt index, const AsciiString &source,
		const AsciiString &name, const AsciiString &experience);

private:
	Bool rva004079D5(Int blingKey, CreateAHeroBlingNode **found) const;	// 0x004079D5

	unsigned char m_pad00[0x0C];
 UnsignedInt heroClass, heroSubclass;
 _STL::map<int,int> bling, priorBling;
 UnsignedInt red, green, blue;
	UnsignedInt m_state38;
	unsigned char m_pad3C[0x4C - 0x3C];
 AsciiString m_heroName;
 unsigned char m_pad50[0x5C - 0x50];
	_STL::vector<bool> m_awardEarnedFlags; // +0x5C
	Bool m_flag70, m_updateAwards; // +0x70, +0x71
	unsigned char m_pad72[2];
	CreateAHeroBlingNode *m_blingHeader;	// +0x74, map end node
	unsigned char m_pad78[0x80 - 0x78];
	BfmeHeroElement005C39DE m_buttons[CAH_MAX_EXP_LEVELS]; // +0x80
 unsigned char pad134[4];
 Int animationState, animationState2;
};

Bool rva00406DE3RollChance();
class UpgradeCenter { public: const UpgradeTemplate *findUpgrade(const AsciiString &) const; };
extern UpgradeCenter *TheUpgradeCenter;
extern int g_Va00DFE348;
extern int g_Va00DBA4E4;
class Rva0021BFD8 { public: Bool rva0021BFD8(const StringBase<char> &); };
class Rva00406D67 { public: Rva00406D67 *rva00406D67(unsigned,unsigned,unsigned); unsigned data[4]; };
namespace _STL {
template <> vector<AsciiString,allocator<AsciiString> >::~vector();
}
class Drawable { public: void rva00274176(bool); void rva0027248A(int,int); int rva00272709(); int rva0027272B(); };
class Rva002B224BDwordField;



// ?Update@CreateAHeroHero@@QAE_NH@Z native0x004083FF..0x00408839 full1082B
Bool CreateAHeroHero::Update(Int flags)
{
 CreateAHeroManager *manager = (CreateAHeroManager *)g_Va00DFE348;
 Object *object = 0;
 if (manager) object = ((Rva004076EE *)this)->rva004076EE();
 if (!object) return false;
 AsciiString on = manager->upgradeOn;
 AsciiString off = manager->upgradeOff;
 const UpgradeTemplate *onUpgrade = TheUpgradeCenter->findUpgrade(on);
 const UpgradeTemplate *offUpgrade = TheUpgradeCenter->findUpgrade(off);
 Drawable *drawable = object->getDrawable();
 Bool useShort = false, useFull = false;
 if (onUpgrade && offUpgrade) {
  if (manager->active) { object->rva00293077(onUpgrade); object->rva00290D42(offUpgrade); }
  else { object->rva00293077(offUpgrade); object->rva00290D42(onUpgrade); }
 }
 Int changes = 0;
 m_state38 |= flags;
 if (m_state38 & 4) {
  for (_STL::map<int,int>::iterator it=bling.begin();it!=bling.end();it++) {
   UnsignedInt id = (TheUpgradeCenter?p4Operand(it->second):p4Operand(it->second));
   Int key = it->first;
   AsciiString upgrade = manager->GetBlingUpgradeName(key,this,id);
   object->rva00293077(TheUpgradeCenter->findUpgrade(upgrade));
   if (priorBling[key] != id) {
    priorBling[key] = id;
    ++changes;
    if (changes == 1) { if(manager->fullBling==key) useFull=true; else useShort=true; }
    else if(changes>1) {useShort=false;useFull=false;}
   }
  }
  m_state38 &= ~4;
  m_state38 |= 8;
 }
 if (m_state38 & 3) {
  AsciiString classUpgradeName = manager->GetClassUpgradeName(heroClass);
  const UpgradeTemplate *classUpgrade = TheUpgradeCenter->findUpgrade(classUpgradeName);
  if(classUpgrade) {
   object->rva00293077(classUpgrade);
   AsciiString subclassUpgradeName = manager->GetSubClassUpgradeName(heroClass,heroSubclass);
   const UpgradeTemplate *subclassUpgrade = TheUpgradeCenter->findUpgrade(subclassUpgradeName);
   if(subclassUpgrade) object->rva00293077(subclassUpgrade);
  }
  if(drawable) drawable->rva00274176(false);
  m_state38 &= ~3;
  m_state38 |= 0x80;
  if(manager->active) {
   useFull=useShort=false;
   Object *object=((Rva004076EE *)this)->rva004076EE();
   if(object) object->setSpecialModelConditionState((ModelConditionFlagType)0x20f,1);
  }
 }
 if ((m_state38 & 8) && drawable) {
  Rva00406D67 color;
  color.rva00406D67(red,green,blue);
  _STL::vector<AsciiString> names;
  m_state38 &= ~8;
  drawable->rva0027248A((int)&color,(int)&names);
  if(changes==0) useShort=true;
 }
 if(m_state38 & 0x200) {
  m_state38 &= ~0x200;
  ((Rva0021937DTarget *)this)->rva00407E94();
 }
 AsciiString current = rva004073DC((const Rva002B224BDwordField *)drawable);
 if(manager->active) {
  if(((Rva0021BFD8 *)manager)->rva0021BFD8(*(const StringBase<char> *)&current)) return true;
  if(m_state38 & 0x100) m_state38 &= ~0x100;
  else if(rva00406DE3RollChance() && (useShort || useFull)) {
   AsciiString animation("#(MODEL)");
   Int frames=0;
   Int condition;
   if(useShort) { condition=0x224; animation.concat(manager->fullAnimation); }
   else { animation.concat(manager->shortAnimation); condition=0x226; }
   if(rva00406F51((const Rva002B224BDwordField *)drawable,&animation,&frames)) {
    frames -= *(UnsignedInt *)((char *)TheCreateAHeroManager+0x1E4);
    frames=(Int)((double)(float)((float)(UnsignedInt)frames * (1.0f/30.0f)) * g_Va00DBA4E4);
    frames = _STL::max(0,frames);
    ((Rva004076EE *)this)->rva00407AE6((ModelConditionFlagType)condition,frames);
   }
  }
 }
 if(drawable) { animationState=drawable->rva00272709(); animationState2=drawable->rva0027272B(); }
 return true;
}