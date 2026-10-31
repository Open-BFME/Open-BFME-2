// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// INI reload slots of the Locomotor store (vftable 0x00BDE970, class
// Rva001E72B4):
//
//   slot 4, 0x001E51AC  clear the "needs restart" byte; when the shared
//                       slot 2 (0x001B5384) reports a reload, put "RIF:
//                       Locomotor reloaded" on screen through TheInGameUI
//                       (slot 16, cdecl; skipped without TheInGameUI) and
//                       latch the "reloaded" byte; pass a pending restart out
//                       through the argument, clearing it; answer the latch.
//   slot 5, 0x001E3934  once after a reload latched its byte: run
//                       0x002CF1C9 on TheThingFactory, clear the latch and
//                       answer true.
//
// Both bytes (VA 0x00DFDC60 "reloaded", 0x00DFDC61 "needs restart") are
// file-static: slot 4 loads the vptr before it stores the restart byte,
// which MSVC 7.1 schedules that way only for a static it can prove `this`
// does not alias. Their only other user (around 0x001E8B6A) sits in the same
// address range. Names are address-derived; the byte meanings are inferred
// from their uses.

#include "unicode_string.h"

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void message(UnicodeString format, ...);
};
extern InGameUI *TheInGameUI;	// VA 0x00DFEDF0

class Rva002CF1C9
{
public:
	void rva002CF1C9();
};

// View: only the 0x002CF1C9 member is called here.
class ThingFactory : public Rva002CF1C9
{
};
extern ThingFactory *TheThingFactory;	// VA 0x00DFF000

// g_Va00DFDC60: VA 0x00DFDC60 (.bss); retail initial byte 00.
static bool g_Va00DFDC60;
// g_Va00DFDC61: VA 0x00DFDC61 (.bss); retail initial byte 00.
static bool g_Va00DFDC61;

static __forceinline void clearLocomotorRestart()
{
	g_Va00DFDC61 = false;
}

class Rva001E72B4Base
{
public:
	virtual void v00();
	virtual void v01();
	virtual bool rva001B5384Slot2();
};

class Rva001E72B4 : public Rva001E72B4Base
{
public:
	bool rva001E51AC(bool *needsRestart);
	bool rva001E3934();
};

bool Rva001E72B4::rva001E51AC(bool *needsRestart)
{
	clearLocomotorRestart();
	if (rva001B5384Slot2())
	{
		if (TheInGameUI)
			TheInGameUI->message(UnicodeString(L"RIF: Locomotor reloaded"));
		g_Va00DFDC60 = true;
	}
	if (g_Va00DFDC61)
	{
		*needsRestart = true;
		clearLocomotorRestart();
	}
	return g_Va00DFDC60;
}

bool Rva001E72B4::rva001E3934()
{
	if (g_Va00DFDC60)
	{
		TheThingFactory->rva002CF1C9();
		g_Va00DFDC60 = false;
		return true;
	}
	return false;
}

// Native1E8A94..1E8C1B; WB ADD4F0 names LocomotorStore parser.
// BFME1/ZH supplies parser semantics; target adds INI type5 retirement.
// Native template154 map+C vector+18 and restart byte are target facts.
// The vector adapter reuses the verified49B pointer-word ABI at4DFCB0;
// it preserves LocomotorTemplate pointer bits, without asserting ModuleData identity.
// The field-table label describes its measured parser role; data contents unclaimed.
#include "ascii_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <map>
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator++(); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> pair<_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::iterator, bool> _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::insert_unique(const pair<const int, int> &); }
// Call retail's hinted insert_unique (0x00422EC0) instead of emitting this unit's own copy.
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, pair<int const, int> const &); }

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
class ModuleData;
class INI;
typedef void (*INIFieldParseProc)(INI *ini,void *instance,void *store,const void *userData);
struct FieldParse { const char *token; INIFieldParseProc parse; const void *userData; int offset; };
class INI {
public:
 const char *getNextToken(const char *);
 void initFromINI(void *,const FieldParse *);
 static void parseBool(INI *,void *,void *,const void *);
 static void parseBitString32(INI *,void *,void *,const void *);
 static void parseIndexList(INI *,void *,void *,const void *);
 static void parseInt(INI *,void *,void *,const void *);
 static void parseReal(INI *,void *,void *,const void *);
 static void parseAngleReal(INI *,void *,void *,const void *);
 static void parsePercentToReal(INI *,void *,void *,const void *);
 static void parseAngularVelocityReal(INI *,void *,void *,const void *);
 static void parseDurationReal(INI *,void *,void *,const void *);
 static void parseDurationUnsignedInt(INI *,void *,void *,const void *);
 static void parseVelocityReal(INI *,void *,void *,const void *);
 char prefix[8]; int type;
};
void parseCanMoveBackwards(INI *,void *,void *,const void *);
class INIException { public: INIException(int,const char*,...); INIException(const INIException &); ~INIException(); char *message; int code; };
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../Include/Common/Overridable.h"
class LocomotorTemplate { public: LocomotorTemplate() throw(); void validate(); char storage[0x154]; };
class Rva001E6731 { public: unsigned rva001E71FA(const int &); };
struct LocomotorParserView { void *vtable; Overridable *next; bool overrideFlag; char pad9[3]; int retired; AsciiString name; __forceinline void setName(const AsciiString &value) { name.setCopyInline(value); } };
class LocomotorStore {
public:
 LocomotorTemplate *findLocomotorTemplate(int);
 LocomotorTemplate *newOverride(LocomotorTemplate *);
 static void parseLocomotorTemplateDefinition(INI *);
 char pad[0xC]; _STL::map<int,int> templates; _STL::vector<LocomotorTemplate *> retired;
};
extern LocomotorStore *TheLocomotorStore;

// User data of the 0x007DE2F8 table: retail's .data name arrays at
// 0x009B8F58, 0x009B8E6C, 0x009B8E3C and 0x009B8F1C.
static const char *TheLocomotorSurfaceTypeNames[] = { "GROUND", "WATER", "CLIFF", "AIR", "RUBBLE", "OBSTACLE", "IMPASSABLE", "DEEP_WATER", "WALL_RAILING", 0 };
static const char *TheLocomotorBehaviorZNames[] = { "NO_Z_MOTIVE_FORCE", "SEA_LEVEL", "SURFACE_RELATIVE_HEIGHT", "ABSOLUTE_HEIGHT", "FIXED_SURFACE_RELATIVE_HEIGHT", "FIXED_ABSOLUTE_HEIGHT", "FIXED_RELATIVE_TO_GROUND_AND_BUILDINGS", "RELATIVE_TO_HIGHEST_LAYER", "FLOATING_Z", "SCALING_WALLS", 0 };
static const char *TheLocomotorAppearanceNames[] = { "TWO_LEGS", "FOUR_WHEELS", "HOVER", "WINGS", "FOUR_LEGS_HUGE", "GIANT_BIRD", "HORDE", "HUGE_TWO_LEGS", "TREADS", "SHIP", "OTHER", 0 };
static const char *TheLocomotorFormationPriorityNames[] = { "NO_FORMATION", "CAVALRY1", "CAVALRY2", "CAVALRY3", "MELEE1", "MELEE2", "MELEE3", "RANGED1", "RANGED2", "RANGED3", "ARTILLERY1", "ARTILLERY2", "ARTILLERY3", "UNUSED", 0 };
// LocomotorTemplate field table, retail .rdata 0x007DE2F8 (88 fields and the
// zero sentinel); tokens, callbacks, user data and offsets are read from it.
extern const FieldParse LocomotorTemplateFields[] =
{
	{ "Surfaces", &INI::parseBitString32, TheLocomotorSurfaceTypeNames, 0x14 },
	{ "Speed", &INI::parseVelocityReal, 0, 0x20 },
	{ "LookAheadMult", &INI::parseReal, 0, 0x18 },
	{ "NonDirtyTransform", &INI::parseBool, 0, 0x1c },
	{ "SpeedDamaged", &INI::parsePercentToReal, 0, 0x24 },
	{ "TurnTime", &INI::parseDurationUnsignedInt, 0, 0x2c },
	{ "TurnTimeDamaged", &INI::parseDurationUnsignedInt, 0, 0x30 },
	{ "SlowTurnRadius", &INI::parseReal, 0, 0x34 },
	{ "FastTurnRadius", &INI::parseReal, 0, 0x38 },
	{ "TurnThreshold", &INI::parseAngleReal, 0, 0x3c },
	{ "TurnThresholdHS", &INI::parseAngleReal, 0, 0x40 },
	{ "Acceleration", &INI::parseDurationUnsignedInt, 0, 0x44 },
	{ "Lift", &INI::parsePercentToReal, 0, 0x48 },
	{ "LiftDamaged", &INI::parsePercentToReal, 0, 0x4c },
	{ "Braking", &INI::parseDurationUnsignedInt, 0, 0x50 },
	{ "MinSpeed", &INI::parsePercentToReal, 0, 0x28 },
	{ "MinTurnSpeed", &INI::parsePercentToReal, 0, 0x54 },
	{ "PreferredHeight", &INI::parseReal, 0, 0x58 },
	{ "PreferredHeightDamping", &INI::parseReal, 0, 0x60 },
	{ "PreferredAttackHeight", &INI::parseReal, 0, 0x5c },
	{ "CirclingRadius", &INI::parseReal, 0, 0x64 },
	{ "SpeedLimitZ", &INI::parseVelocityReal, 0, 0x68 },
	{ "MaxThrustAngle", &INI::parseAngleReal, 0, 0x6c },
	{ "ZAxisBehavior", &INI::parseIndexList, TheLocomotorBehaviorZNames, 0x70 },
	{ "Appearance", &INI::parseIndexList, TheLocomotorAppearanceNames, 0x74 },
	{ "FormationPriority", &INI::parseIndexList, TheLocomotorFormationPriorityNames, 0x78 },
	{ "AccDecTrigger", &INI::parseReal, 0, 0x7c },
	{ "WalkDistance", &INI::parseReal, 0, 0x80 },
	{ "MaxOverlappedHeight", &INI::parseReal, 0, 0xa4 },
	{ "MaxTurnWithoutReform", &INI::parseAngleReal, 0, 0x84 },
	{ "AccelerationPitchLimit", &INI::parseAngleReal, 0, 0x88 },
	{ "BounceAmount", &INI::parseAngularVelocityReal, 0, 0x8c },
	{ "PitchStiffness", &INI::parseReal, 0, 0x90 },
	{ "RollStiffness", &INI::parseReal, 0, 0x94 },
	{ "PitchDamping", &INI::parseReal, 0, 0x98 },
	{ "RollDamping", &INI::parseReal, 0, 0x9c },
	{ "PitchInDirectionOfZVelFactor", &INI::parseReal, 0, 0xa0 },
	{ "ForwardVelocityPitchFactor", &INI::parseReal, 0, 0xa8 },
	{ "LateralVelocityRollFactor", &INI::parseReal, 0, 0xac },
	{ "ForwardAccelerationPitchFactor", &INI::parseReal, 0, 0xb0 },
	{ "LateralAccelerationRollFactor", &INI::parseReal, 0, 0xb4 },
	{ "UniformAxialDamping", &INI::parseReal, 0, 0xb8 },
	{ "TurnPivotOffset", &INI::parseReal, 0, 0xbc },
	{ "Apply2DFrictionWhenAirborne", &INI::parseBool, 0, 0xd2 },
	{ "DownhillOnly", &INI::parseBool, 0, 0xd3 },
	{ "AllowAirborneMotiveForce", &INI::parseBool, 0, 0xd1 },
	{ "LocomotorWorksWhenDead", &INI::parseBool, 0, 0xd0 },
	{ "AirborneTargetingHeight", &INI::parseInt, 0, 0xc0 },
	{ "StickToGround", &INI::parseBool, 0, 0xd4 },
	{ "CanMoveBackwards", &parseCanMoveBackwards, 0, 0xd8 },
	{ "HasSuspension", &INI::parseBool, 0, 0xdc },
	{ "FrontWheelTurnAngle", &INI::parseAngleReal, 0, 0xe8 },
	{ "MaximumWheelExtension", &INI::parseReal, 0, 0xe0 },
	{ "MaximumWheelCompression", &INI::parseReal, 0, 0xe4 },
	{ "CloseEnoughDist", &INI::parseReal, 0, 0xc4 },
	{ "CloseEnoughDist3D", &INI::parseBool, 0, 0xc8 },
	{ "SlideIntoPlaceTime", &INI::parseDurationReal, 0, 0xcc },
	{ "CrewPowered", &INI::parseBool, 0, 0xec },
	{ "UseTerrainSmoothing", &INI::parseBool, 0, 0xed },
	{ "WanderWidthFactor", &INI::parseReal, 0, 0xf0 },
	{ "WanderLengthFactor", &INI::parseReal, 0, 0xf4 },
	{ "WanderAboutPointRadius", &INI::parseReal, 0, 0xf8 },
	{ "BurningDeathRadius", &INI::parseReal, 0, 0xfc },
	{ "BurningDeathIsCavalry", &INI::parseBool, 0, 0x100 },
	{ "ChargeSpeed", &INI::parsePercentToReal, 0, 0x104 },
	{ "ChargeAvailable", &INI::parseBool, 0, 0x108 },
	{ "ChargeIgnoresCondition", &INI::parseBool, 0, 0x109 },
	{ "EnableHighSpeedTurnModelconditions", &INI::parseBool, 0, 0x10a },
	{ "WaitForFormation", &INI::parseBool, 0, 0x10b },
	{ "RudderCorrectionDegree", &INI::parseReal, 0, 0x10c },
	{ "RudderCorrectionRate", &INI::parseReal, 0, 0x110 },
	{ "ElevatorCorrectionDegree", &INI::parseReal, 0, 0x114 },
	{ "ElevatorCorrectionRate", &INI::parseReal, 0, 0x118 },
	{ "AeleronCorrectionDegree", &INI::parseReal, 0, 0x11c },
	{ "AeleronCorrectionRate", &INI::parseReal, 0, 0x120 },
	{ "SwoopStandoffRadius", &INI::parseReal, 0, 0x124 },
	{ "SwoopStandoffHeight", &INI::parseReal, 0, 0x128 },
	{ "SwoopTerminalVelocity", &INI::parseReal, 0, 0x12c },
	{ "SwoopAccelerationRate", &INI::parseReal, 0, 0x130 },
	{ "SwoopSpeedTuningFactor", &INI::parseReal, 0, 0x134 },
	{ "BackingUpSpeed", &INI::parsePercentToReal, 0, 0x138 },
	{ "BackingUpStopWhenTurning", &INI::parseBool, 0, 0x13c },
	{ "BackingUpDistanceMin", &INI::parseReal, 0, 0x140 },
	{ "BackingUpDistanceMax", &INI::parseReal, 0, 0x144 },
	{ "BackingUpAngle", &INI::parseReal, 0, 0x148 },
	{ "RiverModifier", &INI::parsePercentToReal, 0, 0x14c },
	{ "ScalesWalls", &INI::parseBool, 0, 0x150 },
	{ "TurnWhileMoving", &INI::parseBool, 0, 0x151 },
	{ 0, 0, 0, 0 }
};
void LocomotorStore::parseLocomotorTemplateDefinition(INI *ini) {
 if(!TheLocomotorStore) throw INIException(3,"TheLocomotorStore==NULL");
 const char *token=ini->getNextToken(0);
 LocomotorTemplate *loco;
 {
 int key=TheNameKeyGenerator->nameToKey(token);
 LocomotorStore *store=TheLocomotorStore;
 LocomotorTemplate *original=store->findLocomotorTemplate(key);
 loco=original;
 if(loco) {
  if(ini->type==2) {
   LocomotorParserView *locomotorParserView=(LocomotorParserView *)loco;
   LocomotorTemplate *final=locomotorParserView->next ? (LocomotorTemplate *)locomotorParserView->next->friend_getFinalOverride() : loco;
   loco=store->newOverride(final);
  } else if(ini->type==5) {
   ((LocomotorParserView *)loco)->retired=1;
   Rva001E6731 *map=(Rva001E6731 *)&TheLocomotorStore->templates;
   map->rva001E71FA(key);
   reinterpret_cast<_STL::vector<const ModuleData*> *>(&TheLocomotorStore->retired)->push_back(reinterpret_cast<const ModuleData* const&>(original));
   if(((LocomotorParserView *)loco)->overrideFlag) g_Va00DFDC61=true;
   loco=new LocomotorTemplate;
   ((LocomotorParserView *)loco)->retired=0;
   TheLocomotorStore->templates[key]=(int)loco;
  } else return;
 } else {
  loco=new LocomotorTemplate;
  if(ini->type==2) ((LocomotorParserView *)loco)->overrideFlag=true;
  TheLocomotorStore->templates[key]=(int)loco;
 }
 }
 if(loco) {
  { AsciiString name(token); AsciiString *dest=&((LocomotorParserView *)loco)->name; dest->setCopyInline(name); }
 // Diagnostic lifetime inferred from native EH; original local spelling unknown.
 if(0){AsciiString diagnostic;}
  ini->initFromINI(loco,LocomotorTemplateFields);
  loco->validate();
 }
}


