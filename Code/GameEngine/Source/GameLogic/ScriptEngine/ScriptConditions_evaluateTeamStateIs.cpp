// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ZH donor: GeneralsMD ScriptConditions.cpp evaluateTeamStateIs and
// evaluateTeamStateIsNot. Target evidence: the evaluateCondition jump table
// (0x007EC5C0) sends cases 11 and 12 to 0x003E9471 and 0x003E94E5, which
// initConditionTemplates names TEAM_STATE_IS and TEAM_STATE_IS_NOT; both
// compare the team state string at +0x44 with a copied parameter string via
// the rowed StringBase<char>::compare 0x000069D6.
// The shared AsciiString compare declaration is nonthrowing: retail stores
// no EH state for the copied name around the comparison. Its existing ABI
// spelling resolves directly to the verified StringBase worker.

//
// ?evaluateHasUnits@ScriptConditions@@IAE_NPAVParameter@@@Z @ 0x003E9373 254B
// ZH donor: GeneralsMD ScriptConditions.cpp evaluateHasUnits, verbatim.
// Target evidence: the jump table sends case 10 to 0x003E9373, which
// initConditionTemplates names TEAM_HAS_UNITS; the body compares the
// "<This Team>" literal (0x0081531C) with the rowed compare 0x000069B1,
// resolves teams with the rowed getTeamNamed 0x003584E9 and reads the
// prototype name through Team+0x30 / TeamPrototype+0x14 with the
// TheEmptyString fallback, as ZH's Team::getName does. 0x0039DEC4 (rowed
// rva0039DEC4@Team) is ZH's Team::hasAnyUnits by its body: it skips dead,
// destroyed, structure, projectile and mine members. 0x003A2659 is ZH's
// one-argument TeamFactory::findTeamPrototype: it splits the qualified name
// and forwards to the two-argument findTeamPrototype 0x0039FE6C. The instance
// walk loads the member pointer 0x009C4AF5 (DLINK_ITERATOR<Team>).
//
// ?evaluateNamedAttackedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E9556 169B
// ?evaluateTeamAttackedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E95FF 246B
// ?evaluateNamedAttackedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E96F5 137B
// ZH donors: the same-name GeneralsMD ScriptConditions.cpp bodies. Target
// evidence: jump-table cases 19, 20 and 21 call these addresses, and
// initConditionTemplates names them NAMED_ATTACKED_BY_OBJECTTYPE,
// TEAM_ATTACKED_BY_OBJECTTYPE and NAMED_ATTACKED_BY_PLAYER. BFME2 keeps the
// attacker lookup by m_sourceID (DamageInfo+0x08, rowed findObjectByID
// 0x00049DC5) without ZH's later m_sourceTemplate branch; the type test is
// the pinned ObjectTypes::isInSet 0x00376A62 on the attacker template's name
// (+0x64) through an ObjectTypesTemp (rowed ctor 0x003BA7FF) filled by the
// cdecl objectTypesFromParam 0x00566E6C. The player test walks every player
// of the parameter's mask (rowed rva00357B82 plus getEachPlayerFromMask)
// against the rowed getControllingPlayer 0x0028AFA9. The body module is
// Object+0x254 and getLastDamageInfo its vslot +0x3C, as in the rowed
// evaluateTeamAttackedByPlayer.
//
// ??0ObjectTypesTemp@@QAE@XZ @ 0x003BA7FF 64B (rehomed from
// ObjectTypesTempCtor.cpp): m_types(0) then new ObjectTypes (0x14 bytes,
// rowed ctor 0x003769F9), as Zero Hour's ScriptConditions.cpp helper.
//
// ?evaluateBuiltByPlayer@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@1@Z @ 0x003E977E 430B
// ZH/BFME 1 donor: the same-name ScriptConditions.cpp body. Target evidence:
// jump-table case 23 calls 0x003E977E, which initConditionTemplates names
// BUILT_BY_PLAYER. The body looks the type up with the pinned
// ThingFactory::findTemplate 0x002D06CA before the cached-result test
// (Condition customData +0x44 / customFrame +0x48 against TheScriptEngine
// +0x1A15C), fills two STLport vectors through ObjectTypes::
// prepForPlayerCounting 0x00376C50 (its body walks m_objectTypes, pushes each
// found template and resizes the counts, as ZH's) and, unlike ZH's single
// player, counts every player of the parameter's mask with the rowed
// countObjectsByThingTemplate 0x002AB0C5 and sum 0x003BD46E. Retail records
// EH states around the vectors' inline free() calls, which /EHs (extern "C"
// may throw) reproduces; the unit's other bodies make no C calls in EH
// scope.
//
// ?evaluatePlayerUnitCondition@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@111@Z @ 0x003E9C3B 551B
// ZH/BFME 1 donor: the same-name ScriptConditions.cpp body. Target evidence:
// jump-table case 58 calls 0x003E9C3B, which initConditionTemplates names
// PLAYER_HAS_OBJECT_COMPARISON (ZH's caller of evaluatePlayerUnitCondition).
// Same cache, vectors and prepForPlayerCounting as evaluateBuiltByPlayer; the
// count sums every non-null player of the mask (countObjectsByThingTemplate
// with ignoreDead true, sum 0x003BD46E) before the six-way comparison on
// Parameter::getInt (+0x08).
//
// ?evaluatePlayerLostObjectType@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E9EB0 454B
// ZH/BFME 1 donor: the same-name ScriptConditions.cpp body. Target evidence:
// jump-table case 104 calls 0x003E9EB0, which initConditionTemplates names
// PLAYER_LOST_OBJECT_TYPE. BFME 2 runs ZH's single-player body once per
// player of the mask: each player's summed count is compared with
// ScriptEngine::getObjectCount 0x00206255 and stored back through
// setObjectCount 0x00207DF4 (both index the per-player CRC maps at
// ScriptEngine+0x1A164 by Player::getPlayerIndex, +0x54); a drop returns
// true at once.
//
// ?evaluateNamedDestroyedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003EA076 180B
// BFME 1 donor: ScriptConditionsNamedByType.cpp's evaluateNamedDestroyedByType
// (its name for template NAMED_DESTROYED_BY_OBJECTTYPE). Target evidence:
// jump-table case 130 calls 0x003EA076, which initConditionTemplates names
// NAMED_DESTROYED_BY_OBJECTTYPE. It is evaluateNamedAttackedByType's chain
// with ZH's Object::isEffectivelyDead test (m_privateStatus +0x438 bit 0, as
// the rowed Object::fireCurrentWeapon unit lays it out) after the damage-info
// check.
//
// ?evaluateHasCommandPointsToBuildUnit@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E81E8 250B
// No donor body (BFME 1 leaves its case-126 body address-named). Target
// evidence: jump-table case 126 calls 0x003E81E8, which
// initConditionTemplates names HAS_COMMAND_POINTS_TO_BUILD_UNIT; the name
// follows that template as BFME 1's evaluateHasCommandPointsToBuildTeam
// follows case 125's (structural inference, not a recovered symbol). The
// body sizes the parsed ObjectTypes list inline (vector +0x08/+0x0C), takes
// the mask's single player (rowed getPlayerFromMask 0x002A7B91), queries
// that player's command points at +0x60 (rowed 0x002A7548 with 1), and
// tests each listed template, found with findTemplate on the pinned
// getNthInList 0x002041AC result, against ThingTemplate+0x618 (the cost the
// rowed 0x002A7557 adds to the points in use).
//
// ?evaluatePlayerHasKilledTypeUnits@ScriptConditions@@IAE_NPAVParameter@@00@Z @ 0x003E82E2 205B
// BFME 1 donor: ScriptConditionsPlayerHasKilledTypeUnits.cpp, same name and
// shape. Target evidence: jump-table case 129 calls 0x003E82E2, which
// initConditionTemplates names PLAYER_HAS_KILLED_TYPE_UNITS. The first
// player of the mask supplies the kill records at Player+0x3BC; a named
// ObjectTypes list (rowed ScriptEngine::getObjectTypes 0x00357651) sums the
// rowed 0x0039C0F4 count over getNthInList, otherwise the raw type name is
// counted, and the total is compared with the count parameter's getInt.
//
// ?rva003E63CD@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@11@Z @ 0x003E63CD 217B
// Target evidence: jump-table case 134 calls 0x003E63CD, which
// initConditionTemplates names COMPARISON_TREES_IN_TRIGGER_AREA (comparison,
// int, trigger area). The area comes from the rowed
// getQualifiedTriggerAreaByName 0x0035768D; the cached result is reused
// while TheTerrainLogic's +0x1910 stamp is not past the condition's custom
// frame, otherwise the rowed TerrainLogic query 0x0027F171 counts inside the
// trigger and Zero Hour's six-way comparison sets the cache. BFME 2-only
// condition with no donor body, so the method keeps an address name.
//
// ?rva003E5267@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E5267 132B
// Target evidence: jump-table case 193 calls 0x003E5267, which
// initConditionTemplates names UNIT_USING_STANCE (unit, stance). The named
// unit (rowed getUnitNamed 0x003588E7) is searched with findModule
// 0x0028B6D6 for a static NameKeyGenerator key of the string
// "StancesBehavior" (guard bit 0x00E02E28, key 0x00E02E24), and the module's
// rowed 0x0045ED4B stance is compared with the parameter's int. BFME 2-only
// condition with no donor body, so the method keeps an address name.
//
// ?rva003E51D9@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E51D9 142B
// Target evidence: jump-table case 147 calls 0x003E51D9, which
// initConditionTemplates names OBJECT_OF_TYPE_OR_LIST_INSIDE_REFD_BASE
// (object type, base). The named base (rowed getUnitNamed 0x003588E7)
// yields its CastleBehavior module (findModule on the rowed key 0x003955DA),
// and the rowed CastleBehavior walk 0x003977F6 tests the parsed
// ObjectTypesTemp list; retail turns its byte result into the Boolean with
// test/setne. BFME 2-only condition with no donor body, so the method keeps
// an address name.
//
// ?evaluateNamedSelected@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@@Z @ 0x003E9B6A 209B
// BFME 1 donor: ScriptConditionsEvaluateNamedSelected.cpp, same name and
// logic. Target evidence: jump-table case 37 calls 0x003E9B6A, which
// initConditionTemplates names NAMED_SELECTED (unit). Retail returns false
// in a multiplayer session (TheGameEngine slot +0x58), reuses the cached
// custom data unless it is zero or TheInGameUI's +0x120 selection frame
// moved, and otherwise walks the +0x124 selected-drawable list comparing
// each drawable's object (+0xFC) name at Object+0x88 with the parameter
// string via rowed StringBase compare 0x000069D6. BFME 2 differs from the
// donor in the vtable slots and the Object name offset; the loop re-reads
// end() each pass, unlike the donor's hoisted end iterator.
//
// ?evaluateNamedReachedWaypointsEnd@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E992C 243B
// BFME 1 donor: ScriptConditionsNamedUnit.cpp, same name and shape (BFME 2
// passes the Parameter itself to the rowed getUnitNamed 0x003588E7).
// Target evidence: jump-table case 34 calls 0x003E992C, which
// initConditionTemplates names NAMED_REACHED_WAYPOINTS_END (unit, waypoint
// path). The object's AI (Object+0x258) supplies the completed waypoint at
// +0x13C, whose three path labels come back by value from the rowed
// getters 0x0027F5A6, 0x0027F5C1 and 0x0027F5DC and are compared with a copy
// of the path name; the copy's unwind state uses handler 0x007834D3.
//
// ?evaluateTeamReachedWaypointsEnd@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E9A1F 331B
// Zero Hour source, verbatim apart from the view types and the path-label
// casts. Target evidence:
// jump-table case 35 calls 0x003E9A1F, which initConditionTemplates names
// TEAM_REACHED_WAYPOINTS_END (team, waypoint path). The team comes from the
// rowed getTeamNamed 0x003584E9 and its members from iterate_TeamMemberList
// 0x00263864 and advance 0x00263526; each member is tested as in the named
// condition, with every label compared before the found flag is read.
//
// ?evaluateUnitHasEmptied@ScriptConditions@@IAE_NPAVParameter@@@Z @ 0x003E4860 193B
// Zero Hour source, verbatim apart from the view types. Target evidence:
// jump-table case 76 calls 0x003E4860, which initConditionTemplates names
// UNIT_EMPTIED (unit). The per-object records hang off the list head at
// VA 0x00E02E00; a record is 0x14 bytes allocated with operator new
// 0x0002FDA0 and built by the inlined ctor (rowed out of line as
// 0x003E3C22: vtable 0x00835B34, next +0x04, object id +0x08, frame +0x0C,
// count +0x10), matching Zero Hour's TransportStatus. The object's id is
// Object+0x74, its contain module Object+0x250 (getContainCount(0) at
// +0x114) and the frame TheGameLogic+0x40.
//
// ?evaluateUnitHealth@ScriptConditions@@IAE_NPAVParameter@@00@Z @ 0x003E5587 318B
// Zero Hour's evaluateUnitHealth with a BFME 2 horde branch. Target
// evidence: jump-table case 53 calls 0x003E5587, which initConditionTemplates
// names UNIT_HEALTH (unit, comparison, int). An object without a body
// (Object+0x254) fails; a template with KindOf bit 0x6D (byte +0x115 bit 5)
// takes current and maximum health as unsigned counts from slots +0x188 and
// +0x17C of the interface the rowed Object::rva0028C197 returns (staying at
// 0 and 1.0f without one), any other object from body slots +0x10 and +0x1C.
// The percentage is truncated from current * 100 / maximum when the maximum
// is positive and compared six ways with the int parameter; retail
// multiplies before dividing only with the product kept in its own local.
//
// ?rva003E4519@ScriptConditions@@IAE_NPAVParameter@@@Z @ 0x003E4519 76B
// Target evidence: jump-table case 173 calls 0x003E4519, which
// initConditionTemplates names PLAYER_HAS_REACHED_LEVEL_CAP (player). Each
// player of the parameter's mask (rowed rva00357B82 plus
// getEachPlayerFromMask 0x002A7BC9) passes when its int at +0x1C reaches
// what the rowed 0x003802DF returns for the object at Player+0x08. BFME
// 2-only condition with no donor body, so the method keeps an address name.
//
// ?rva003E6BC5@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@@Z @ 0x003E6BC5 325B
// Target evidence: jump-table case 200 calls 0x003E6BC5, which
// initConditionTemplates names TYPE_SELECTED (object type); it starts where
// evaluateTeamOwnedByPlayer (0x003E6B57, 110 bytes) ends. Same caching and
// selected-drawable walk as NAMED_SELECTED, but each drawable's object
// parses the type parameter into an ObjectTypesTemp (ctor 0x003BA7FF,
// Script_objectTypesFromParam 0x00566E6C) and tests its template's name
// with the rowed isInSet 0x00376A62. BFME 2-only condition with no donor
// body, so the method keeps an address name.
#include <vector>
#include <list>
#include "ascii_string.h"

class Parameter
{
public:
	int getInt() const { return m_int; }
	const AsciiString &getString() const { return m_string; }
	unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
	unsigned char m_afterString[8];
};

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	bool done() const
	{
		return m_cur == 0;
	}
	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

class Object;

// The member iterator BFME2 returns by value from Team::iterate_TeamMemberList
// (24 bytes, out-of-line advance; see TeamRva0039DDC2.cpp).
template <>
class DLINK_ITERATOR<Object>
{
private:
	Object *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

#include "Common/Snapshot.h"

class Team;
class Player;

#include "../../Common/GameLogicObjectLookupView.h"

struct DamageInfoInput
{
	unsigned char m_pad00[0x08];
	ObjectID m_sourceID; // +0x08
};

struct DamageInfo
{
	DamageInfoInput in;
};

class BodyModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual float getHealth() const; // +0x10
	virtual void s05(); virtual void s06();
	virtual float getMaxHealth() const; // +0x1C
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual const DamageInfo *getLastDamageInfo() const; // +0x3C
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	int getCommandPoints() const { return m_commandPoints; }
	// KindOf bit 0x6D (byte +0x115, bit 5), unnamed: the horde kinds whose
	// health lives in the contain interface.
	bool testKindOf6D() const { return (m_kindOf115 & 0x20) != 0; }
private:
	unsigned char m_pad00[0x64];
	AsciiString m_name; // +0x64
	unsigned char m_pad68[0x115 - 0x68];
	unsigned char m_kindOf115; // +0x115
	unsigned char m_pad116[0x618 - 0x116];
	int m_commandPoints; // +0x618
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module;

// The module findModule returns for the "StancesBehavior" key; the rowed
// 0x0045ED4B reads its current stance.
class StancesBehavior
{
public:
	int rva0045ED4B() const;
};

class ObjectTypes;

// The module findModule returns for CastleBehavior's rowed name key
// 0x003955DA; the rowed 0x003977F6 tests its members against a type set.
class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
	bool rva003977F6(ObjectTypes *types);
};

// The rowed path-label getters (Waypoint::getPathLabel1..3), each named for
// its address and called through a cast because an inline forwarder
// returning the string is not expanded under /EHs (as in
// Map/TerrainLogicWaypointLookups.cpp).
class Rva0027F5A6
{
public:
	AsciiString rva0027F5A6();
};
class Rva0027F5C1
{
public:
	AsciiString rva0027F5C1();
};
class Rva0027F5DC
{
public:
	AsciiString rva0027F5DC();
};

class Waypoint;

// ContainModuleInterface::getContainCount(0) is vtable slot +0x114 (as in
// Object/Contain/Rva00478231Contain.cpp).
#define BFME_SLOT(n) virtual void slot##n() = 0
class ContainModuleInterface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23); BFME_SLOT(24);
	BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27); BFME_SLOT(28); BFME_SLOT(29);
	BFME_SLOT(30); BFME_SLOT(31); BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34);
	BFME_SLOT(35); BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43); BFME_SLOT(44);
	BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47); BFME_SLOT(48); BFME_SLOT(49);
	BFME_SLOT(50); BFME_SLOT(51); BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54);
	BFME_SLOT(55); BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58); BFME_SLOT(59);
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63); BFME_SLOT(64);
	BFME_SLOT(65); BFME_SLOT(66); BFME_SLOT(67); BFME_SLOT(68);
	virtual unsigned int getContainCount(int unused) = 0; // +0x114
};

// The interface rowed Object::rva0028C197 returns (the +0x250 module's slot
// +0x7C answer); slots +0x17C and +0x188 return unsigned counts.
class Rva0028C197Iface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23); BFME_SLOT(24);
	BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27); BFME_SLOT(28); BFME_SLOT(29);
	BFME_SLOT(30); BFME_SLOT(31); BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34);
	BFME_SLOT(35); BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43); BFME_SLOT(44);
	BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47); BFME_SLOT(48); BFME_SLOT(49);
	BFME_SLOT(50); BFME_SLOT(51); BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54);
	BFME_SLOT(55); BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58); BFME_SLOT(59);
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63); BFME_SLOT(64);
	BFME_SLOT(65); BFME_SLOT(66); BFME_SLOT(67); BFME_SLOT(68); BFME_SLOT(69);
	BFME_SLOT(70); BFME_SLOT(71); BFME_SLOT(72); BFME_SLOT(73); BFME_SLOT(74);
	BFME_SLOT(75); BFME_SLOT(76); BFME_SLOT(77); BFME_SLOT(78); BFME_SLOT(79);
	BFME_SLOT(80); BFME_SLOT(81); BFME_SLOT(82); BFME_SLOT(83); BFME_SLOT(84);
	BFME_SLOT(85); BFME_SLOT(86); BFME_SLOT(87); BFME_SLOT(88); BFME_SLOT(89);
	BFME_SLOT(90); BFME_SLOT(91); BFME_SLOT(92); BFME_SLOT(93); BFME_SLOT(94);
	virtual unsigned int rvaSlot17C() = 0; // +0x17C
	BFME_SLOT(96); BFME_SLOT(97);
	virtual unsigned int rvaSlot188() = 0; // +0x188
};
#undef BFME_SLOT

// AIUpdateInterface keeps the last completed waypoint at +0x13C.
class AIUpdateInterface
{
public:
	const Waypoint *getCompletedWaypoint() const { return m_completedWaypoint; }
private:
	unsigned char m_pad00[0x13C];
	const Waypoint *m_completedWaypoint; // +0x13C
};

class Object
{
public:
	Module *findModule(NameKeyType key) const;
	void *rva0028C197() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	const AsciiString &getName() const { return m_name; }
	ContainModuleInterface *getContain() const { return m_contain; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Player *getControllingPlayer() const;
	bool isEffectivelyDead() const { return (m_privateStatus & EFFECTIVELY_DEAD) != 0; }
private:
	enum { EFFECTIVELY_DEAD = 0x01 };
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x74 - 0x08];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x88 - 0x78];
	AsciiString m_name; // +0x88
	unsigned char m_pad8C[0x250 - 0x8C];
	ContainModuleInterface *m_contain; // +0x250
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus; // +0x438
};

extern GameLogic *TheGameLogic;

class Drawable
{
public:
	Object *getObject() const { return m_object; }
private:
	unsigned char m_pad00[0xFC];
	Object *m_object; // +0xFC
};

typedef _STL::list<Drawable *> DrawableList;

// Vtable slots from retail: isMultiplayerSession is GameEngine slot 22
// (+0x58, Common/GameEngineSlots.cpp); InGameUI +0x120 is the selection
// frame and +0x124 the selected-drawable list (LeftHUDInput.cpp).
#define BFME_SLOT(n) virtual void slot##n() = 0
class GameEngine
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21);
	virtual bool isMultiplayerSession() = 0; // +0x58
};
extern GameEngine *TheGameEngine;

class InGameUI
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23); BFME_SLOT(24);
	BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27); BFME_SLOT(28); BFME_SLOT(29);
	BFME_SLOT(30); BFME_SLOT(31); BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34);
	BFME_SLOT(35); BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43); BFME_SLOT(44);
	BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47); BFME_SLOT(48); BFME_SLOT(49);
	BFME_SLOT(50); BFME_SLOT(51); BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54);
	BFME_SLOT(55); BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58); BFME_SLOT(59);
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63); BFME_SLOT(64);
	BFME_SLOT(65); BFME_SLOT(66); BFME_SLOT(67); BFME_SLOT(68); BFME_SLOT(69);
	BFME_SLOT(70); BFME_SLOT(71);
	virtual unsigned int getFrameSelectionChanged() = 0; // +0x120
	virtual const DrawableList *getAllSelectedDrawables() = 0; // +0x124
};
extern InGameUI *TheInGameUI;
#undef BFME_SLOT

class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	bool isInSet(const AsciiString &name) const;
	unsigned int getListSize() const { return m_objectTypes.size(); }
	AsciiString getNthInList(unsigned int index) const;
	int prepForPlayerCounting(_STL::vector<const ThingTemplate *> &templates, _STL::vector<int> &counts);
private:
	AsciiString m_listName; // +0x04
	_STL::vector<AsciiString> m_objectTypes; // +0x08
};

class ObjectTypesTemp
{
public:
	ObjectTypesTemp();
	~ObjectTypesTemp() { ::delete m_types; }
	ObjectTypes *m_types;
};

// Zero Hour defines ObjectTypesTemp in ScriptConditions.cpp, and retail's
// out-of-line copy of its ctor (0x003BA7FF) belongs to that unit: the
// callers keep types.m_types in a register across the parse and isInSet
// calls (and into the destructor), which VC7.1 only does when the ctor's
// body is compiled in the same unit and so is known not to keep `this`.
ObjectTypesTemp::ObjectTypesTemp() : m_types(0)
{
	m_types = new ObjectTypes;
}

void Script_objectTypesFromParam(Parameter *pTypeParm, ObjectTypes *outObjectTypes);

// Player+0x60's command-point tracker; its "available" query 0x002A7548
// returns the cap (0x002A7461) less the points in use (+0x08).
class Rva002A7461
{
public:
	int rva002A7548(int);
private:
	unsigned char m_pad00[0x08];
	int m_used; // +0x08
};

// Player+0x3BC; 0x0039C0F4 sums its per-type kill records whose name
// matches (the rowed Rva0039C0F4Sum unit).
class Rva0039C0F4
{
public:
	int rva0039C0F4(const AsciiString &objectType);
};

// The object at Player+0x08 whose rowed 0x003802DF answers the level cap.
class Rva00380200
{
public:
	int rva003802DF();
};

class Player
{
public:
	Rva00380200 *getRva08() { return reinterpret_cast<Rva00380200 *>(m_pad08); }
	int getRva1C() const { return m_1C; }
	int getPlayerIndex() const { return m_playerIndex; }
	Rva002A7461 *getCommandPoints() { return &m_commandPoints; }
	Rva0039C0F4 *getKills() { return &m_kills; }
	void countObjectsByThingTemplate(int numThingTemplates, const ThingTemplate *const *things, bool ignoreDead, int *counts, bool ignoreUnderConstruction) const;
private:
	unsigned char m_pad00[0x08];
	unsigned char m_pad08[0x1C - 0x08];
	int m_1C; // +0x1C
	unsigned char m_pad20[0x54 - 0x20];
	int m_playerIndex; // +0x54
	unsigned char m_pad58[0x60 - 0x58];
	Rva002A7461 m_commandPoints; // +0x60
	unsigned char m_pad6C[0x3BC - 0x6C];
	Rva0039C0F4 m_kills; // +0x3BC
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

int __cdecl Rva003BD46ESum(void *range);

class Condition
{
public:
	int getCustomData() const { return m_customData; }
	unsigned int getCustomFrame() const { return m_customFrame; }
	void setCustomData(int value) { m_customData = value; }
	void setCustomFrame(unsigned int value) { m_customFrame = value; }
private:
	unsigned char m_pad00[0x44];
	int m_customData; // +0x44
	unsigned int m_customFrame; // +0x48
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
	Player *getPlayerFromMask(int mask);
};
extern PlayerList *ThePlayerList;

class TeamPrototype
{
public:
	const AsciiString &getName() const { return m_name; }
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const;
private:
	unsigned char m_pad00[0x14];
	AsciiString m_name; // +0x14
	unsigned char m_pad18[0x334 - 0x18];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	const AsciiString &getState() const { return m_state; }
	const AsciiString &getName() const
	{
		return m_proto == NULL ? AsciiString::TheEmptyString : m_proto->getName();
	}
	// Zero Hour's Team::hasAnyUnits; the ledger keeps the address name.
	bool rva0039DEC4();
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
private:
	unsigned char m_pad08[0x30 - 0x08];
	TeamPrototype *m_proto; // +0x30
	unsigned char m_pad34[0x44 - 0x34];
	AsciiString m_state; // +0x44
};

inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList() const
{
	return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
}

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype(const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

class PolygonTrigger;

// TerrainLogic (TheTerrainLogic 0x00DFEC50): +0x1910 is the frame stamp
// TerrainLogicRva00283CE7.cpp stores from TheGameLogic's frame; the rowed
// 0x0027F171 counts the grid hits inside a PolygonTrigger's radius.
class BfmeThingCME
{
public:
	int rva0027F171(PolygonTrigger *trigger);
};

class TerrainLogic
{
public:
	unsigned int getStamp() const { return m_stamp; }
	int rva0027F171(PolygonTrigger *trigger) { return reinterpret_cast<BfmeThingCME *>(this)->rva0027F171(trigger); }
private:
	unsigned char m_pad00[0x1910];
	unsigned int m_stamp; // +0x1910
};
extern TerrainLogic *TheTerrainLogic;

class ScriptEngine
{
public:
	PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString name);
	Team *getTeamNamed(AsciiString, bool);
	Object *getUnitNamed(Parameter *pUnitParm);
	int rva00357B82(Parameter *pPlayerParm);
	ObjectTypes *getObjectTypes(const AsciiString &objectTypeList);
	unsigned int getFrameObjectCountChanged() const { return m_frameObjectCountChanged; }
	int getObjectCount(int playerIndex, const AsciiString &objectTypeName) const;
	void setObjectCount(int playerIndex, const AsciiString &objectTypeName, int newCount);
private:
	unsigned char m_pad00[0x1A15C];
	unsigned int m_frameObjectCountChanged; // +0x1A15C
};
extern ScriptEngine *TheScriptEngine;

#define THIS_TEAM "<This Team>"

class ScriptConditions
{
protected:
	bool evaluateHasUnits(Parameter *);
	bool evaluateNamedAttackedByType(Parameter *, Parameter *);
	bool evaluateTeamAttackedByType(Parameter *, Parameter *);
	bool evaluateNamedAttackedByPlayer(Parameter *, Parameter *);
	bool evaluateTeamStateIs(Parameter *, Parameter *);
	bool evaluateTeamStateIsNot(Parameter *, Parameter *);
	bool evaluateBuiltByPlayer(Condition *, Parameter *, Parameter *);
	bool evaluatePlayerUnitCondition(Condition *, Parameter *, Parameter *, Parameter *, Parameter *);
	bool evaluatePlayerLostObjectType(Parameter *, Parameter *);
	bool evaluateNamedDestroyedByType(Parameter *, Parameter *);
	bool evaluateHasCommandPointsToBuildUnit(Parameter *, Parameter *);
	bool evaluatePlayerHasKilledTypeUnits(Parameter *, Parameter *, Parameter *);
	bool rva003E63CD(Condition *, Parameter *, Parameter *, Parameter *);
	bool rva003E5267(Parameter *, Parameter *);
	bool rva003E51D9(Parameter *, Parameter *);
	bool evaluateNamedSelected(Condition *, Parameter *);
	bool evaluateNamedReachedWaypointsEnd(Parameter *, Parameter *);
	bool evaluateTeamReachedWaypointsEnd(Parameter *, Parameter *);
	bool evaluateUnitHasEmptied(Parameter *);
	bool evaluateUnitHealth(Parameter *, Parameter *, Parameter *);
	bool rva003E4519(Parameter *);
	bool rva003E6BC5(Condition *, Parameter *);
};
bool ScriptConditions::evaluateHasUnits(Parameter *pTeamParm)
{
	AsciiString desiredTeamName = pTeamParm->getString();
	// If they are calling a <this team> condition, do it.
	if (desiredTeamName.compare(THIS_TEAM) == 0) {
		Team *theTeam = TheScriptEngine->getTeamNamed(desiredTeamName, false);
		if (theTeam) {
			return (theTeam->rva0039DEC4());
		}
		return false;
	}
	Team *thisTeam = TheScriptEngine->getTeamNamed(THIS_TEAM, false);
	if (thisTeam && thisTeam->getName() == desiredTeamName) {
		return thisTeam->rva0039DEC4();
	}

	TeamPrototype *pProto = NULL;
	pProto = TheTeamFactory->findTeamPrototype(desiredTeamName);

	if (pProto) {
		for (DLINK_ITERATOR<Team> iter = pProto->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
			if (iter.cur()->rva0039DEC4()) {
				return true;
			}
		}
	}
	return false;
}
bool ScriptConditions::evaluateTeamStateIs(Parameter *pTeamParm, Parameter *pStateParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	AsciiString stateName = pStateParm->getString();
	if (theTeam) {
		return (theTeam->getState() == stateName);
	}
	return false;
}
bool ScriptConditions::evaluateTeamStateIsNot(Parameter *pTeamParm, Parameter *pStateParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	AsciiString stateName = pStateParm->getString();
	if (theTeam) {
		return (!(theTeam->getState() == stateName));
	}
	return false;
}
bool ScriptConditions::evaluateNamedAttackedByType(Parameter *pUnitParm, Parameter *pTypeParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!theObj) {
		return false;
	}

	BodyModuleInterface *theBodyModule = theObj->getBodyModule();
	if (!theBodyModule) {
		return false;
	}

	const DamageInfo *lastDamageInfo = theBodyModule->getLastDamageInfo();

	if (!lastDamageInfo) {
		return false;
	}

	ObjectID id = lastDamageInfo->in.m_sourceID;
	Object *pAttacker = TheGameLogic->findObjectByID(id);
	if (!pAttacker || !pAttacker->getTemplate()) {
		return false;
	}

	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);
	return types.m_types->isInSet(pAttacker->getTemplate()->getName());
}
bool ScriptConditions::evaluateTeamAttackedByType(Parameter *pTeamParm, Parameter *pTypeParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam) {
		return false;
	}

	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		BodyModuleInterface *theBodyModule = iter.cur()->getBodyModule();
		if (!theBodyModule) {
			continue;
		}

		const DamageInfo *lastDamageInfo = theBodyModule->getLastDamageInfo();

		if (!lastDamageInfo) {
			continue;
		}

		ObjectID id = lastDamageInfo->in.m_sourceID;
		Object *pAttacker = TheGameLogic->findObjectByID(id);
		if (!pAttacker || !pAttacker->getTemplate()) {
			continue;
		}
		if (types.m_types->isInSet(pAttacker->getTemplate()->getName())) {
			return true;
		}
	}

	return false;
}
bool ScriptConditions::evaluateNamedAttackedByPlayer(Parameter *pUnitParm, Parameter *pPlayerParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!theObj) {
		return false;
	}

	BodyModuleInterface *theBodyModule = theObj->getBodyModule();
	if (!theBodyModule) {
		return false;
	}

	const DamageInfo *lastDamageInfo = theBodyModule->getLastDamageInfo();

	if (!lastDamageInfo) {
		return false;
	}

	ObjectID id = lastDamageInfo->in.m_sourceID;
	Object *pAttacker = TheGameLogic->findObjectByID(id);
	if (!pAttacker) {
		return false;
	}
	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	while (mask) {
		Player *victimPlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (pAttacker->getControllingPlayer() == victimPlayer) {
			return true;
		}
	}
	return false;
}
bool ScriptConditions::evaluateBuiltByPlayer(Condition *pCondition, Parameter *pTypeParm, Parameter *pPlayerParm)
{
	const ThingTemplate *pTemplate = TheThingFactory->findTemplate(pTypeParm->getString());
	if (!pTemplate) {
		return false;
	}

	if (pCondition->getCustomData() != 0) {
		// We have a cached value.
		if (TheScriptEngine->getFrameObjectCountChanged() == pCondition->getCustomFrame()) {
			// object count hasn't changed.  Use cached value.
			if (pCondition->getCustomData() == 1) return true;
			if (pCondition->getCustomData() == -1) return false;
		}
	}

	_STL::vector<int> counts;
	_STL::vector<const ThingTemplate *> templates;

	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);

	int numTemplates = types.m_types->prepForPlayerCounting(templates, counts);
	if (numTemplates == 0) {
		return false;
	}

	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	while (mask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
		pPlayer->countObjectsByThingTemplate(numTemplates, &(*templates.begin()), false, &(*counts.begin()), true);
		pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
		int sumOfObjs = Rva003BD46ESum(&counts);
		if (sumOfObjs != 0) {
			pCondition->setCustomData(1); // true.
			return true;
		}
	}
	pCondition->setCustomData(-1); // false.
	return false;
}
bool ScriptConditions::evaluatePlayerUnitCondition(Condition *pCondition, Parameter *pPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm, Parameter *pUnitTypeParm)
{
	if (pCondition->getCustomData() != 0) {
		// We have a cached value.
		if (TheScriptEngine->getFrameObjectCountChanged() == pCondition->getCustomFrame()) {
			// object count hasn't changed.  Use cached value.
			if (pCondition->getCustomData() == 1) return true;
			if (pCondition->getCustomData() == -1) return false;
		}
	}

	_STL::vector<int> counts;
	_STL::vector<const ThingTemplate *> templates;

	ObjectTypesTemp types;
	Script_objectTypesFromParam(pUnitTypeParm, types.m_types);

	int numObjs = types.m_types->prepForPlayerCounting(templates, counts);
	if (numObjs == 0) {
		return false;
	}

	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	int count = 0;
	while (mask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (pPlayer) {
			pPlayer->countObjectsByThingTemplate(numObjs, &(*templates.begin()), true, &(*counts.begin()), true);
			count += Rva003BD46ESum(&counts);
		}
	}

	bool comparison = false;
	switch (pComparisonParm->getInt())
	{
		case 0: comparison = (count < pCountParm->getInt()); break;
		case 1: comparison = (count <= pCountParm->getInt()); break;
		case 2: comparison = (count == pCountParm->getInt()); break;
		case 3: comparison = (count >= pCountParm->getInt()); break;
		case 4: comparison = (count > pCountParm->getInt()); break;
		case 5: comparison = (count != pCountParm->getInt()); break;
	}

	pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
	if (comparison) {
		pCondition->setCustomData(1); // true.
		return true;
	}
	pCondition->setCustomData(-1); // false.
	return false;
}
bool ScriptConditions::evaluatePlayerLostObjectType(Parameter *pPlayerParm, Parameter *pTypeParm)
{
	_STL::vector<int> counts;
	_STL::vector<const ThingTemplate *> templates;

	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);

	int numTemplates = types.m_types->prepForPlayerCounting(templates, counts);
	if (numTemplates == 0) {
		return false;
	}

	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player) {
			player->countObjectsByThingTemplate(numTemplates, &(*templates.begin()), true, &(*counts.begin()), true);

			int sumOfObjs = Rva003BD46ESum(&counts);
			int currentCount = TheScriptEngine->getObjectCount(player->getPlayerIndex(), pTypeParm->getString());

			if (sumOfObjs != currentCount) {
				TheScriptEngine->setObjectCount(player->getPlayerIndex(), pTypeParm->getString(), sumOfObjs);
			}

			if (sumOfObjs < currentCount) {
				return true;
			}
		}
	}
	return false;
}
bool ScriptConditions::evaluateNamedDestroyedByType(Parameter *pUnitParm, Parameter *pTypeParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!theObj) {
		return false;
	}

	BodyModuleInterface *theBodyModule = theObj->getBodyModule();
	if (!theBodyModule) {
		return false;
	}

	const DamageInfo *lastDamageInfo = theBodyModule->getLastDamageInfo();

	if (!lastDamageInfo) {
		return false;
	}

	if (!theObj->isEffectivelyDead()) {
		return false;
	}

	ObjectID id = lastDamageInfo->in.m_sourceID;
	Object *pAttacker = TheGameLogic->findObjectByID(id);
	if (!pAttacker || !pAttacker->getTemplate()) {
		return false;
	}

	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);
	return types.m_types->isInSet(pAttacker->getTemplate()->getName());
}
bool ScriptConditions::evaluateHasCommandPointsToBuildUnit(Parameter *pPlayerParm, Parameter *pTypeParm)
{
	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);

	unsigned int numTypes = types.m_types->getListSize();
	if (numTypes == 0) {
		return false;
	}

	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	if (!mask) {
		return false;
	}

	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (!player) {
		return false;
	}

	int available = player->getCommandPoints()->rva002A7548(1);
	for (unsigned int i = 0; i < numTypes; ++i) {
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(types.m_types->getNthInList(i));
		if (thingTemplate && available <= thingTemplate->getCommandPoints()) {
			return true;
		}
	}
	return false;
}
bool ScriptConditions::evaluatePlayerHasKilledTypeUnits(Parameter *pPlayerParm, Parameter *pCountParm, Parameter *pTypeParm)
{
	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
	if (thePlayer) {
		Rva0039C0F4 *kills = thePlayer->getKills();
		if (kills) {
			ObjectTypes *types = TheScriptEngine->getObjectTypes(pTypeParm->getString());
			int total = 0;
			if (types) {
				for (unsigned int typeIndex = 0; typeIndex < types->getListSize(); ++typeIndex) {
					AsciiString typeName = types->getNthInList(typeIndex);
					total += kills->rva0039C0F4(typeName);
				}
			} else {
				total = kills->rva0039C0F4(pTypeParm->getString());
			}
			return total >= pCountParm->getInt();
		}
	}
	return false;
}

bool ScriptConditions::rva003E63CD(Condition *pCondition, Parameter *pComparisonParm, Parameter *pCountParm, Parameter *pTriggerParm)
{
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());
	if (!pTrig)
		return false;
	if (TheTerrainLogic->getStamp() <= pCondition->getCustomFrame()) {
		if (pCondition->getCustomData() == -1)
			return false;
		if (pCondition->getCustomData() == 1)
			return true;
	}
	int count = TheTerrainLogic->rva0027F171(pTrig);
	bool comparison = false;
	switch (pComparisonParm->getInt()) {
		case 0: comparison = count < pCountParm->getInt(); break;
		case 1: comparison = count <= pCountParm->getInt(); break;
		case 2: comparison = count == pCountParm->getInt(); break;
		case 3: comparison = count >= pCountParm->getInt(); break;
		case 4: comparison = count > pCountParm->getInt(); break;
		case 5: comparison = count != pCountParm->getInt(); break;
	}
	pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
	if (comparison) {
		pCondition->setCustomData(1);
		return true;
	}
	pCondition->setCustomData(-1);
	return false;
}

bool ScriptConditions::rva003E5267(Parameter *pUnitParm, Parameter *pStanceParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!theObj)
		return false;
	static const NameKeyType key_StancesBehavior = TheNameKeyGenerator->nameToKey("StancesBehavior");
	StancesBehavior *stances = (StancesBehavior *)theObj->findModule(key_StancesBehavior);
	if (stances) {
		int stance = pStanceParm->getInt();
		return stances->rva0045ED4B() == stance;
	}
	return false;
}

bool ScriptConditions::rva003E51D9(Parameter *pTypeParm, Parameter *pBaseParm)
{
	Object *theBase = TheScriptEngine->getUnitNamed(pBaseParm);
	if (!theBase)
		return false;
	CastleBehavior *castle = (CastleBehavior *)theBase->findModule(CastleBehavior::rva0003955DA());
	if (!castle)
		return false;
	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);
	bool found = castle->rva003977F6(types.m_types) != 0;
	return found;
}

bool ScriptConditions::evaluateNamedSelected(Condition *pCondition, Parameter *pUnitParm)
{
	if (TheGameEngine->isMultiplayerSession())
		return false;

	bool anyChanges = false;
	if (pCondition->getCustomData() == 0)
		anyChanges = true;

	if (TheInGameUI->getFrameSelectionChanged() != pCondition->getCustomFrame())
		anyChanges = true;

	if (!anyChanges)
	{
		if (pCondition->getCustomData() == -1)
			return false;
		if (pCondition->getCustomData() == 1)
			return true;
	}

	bool isSelected = false;
	const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
	for (DrawableList::const_iterator it = selected->begin(); it != selected->end(); ++it)
	{
		Drawable *draw = *it;
		if (draw->getObject()->getName().compare(pUnitParm->getString()) == 0)
		{
			isSelected = true;
			break;
		}
	}

	pCondition->setCustomData(-1);
	if (isSelected)
		pCondition->setCustomData(1);
	pCondition->setCustomFrame(TheInGameUI->getFrameSelectionChanged());
	return isSelected;
}

bool ScriptConditions::evaluateNamedReachedWaypointsEnd(Parameter *pUnitParm, Parameter *pWaypointPathParm)
{
	Object *theObj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!theObj)
		return false;

	AIUpdateInterface *ai = theObj->getAIUpdateInterface();
	if (!ai)
		return false;

	const Waypoint *targetWay = ai->getCompletedWaypoint();
	if (!targetWay)
		return false;

	AsciiString pathName = pWaypointPathParm->getString();
	if (((Rva0027F5A6 *)targetWay)->rva0027F5A6() == pathName)
		return true;
	if (((Rva0027F5C1 *)targetWay)->rva0027F5C1() == pathName)
		return true;
	if (((Rva0027F5DC *)targetWay)->rva0027F5DC() == pathName)
		return true;

	return false;
}

bool ScriptConditions::evaluateTeamReachedWaypointsEnd(Parameter *pTeamParm, Parameter* pWaypointPathParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( pTeamParm->getString(), false );
	if (!theTeam) {
		return false;
	}

	AsciiString	pathName = pWaypointPathParm->getString();
	bool anyAtEnd = false;
	bool anyNotAtEnd = false;
	// Note - This returns true if any of the team completed the path.  This is as the current
	// implementation tends to do group pathfinding by default, so we trigger when the leader actually thinks
	// that he has reached the end of the waypoint path.
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *pObj = iter.cur();
		if (!pObj) {
			continue;
		}
		AIUpdateInterface *ai = pObj->getAIUpdateInterface();
		if (!ai) continue; // in case there are any rocks or trees in the team :)

		const Waypoint *targetWay = ai->getCompletedWaypoint();

		if (!targetWay) {
			anyNotAtEnd = true;
			continue;
		}
		bool found = false;
		if (((Rva0027F5A6 *)targetWay)->rva0027F5A6() == pathName) found = true;
		if (((Rva0027F5C1 *)targetWay)->rva0027F5C1() == pathName) found = true;
		if (((Rva0027F5DC *)targetWay)->rva0027F5DC() == pathName) found = true;
		if (found) {
			anyAtEnd = true;
		} else {
			anyNotAtEnd = true;
		}
	}
	return anyAtEnd;
}

class TransportStatus
{
public:
	TransportStatus *m_nextStatus;
	ObjectID m_objID;
	unsigned int m_frameNumber;
	int m_unitCount;
public:
	TransportStatus() : m_objID(INVALID_OBJECT_ID), m_frameNumber(0), m_unitCount(0), m_nextStatus(NULL) {}
	virtual ~TransportStatus();
};

static TransportStatus *s_transportStatuses;

bool ScriptConditions::evaluateUnitHasEmptied(Parameter *pUnitParm)
{
	Object *object = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!object) {
		return false;
	}

	// have we checked this one before?
	TransportStatus *stats = s_transportStatuses;
	while (stats) {
		if (stats->m_objID == object->getID()) {
			break;
		}

		stats = stats->m_nextStatus;
	}

	ContainModuleInterface *cmi = object->getContain();
	int numPeeps = cmi ? cmi->getContainCount(0) : 0;

	unsigned int frameNum = TheGameLogic->getFrame();

	if (stats == NULL)
	{
		TransportStatus *transportStatus = new TransportStatus;
		transportStatus->m_objID = object->getID();
		transportStatus->m_frameNumber = frameNum;
		transportStatus->m_unitCount = numPeeps;
		transportStatus->m_nextStatus = s_transportStatuses;
		s_transportStatuses = transportStatus;
		return false;
	}

	if (stats->m_frameNumber == frameNum - 1) {
		if (stats->m_unitCount > 0 && numPeeps == 0) {
			// don't actually update the info on this round, because we want to make sure that
			// multiple calls to this in the same frame actually work.
			return true;
		}
	}

	// perform the update.
	stats->m_frameNumber = frameNum;
	stats->m_unitCount = numPeeps;
	return false;
}

bool ScriptConditions::evaluateUnitHealth(Parameter *pUnitParm, Parameter *pComparisonParm, Parameter *pHealthPercent)
{
	Object *theObj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!theObj)
		return false;
	if (!theObj->getBodyModule())
		return false;
	float curHealth = 0.0f;
	float maxHealth = 1.0f;
	int healthPercent = 0;
	if (theObj->getTemplate()->testKindOf6D()) {
		Rva0028C197Iface *horde = (Rva0028C197Iface *)theObj->rva0028C197();
		if (horde) {
			curHealth = (float)horde->rvaSlot188();
			maxHealth = (float)horde->rvaSlot17C();
		}
	} else {
		curHealth = theObj->getBodyModule()->getHealth();
		maxHealth = theObj->getBodyModule()->getMaxHealth();
	}
	if (maxHealth > 0.0f) {
		float pct = curHealth * 100.0f;
		healthPercent = (int)(pct / maxHealth);
	}
	switch (pComparisonParm->getInt())
	{
		case 0: return healthPercent < pHealthPercent->getInt();
		case 1: return healthPercent <= pHealthPercent->getInt();
		case 2: return healthPercent == pHealthPercent->getInt();
		case 3: return healthPercent >= pHealthPercent->getInt();
		case 4: return healthPercent > pHealthPercent->getInt();
		case 5: return healthPercent != pHealthPercent->getInt();
	}
	return false;
}

bool ScriptConditions::rva003E4519(Parameter *pPlayerParm)
{
	int playerMask = TheScriptEngine->rva00357B82(pPlayerParm);
	while (playerMask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
		if (player && player->getRva1C() >= player->getRva08()->rva003802DF())
			return true;
	}
	return false;
}

bool ScriptConditions::rva003E6BC5(Condition *pCondition, Parameter *pTypeParm)
{
	if (TheGameEngine->isMultiplayerSession())
		return false;

	bool anyChanges = false;
	if (pCondition->getCustomData() == 0)
		anyChanges = true;

	if (TheInGameUI->getFrameSelectionChanged() != pCondition->getCustomFrame())
		anyChanges = true;

	if (!anyChanges)
	{
		if (pCondition->getCustomData() == -1)
			return false;
		if (pCondition->getCustomData() == 1)
			return true;
	}

	bool isSelected = false;
	const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
	for (DrawableList::const_iterator it = selected->begin(); it != selected->end(); ++it)
	{
		Object *obj = (*it)->getObject();
		if (!obj)
			continue;
		ObjectTypesTemp types;
		Script_objectTypesFromParam(pTypeParm, types.m_types);
		const ThingTemplate *tmpl = obj->getTemplate();
		if (tmpl && types.m_types->isInSet(tmpl->getName()))
		{
			isSelected = true;
			break;
		}
	}

	pCondition->setCustomData(-1);
	if (isSelected)
		pCondition->setCustomData(1);
	pCondition->setCustomFrame(TheInGameUI->getFrameSelectionChanged());
	return isSelected;
}
