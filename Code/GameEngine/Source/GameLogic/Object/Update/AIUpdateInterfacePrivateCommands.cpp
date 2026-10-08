// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// AIUpdateInterface's private command handlers: the bodies BFME2's
// AICommandInterface::aiDoCommand (0x002673F6) reaches through its jump table
// at VA 0x00667BA6, one AIUpdate vtable slot per AICommandParms::m_cmd. They
// are named after real Zero Hour handlers where the body is one, and otherwise
// bfmePrivateCommandXX after the BFME2 command id XX that dispatches to them.
// BFME1-era names numbered by state id or by BFME1's command table are not
// used (BFME1's bfmePrivateCommand1B is command 0x02 here). Several bodies
// were first ported from Open-BFME-1's AIUpdateInterfacePrivateCommands.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1) and placed by masked whole-.text search; callee addresses are read off
// retail's call sites (reverse/symbols.csv).
//
// Declared once here, the fields line up with upstream's own order at +0x48
// onward (m_lastCommandSource, m_guardMode, m_guardTargetType[2], the guard
// location, m_objectToGuard). The same is true of StateMachine, whose slot at
// vtable+0x38 every handler uses.
//
// The state machine slot at vtable+0x38 is the goal object: the object-order
// handlers set it from their argument and bfmePrivateCommand02 clears it by
// passing null.
//
// The handlers' own declaration order is not evidence of their slots; the
// slots quoted beside each body are read from aiDoCommand and vtable
// 0x00C47B98, and bodies that dispatch through the owner's vtable do it by a
// cast to a slot view (AIUpdateSlot30 and the like). isIdle is slot 110
// (+0x1B8): BFME2's AIGroup::isIdle (0x0036DF4D) and joinTeam call it there.

// STLport's vector<Coord3D> (privateFollowPathAppend's local paths) with the
// bfmealloc shim: retail frees through the plain one-argument free, and /EHs
// (not /EHsc) keeps the unwind state store retail emits before that free.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/arch:SSE /G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

enum ObjectID
{
	INVALID_ID = 0
};

enum CanEnterType
{
	CHECK_CAPACITY = 0,
	DONT_CHECK_CAPACITY = 1,
	COMBATDROP_INTO = 2
};

enum KindOfType
{
	KINDOF_PROJECTILE = 0x19,
	// Bit 7 of the KindOf byte at template+0x11F; privateFollowWaypointPath
	// and Object 0x0028ECDB both test it. Its name is not evidenced.
	BFME_KINDOF_BF = 0xBF,
	// Bit 5 of byte template+0x115; privateIdle idles a contained member
	// carrying it only while that member attacks or has a victim. Unnamed.
	BFME_KINDOF_6D = 0x6D,
	// Bit 6 of byte template+0x10B: an object of this kind does not push its
	// allies aside (privateMoveAwayFromUnit), where Zero Hour tests
	// KINDOF_NO_COLLIDE; the name is donor-carried.
	KINDOF_NO_COLLIDE = 0x1E,
	// Bit 5 of byte template+0x117; it lets privateMoveAwayFromUnit push
	// allies aside. Unnamed.
	BFME_KINDOF_7D = 0x7D
};

// The two model conditions privateIdle clears, as bits of Object+0x10C:
// byte +0x113 mask 0x20 (1*32+29) and byte +0x11F mask 0x10 (4*32+28). BFME1's
// privateIdle clears MODELCONDITION_MOVING and MODELCONDITION_BACKING_UP at
// this point, so those names are donor-carried, not evidenced here.
enum ModelConditionFlagType
{
	BFME_MODELCONDITION_MOVING = 1 * 32 + 29,
	BFME_MODELCONDITION_BACKING_UP = 4 * 32 + 28
};

class ModelConditionFlags
{
public:
	UnsignedInt test(UnsignedInt bit) const { return m_words[bit >> 5] & (1U << (bit & 0x1f)); }
	void clear(UnsignedInt bit) { m_words[bit >> 5] &= ~(1U << (bit & 0x1f)); }

private:
	UnsignedInt m_words[19];
};

// Status bit 0x26 is tested by privateHunt and bfmePrivateCommand37; its
// name is not evidenced.
enum ObjectStatusTypes
{
	BFME_OBJECT_STATUS_26 = 0x26,
	// Set around privateAttackPosition's partition search, where Zero Hour
	// sets OBJECT_STATUS_IGNORING_STEALTH; the name is donor-carried.
	OBJECT_STATUS_IGNORING_STEALTH = 0x1B
};

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum GuardTargetType
{
	GUARDTARGET_OBJECT = 1,
	GUARDTARGET_LOCATION = 2,
	GUARDTARGET_AREA = 3,
	GUARDTARGET_NONE = 4
};

enum StateID
{
	BFME_AI_MOVE_TO = 0x01,
	BFME_AI_GUARD = 0x10,
	BFME_AI_HUNT = 0x11,
	BFME_AI_GET_REPAIRED = 0x18,
	BFME_AI_STATE_1B = 0x1B,
	BFME_AI_STATE_1C = 0x1C,
	BFME_AI_STATE_1D = 0x1D,
	BFME_AI_STATE_1E = 0x1E,
	BFME_AI_FACE_OBJECT = 0x1F,
	BFME_AI_ATTACK_MOVE_TO = 0x21,
	BFME_AI_STATE_25 = 0x25,
	BFME_AI_EXIT_INSTANTLY = 0x26,
	BFME_AI_STATE_37 = 0x37,
	BFME_AI_STATE_38 = 0x38,
	BFME_AI_GUARD_RETALIATE = 0x3E,
	BFME_AI_STATE_3F = 0x3F,
	// ZH's AI_ATTACK_POSITION order is state 9 here (privateAttackPosition).
	BFME_AI_ATTACK_POSITION = 0x09,
	INVALID_STATE_ID = 999999
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;

	void set(const Coord3D *other) { x = other->x; y = other->y; z = other->z; }
	void sub(const Coord3D *other) { x -= other->x; y -= other->y; z -= other->z; }
	float length() const;						///< matched 0x00003571
};

// Reuse the verified Coord3D push-back specialization at2CE7DC.
namespace _STL { template<> void vector<Coord3D>::push_back(const Coord3D&); }

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region3D
{
	Coord3D lo, hi;

	__forceinline Bool isInRegionNoZ(const Coord3D *query) const
	{
		return (lo.x < query->x) && (query->x < hi.x)
			&& (lo.y < query->y) && (query->y < hi.y);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
// The three native calls target the rowed predicate in Rva0028ECDB.cpp
// at 0x0028ECDB, passing the complete Object as this and the unchanged
// destination pointer. Its byte-verified view reads the template at +4
// and the containment word at +0x250. Keep that provider ABI; the body
// name and the position test remain unnamed.
class Rva0028ECDBHost
{
public:
	bool rva0028ECDB(void *position);
};

// Only the two virtuals privateGuardPosition dispatches are placed: getExtent
// at vtable+0x20 and findClosestEdgePoint at +0x34 (BFME2 slots, read from
// retail 0x00264C45 and 0x00264C82).
class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);	///< pinned 0x002802FE
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void getExtent(Region3D *extent) const;
	virtual void slot09(); virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual Coord3D findClosestEdgePoint(const Coord3D *closestTo) const;
};

extern TerrainLogic *TheTerrainLogic;

class WeaponSetFlags
{
public:
	Bool test(Int type) const { return (m_words[0] & (1U << type)) != 0; }

	UnsignedInt m_words[1];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
public:
	// 0x0047A699 (pinned): BFME2's contact-weapon query is an out-of-line
	// body that answers false (xor al, al; ret), folded with other such stubs.
	Bool isContactWeapon() const;
	float getContinueAttackRange() const { return m_continueAttackRange; }

	Int getAntiMask() const { return m_antiMask; }

	unsigned char m_unmodelled_00[0x10C];
	Int m_antiMask;								// +0x10C (isClearingMines)
	unsigned char m_unmodelled_110[0x148 - 0x110];
	float m_continueAttackRange;				// +0x148 (privateAttackPosition)
	unsigned char m_unmodelled_14C[0x4D4 - 0x14C];
	unsigned char m_bit0 : 1;
	unsigned char m_bit1 : 1;
	unsigned char m_bit2 : 1;
	unsigned char m_bit3 : 1;
	unsigned char m_bit4 : 1;					// WeaponTemplate+0x4D4 bit 4
};

// The weapon handle bfmeCurrentWeaponTemplateFlag4 asks the object for. It is
// the same question privateAttackMoveToPosition and privateGuardRetaliate ask
// through Object::getCurrentWeapon -- both take a null slot argument and both
// come back with the object's current weapon -- but the two calls are pinned
// separately, ?bfmeAskCLE@BfmeSubCLE@@ through ILT 0x00009C41 and
// ?getCurrentWeapon@Object@@ through ILT 0x00031A7F to body 0x001BE230. Until
// one caller settles whether those two thunks reach the same body, both
// spellings stay, and this one is reached by a cast the way the other
// address-named helpers in this TU are.
class BfmeXCLE
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }

private:
	void *m_vtable;
	const WeaponTemplate *m_template;			// +0x04
};

class BfmeSubCLE
{
public:
	BfmeXCLE *bfmeAskCLE(int);					///< ILT 0x00009C41
};

class Weapon
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }
	float getContinueAttackRange() const { return getTemplate()->getContinueAttackRange(); }
	Bool isContactWeapon() const { return getTemplate()->isContactWeapon(); }
	void setMaxShotCount(Int maxShots) { m_maxShotCount = maxShots; m_shotsFired = 0; }
	Int getAntiMask() const { return getTemplate()->getAntiMask(); }

	void *m_vtable;
	const WeaponTemplate *m_template;			// +0x04
	unsigned char m_unmodelled_08[0x20 - 0x08];
	Int m_shotsFired;
	unsigned char m_unmodelled_24[0x34 - 0x24];
	Int m_maxShotCount;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	// BFME2 keeps the KindOf bitset at +0x108 as 32-bit words: privateHunt
	// tests KINDOF_PROJECTILE (0x19) as bit 1 of byte +0x10B, the same layout
	// Rva00290EFEGetGhostObject.cpp and Object_isAbleToAttack.cpp read, and
	// privateMoveAwayFromUnit loads word +0x114 once to test two bits of it
	// (0x6D, 0x7D). The test hands back the masked word rather than a Bool:
	// cl then narrows a lone test to one byte and shares a loaded word, where
	// a `!= 0` result is materialised with a shift. Retail folds the whole
	// Thing -> template -> bitset chain; at /O1 the stand-in needs
	// __forceinline to do the same.
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindof[t >> 5] & (1U << (t & 31)); }

	unsigned char m_unmodelled_08[0x108 - 8];
	UnsignedInt m_kindof[4];					// +0x108
	unsigned char m_unmodelled_118[0x614 - 0x118];
	// A template flag that lets privateMoveAwayFromUnit push allies aside
	// whatever else holds; unnamed.
	Bool m_bfmeFlag614;							// +0x614

	// 0x0033C259: a float per locomotor set, which chooseLocomotorSet
	// stores at AIUpdate +0x1F8; unnamed.
	float rva0033C259(Int locomotorSet) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_template->isKindOf(t); }

	virtual void slot00();
	ThingTemplate *m_template;
};

class Object;
class AIUpdateInterface;
class Player;


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class AttackPriorityInfo;

class ScriptEngine
{
public:
	// 0x00205DDD resolves loadPostProcess's saved attack-info name where Zero
	// Hour's AIUpdateInterface::xfer calls getAttackInfo; name donor-carried.
	const AttackPriorityInfo *getAttackInfo(const AsciiString &name);
};

extern ScriptEngine *TheScriptEngine;

// The global at 0x00E01DBC; loadPostProcess hands it the owner last
// (0x00333E5B). Unnamed beyond the ledger's existing name.
struct LuaDrawableState
{
	void rva00333E5B(Object *obj);
};

class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
class UpdateModule
{
	friend class AIUpdateInterface;
protected:
	virtual void loadPostProcess();				///< matched 0x0058B03E
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	unsigned char m_unmodelled_00[0x14];
	Int m_commandType;							// +0x14 (BFME2; 0x0E idles the unit)
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(Int i) const;			///< pinned 0x00409EE8
};

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);	///< pinned 0x0031D5F8
};

extern ControlBar *TheControlBar;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
// ZH's Waypoint: the location at +0x0C and the first link at +0x20.
class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }
	Waypoint *getLink(Int i) const { return m_links[i]; }

private:
	unsigned char m_unmodelled_00[0x0C];
	Coord3D m_location;							// +0x0C
	unsigned char m_unmodelled_18[0x20 - 0x18];
	Waypoint *m_links[1];						// +0x20
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *position) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OpenContain.h
// BFME2 slots, from privateExitInstantly (0x0026488B, +0x84) and the enter
// order handler (0x00264775, +0x80) reaching one interface.
class HordeContainInterface
{
public:
	virtual void slot00() = 0; 	virtual void slot01() = 0;
	virtual void slot02() = 0; 	virtual void slot03() = 0;
	virtual void slot04() = 0; 	virtual void slot05() = 0;
	virtual void slot06() = 0; 	virtual void slot07() = 0;
	virtual void slot08() = 0; 	virtual void slot09() = 0;
	virtual void slot10() = 0; 	virtual void slot11() = 0;
	virtual void slot12() = 0; 	virtual void slot13() = 0;
	virtual void slot14() = 0; 	virtual void slot15() = 0;
	virtual void slot16() = 0; 	virtual void slot17() = 0;
	virtual void slot18() = 0; 	virtual void slot19() = 0;
	virtual void slot20() = 0; 	virtual void slot21() = 0;
	virtual void slot22() = 0; 	virtual void slot23() = 0;
	virtual void slot24() = 0; 	virtual void slot25() = 0;
	virtual void slot26() = 0; 	virtual void slot27() = 0;
	virtual void slot28() = 0; 	virtual void slot29() = 0;
	virtual void slot30() = 0; 
	virtual void slot31() = 0;
	virtual void enterObject(Object *, CommandSourceType) = 0;
	virtual void exitObject(Object *, CommandSourceType) = 0;
};

// The contained list privateIdle walks: a sentinel-headed ring whose nodes
// hold the object at +0x08 (the layout BFME1's privateIdle donor reads).
struct BfmeContainedNode
{
	BfmeContainedNode *m_next;
	BfmeContainedNode *m_prev;
	Object *m_object;
};

struct BfmeContainedList
{
	BfmeContainedNode *m_head;
};

// Returned by value through a hidden pointer, so it is not a plain aggregate
// to MSVC; the declared constructor says so. Its first word is not read here.
struct BfmeContainedRange
{
	BfmeContainedRange();

	void *m_unmodelled_00;
	BfmeContainedList *m_list;					// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
// BFME2 slot 31 (+0x7C) hands out the horde interface.
class ContainModuleInterface
{
public:
	virtual void slot00() = 0; 	virtual void slot01() = 0;
	virtual void slot02() = 0; 	virtual void slot03() = 0;
	virtual void slot04() = 0; 	virtual void slot05() = 0;
	virtual void slot06() = 0; 	virtual void slot07() = 0;
	virtual void slot08() = 0; 	virtual void slot09() = 0;
	virtual void slot10() = 0; 	virtual void slot11() = 0;
	virtual void slot12() = 0; 	virtual void slot13() = 0;
	virtual void slot14() = 0; 	virtual void slot15() = 0;
	virtual void slot16() = 0; 	virtual void slot17() = 0;
	virtual void slot18() = 0; 	virtual void slot19() = 0;
	virtual void slot20() = 0; 	virtual void slot21() = 0;
	virtual void slot22() = 0; 	virtual void slot23() = 0;
	virtual void slot24() = 0; 	virtual void slot25() = 0;
	virtual void slot26() = 0; 	virtual void slot27() = 0;
	virtual void slot28() = 0; 	virtual void slot29() = 0;
	virtual void slot30() = 0; 
	virtual HordeContainInterface *getHordeContainInterface() = 0;
	virtual void slot32() = 0; 	virtual void slot33() = 0;
	virtual void slot34() = 0; 	virtual void slot35() = 0;
	virtual void slot36() = 0; 	virtual void slot37() = 0;
	virtual void slot38() = 0; 	virtual void slot39() = 0;
	virtual void slot40() = 0; 	virtual void slot41() = 0;
	virtual void slot42() = 0; 	virtual void slot43() = 0;
	virtual void slot44() = 0; 	virtual void slot45() = 0;
	virtual void slot46() = 0; 	virtual void slot47() = 0;
	virtual void slot48() = 0; 	virtual void slot49() = 0;
	virtual void slot50() = 0; 	virtual void slot51() = 0;
	virtual void slot52() = 0; 	virtual void slot53() = 0;
	virtual void slot54() = 0; 	virtual void slot55() = 0;
	virtual void slot56() = 0; 	virtual void slot57() = 0;
	virtual void slot58() = 0; 	virtual void slot59() = 0;
	virtual void slot60() = 0; 	virtual void slot61() = 0;
	virtual void slot62() = 0; 	virtual void slot63() = 0;
	virtual void slot64() = 0; 	virtual void slot65() = 0;
	virtual void slot66() = 0; 	virtual void slot67() = 0;
	virtual void slot68() = 0; 	virtual void slot69() = 0;
	// Slot 70 (+0x118), read from privateIdle (0x0026D5FB). It returns an
	// eight-byte holder through a hidden pointer; the contained list is its
	// second word. BFME1's privateIdle asks getContainedItemsList at this
	// point (a list pointer there), so the name is donor-carried.
	virtual BfmeContainedRange getContainedItemsList() = 0;
};

class BFMEActionManager
{
public:
	// Body 0x0041C2D0 (ret 0x18). BFME2 takes six arguments: the sixth is an
	// out-flag (a null pointer is replaced by a local byte, which is cleared
	// and later set), and the fifth is passed through as the third argument
	// of the contain module's validity test at its vtable+0x98; WorldBuilder
	// pushes it as a byte, so it is a Bool.
	Bool canEnterObject(const Object *obj, const Object *objectToEnter, CommandSourceType commandSource,
		CanEnterType mode, Bool passThrough, Bool *outFlag);
	// Body 0x000C4080 (113 B, ret 0xC), reached through ILT 0x00012B57. A
	// three-argument object/object/source test distinct from the five-argument
	// canEnterObject above; its name is not evidenced, so it keeps the address.
	Bool rva000C4080(const Object *, const Object *, CommandSourceType);
};

// The shared singleton uses its defining GameClient.cpp type. These two
// rowed predicates use the real ActionManager spelling; unrowed interface
// methods above retain their existing borrowed view until recovered.
class ActionManager
{
public:
	Bool canGetHealedAt(const Object *, const Object *, CommandSourceType);
	Bool canGetRepairedAt(const Object *, const Object *, CommandSourceType);
};
extern ActionManager *TheActionManager;

// ZH's AIUpdateInterface derives from AICommandInterface at +0x20. The two
// order issuers here are matched under address names: 0x0026C347 builds
// AICMD 0x17 (the enter order, aiEnter) and 0x0026C3AC AICMD 0x18 (the dock
// order, aiDock; command 0x18 dispatches to the matched privateDock).
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType commandSource);	///< matched 0x001E8A38
	void rva0026C347(Object *obj, CommandSourceType commandSource);
	void rva0026C486(Object *obj, CommandSourceType commandSource);	///< matched 0x0026C486
	void rva0026C3AC(Object *obj, CommandSourceType commandSource);
	// Matched 0x0026C2D9: the object attack order privateAttackPosition
	// gives the victim its partition search finds (ZH aiAttackObject there).
	void rva0026C2D9(Object *victim, Int maxShotsToFire, CommandSourceType commandSource);
	// Matched 0x0026C411: the object-plus-position order privateMoveAwayFromUnit
	// hands to its horde container's AI.
	void rva0026C411(Object *obj, const Coord3D *pos, CommandSourceType commandSource);
	// Matched 0x0026C26D: the position order joinTeam gives where Zero Hour
	// calls aiMoveToPosition(pos, CMD_FROM_AI).
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType commandSource);
};

// The 24-byte team-member iterator (Common/RTS/TeamIterateTeamMemberList.cpp
// models the whole of it); joinTeam reads only its current object at +0.
template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	DLINK_ITERATOR();
	void advance();									///< pinned 0x00263526
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }

private:
	OBJCLASS *m_cur;
	unsigned char m_unmodelled_04[0x18 - 0x04];
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	///< matched 0x00263864
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Bool isMobile() const;
	Bool testStatus(ObjectStatusTypes bit) const;	///< 0x0004E536
	void setStatus(ObjectStatusTypes bit, Bool set);	///< matched 0x0023DB0E
	// Thing::getPosition: the cached position the object-order handlers hand
	// to the move voice (the +0x38 operand in their bodies).
	const Coord3D *getPosition() const { return &m_cachedPos; }
	const WeaponSetFlags &getWeaponSetFlags() const;
	Weapon *getCurrentWeapon(WeaponSlotType *wslot);
	const AsciiString &getCommandSetString() const;	///< pinned 0x00290E67
	UnsignedInt isDisabledByType(Int type) const { return m_disabledMask & (1U << type); }
	ObjectID getID() const { return m_id; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 0x01) != 0; }
	Bool isOffMap() const { return (m_privateStatus & 0x08) != 0; }
	Team *getTeam() const { return m_team; }
	// 0x0006F039 (ledger name Object::isKindOf) tests a bit of the word run
	// at +0x10C; privateMoveAwayFromUnit asks it for bit 0x84. Reached under
	// an address name here because that run is not the template's KindOf.
	Bool rva0006F039(Int bit) const;
	// 0x0028CE7B: a small enum privateMoveAwayFromUnit compares against 4
	// before telling moveAllies; unnamed.
	signed char rva0028CE7B() const;
	// AIUpdate's loadPostProcess re-registers a resting owner with these:
	// 0x0028B511 reads the word at +0x40C (matched), 0x0028ACEE and
	// 0x0028AD7C forward to the helper at +0xA4, and 0x0028B525 stores the
	// word at +0x40C back. Unnamed.
	Int rva0028B511() const;
	void rva0028ACEE(const Coord3D *pos, Int value);
	void rva0028AD7C();
	void rva0028B525(Int value);
	AIUpdateInterface *getAI() const { return m_ai; }
	ContainModuleInterface *getContain() const { return m_contain; }
	void rva0028AE6D();							///< matched 0x0028AE6D, the model-condition notifier
	// 0x0028DB3C, called last in privateIdle where BFME1 calls
	// adjustModelConditionForWeaponStatus; unnamed here.
	void rva0028DB3C();
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}

	unsigned char m_unmodelled_08[0x38 - 8];
	Coord3D m_cachedPos;						// +0x38
	unsigned char m_unmodelled_44[0x74 - 0x44];
	ObjectID m_id;								// +0x74
	unsigned char m_unmodelled_78[0x90 - 0x78];
	UnsignedInt m_status;						// +0x90
	unsigned char m_flags;						// +0x94
	unsigned char m_unmodelled_95[0xB8 - 0x95];
	// A radius: privateMoveAwayFromUnit lets the unit stay put when its
	// order point lies within it of the goal. Unnamed.
	float m_bfmeRadiusB8;						// +0xB8
	unsigned char m_unmodelled_BC[0x10C - 0xBC];
	ModelConditionFlags m_modelConditionFlags;	// +0x10C
	unsigned char m_unmodelled_158[0x1C8 - 0x158];
	// Zero Hour's disabled mask; isDoingGroundMovement tests DISABLED_HELD.
	UnsignedInt m_disabledMask;					// +0x1C8
	unsigned char m_unmodelled_1CC[0x250 - 0x1CC];
	ContainModuleInterface *m_contain;			// +0x250 (BFME2; the enter and exit handlers)
	unsigned char m_unmodelled_254[0x258 - 0x254];
	AIUpdateInterface *m_ai;					// +0x258 (BFME2; its AICommandInterface at +0x20 takes the command-button idle)
	unsigned char m_unmodelled_25C[0x274 - 0x25C];
	Object *m_containedBy;						// +0x274 (BFME2; privateExitInstantly's getContainedBy fallback)
	unsigned char m_unmodelled_278[0x304 - 0x278];
	Team *m_team;								// +0x304 (BFME2; joinTeam)
	unsigned char m_unmodelled_308[0x410 - 0x308];
	UnsignedInt m_formationID;					// +0x410 (BFME2; BFME1 +0x31C)
	unsigned char m_unmodelled_414[0x438 - 0x414];
	// Zero Hour's m_privateStatus: bit 0 EFFECTIVELY_DEAD, bit 3 OFF_MAP
	// (PartitionFilterSameMapStatus::allow 0x002611BF compares bit 3 of two
	// objects where Zero Hour compares isOffMap()).
	unsigned char m_privateStatus;				// +0x438
};

// The StateMachine member vector of positions at +0x3C (Zero Hour's
// m_goalPath); its assignment forwarder 0x00351759 is address-named
// (Rva0035149F.cpp), so the path commands reach it by a cast.
class Rva0035149F
{
public:
	UnsignedInt size() const { return m_finish - m_start; }
	const Coord3D *begin() const { return m_start; }
	const Coord3D *end() const { return m_finish; }
	const Coord3D &operator[](Int i) const { return m_start[i]; }

private:
	Coord3D *m_start, *m_finish, *m_end;
};
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void clear();
	virtual void slot18();
	virtual void initDefaultState();			// slot 7 (+0x1C), onObjectCreated
	virtual void setState(StateID state);
	// Slots 9 and 10 (+0x24, +0x28): the two queries AIUpdate slots 104 and
	// 105 forward; unnamed.
	virtual Int slot24();
	virtual Int slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(const Object *object);
	void setGoalPosition(const Coord3D *pos);	///< pinned 0x00262224
	void setGoalPosition(const Coord3D *pos, float range);	///< matched 0x004D745C
	StateID getCurrentStateID() const { return m_currentState ? m_currentState->m_ID : INVALID_STATE_ID; }
	StateID getTemporaryState() const { return m_temporaryState ? m_temporaryState->m_ID : INVALID_STATE_ID; }
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }

	// Zero Hour's m_currentState and m_goalPosition, at the offsets
	// privateAttackPosition reads (+0x04, the state's id at +0x04; +0x24).
	struct State
	{
		void *m_vtable;
		StateID m_ID;
	};
	State *m_currentState;						// +0x04
	unsigned char m_unmodelled_08[0x24 - 0x08];
	Coord3D m_goalPosition;						// +0x24
	unsigned char m_unmodelled_30[0x38 - 0x30];
	// Zero Hour's m_locked: isLocked / unlock / lock read and write it inline
	// (doQuickExit); the release build drops lock()'s message.
	Bool m_locked;								// +0x38
	unsigned char m_unmodelled_39[0x3C - 0x39];
	Rva0035149F m_goalPath;						// +0x3C
	unsigned char m_unmodelled_48[0x50 - 0x48];
	State *m_temporaryState;					// +0x50 (privateMoveAwayFromUnit)
	// The temporary state's frame limit; -1 is held with no limit
	// (isAllowedToRespondToAiCommands refuses every order then).
	Int m_temporaryStateFrames;					// +0x54
};

// ZH's AIStateMachine::setGoalWaypoint (pinned 0x003E3BFB).
class Team;

class AIStateMachine
{
public:
	// 0x00351C48: Zero Hour's AIStateMachine(Object *, AsciiString name). It
	// builds the StateMachine base (0x004D79E1) and the goal path; BFME2
	// passes an integer key (0x4A9A0E38 from makeStateMachine) where Zero
	// Hour passes the name. The parameter's type is an inference.
	AIStateMachine(Object *owner, UnsignedInt nameKey);
	void addToGoalPath(const Coord3D *pathPoint);	// pinned 0x0035385E (ZH name)
	void setGoalWaypoint(const Waypoint *way);
	void setGoalTeam(const Team *team);			///< pinned 0x0035042D

	unsigned char m_unmodelled_00[0x68];		// makeStateMachine allocates 0x68 bytes
};

class Rva00351759
{
public:
	Rva0035149F &rva00351759(const Rva0035149F &other);
};

// Locomotor helper 0x001E4147 (matched, Rva001E4147Copy.cpp): copies the
// position at +0x38 of the object it is handed to +0x14 of the locomotor.
struct Rva001E4147Twelve;
// Object's flag word at +0x370, handed out by the matched lea getter
// 0x0028B7AE (DispDwordLeaFieldGetters.cpp); command 0x47 refuses an object
// with bit 8 set.
class Rva0028B7AELeaGetter
{
public:
	void *get() const;
	Bool testBit8() const { return (UnsignedInt)((*(const UnsignedInt *)get() >> 8) & 1); }
};

// 0x00263910 (matched, Rva00263910Goal.cpp): the clipped goal position with an
// explicit range; setGoalPositionClipped (0x00265667) forwards to it with the
// global default.
class Rva00263910
{
public:
	void rva00263910(const Coord3D *pos, float range, int commandSource);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
// TheAI (0x00DFF0F8) hands out its pathfinder from +0x10. The pathfinder query
// 0x002EE7EE that command 0x52 asks about the owner is unnamed.
class Path;

class Pathfinder
{
public:
	Bool getClosestPointOnLand(const Coord3D *pos, Object *obj, Coord3D *result);
	// Zero Hour's getMoveAwayFromPath (0x002F9DBA) and moveAllies
	// (0x002F3C09, which BFME2 hands a third, Bool argument): the calls
	// privateMoveAwayFromUnit makes at Zero Hour's points. Names donor-carried.
	Path *getMoveAwayFromPath(Object *obj, Object *otherObj, Path *pathToAvoid, Object *otherObj2, Path *pathToAvoid2);
	void moveAllies(Object *obj, Path *path, Bool flag);
	// The two pathfinder calls AIUpdate slot 139 (0x0026412B) makes: one
	// taking the owner, then one taking the owner and a destination and
	// returning the new path. Unnamed.
	void rva002EF2A6(Object *obj);
	Path *GetHordeUnitPath(Object *obj, const Coord3D *destination);
	// Asked by AIUpdate slot 141 (0x00263404) whether a point down the path
	// will do for the owner; unnamed.
	Bool rva002ECC0D(Object *obj, const Coord3D *pos);
};

// The node AIUpdate slot 141 gets back from the path; only its +0x08 word is
// read (tested non-zero). Unnamed.
struct Rva003642DFNode
{
	unsigned char m_unmodelled_00[0x08];
	Int m_bfmeWord08;							// +0x08
};

// What 0x003642DF returns by value (16 bytes): a node and a position. Its
// default constructor only nulls the node: the shared null-first-word body
// 0x00326BE6, called out of line. Unnamed.
struct Rva003642DFResult
{
	Rva003642DFResult();
	Rva003642DFNode *m_node;					// +0x00
	Coord3D m_pos;								// +0x04
};

class Rva00263404Product;

// Zero Hour's Path (0x28 bytes, constructor 0x00363DC8); privateMoveAwayFromUnit
// reads a flag byte at +0x0D.
class Path
{
public:
	Path();										///< matched 0x00363DC8
	// AIUpdate slot 134 appends nodes with these (matched 0x002655E3 and
	// 0x00363B24); unnamed.
	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, Int value);
	void SetLastNodePortal(Int value);
	// The point `dist` along the path, and what slot 141 hands back to it.
	// Unnamed.
	Rva003642DFResult rva003642DF(float dist);
	void rva00365DF0(Rva00263404Product *product);
	unsigned char m_unmodelled_00[0x0C];
	// Set by slot 134 on a path it starts; 0x002655E3 tests it. Unnamed.
	Bool m_bfmeFlag0C;							// +0x0C
	Bool m_bfmeFlag0D;							// +0x0D
	unsigned char m_unmodelled_0E[0x28 - 0x0E];
};

// TheAI's data block at +0x18; privateMoveAwayFromUnit reads a flag at +0xB9
// before letting a BFME_KINDOF_6D unit push its allies aside. Unnamed.
struct AIData
{
	unsigned char m_unmodelled_00[0xB9];
	Bool m_bfmeFlagB9;							// +0xB9
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	const AIData *getAiData() const { return m_aiData; }

private:
	unsigned char m_unmodelled_00[0x10];
	Pathfinder *m_pathfinder;					// +0x10
	unsigned char m_unmodelled_14[0x18 - 0x14];
	AIData *m_aiData;							// +0x18
};

extern AI *TheAI;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	Object *findObjectByID(ObjectID id);		///< matched 0x00049DC5

private:
	unsigned char m_unmodelled_00[0x40];
	UnsignedInt m_frame;						// +0x40
};

extern GameLogic *TheGameLogic;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
// BFME2 chains partition filters instead of passing a null-terminated array:
// link (pinned 0x00625790) appends its argument to the +0x04 chain and
// returns this. The two filters privateAttackPosition builds install vtables
// 0x00BF91B0 (slot 1 is the matched PartitionFilterPossibleToAttack::allow
// 0x00260FD0, whose +0x08/+0x0C/+0x10 fields these are) and 0x00BF91BC; the
// second one's name is Zero Hour's (the filter its privateAttackPosition pairs
// with the attack filter), donor-carried.
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *objOther) = 0;
	PartitionFilter *link(PartitionFilter *next);

private:
	PartitionFilter *m_next;					// +0x04
};

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};

class PartitionFilterPossibleToAttack : public PartitionFilter
{
public:
	PartitionFilterPossibleToAttack(AbleToAttackType t, const Object *obj, CommandSourceType commandSource)
		: m_obj(obj), m_commandSource(commandSource), m_attackType(t) {}
	virtual Bool allow(Object *objOther);

private:
	const Object *m_obj;						// +0x08
	CommandSourceType m_commandSource;			// +0x0C
	AbleToAttackType m_attackType;				// +0x10
};

class PartitionFilterSameMapStatus : public PartitionFilter
{
public:
	PartitionFilterSameMapStatus(const Object *obj) : m_obj(obj) {}
	virtual Bool allow(Object *objOther);

private:
	const Object *m_obj;						// +0x08
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
// Zero Hour's defaults, as privateAttackPosition stores them: no flags, radii
// 0 and 100, RANDOM_START_ANGLE (-99999.9), maxZDelta 1e10, then three objects.
struct FindPositionOptions
{
	FindPositionOptions()
		: flags(0), minRadius(0.0f), maxRadius(0.0f), startAngle(-99999.9f), maxZDelta(1e10f),
		ignoreObject(0), sourceToPathToDest(0), relationshipObject(0) {}

	Int flags;
	float minRadius;
	float maxRadius;
	float startAngle;
	float maxZDelta;
	const Object *ignoreObject;
	const Object *sourceToPathToDest;
	const Object *relationshipObject;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, Int dc, PartitionFilter *filters);	///< pinned 0x00625360
	// 0x00285202 is called with no this and cleans no stack (cdecl, three
	// arguments): BFME2's findPositionAround is static. Name from Zero Hour.
	static Bool findPositionAround(const Coord3D *center, const FindPositionOptions *options, Coord3D *result);
};

extern PartitionManager *ThePartitionManager;

// An int global the temporary move order scales by 20 (named by address).
extern Int g_Va00DBA4E4;

// The two AIStateMachine helpers command 0x31 reaches when given a value:
// 0x0033FCC8 (matched, Rva0033FCC8Copy.cpp) and 0x0033FCE1, which takes a
// state id first (pinned under the BFME1 donor_sweep name).
class Rva0033FCC8
{
public:
	void rva0033FCC8();
};

class BfmeSubVfn1A6
{
public:
	void notify(int state, void *value);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
// isDoingGroundMovement reads the template's legal surfaces at +0x14.
enum LocomotorSurfaceType
{
	LOCOMOTORSURFACE_AIR = 8
};

class LocomotorTemplate
{
public:
	unsigned char m_unmodelled_00[0x14];
	Int m_surfaces;								// +0x14
};

class Rva001E4147
{
public:
	void rva001E4147(Rva001E4147Twelve *src);
	Int getLegalSurfaces() const { return m_template->m_surfaces; }

	void *m_unmodelled_00;
	const LocomotorTemplate *m_template;		// +0x04
};

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

// The argument of AIUpdate slot 141; its slot 6 (+0x18) makes something from
// the owner, the point and the node, which the path then takes
// (0x00365DF0). Unnamed.
class Rva00263404Source : public BfmeVirtualSlots<6>
{
public:
	virtual Rva00263404Product *slot6(Object *obj, const Coord3D *pos, Rva003642DFNode *node) = 0;
};

// AIUpdate vtable slots 108-111, reached by cast from the handlers below, in
// Zero Hour's order. Slot 108 (+0x1B0) is asked first by
// privateMoveAwayFromUnit where Zero Hour asks isAllowedToMoveAwayFromUnit;
// slot 110 (+0x1B8) is isIdle, which BFME2's AIGroup::isIdle (0x0036DF4D)
// dispatches and joinTeam asks of a teammate where Zero Hour asks isIdle.
class AIUpdateSlot110 : public BfmeVirtualSlots<108>
{
public:
	virtual Bool isAllowedToMoveAwayFromUnit() const = 0;
	virtual void slot109() = 0;
	virtual Bool isIdle() const = 0;
	// Slot 111 (+0x1BC), asked of the owner and of each contained member by
	// privateIdle where BFME1's privateIdle asks isAttacking (donor-carried).
	virtual Bool isAttacking() const = 0;
};

// The horde interface's slot 116 (+0x1D0), which privateMoveAwayFromUnit
// calls on its container's horde after handing the order up; unnamed.
class HordeContainSlot116 : public BfmeVirtualSlots<116>
{
public:
	virtual void slot116() = 0;
};

// privateFollowPathAppend dispatches privateFollowPath through the owner's
// vtable at slot 30 (+0x78), the slot aiDoCommand reaches it by for command 0x0A.
class AIUpdateSlot30 : public BfmeVirtualSlots<30>
{
public:
	virtual void privateFollowPath(const Rva0035149F *path, Object *ignoreObject, CommandSourceType commandSource, Bool exitProduction) = 0;
};

// onObjectCreated builds the state machine through the owner's slot 150
// (+0x258), where Zero Hour calls makeStateMachine (donor-carried).
class AIUpdateSlot150 : public BfmeVirtualSlots<150>
{
public:
	virtual StateMachine *makeStateMachine() = 0;
};

// joinTeam resets the locomotor set through the owner's slot 142 (+0x238).
class AIUpdateSlot142 : public BfmeVirtualSlots<142>
{
public:
	virtual Bool chooseLocomotorSet(Int wst) = 0;
};

// AIUpdate slot 134 first hands its point to slot 133 (+0x214, 0x00262C53).
class AIUpdateSlot133 : public BfmeVirtualSlots<133>
{
public:
	virtual void setLocomotorGoalPositionExplicitSmart(const Coord3D &pos) = 0;
};

// privateIdle dispatches privateGuardPosition through the owner's vtable at
// slot 63 (+0xFC), the slot aiDoCommand reaches it by for command 0x1E.
class AIUpdateSlot63 : public BfmeVirtualSlots<63>
{
public:
	virtual void privateGuardPosition(const Coord3D *position, GuardMode guardMode, CommandSourceType commandSource) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
// Only the head isAllowedToRespondToAiCommands reads.
struct AICommandParms
{
	Int m_cmd;									// +0x00
	CommandSourceType m_cmdSource;				// +0x04
};

enum MoodMatrixParameters
{
	MM_Controller_AI = 0x00000002,
	MM_Mood_Sleep = 0x00000100
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public BfmeVirtualSlots<96>
{
public:
	virtual Bool bfmeCurrentWeaponTemplateFlag4() const;
	virtual void clearGuardTargetType();

	void setGoalPositionClipped(const Coord3D *position, CommandSourceType commandSource);
	void setCurrentVictim(const Object *victim);	///< matched 0x00268D1F
	void ignoreObstacle(const Object *obj);			///< matched 0x00268D88
	Object *getCurrentVictim() const;				///< matched 0x00268D71
	void destroyPath();								///< matched 0x00262A8A
	Path *getPath() { return m_path; }
	void setIgnoreCollisionTime(Int frames) { m_ignoreCollisionsUntil = TheGameLogic->getFrame() + frames; }
	Bool isPathAvailable(const Coord3D *destination) const;
	Bool isMoving() const;							///< pinned 0x00264688
	Int getCurrentStateID() const;					///< matched 0x00262FC3

protected:
	void wakeUpNow();								///< matched 0x00262871

	virtual void privateExitInstantly(Object *objectToExit, CommandSourceType commandSource);
	virtual void privateEnter(Object *object, CommandSourceType commandSource);
	virtual void privateMoveToPosition(const Coord3D *position, float range, CommandSourceType commandSource);
	virtual void bfmePrivateCommand01(Object *obj, CommandSourceType commandSource);
	virtual void bfmePrivateCommand02(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand03(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand04(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand38(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand41(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand3C(Object *obj, CommandSourceType commandSource);
	virtual void privateFollowWaypointPath(const Waypoint *way, CommandSourceType commandSource);
	virtual void privateAttackFollowWaypointPath(const Waypoint *way, Int maxShotsToFire, Bool asTeam, CommandSourceType commandSource);
	virtual void privateAttackMoveToPositionAndOrientation(const Coord3D *position, float range, Int maxShotsToFire, CommandSourceType commandSource);
	virtual void privateAttackTeam(const Team *team, Int maxShotsToFire, CommandSourceType commandSource);
	virtual void privateCommandButton(const CommandButton *commandButton, CommandSourceType commandSource);
	virtual void privateCommandButtonPosition(const CommandButton *commandButton, const Coord3D *pos, CommandSourceType commandSource);
	virtual void bfmePrivateCommand42(Object *obj, CommandSourceType commandSource);
	virtual void bfmePrivateCommand24(const Rva0035149F *path, Object *ignoreObject, float value, CommandSourceType commandSource);
	virtual void bfmePrivateCommand25(const Rva0035149F *path, Object *ignoreObject, float value, CommandSourceType commandSource);
	virtual void privateFollowPath(const Rva0035149F *path, Object *ignoreObject, CommandSourceType commandSource, Bool exitProduction);
	virtual void privateMoveToPositionAmphibious(const Coord3D *position, Int value, CommandSourceType commandSource);
	virtual void bfmePrivateCommand31(Int value, CommandSourceType commandSource);
	virtual void privateMoveToPositionSA(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand48(Object *obj, CommandSourceType commandSource);
	virtual void bfmePrivateCommand39(Object *victim, CommandSourceType commandSource);
	virtual void privateAttackMoveToPosition(const Coord3D *position, Int maxShotsToFire, CommandSourceType commandSource);
	virtual void privateHunt(CommandSourceType commandSource);
	virtual void privateFaceObject(Object *target, CommandSourceType commandSource);
	virtual void privateGetRepaired(Object *repairDepot, CommandSourceType commandSource);
	virtual void privateGuardObject(Object *objectToGuard, GuardMode guardMode, CommandSourceType commandSource);
	virtual void privateGuardPosition(const Coord3D *position, GuardMode guardMode, CommandSourceType commandSource);
	virtual void privateGuardAreaFromPosition(const PolygonTrigger *area, GuardMode guardMode,
		CommandSourceType commandSource, const Coord3D *position);
	virtual void privateGuardRetaliate(Object *victim, const Coord3D *position, Int maxShotsToFire, CommandSourceType commandSource);
	// Declared last so no slot above moves; nothing in this TU dispatches it.
	virtual void privateMoveToObject(Object *obj, CommandSourceType commandSource);
	// BFME2 aiDoCommand handlers named by their command id (see the bodies).
	virtual void privateAttackArea(const PolygonTrigger *areaToGuard, CommandSourceType commandSource);
	virtual void privateFacePosition(const Coord3D *position, CommandSourceType commandSource);
	virtual void privateGetHealed(Object *healDepot, CommandSourceType commandSource);
	virtual void bfmePrivateCommand37(Int value, CommandSourceType commandSource);
	virtual void bfmePrivateCommand3D(Object *obj, CommandSourceType commandSource);
	virtual void bfmePrivateCommand3E(Object *obj, CommandSourceType commandSource);
	virtual void bfmePrivateCommand4A(Object *obj, const Coord3D *pos, CommandSourceType commandSource);
	virtual void bfmePrivateCommand4B(Object *obj, const Coord3D *pos, CommandSourceType commandSource);
	virtual void bfmePrivateCommand4C(Object *obj, const Rva0035149F *path, CommandSourceType commandSource);
	virtual void bfmePrivateCommand4D(Object *obj, const Rva0035149F *path, CommandSourceType commandSource);
	virtual void bfmePrivateCommand53(CommandSourceType commandSource);
	virtual void bfmePrivateCommand54(Object *obj, const Coord3D *pos, CommandSourceType commandSource);
	virtual void privateIdle(CommandSourceType commandSource);
	virtual void privateAttackPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType commandSource);
	virtual void privateFollowPathAppend(const Coord3D *pos, CommandSourceType commandSource);
	virtual void privateMoveAwayFromUnit(Object *unit, const Coord3D *pos, CommandSourceType commandSource);
public:
	virtual void doQuickExit(const _STL::vector<Coord3D> *path);
	virtual Int rva0026E988();
	virtual void onObjectCreated();
	virtual Bool isClearingMines() const;
	virtual Bool isDoingGroundMovement() const;
	virtual Bool isAllowedToRespondToAiCommands(const AICommandParms *parms) const;
	virtual Object *getEnterTarget();
	virtual Bool chooseLocomotorSet(Int wst);
	virtual void joinTeam();
	Int rva00260DED() const;						///< matched 0x00260DED (a state id getter)
protected:
	virtual AIStateMachine *makeStateMachine();
public:
	Bool chooseLocomotorSetExplicit(Int wst);		// pinned 0x00268A37 (ZH name)
	void chooseGoodLocomotorFromCurrentSet();		// pinned 0x00263FA7 (ZH name)
	UnsignedInt getMoodMatrixValue() const;			// pinned 0x00264F5E (ZH name)
	virtual Int rva0026E999();
	virtual void micropathToPosition(const Coord3D *destination);
	virtual void rva00263404(Rva00263404Source *source);
	virtual void appendPositionToLocomotorPath(const Coord3D &pos, Int value);
protected:
	virtual void loadPostProcess();
public:
	// Zero Hour's construct (the slot just before getEnterTarget); BFME2's
	// takes a sixth dword (ret 0x18; DozerAIUpdate's 0x00488F52 reads it at
	// [ebp+0x1C]) whose type and name are not evidenced.
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, float angle,
		Player *owningPlayer, Bool isRebuild, Int bfmeArg6);
	void rva00262989(UnsignedInt frame);			///< matched 0x00262989
protected:

	// Zero Hour's ObjectModule accessor. privateMoveToObject reads the owner
	// through it, and that is not cosmetic: see the body.
	Object *getObject() const { return m_object; }
	StateMachine *getStateMachine() const { return m_stateMachine; }
	Object *getGoalObject() { return getStateMachine()->getGoalObject(); }
	const Coord3D *getGoalPosition() const { return getStateMachine()->getGoalPosition(); }

	void playMoveVoiceResponse(const Coord3D *position);		///< 0x0026B403 (voice message 0x7E7)
	// 0x0026B37F posts voice message 0x7E8 for a position, the voice the
	// attack-move orders (privateAttackFollowWaypointPath, command 0x49)
	// answer with; its name is not evidenced.
	void playVoiceEnterStateAttackMove(const Coord3D *position);
	void playAttackVoiceResponse(Object *victim);
	void playAttackVoiceResponse(const Coord3D *position);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;

	// Upstream's guard fields, in upstream's order. The +0x4C word also
	// carries bfmePrivateCommand37's value, and command 0x20 (banked) keeps a
	// team word at +0x68.
	GuardMode m_guardMode;						// +0x4C
	GuardTargetType m_guardTargetType[2];		// +0x50, a two-deep stack
	Coord3D m_locationToGuard;					// +0x58, privateGuardPosition
	ObjectID m_objectToGuard;					// +0x64
	UnsignedInt m_guardExtra;					// +0x68
	const PolygonTrigger *m_areaToGuard;		// +0x6C, privateAttackArea
	// Zero Hour's m_attackInfo, next after m_areaToGuard there too;
	// loadPostProcess resolves it from the name at +0x214.
	const AttackPriorityInfo *m_attackInfo;		// +0x70
	unsigned char m_unmodelled_74[0x140 - 0x74];
	Path *m_path;								// +0x140 (Zero Hour's m_path; destroyPath clears it)
	unsigned char m_unmodelled_144[0x16C - 0x144];
	int m_blockedFrames;						// +0x16C
	unsigned char m_unmodelled_170[0x178 - 0x170];
	UnsignedInt m_ignoreCollisionsUntil;		// +0x178 (Zero Hour's setIgnoreCollisionTime target)
	unsigned char m_unmodelled_17C[0x198 - 0x17C];
	ObjectID m_moveOutOfWay1;					// +0x198
	ObjectID m_moveOutOfWay2;					// +0x19C
	float m_pathFloat1A0;						// +0x1A0, the path orders' float argument
	unsigned char m_unmodelled_1A4[0x1DC - 0x1A4];
	Int m_validLocomotorSurfaces;				// +0x1DC (Zero Hour's m_locomotorSet.getValidSurfaces())
	unsigned char m_unmodelled_1E0[0x1F0 - 0x1E0];
	Rva001E4147 *m_curLocomotor;				// +0x1F0 (BFME2; BFME1 +0x1CC)
	Int m_curLocomotorSet;						// +0x1F4 (Zero Hour's name; chooseLocomotorSet)
	// A float chooseLocomotorSet takes from the template for the new set and
	// a player's order 0 or 1 is refused while it is zero
	// (isAllowedToRespondToAiCommands); unnamed.
	float m_bfmeFloat1F8;						// +0x1F8
	// Zero Hour's locomotor goal pair (setLocomotorGoalPositionExplicit's
	// fields follow m_curLocomotorSet there); slot 139 stores goal type 4 and
	// a destination. Names donor-carried, placement inferred.
	Int m_locomotorGoalType;					// +0x1FC
	Coord3D m_locomotorGoalData;				// +0x200
	unsigned char m_unmodelled_20C[0x214 - 0x20C];
	// The attack-info name loadPostProcess resolves into m_attackInfo when it
	// is not empty (inferred: Zero Hour reads it in xfer instead).
	AsciiString m_attackInfoName;				// +0x214
	unsigned char m_unmodelled_218[0x3B1 - 0x218];
	Bool m_waitingForPath;						// +0x3B1, Zero Hour's isWaitingForPath() in privateFollowPathAppend (BFME1 +0x31E; donor-carried)
	unsigned char m_unmodelled_3B2[0x3B8 - 0x3B2];
	// Zero Hour's m_isBlocked: cleared with m_blockedFrames by the move
	// orders, tested by privateMoveAwayFromUnit where Zero Hour tests it.
	Bool m_isBlocked;							// +0x3B8
	Bool m_upgradedLocomotors;					// +0x3B9 (Zero Hour's name; chooseLocomotorSet)
	Bool m_canPathThroughUnits;					// +0x3BA (ZH name; privateMoveAwayFromUnit's retry flag)
	unsigned char m_unmodelled_3BB[0x3BD - 0x3BB];
	unsigned char m_isAiDead;					// +0x3BD (BFME2; BFME1 +0x32B)
	unsigned char m_unmodelled_3BE[0x3C5 - 0x3BE];
	// isAllowedToRespondToAiCommands refuses player orders while +0x3C5 is
	// set and script orders while +0x3C6 is set; unnamed.
	Bool m_bfmeIgnorePlayerCommands;			// +0x3C5
	Bool m_bfmeIgnoreScriptCommands;			// +0x3C6
	unsigned char m_unmodelled_3C7[0x3C9 - 0x3C7];
	// While set, chooseLocomotorSet refuses to change sets; unnamed.
	Bool m_bfmeLocomotorSetLocked;				// +0x3C9
	unsigned char m_unmodelled_3CA[0x3CF - 0x3CA];
	// Set only while privateMoveAwayFromUnit asks the pathfinder; unnamed.
	Bool m_bfmeFindingMoveAwayPath;				// +0x3CF
	unsigned char m_unmodelled_3D0[0x3DC - 0x3D0];
	// Slot 141 acts only while this is non-zero, hands it to 0x00262989 and
	// clears it. Unnamed.
	UnsignedInt m_bfmeWord3DC;					// +0x3DC
};

// Retail 0x00271630. BFME gates Zero Hour's move-to-object order on a
// three-argument ActionManager test, then drives the state machine as
// upstream does. The owner is read through getObject(), as upstream writes it:
// reading m_object directly compiles to the same load but hands the three
// vtable temporaries EDX, EAX, EDX where retail has EAX, EDX, EAX (MSVC 7.1
// assigns scratch registers round-robin and the inlined accessor's return
// value is one more step; docs/shape_levers.md, "Scratch registers rotate").
void AIUpdateInterface::privateMoveToObject(Object *obj, CommandSourceType commandSource)
{
	if (!reinterpret_cast<BFMEActionManager *>(TheActionManager)->rva000C4080(getObject(), obj, commandSource))
		return;
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x3c);
}


// Command 0x02, slot 25, retail 0x00267DAD, the shortest of the position
// family: it clears the goal object rather than setting one, takes the
// clipped goal position, and skips the locomotor, the blocked counters and the
// voice response. BFME1 carried this body as bfmePrivateCommand1B, after its
// state id.
void AIUpdateInterface::bfmePrivateCommand02(const Coord3D *position, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(0);
	setGoalPositionClipped(position, commandSource);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_1B);
}


// Retail 0x00273730. BFME command 0x39 orders a giant bird to force-attack
// one object with one shot, then answers player and script orders with attack voice.
void AIUpdateInterface::bfmePrivateCommand39(Object *victim, CommandSourceType commandSource)
{
	if (!victim)
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(victim);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x2e);

	Weapon *weapon = m_object->getCurrentWeapon(0);
	if (weapon)
	{
		weapon->m_maxShotCount = 1;
		weapon->m_shotsFired = 0;
	}

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playAttackVoiceResponse(victim);
}


// BFME2 aiDoCommand (0x002673F6) switches on AICommandParms::m_cmd through the
// jump table at VA 0x00667BA6 and calls one AIUpdateInterface vtable slot per
// command, passing m_obj (+0x14), &m_pos (+0x08) or &m_coords (+0x20) and the
// command source. The handlers below are named by that command id, the way
// bfmePrivateCommand39 (command 0x39, slot 35) is; slot numbers are of the
// AIUpdate vtable 0x00C47B98, whose other slots are this class's matched
// privateDock / privateMoveToObject. The state ids are the target's constants.

// Command 0x3D, slot 49, retail 0x002647EF.
void AIUpdateInterface::bfmePrivateCommand3D(Object *obj, CommandSourceType commandSource)
{
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x34);
}

// Command 0x3E, slot 56, retail 0x00264963: with no object given it falls back
// to the owner's object at +0x274, and does nothing when that is null too.
void AIUpdateInterface::bfmePrivateCommand3E(Object *obj, CommandSourceType commandSource)
{
	if (!obj)
	{
		obj = m_object->m_containedBy;
		if (!obj)
			return;
	}
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x35);
}

// Command 0x4A, slot 57, retail 0x002649A3.
void AIUpdateInterface::bfmePrivateCommand4A(Object *obj, const Coord3D *pos, CommandSourceType commandSource)
{
	StateMachine *sm = m_stateMachine;
	sm->clear();
	sm->setGoalObject(obj);
	sm->setGoalPosition(pos);
	m_lastCommandSource = commandSource;
	sm->setState((StateID)0x41);
}

// Command 0x4B, slot 54, retail 0x002648F1.
void AIUpdateInterface::bfmePrivateCommand4B(Object *obj, const Coord3D *pos, CommandSourceType commandSource)
{
	StateMachine *sm = m_stateMachine;
	sm->clear();
	sm->setGoalObject(obj);
	sm->setGoalPosition(pos);
	m_lastCommandSource = commandSource;
	sm->setState((StateID)0x42);
}

// Command 0x4C, slot 58, retail 0x002649DC.
void AIUpdateInterface::bfmePrivateCommand4C(Object *obj, const Rva0035149F *path, CommandSourceType commandSource)
{
	StateMachine *sm = m_stateMachine;
	sm->clear();
	sm->setGoalObject(obj);
	reinterpret_cast<Rva00351759 *>(sm)->rva00351759(*path);
	m_lastCommandSource = commandSource;
	sm->setState((StateID)0x45);
}

// Command 0x4D, slot 55, retail 0x0026492A.
void AIUpdateInterface::bfmePrivateCommand4D(Object *obj, const Rva0035149F *path, CommandSourceType commandSource)
{
	StateMachine *sm = m_stateMachine;
	sm->clear();
	sm->setGoalObject(obj);
	reinterpret_cast<Rva00351759 *>(sm)->rva00351759(*path);
	m_lastCommandSource = commandSource;
	sm->setState((StateID)0x44);
}

// Command 0x53, slot 77, retail 0x00264AB2.
void AIUpdateInterface::bfmePrivateCommand53(CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	m_stateMachine->clear();
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x4a);
}

// Command 0x54, slot 59, retail 0x00264A15.
void AIUpdateInterface::bfmePrivateCommand54(Object *obj, const Coord3D *pos, CommandSourceType commandSource)
{
	StateMachine *sm = m_stateMachine;
	sm->clear();
	sm->setGoalObject(obj);
	sm->setGoalPosition(pos);
	m_lastCommandSource = commandSource;
	sm->setState((StateID)0x4b);
}

// Command 0x12, slot 43, retail 0x002646E9. aiHunt (0x002AE657) issues
// AICMD 0x12; BFME1's privateHunt (mobile, not a projectile, then AI_HUNT,
// state 0x11) plus a BFME2 status-bit guard.
void AIUpdateInterface::privateHunt(CommandSourceType commandSource)
{
	if (!getObject()->isMobile())
		return;
	if (getObject()->isKindOf(KINDOF_PROJECTILE))
		return;
	if (getObject()->testStatus(BFME_OBJECT_STATUS_26))
		return;
	m_stateMachine->clear();
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_HUNT);
}

// Command 0x26, slot 69, retail 0x002645B9. aiFaceObject (0x003C771D)
// issues AICMD 0x26; BFME1's privateFaceObject shape, with BFME2's state 0x24
// and one blocked byte at +0x3B8 instead of the two at +0x325.
void AIUpdateInterface::privateFaceObject(Object *target, CommandSourceType commandSource)
{
	if (!getObject()->isMobile())
		return;
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(target);
	m_blockedFrames = 0;
	m_isBlocked = false;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x24);
}

// Command 0x37, slot 62, retail 0x00264CBB: AICommandParms::m_intValue (+0x34)
// is stored at +0x4C before the state machine enters state 0x18.
void AIUpdateInterface::bfmePrivateCommand37(Int value, CommandSourceType commandSource)
{
	Object *obj = getObject();
	if (obj->testStatus(BFME_OBJECT_STATUS_26))
		return;
	if (!obj->isMobile())
		return;
	if (getObject()->isKindOf(KINDOF_PROJECTILE))
		return;
	m_guardMode = (GuardMode)value;
	m_stateMachine->clear();
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x18);
}

// Command 0x15 (ZH AICMD_GET_HEALED, one below ZH's numbering as HUNT 0x12
// and DOCK 0x18 are), slot 46, retail 0x0026DD89: the donor body, ending in
// aiEnter.
void AIUpdateInterface::privateGetHealed(Object *healDepot, CommandSourceType commandSource)
{
	if (TheActionManager->canGetHealedAt(getObject(), healDepot, commandSource) == false)
		return;
	reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(this) + 0x20)->rva0026C347(healDepot, commandSource);
}

// Command 0x16 (AICMD_GET_REPAIRED), slot 47, retail 0x0026DDBB: BFME1's
// privateGetRepaired, ending in aiDock.
void AIUpdateInterface::privateGetRepaired(Object *repairDepot, CommandSourceType commandSource)
{
	if (TheActionManager->canGetRepairedAt(getObject(), repairDepot, commandSource) == false)
		return;
	reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(this) + 0x20)->rva0026C3AC(repairDepot, commandSource);
}

// Command 0x1F, slot 64, retail 0x00264D0E: BFME1's privateGuardObject
// (guard target type OBJECT in the free slot, mode at +0x4C, the guarded
// object's id at +0x64, AI_GUARD) behind BFME2's status-bit guard.
// AIUpdateInterface::privateGuardObject is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateGuardObject.cpp (0x00264D0E).

// Command 0x27, slot 70, retail 0x00267D65. aiFacePosition (0x003C7782)
// issues AICMD 0x27; ZH's privateFacePosition with BFME2's state 0x25 and
// one blocked byte at +0x3B8.
void AIUpdateInterface::privateFacePosition(const Coord3D *position, CommandSourceType commandSource)
{
	if (!getObject()->isMobile())
		return;
	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_isBlocked = false;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x25);
}

// Command 0x23, slot 68, retail 0x0026C1CE. aiAttackArea (0x0036F136)
// issues AICMD 0x23; BFME1's privateAttackArea (state 0x1F here) plus an
// attack voice at the area's centre for player and script orders.
void AIUpdateInterface::privateAttackArea(const PolygonTrigger *areaToGuard, CommandSourceType commandSource)
{
	if (!getObject()->isMobile())
		return;
	if (getObject()->isKindOf(KINDOF_PROJECTILE))
		return;

	m_areaToGuard = areaToGuard;
	m_stateMachine->clear();
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x1f);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
	{
		Coord3D pos;
		areaToGuard->getCenterPoint(&pos);
		playAttackVoiceResponse(&pos);
	}
}

// Command 0x1A (ZH AICMD_EXIT_INSTANTLY, one below ZH's numbering), slot 53,
// retail 0x0026488B: BFME1's privateExitInstantly (default to the container
// we are in, state 0x26) without the subdued test, and handing the exit to a
// horde container's interface when there is one.
void AIUpdateInterface::privateExitInstantly(Object *objectToExit, CommandSourceType commandSource)
{
	Object *us = getObject();
	if (!objectToExit)
	{
		objectToExit = us->m_containedBy;
		if (!objectToExit)
			return;
	}

	ContainModuleInterface *contain = us->m_contain;
	if (contain)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde)
		{
			horde->exitObject(objectToExit, commandSource);
			return;
		}
	}

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(objectToExit);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_EXIT_INSTANTLY);
}

// Retail 0x0026E9AA, AIUpdate vtable 0x00C47B98 slot 124, right after the
// getGuardTargetType slot (123, the m_guardTargetType[1] getter at 0x0009AAA4):
// ZH AIUpdate.h's inline clearGuardTargetType, which shifts the guard target
// stack down and empties the top.
void AIUpdateInterface::clearGuardTargetType()
{
	m_guardTargetType[1] = m_guardTargetType[0];
	m_guardTargetType[0] = GUARDTARGET_NONE;
}

// The move-order family. Each prepares the locomotor with the owner's position
// (0x001E4147), resets the blocked counters, enters its state and answers
// player and script orders with a voice. Command 0x01 takes an object (and is
// gated on the AI-dead byte), the rest a position.

// Command 0x01, slot 15, retail 0x0026B637: move to an object.
void AIUpdateInterface::bfmePrivateCommand01(Object *obj, CommandSourceType commandSource)
{
	if (m_isAiDead)
		return;
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_blockedFrames = 0;
	m_isBlocked = false;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_MOVE_TO);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(obj->getPosition());
}

// Command 0x03, slot 19, retail 0x0026B6B2: state 0x1C.
void AIUpdateInterface::bfmePrivateCommand03(const Coord3D *position, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_isBlocked = false;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_1C);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(position);
}

// Command 0x04, slot 20, retail 0x0026B720: state 0x1D.
void AIUpdateInterface::bfmePrivateCommand04(const Coord3D *position, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_isBlocked = false;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_1D);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(position);
}

// Command 0x38, slot 21, retail 0x0026B78E: state 0x1E.
void AIUpdateInterface::bfmePrivateCommand38(const Coord3D *position, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_isBlocked = false;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_1E);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(position);
}

// Command 0x41, slot 22, retail 0x0026B7FC: state 0x37.
void AIUpdateInterface::bfmePrivateCommand41(const Coord3D *position, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_isBlocked = false;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_37);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(position);
}

// Command 0x3C, slot 82, retail 0x0026B86A: an object order a contained unit
// cannot take; the previous goal object becomes the current victim.
void AIUpdateInterface::bfmePrivateCommand3C(Object *obj, CommandSourceType commandSource)
{
	if (m_isAiDead)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->m_containedBy)
		return;

	Object *oldGoal = m_stateMachine->getGoalObject();
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_lastCommandSource = commandSource;
	setCurrentVictim(oldGoal);
	m_stateMachine->setState((StateID)0x31);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(obj->getPosition());
}

// Command 0x47, slot 16, retail 0x00267CFA: a position order into state 0x3F
// with no voice, refused while bit 8 of the owner's +0x370 flag word is set.
void AIUpdateInterface::privateMoveToPositionSA(const Coord3D *position, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	if (reinterpret_cast<const Rva0028B7AELeaGetter *>(m_object)->testBit8())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_isBlocked = false;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_3F);
}

// Command 0x48, slot 18, retail 0x00264558: the object form of command 0x47
// (state 0x3F, no voice), gated on the AI-dead byte as command 0x01 is.
void AIUpdateInterface::bfmePrivateCommand48(Object *obj, CommandSourceType commandSource)
{
	if (m_isAiDead)
		return;
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_blockedFrames = 0;
	m_isBlocked = false;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_3F);
}

// Command 0x31, slot 80, retail 0x00264B86: AICommandParms::m_intValue
// (+0x34) selects the form. With zero it is an ordinary order into state 0x2A;
// otherwise the state machine is handed state 0x2A and the value through
// 0x0033FCE1, after 0x0033FCC8, without recording the command source.
void AIUpdateInterface::bfmePrivateCommand31(Int value, CommandSourceType commandSource)
{
	if (value == 0)
	{
		m_stateMachine->clear();
		m_lastCommandSource = commandSource;
		m_stateMachine->setState((StateID)0x2a);
	}
	else
	{
		reinterpret_cast<Rva0033FCC8 *>(m_stateMachine)->rva0033FCC8();
		reinterpret_cast<BfmeSubVfn1A6 *>(m_stateMachine)->notify(0x2a, (void *)value);
	}
}

// Command 0x1E, slot 63, retail 0x00264BC2: Zero Hour's privateGuardPosition
// behind BFME2's status-bit, mobility and projectile guards. A player's order
// outside the map extent guards the closest edge point instead.
// AIUpdateInterface::privateGuardPosition is defined with its retail-matched body in Code/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfacePrivateGuardPosition.cpp (0x00264BC2).

// The end of the path that starts at w.
static __forceinline const Waypoint *lastWaypoint(const Waypoint *w)
{
	while (w && w->getLink(0))
		w = w->getLink(0);
	return w;
}

// Command 0x06, slot 26, retail 0x0026B8E5: the BFME1 donor's
// privateFollowWaypointPath (clear the formation id, set the goal waypoint,
// state 3 AS_INDIVIDUALS, move voice at the first waypoint). BFME2 adds one
// branch: a BFME_KINDOF_BF object with a contain module whose path ends at a
// point Object 0x0028ECDB accepts enters state 0x49 instead.
void AIUpdateInterface::privateFollowWaypointPath(const Waypoint *way, CommandSourceType commandSource)
{
	Object *obj = getObject();
	if (!obj->isMobile())
		return;

	obj->m_formationID = 0;
	m_stateMachine->clear();
	reinterpret_cast<AIStateMachine *>(m_stateMachine)->setGoalWaypoint(way);
	m_lastCommandSource = commandSource;

	const Waypoint *last;
	if (obj->isKindOf(BFME_KINDOF_BF) && obj->m_contain && way
		&& (last = lastWaypoint(way)) != 0 && reinterpret_cast<Rva0028ECDBHost *>(obj)->rva0028ECDB(const_cast<Coord3D *>(last->getLocation())))
		m_stateMachine->setState((StateID)0x49);
	else
		m_stateMachine->setState((StateID)3);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(way->getLocation());
}

// Command 0x11, slot 42, retail 0x0026C150: Zero Hour's
// privateAttackFollowWaypointPath. BFME2 gates it on the AI-dead byte, enters
// state 0x22 (0x23 as a team), arms the current weapon's shot counters, and
// answers player and script orders with voice 0x7E8 at the first waypoint.
void AIUpdateInterface::privateAttackFollowWaypointPath(const Waypoint *way, Int maxShotsToFire, Bool asTeam, CommandSourceType commandSource)
{
	if (m_isAiDead)
		return;
	if (!m_object->isMobile())
		return;

	m_stateMachine->clear();
	reinterpret_cast<AIStateMachine *>(m_stateMachine)->setGoalWaypoint(way);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)(asTeam ? 0x23 : 0x22));

	Weapon *weapon = m_object->getCurrentWeapon(0);
	if (weapon)
	{
		weapon->m_shotsFired = 0;
		weapon->m_maxShotCount = maxShotsToFire;
	}

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playVoiceEnterStateAttackMove(way->getLocation());
}

// Command 0x51, slot 14, retail 0x0026C04E: the attack-move order to a
// position with an explicit goal range (state 0x21, the current weapon armed
// with the order's shot limit, voice 0x7E8), refused while the AI is dead,
// the owner cannot move, or bit 8 of its +0x370 flag word is set.
void AIUpdateInterface::privateAttackMoveToPositionAndOrientation(const Coord3D *position, float range, Int maxShotsToFire, CommandSourceType commandSource)
{
	if (m_isAiDead)
		return;
	if (!m_object->isMobile())
		return;
	if (reinterpret_cast<const Rva0028B7AELeaGetter *>(m_object)->testBit8())
		return;

	m_stateMachine->clear();
	reinterpret_cast<Rva00263910 *>(this)->rva00263910(position, range, commandSource);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_ATTACK_MOVE_TO);

	Weapon *weapon = m_object->getCurrentWeapon(0);
	if (weapon)
	{
		weapon->m_shotsFired = 0;
		weapon->m_maxShotCount = maxShotsToFire;
	}

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playVoiceEnterStateAttackMove(position);
}

// Command 0x0D, slot 39, retail 0x0026BFD9 (AICommandParms::m_team at +0x1C):
// Zero Hour's privateAttackTeam behind BFME2's +0x370 bit-8 guard, entering
// state 0x17 and answering player and script orders with the attack voice at
// the goal object the team resolved to.
void AIUpdateInterface::privateAttackTeam(const Team *team, Int maxShotsToFire, CommandSourceType commandSource)
{
	if (reinterpret_cast<const Rva0028B7AELeaGetter *>(m_object)->testBit8())
		return;

	m_stateMachine->clear();
	reinterpret_cast<AIStateMachine *>(m_stateMachine)->setGoalTeam(team);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x17);

	Weapon *weapon = m_object->getCurrentWeapon(0);
	if (weapon)
	{
		weapon->m_shotsFired = 0;
		weapon->m_maxShotCount = maxShotsToFire;
	}

	Object *victim = m_stateMachine->getGoalObject();
	if (victim && (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT))
		playAttackVoiceResponse(victim);
}

// Command 0x2A, slot 72, retail 0x0026DE77 (AICommandParms' button at +0xB8):
// Zero Hour's privateCommandButton as BFME2 has it. The button is honoured
// only if it is in the owner's command set, and the one command type it
// handles here, 0x0E, idles the unit through its own AI.
void AIUpdateInterface::privateCommandButton(const CommandButton *commandButton, CommandSourceType commandSource)
{
	if (!commandButton)
		return;
	if (getObject()->isKindOf(KINDOF_PROJECTILE))
		return;
	Object *obj = getObject();
	if (!obj)
		return;
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai)
		return;

	const CommandSet *commandSet = TheControlBar->findCommandSet(obj->getCommandSetString());
	if (!commandSet)
		return;
	for (Int i = 0; i < 32; i++)
	{
		const CommandButton *button = commandSet->getCommandButton(i);
		if (commandButton == button && commandButton->m_commandType == 0x0E)
			reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(ai) + 0x20)->aiIdle(commandSource);
	}
}

// Command 0x28, slot 73, retail 0x00267E8E: privateCommandButtonPosition. BFME2
// walks the owner's command set for the button as privateCommandButton does,
// but no button type does anything with a position, so only the lookups
// remain.
void AIUpdateInterface::privateCommandButtonPosition(const CommandButton *commandButton, const Coord3D *pos, CommandSourceType commandSource)
{
	if (!commandButton)
		return;
	if (getObject()->isKindOf(KINDOF_PROJECTILE))
		return;
	Object *obj = getObject();
	if (!obj)
		return;
	if (!obj->m_ai)
		return;

	const CommandSet *commandSet = TheControlBar->findCommandSet(obj->getCommandSetString());
	if (!commandSet)
		return;
	for (Int i = 0; i < 32; i++)
	{
		const CommandButton *button = commandSet->getCommandButton(i);
		if (commandButton == button)
		{
		}
	}
}

// Command 0x42, slot 23, retail 0x0026D56C: command 0x01's move to an object
// without the AI-dead gate, into state 0x38. When the target carries KindOf
// bit 0xBF, its own AI is then handed us and the source through
// AICommandInterface 0x0026C486.
void AIUpdateInterface::bfmePrivateCommand42(Object *obj, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_blockedFrames = 0;
	m_isBlocked = false;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_38);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(obj->getPosition());

	if (obj->isKindOf(BFME_KINDOF_BF))
		reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(obj->m_ai) + 0x20)->rva0026C486(m_object, commandSource);
}

// Command 0x17, slot 48, retail 0x00264775: the enter order. A horde
// container takes the order through its own interface (a tail call); otherwise
// a mobile unit the ActionManager lets in without the capacity check enters
// state 0x0F with the target as its goal.
void AIUpdateInterface::privateEnter(Object *object, CommandSourceType commandSource)
{
	Object *me = getObject();
	ContainModuleInterface *contain = me->m_contain;
	if (contain)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde)
		{
			horde->enterObject(object, commandSource);
			return;
		}
	}

	if (!me->isMobile())
		return;

	if (reinterpret_cast<BFMEActionManager *>(TheActionManager)->canEnterObject(me, object, commandSource, DONT_CHECK_CAPACITY, 0, 0))
	{
		m_stateMachine->clear();
		m_stateMachine->setGoalObject(object);
		m_lastCommandSource = commandSource;
		m_stateMachine->setState((StateID)0x0f);
	}
}

// Command 0x24, slot 31, retail 0x0026BB5A: Zero Hour's privateFollowPath shape
// (AICommandParms::m_coords as the path, m_obj as the obstacle to ignore) with
// BFME2's range-taking goal position (FLT_MAX), the float from m_pos.x kept at
// +0x1A0, and state 0x36. An empty path does nothing.
void AIUpdateInterface::bfmePrivateCommand24(const Rva0035149F *path, Object *ignoreObject, float value, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;

	m_stateMachine->clear();
	if (path->size() > 0)
	{
		Coord3D pos;
		pos.set(&(*path)[path->size() - 1]);
		m_stateMachine->setGoalPosition(&pos, 3.402823466e+38F);
		if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
			playMoveVoiceResponse(&pos);
		reinterpret_cast<Rva00351759 *>(m_stateMachine)->rva00351759(*path);
		m_lastCommandSource = commandSource;
		ignoreObstacle(ignoreObject);
		m_pathFloat1A0 = value;
		m_stateMachine->setState((StateID)0x36);
	}
}

// Command 0x25, slot 32, retail 0x0026BC16: Zero Hour's privateFollowPath shape
// (AICommandParms::m_coords as the path, m_obj as the obstacle to ignore) with
// BFME2's range-taking goal position (FLT_MAX), the float from m_pos.x kept at
// +0x1A0, and state 0x3D. An empty path does nothing.
void AIUpdateInterface::bfmePrivateCommand25(const Rva0035149F *path, Object *ignoreObject, float value, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;

	m_stateMachine->clear();
	if (path->size() > 0)
	{
		Coord3D pos;
		pos.set(&(*path)[path->size() - 1]);
		m_stateMachine->setGoalPosition(&pos, 3.402823466e+38F);
		if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
			playMoveVoiceResponse(&pos);
		reinterpret_cast<Rva00351759 *>(m_stateMachine)->rva00351759(*path);
		m_lastCommandSource = commandSource;
		ignoreObstacle(ignoreObject);
		m_pathFloat1A0 = value;
		m_stateMachine->setState((StateID)0x3d);
	}
}

// Commands 0x09 and 0x0A, slot 30, retail 0x0026BA84: Zero Hour's
// privateFollowPath (aiDoCommand passes exitProduction FALSE for 0x09, TRUE for
// 0x0A) with BFME2's range-taking goal position (FLT_MAX), and state 0x43 for
// an owner Object 0x0028ECDB accepts at its own position.
void AIUpdateInterface::privateFollowPath(const Rva0035149F *path, Object *ignoreObject, CommandSourceType commandSource, Bool exitProduction)
{
	Object *obj = getObject();
	if (!obj->isMobile())
		return;

	m_stateMachine->clear();
	if (path->size() > 0)
	{
		Coord3D pos;
		pos.set(&(*path)[path->size() - 1]);
		m_stateMachine->setGoalPosition(&pos, 3.402823466e+38F);
		if (!exitProduction && (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT))
			playMoveVoiceResponse(&pos);
	}
	reinterpret_cast<Rva00351759 *>(m_stateMachine)->rva00351759(*path);
	m_lastCommandSource = commandSource;
	ignoreObstacle(ignoreObject);

	if (reinterpret_cast<Rva0028ECDBHost *>(obj)->rva0028ECDB(const_cast<Coord3D *>(obj->getPosition())))
		m_stateMachine->setState((StateID)0x43);
	else if (exitProduction)
		m_stateMachine->setState((StateID)7);
	else
		m_stateMachine->setState((StateID)6);
}

// Command 0x4E, slot 13, retail 0x0026B487: BFME2's privateMoveToPosition,
// taking AICommandParms::m_pos and a goal range. An AI-sourced order to a unit
// that is not idle (slot 110) becomes a temporary move (state 1 for
// g_Va00DBA4E4 * 20 frames through 0x0033FCE1) that keeps the current state
// machine; otherwise it is the ordinary move into state 1 with the move voice.
void AIUpdateInterface::privateMoveToPosition(const Coord3D *position, float range, CommandSourceType commandSource)
{
	Object *obj = getObject();
	if (!obj->isMobile())
		return;
	if (reinterpret_cast<const Rva0028B7AELeaGetter *>(obj)->testBit8())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	if (!reinterpret_cast<AIUpdateSlot110 *>(this)->isIdle() && commandSource == CMD_FROM_AI)
	{
		reinterpret_cast<Rva0033FCC8 *>(m_stateMachine)->rva0033FCC8();
		reinterpret_cast<Rva00263910 *>(this)->rva00263910(position, range, commandSource);
		m_blockedFrames = 0;
		m_isBlocked = false;
		reinterpret_cast<BfmeSubVfn1A6 *>(m_stateMachine)->notify(BFME_AI_MOVE_TO, (void *)(g_Va00DBA4E4 * 20));
		return;
	}

	m_stateMachine->clear();
	reinterpret_cast<Rva00263910 *>(this)->rva00263910(position, range, commandSource);
	m_blockedFrames = 0;
	m_isBlocked = false;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_MOVE_TO);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(position);
}

// Command 0x52, slot 17, retail 0x0026B567 (AICommandParms::m_pos and
// m_intValue): a move to a position. When TheAI's pathfinder accepts the
// owner where it stands (0x002EE7EE) and the order is within 100 of it, the
// owner's own position is the goal. State 0x4D with a value, 0x40 without,
// and the move voice for player and script orders.
void AIUpdateInterface::privateMoveToPositionAmphibious(const Coord3D *position, Int value, CommandSourceType commandSource)
{
	Object *obj = getObject();
	const Coord3D *objPos = obj->getPosition();
	Coord3D adjusted;
	if (TheAI->pathfinder()->getClosestPointOnLand(objPos, obj, &adjusted))
	{
		Coord3D diff;
		diff.set(position);
		diff.sub(objPos);
		if (diff.length() < 100.0f)
			position = objPos;
	}

	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_isBlocked = false;
	m_lastCommandSource = commandSource;
	if (value)
		m_stateMachine->setState((StateID)0x4d);
	else
		m_stateMachine->setState((StateID)0x40);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(position);
}

// Command 0x05, slot 24, retail 0x0026D5FB: the BFME1 donor's privateIdle
// (reference/open-bfme-1 AIUpdateInterfacePrivateIdle.cpp). Projectiles and an
// owner with bit 8 of its +0x370 flag word set are left alone. A container
// idles its members when it is no horde or is itself busy; BFME2 spares a
// BFME_KINDOF_6D member that is not busy. A player's idle to a mobile owner
// that is not status 0x26 guards where it stands instead.
void AIUpdateInterface::privateIdle(CommandSourceType commandSource)
{
	if (getObject()->isKindOf(KINDOF_PROJECTILE))
		return;
	if (reinterpret_cast<const Rva0028B7AELeaGetter *>(getObject())->testBit8())
		return;

	ContainModuleInterface *contain = getObject()->getContain();
	Bool idleContained = false;
	if (contain)
	{
		if (contain->getHordeContainInterface() == 0)
			idleContained = true;
		if (reinterpret_cast<AIUpdateSlot110 *>(this)->isAttacking() || getCurrentVictim() != 0)
			idleContained = true;

		if (idleContained)
		{
			BfmeContainedRange items = contain->getContainedItemsList();
			for (BfmeContainedNode *node = items.m_list->m_head->m_next;
				node != items.m_list->m_head; node = node->m_next)
			{
				Object *member = node->m_object;
				AIUpdateInterface *ai = member ? member->getAI() : 0;
				if (!ai)
					continue;
				if (!member->isKindOf(BFME_KINDOF_6D)
					|| reinterpret_cast<AIUpdateSlot110 *>(ai)->isAttacking()
					|| ai->getCurrentVictim() != 0)
					reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(ai) + 0x20)->aiIdle(commandSource);
			}
		}
	}

	if (commandSource == CMD_FROM_PLAYER && getObject()->isMobile())
	{
		Object *obj = getObject();
		if (!obj->testStatus(BFME_OBJECT_STATUS_26) && !obj->isKindOf(KINDOF_PROJECTILE))
		{
			reinterpret_cast<AIUpdateSlot63 *>(this)->privateGuardPosition(obj->getPosition(), GUARDMODE_NORMAL, commandSource);
			return;
		}
	}

	m_stateMachine->clear();
	m_stateMachine->setState((StateID)0);
	getObject()->clearModelConditionState(BFME_MODELCONDITION_MOVING);
	getObject()->clearModelConditionState(BFME_MODELCONDITION_BACKING_UP);
	getObject()->rva0028DB3C();
	m_lastCommandSource = commandSource;
}

// Command 0x0E, slot 40, retail 0x0026DB1A: Zero Hour's privateAttackPosition
// (AIUpdate.cpp) behind two BFME2 refusals (a player's order to an owner with
// bit 8 of its +0x370 word set; an owner that isOffMap()). BFME2 also
// skips an order to the spot it is already attacking (state 9 with the goal
// within 0.0001 on each axis) and answers player and script orders with the
// attack voice.
void AIUpdateInterface::privateAttackPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType commandSource)
{
	if (reinterpret_cast<const Rva0028B7AELeaGetter *>(getObject())->testBit8() && commandSource == CMD_FROM_PLAYER)
		return;
	if (getObject()->isOffMap())
		return;

	Coord3D localPos;
	localPos.set(pos);
	pos = 0;

	Weapon *weapon = getObject()->getCurrentWeapon(0);
	float continueRange = weapon ? weapon->getContinueAttackRange() : 0.0f;
	if (continueRange > 0.0f)
	{
		getObject()->setStatus(OBJECT_STATUS_IGNORING_STEALTH, true);
		// The filters' scope closes before the status is cleared: retail
		// leaves the unwind state right after the search.
		Object *victim;
		{
			PartitionFilterSameMapStatus filterMapStatus(getObject());
			PartitionFilterPossibleToAttack filterAttack(ATTACK_NEW_TARGET, getObject(), commandSource);
			victim = ThePartitionManager->getClosestObject(&localPos, continueRange, FROM_CENTER_2D, filterAttack.link(&filterMapStatus));
		}
		getObject()->setStatus(OBJECT_STATUS_IGNORING_STEALTH, false);

		if (victim)
		{
			reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(this) + 0x20)->rva0026C2D9(victim, maxShotsToFire, commandSource);
			return;
		}
		maxShotsToFire = 1;
	}

	if (weapon && weapon->isContactWeapon() && !isPathAvailable(&localPos))
	{
		FindPositionOptions fpOptions;
		fpOptions.minRadius = 0.0f;
		fpOptions.maxRadius = 100.0f;
		fpOptions.sourceToPathToDest = getObject();
		Coord3D tmp;
		if (PartitionManager::findPositionAround(&localPos, &fpOptions, &tmp))
			localPos = tmp;
	}

	StateMachine *sm = m_stateMachine;
	if (sm->getCurrentStateID() == BFME_AI_ATTACK_POSITION)
	{
		const Coord3D *goal = sm->getGoalPosition();
		float dx = goal->x - localPos.x;
		if (dx < 0.0001f && dx > -0.0001f)
		{
			float dy = goal->y - localPos.y;
			if (dy < 0.0001f && dy > -0.0001f)
			{
				float dz = goal->z - localPos.z;
				if (dz < 0.0001f && dz > -0.0001f)
					return;
			}
		}
	}

	sm->clear();
	destroyPath();
	setGoalPositionClipped(&localPos, commandSource);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_ATTACK_POSITION);
	m_stateMachine->setGoalObject(0);

	weapon = getObject()->getCurrentWeapon(0);
	if (weapon)
		weapon->setMaxShotCount(maxShotsToFire);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playAttackVoiceResponse(&localPos);
}

// Command 0x35, slot 33, retail 0x0026E074: the BFME1 donor's
// privateFollowPathAppend (open-bfme-1 AIUpdateFollowPathAppend.cpp). A moving
// unit (isMoving, or m_waitingForPath at +0x3B1) not in state 0x10 appends to the goal
// path of a running path state (6, or BFME2's 0x43), or else follows a fresh
// path from its goal position; a stopped one follows a one-point path and
// answers player and script orders with the move voice.
void AIUpdateInterface::privateFollowPathAppend(const Coord3D *pos, CommandSourceType commandSource)
{
	Bool effectivelyMoving = isMoving() || m_waitingForPath;
	if (effectivelyMoving && m_stateMachine->getCurrentStateID() == (StateID)0x10)
		effectivelyMoving = false;

	if ((getCurrentStateID() == 6 || getCurrentStateID() == 0x43)
		&& (Int)m_stateMachine->m_goalPath.size() > 0 && effectivelyMoving)
	{
		reinterpret_cast<AIStateMachine *>(m_stateMachine)->addToGoalPath(pos);
	}
	else if (effectivelyMoving)
	{
		_STL::vector<Coord3D> path;
		path.push_back(m_stateMachine->m_goalPosition);
		path.push_back(*pos);
		reinterpret_cast<AIUpdateSlot30 *>(this)->privateFollowPath(reinterpret_cast<const Rva0035149F *>(&path), 0, commandSource, false);
	}
	else
	{
		_STL::vector<Coord3D> path;
		path.push_back(*pos);
		reinterpret_cast<AIUpdateSlot30 *>(this)->privateFollowPath(reinterpret_cast<const Rva0035149F *>(&path), 0, commandSource, false);
		if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
			playMoveVoiceResponse(pos);
	}
}

// Command 0x34, slot 81, retail 0x0026D765: Zero Hour's
// privateMoveAwayFromUnit with BFME2's position argument and additions. An
// owner with status 0x59 that is idle only lets the unit path through it; an
// owner inside a horde container that is not attacking hands the order up.
// Otherwise the Zero Hour body follows (the move-out-of-the-way state is 0x1A
// here, and LOGICFRAMES_PER_SECOND is g_Va00DBA4E4), except that the unit's
// path is asked for even when it is null, the locomotor is prepared, a unit
// whose goal already lies within the other unit's radius of the order point
// enters the state outright, and moveAllies is gated on several flags.
void AIUpdateInterface::privateMoveAwayFromUnit(Object *unit, const Coord3D *pos, CommandSourceType commandSource)
{
	if (!unit)
		return;
	if (m_isAiDead || !getObject()->isMobile() || !reinterpret_cast<AIUpdateSlot110 *>(this)->isAllowedToMoveAwayFromUnit())
		return;

	Object *me = getObject();
	if (me->testStatus((ObjectStatusTypes)0x59) && m_stateMachine->getCurrentStateID() == (StateID)0)
	{
		if (unit->getAI())
			unit->getAI()->m_canPathThroughUnits = true;
		return;
	}

	Object *container = me->m_containedBy;
	if (container)
	{
		HordeContainInterface *horde = container->getContain() ? container->getContain()->getHordeContainInterface() : 0;
		if (horde && container->getAI() && !reinterpret_cast<AIUpdateSlot110 *>(container->getAI())->isAttacking())
		{
			reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(container->getAI()) + 0x20)->rva0026C411(unit, pos, commandSource);
			reinterpret_cast<HordeContainSlot116 *>(horde)->slot116();
			return;
		}
	}

	ObjectID id = unit->getID();
	if (m_stateMachine->getTemporaryState() == (StateID)0x1A || m_stateMachine->getCurrentStateID() == (StateID)0x1A)
	{
		if (m_moveOutOfWay1 == id)
		{
			if (m_isBlocked)
				setIgnoreCollisionTime(g_Va00DBA4E4 * 2);
			return;
		}
		if (m_moveOutOfWay2 == id)
		{
			if (m_isBlocked)
				setIgnoreCollisionTime(g_Va00DBA4E4 * 2);
			return;
		}
	}
	m_moveOutOfWay2 = m_moveOutOfWay1;
	m_moveOutOfWay1 = id;
	Object *obj2 = TheGameLogic->findObjectByID(m_moveOutOfWay2);
	Path *path2 = 0;
	if (obj2 && obj2->getAI())
		path2 = obj2->getAI()->getPath();

	Path *unitPath = 0;
	if (unit->getAI())
		unitPath = unit->getAI()->getPath();

	m_bfmeFindingMoveAwayPath = true;
	Path *newPath = TheAI->pathfinder()->getMoveAwayFromPath(getObject(), unit, unitPath, obj2, path2);
	if (newPath == 0 && !m_canPathThroughUnits)
	{
		m_canPathThroughUnits = true;
		newPath = TheAI->pathfinder()->getMoveAwayFromPath(getObject(), unit, unitPath, obj2, path2);
	}
	m_bfmeFindingMoveAwayPath = false;

	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	if (newPath)
	{
		StateMachine *sm = m_stateMachine;
		const Coord3D *pathStart = sm->m_goalPath.begin();
		Int n = sm->m_goalPath.end() - pathStart;
		Coord3D goal;
		goal.set(sm->getGoalPosition());
		if (n > 0)
			goal = pathStart[n - 1];

		Bool close;
		goal.sub(pos);
		float r = unit->m_bfmeRadiusB8;
		if (goal.x * goal.x + goal.y * goal.y + goal.z * goal.z < r * r)
			close = true;
		else
		{
			close = false;
			reinterpret_cast<Rva0033FCC8 *>(sm)->rva0033FCC8();
		}

		destroyPath();
		m_path = newPath;
		wakeUpNow();
		if (close)
			m_stateMachine->setState((StateID)0x1A);
		else
			reinterpret_cast<BfmeSubVfn1A6 *>(m_stateMachine)->notify(0x1A, (void *)(g_Va00DBA4E4 * 10));

		if (m_path)
		{
			Bool moveAllies;
			if (m_path->m_bfmeFlag0D && !getObject()->isKindOf(KINDOF_NO_COLLIDE))
				moveAllies = true;
			else
				moveAllies = false;
			Object *obj = getObject();
			AI *ai = TheAI;
			if (obj->isKindOf(BFME_KINDOF_6D) && !ai->getAiData()->m_bfmeFlagB9)
				moveAllies = false;
			if (obj->m_template->m_bfmeFlag614 || obj->isKindOf(BFME_KINDOF_7D))
				moveAllies = true;
			if (obj->testStatus((ObjectStatusTypes)0x39) || obj->testStatus((ObjectStatusTypes)0x32) || obj->rva0006F039(0x84))
				moveAllies = false;
			if (moveAllies)
				ai->pathfinder()->moveAllies(obj, m_path, obj->rva0028CE7B() >= 4);
		}
	}
}

// AIUpdate vtable 0x00C47B98 slot 117, retail 0x00262F19: Zero Hour's
// doQuickExit. The temporary-state setter is 0x0033FCC8 then 0x0033FCE1, as
// in privateMoveToPosition; the exit-production path state is 7.
void AIUpdateInterface::doQuickExit(const _STL::vector<Coord3D> *path)
{
	Bool locked = m_stateMachine->m_locked;
	m_stateMachine->m_locked = false;

	reinterpret_cast<Rva0033FCC8 *>(m_stateMachine)->rva0033FCC8();
	reinterpret_cast<Rva00351759 *>(m_stateMachine)->rva00351759(*reinterpret_cast<const Rva0035149F *>(path));

	reinterpret_cast<BfmeSubVfn1A6 *>(m_stateMachine)->notify(7, (void *)(g_Va00DBA4E4 * 10));
	if (locked)
		m_stateMachine->m_locked = true;
}

// AIUpdate vtable 0x00C47B98 slots 104 and 105, retail 0x0026E988 and
// 0x0026E999: null-safe forwarders to the state machine's slots 9 and 10
// (+0x24, +0x28), answering 0 without a machine. Neither Zero Hour nor the
// BFME1 donor has them at these slots; they keep their addresses as names.
Int AIUpdateInterface::rva0026E988()
{
	if (m_stateMachine)
		return m_stateMachine->slot24();
	return 0;
}

Int AIUpdateInterface::rva0026E999()
{
	if (m_stateMachine)
		return m_stateMachine->slot28();
	return 0;
}

// AIUpdate vtable 0x00C47B98 slot 5, retail 0x002625C8: Zero Hour's
// onObjectCreated, which builds the state machine on first use (slot 150,
// makeStateMachine) and enters its default state (machine slot 7).
void AIUpdateInterface::onObjectCreated()
{
	if (m_stateMachine == 0)
	{
		m_stateMachine = reinterpret_cast<AIUpdateSlot150 *>(this)->makeStateMachine();
		m_stateMachine->initDefaultState();
	}
}

// AIUpdate vtable 0x00C47B98 slot 112, retail 0x00264656: Zero Hour's
// isClearingMines, between isAttacking (slot 111) as Zero Hour orders them.
// Status 0x16 is OBJECT_STATUS_IS_ATTACKING and anti-mask bit 0x10
// WEAPON_ANTI_MINE (Zero Hour's values; the body tests exactly these).
Bool AIUpdateInterface::isClearingMines() const
{
	Object *obj = getObject();
	if (!obj->testStatus((ObjectStatusTypes)0x16))
		return false;

	const Weapon *weapon = obj->getCurrentWeapon(0);
	if (!weapon)
		return false;

	if ((weapon->getAntiMask() & 0x10) == 0)
		return false;

	return true;
}

// AIUpdate vtable 0x00C47B98 slot 137, retail 0x0026731C: Zero Hour's
// isDoingGroundMovement after the locomotor-goal setters (slots 131-136) as
// Zero Hour orders them, without the unmanned-helicopter and allowed-to-fall
// exceptions. Disabled bit 3 is DISABLED_HELD.
Bool AIUpdateInterface::isDoingGroundMovement() const
{
	if (m_validLocomotorSurfaces == LOCOMOTORSURFACE_AIR)
		return false;

	if (m_curLocomotor == 0)
		return false;

	if (m_curLocomotor->getLegalSurfaces() & LOCOMOTORSURFACE_AIR)
		return false;

	if (getObject()->isDisabledByType(3))
		return false;

	return true;
}

// AIUpdate vtable 0x00C47B98 slot 148, retail 0x0026734C: Zero Hour's
// isAllowedToRespondToAiCommands (isEffectivelyDead is bit 0 of the owner's
// m_privateStatus, as in Zero Hour); the sleep exception covers commands
// 0x36 and 0x53 (Zero Hour's AICMD_MOVE_TO_POSITION_EVEN_IF_SLEEPING is one
// command). BFME2 drops the forbid-player-commands module flag and adds the
// +0x3C5 / +0x3C6 refusals, a held temporary state, and player orders 0 and 1
// while m_bfmeFloat1F8 is zero.
Bool AIUpdateInterface::isAllowedToRespondToAiCommands(const AICommandParms *parms) const
{
	if (getObject()->isEffectivelyDead())
		return false;

	UnsignedInt moodParms = getMoodMatrixValue();
	if ((moodParms & MM_Controller_AI) && (moodParms & MM_Mood_Sleep) && parms->m_cmd != 0x36 && parms->m_cmd != 0x53)
		return false;

	CommandSourceType source = parms->m_cmdSource;
	if (source == CMD_FROM_PLAYER && (m_bfmeIgnorePlayerCommands || getObject()->rva0006F039(0xCE)))
		return false;
	if (m_bfmeIgnoreScriptCommands && source == CMD_FROM_SCRIPT)
		return false;
	if (m_stateMachine->m_temporaryState && m_stateMachine->m_temporaryStateFrames == -1)
		return false;
	if (source == CMD_FROM_PLAYER && m_bfmeFloat1F8 == 0.0f && (parms->m_cmd == 0 || parms->m_cmd == 1))
		return false;

	return true;
}

// AIUpdate vtable 0x00C47B98 slot 127 (after construct, slot 126, as Zero
// Hour orders them), retail 0x00264EF2: Zero Hour's getEnterTarget over
// BFME2's state ids. The goal object counts in states 0x0F, 0x31, 0x18,
// 0x2B, 0x19 and 0x34, and in state 0x38 when it is a BFME_KINDOF_BF object.
Object *AIUpdateInterface::getEnterTarget()
{
	Int stateType = getCurrentStateID();
	Object *goal = m_stateMachine->getGoalObject();
	if (goal && stateType != 0x0F && stateType != 0x31 && stateType != 0x18
		&& stateType != 0x2B && stateType != 0x19 && stateType != 0x34)
	{
		if (!goal->isKindOf(BFME_KINDOF_BF) || stateType != 0x38)
			goal = 0;
	}
	return goal;
}

// AIUpdate vtable 0x00C47B98 slot 142, retail 0x00268B20: Zero Hour's
// chooseLocomotorSet (LOCOMOTORSET_NORMAL 0 becomes NORMAL_UPGRADED 1 with
// upgraded locomotors), refusing a change while +0x3C9 is set and storing the
// template's float for the new set at +0x1F8 on success.
Bool AIUpdateInterface::chooseLocomotorSet(Int wst)
{
	if (wst == 0 && m_upgradedLocomotors)
		wst = 1;

	if (wst == m_curLocomotorSet)
		return true;

	if (m_bfmeLocomotorSetLocked)
		return false;

	if (chooseLocomotorSetExplicit(wst))
	{
		chooseGoodLocomotorFromCurrentSet();
		m_bfmeFloat1F8 = getObject()->m_template->rva0033C259(m_curLocomotorSet);
		return true;
	}

	return false;
}

// Slot 150 of eight AIUpdate-family vtables (0x00C4CA00 first; 0x00C47B98
// overrides it with 0x0047EC69), retail 0x00262513:
// Zero Hour's makeStateMachine, newInstance(AIStateMachine)(getObject(),
// "AIUpdateInterfaceStateMachine"), with BFME2's key in place of the name.
AIStateMachine *AIUpdateInterface::makeStateMachine()
{
	return new AIStateMachine(getObject(), 0x4A9A0E38);
}

// AIUpdate vtable 0x00C47B98 slot 103, retail 0x0026D478: Zero Hour's
// joinTeam. BFME2 looks for the teammate first and only then resets the
// locomotor set (slot 142) and the state machine; the rest is Zero Hour's: an
// idle teammate draws a move to its position, otherwise its goal object or
// goal position is taken and the current state (0x00260DED) re-entered.
void AIUpdateInterface::joinTeam()
{
	if (m_isAiDead)
		return;

	if (!getObject()->isMobile())
		return;

	Object *obj = getObject();
	Object *other = 0;
	for (DLINK_ITERATOR<Object> iter = obj->getTeam()->iterate_TeamMemberList(); !iter.done(); iter.advance())
	{
		Object *anObj = iter.cur();
		if (obj == anObj)
			continue;
		if (anObj->getAI() && !anObj->isDisabledByType(3))
		{
			other = anObj;
			break;
		}
	}

	if (other)
	{
		reinterpret_cast<AIUpdateSlot142 *>(this)->chooseLocomotorSet(0);
		m_stateMachine->clear();
		reinterpret_cast<AIStateMachine *>(m_stateMachine)->setGoalWaypoint(0);

		AIUpdateInterface *ai = other->getAI();
		if (reinterpret_cast<AIUpdateSlot110 *>(ai)->isIdle())
		{
			reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(this) + 0x20)->aiMoveToPosition(other->getPosition(), CMD_FROM_AI);
			return;
		}
		if (ai->getGoalObject())
			getStateMachine()->setGoalObject(ai->getGoalObject());
		else
			getStateMachine()->setGoalPosition(ai->getGoalPosition());

		Int state = rva00260DED();
		m_lastCommandSource = CMD_FROM_AI;
		m_stateMachine->setState((StateID)state);
	}
}

// Retail 0x0026412B, AIUpdate vtable 0x00BFA480 slot 139 (+0x22C). Asks the
// pathfinder about the owner, drops the current path, and asks for a new one
// to `destination`; when one comes back it sets locomotor goal type 4 with
// the destination. Goal type 4 is beyond Zero Hour's LocoGoalType (whose
// largest is 3); the identity of this slot is not evidenced.
void AIUpdateInterface::micropathToPosition(const Coord3D *destination)
{
	Object *obj = getObject();
	TheAI->pathfinder()->rva002EF2A6(obj);
	destroyPath();
	m_path = TheAI->pathfinder()->GetHordeUnitPath(obj, destination);
	if (m_path)
	{
		m_locomotorGoalType = 4;
		m_locomotorGoalData = *destination;
	}
}

// Retail 0x00263404, AIUpdate vtable 0x00BFA480 slot 141 (+0x234). While the
// +0x3DC word is set, walks the current path ten units at a time until the
// point is past the last usable node or the pathfinder accepts it for the
// owner; at a usable node it asks `source` for something to hand the path,
// and when it gets one it clears the blocked state and passes the word to
// 0x00262989. The word is cleared either way. Identity not evidenced.
void AIUpdateInterface::rva00263404(Rva00263404Source *source)
{
	if (m_bfmeWord3DC == 0)
		return;
	Path *path = m_path;
	if (path)
	{
		Object *obj = getObject();
		float dist = 0.0f;
		Rva003642DFResult info;
		do
		{
			dist += 10.0f;
			info = path->rva003642DF(dist);
			if (!info.m_node || !info.m_node->m_bfmeWord08)
				break;
		} while (!TheAI->pathfinder()->rva002ECC0D(obj, &info.m_pos));
		if (info.m_node && info.m_node->m_bfmeWord08)
		{
			Rva00263404Product *product = source->slot6(obj, &info.m_pos, info.m_node);
			if (product)
			{
				path->rva00365DF0(product);
				m_blockedFrames = 0;
				m_isBlocked = false;
				rva00262989(m_bfmeWord3DC);
			}
		}
	}
	m_bfmeWord3DC = 0;
}

// Retail 0x002686A4, AIUpdate vtable 0x00BFA480 slot 1. Zero Hour's
// loadPostProcess, BFME2's shape: the attack info is resolved here from its
// saved name, the locomotor set is always re-chosen when one is set (Zero
// Hour also asks m_fixLocoInPostProcess), and a resting owner is
// re-registered through Object's helpers instead of the pathfinder; a moving
// one is left alone, and the owner then goes to the 0x00E01DBC global.
void AIUpdateInterface::loadPostProcess()
{
	// StringBase's out-of-line isEmpty (0x00001E2F), as retail calls it.
	if (!((const StringBase<char> &)m_attackInfoName).isEmpty())
		m_attackInfo = TheScriptEngine->getAttackInfo(m_attackInfoName);

	reinterpret_cast<UpdateModule *>(this)->UpdateModule::loadPostProcess();

	if (m_curLocomotorSet != -1)
	{
		Int lst = m_curLocomotorSet;
		m_curLocomotorSet = -1;
		reinterpret_cast<AIUpdateSlot142 *>(this)->chooseLocomotorSet(lst);
	}

	Object *obj = getObject();
	if (!isMoving())
	{
		Int value = obj->rva0028B511();
		obj->rva0028ACEE(obj->getPosition(), value);
		obj->rva0028AD7C();
		obj->rva0028B525(value);
	}
	reinterpret_cast<LuaDrawableState *>(TheLuaScriptEngine)->rva00333E5B(obj);
}

// Retail 0x0026E9B8, AIUpdate vtable 0x00C47B98 slot 126 (shared by eleven
// AIUpdate tables): the base construct builds nothing.
Object *AIUpdateInterface::construct(const ThingTemplate *what, const Coord3D *pos, float angle,
	Player *owningPlayer, Bool isRebuild, Int bfmeArg6)
{
	return 0;
}

// Retail 0x00267266, AIUpdate vtable 0x00BFA480 slot 134 (+0x218). Hands the
// point to slot 133, starts a path at the owner when there is none (flagging
// it at +0x0C), then gives the path `value` and appends the point on the
// terrain's layer for it with `value`. Identity not evidenced.
void AIUpdateInterface::appendPositionToLocomotorPath(const Coord3D &pos, Int value)
{
	reinterpret_cast<AIUpdateSlot133 *>(this)->setLocomotorGoalPositionExplicitSmart(pos);
	if (!m_path)
	{
		m_path = new Path;
		Object *obj = getObject();
		m_path->rva002655E3(obj->getPosition(), (PathfindLayerEnum)obj->rva0028B511(), 0x7fffffff);
		m_path->m_bfmeFlag0C = true;
	}
	m_path->SetLastNodePortal(value);
	m_path->rva002655E3(&pos, TheTerrainLogic->getLayerForDestination(getObject(), &pos), value);
}
