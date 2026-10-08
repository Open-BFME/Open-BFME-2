// ?isLocationClearOfObjects@BuildAssistant@@UAE_NPBUCoord3D@@PBVThingTemplate@@MPAVObject@@IPAVPlayer@@_N@Z
// partial score=0.83007 date=2026-10-09
// cl: /G7 /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /EHs /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// BuildAssistant.cpp -- BuildAssistant members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function;
// retail supplies the bytes. Zero Hour's isRemovableForConstruction
// (Common/System/BuildAssistant.cpp) with BFME2's second never-removable kind.
//
// Layout (target evidence): Object +0x04 is the thing template, whose kind-of
// bits start at +0x108; the effectively-dead flag is bit 0 at Object +0x438.
// Kind indices are read off the tested bytes: 89 (inert, +0x113 bit 1),
// 152 (+0x11B bit 0), 6 (shrubbery, +0x108 bit 6) and 51 (cleared by build,
// +0x10E bit 3); their BFME2 names are not recovered.
//
// canMakeUnit and its countInProduction callback follow Generals'
// BuildAssistant.cpp (ProductionCountData, countObjectsByThingTemplate and
// iterateObjects); WB's canMakeUnit (assert "Needs an AIUpdateInterface if a
// DOZER", BuildAssistant.cpp:3302) supplies BFME2's additions: a revival
// index argument served by the Player +0x738 revival tracker, the Player +0x60
// limit check that returns 7, and a dozer amount added to the money.
// Target layouts: Player +0x90 Money (+0x94 amount), Object +0x258 AI,
// Object +0x437 script status, ThingTemplate +0x5E0 max simultaneous (word).
// isKindOf returns the masked word (not a Bool) because retail loads the 156
// mask once and tests both templates against it. The two leading NULL checks
// are separate statements as in WB (two "return 1" blocks); joined with ||
// they share one return and retail's late push ebx no longer reproduces.
//
// buildObjectNow follows Zero Hour's (same file) with the line-build kinds
// tested inline and BFME2's changes read off retail and WB's body: only a
// non-dozer builder of neither kind 30 nor 149 clears and moves the site (the
// move result is ignored); a kind-104 builder hands the build to the
// interface WB asserts as getFoundationAIInterface (rowed rva0028BCF4, vslot
// 7, same arguments as the AI's construct, vslot 126); the new object takes
// the builder's +0x45C value (GameLogic::rva0023D0C2), its pathfind layer
// unless kind 2 and a pathfind map entry unless kind 189; a kind-156 builder
// skips onStructureConstructionComplete; and units announce themselves
#include <list>
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "Code/Libraries/Include/Lib/Coord2D.h"
#ifndef CANONICAL_COORD3D_H
#define CANONICAL_COORD3D_H
struct Coord3D {
    float x;
    float y;
    float z;
    float length() const;
    float GetLength() const;
    void normalize();
    bool operator==(const Coord3D &r);
    float GetLengthSqrd() const;
};
#endif // CANONICAL_COORD3D_H
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef float Real;
typedef int Color;
#define GameMakeColor(r, g, b, a) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))
#ifndef NULL
#define NULL 0
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
enum KindOfType
{
	KINDOF_2 = 2,
	KINDOF_SHRUBBERY = 6,
	KINDOF_STRUCTURE = 7,
	KINDOF_12 = 12,
	KINDOF_DOZER = 14,
	KINDOF_15 = 15,
	KINDOF_30 = 30,
	KINDOF_CLEARED_BY_BUILD = 51,
	KINDOF_58 = 58,
	KINDOF_85 = 85,		// ZH's KINDOF_CANNOT_BUILD_NEAR_SUPPLIES role
	KINDOF_86 = 86,		// ZH's KINDOF_SUPPLY_SOURCE role
	KINDOF_INERT = 89,
	KINDOF_104 = 104,
	KINDOF_120 = 120,
	KINDOF_149 = 149,
	KINDOF_152 = 152,
	KINDOF_NOT_SELLABLE = 154,
	KINDOF_156 = 156,
	KINDOF_157 = 157,
	KINDOF_188 = 188,
	KINDOF_189 = 189
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_UNSELECTABLE = 3,
	OBJECT_STATUS_SOLD = 19,
	OBJECT_STATUS_98 = 98
};
enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};
enum DeathType
{
	DEATH_8 = 8					// BFME2's name not recovered
};
enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED
};
typedef UnsignedInt PlayerMaskType;
const PlayerMaskType PLAYERMASK_ALL = 0xFFFFF;
extern float g_00E027C4;
#define TOTAL_FRAMES_TO_SELL_OBJECT g_00E027C4
enum CommandSourceType
{
	CMD_FROM_PLAYER,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};
enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1,
	LAYER_17 = 17			// from here up only KINDOF_189 builds
};
enum CanMakeType
{
	CANMAKE_OK,
	CANMAKE_NO_PREREQ,
	CANMAKE_NO_MONEY,
	CANMAKE_FACTORY_IS_DISABLED,
	CANMAKE_QUEUE_FULL,
	CANMAKE_PARKING_PLACES_FULL,
	CANMAKE_MAXED_OUT_FOR_PLAYER,
	CANMAKE_7						// BFME2: the Player +0x60 check refused
};
enum LegalBuildCode
{
	LBC_OK = 0,
	LBC_NO_CLEAR_PATH = 2,
	LBC_TOO_CLOSE_TO_SUPPLIES = 3,
	LBC_NOT_FLAT_ENOUGH = 5,
	LBC_RESTRICTED_TERRAIN = 6,
	LBC_OBJECTS_IN_THE_WAY = 8,
	LBC_9 = 9
};
enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_3 = 3,
	CELLSHROUD_4 = 4
};
enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_DISABLED = 0x01,
	OBJECT_STATUS_SCRIPT_UNPOWERED = 0x02
};
enum GUICommandType
{
	GUI_COMMAND_DOZER_CONSTRUCT = 1,
	GUI_COMMAND_UNIT_BUILD = 3,
	GUI_COMMAND_46 = 46,
	GUI_COMMAND_53 = 53
};
enum CommandOption
{
	NEED_UPGRADE = 0x40
};
enum UpgradeType
{
	UPGRADE_TYPE_PLAYER,
	UPGRADE_TYPE_OBJECT
};
enum { MAX_COMMANDS_PER_SET = 32 };
class Player;
class Object;
struct Region3D
{
	Coord3D lo, hi;
	Bool isInRegionNoZ( const Coord3D *query ) const
	{
		return (lo.x < query->x) && (query->x < hi.x)
				&& (lo.y < query->y) && (query->y < hi.y);
	}
};
class Team;
struct Rva002A7557In;
class Drawable
{
public:
	void setAnimationLoopDuration(UnsignedInt numFrames);
};
enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};
class GeometryInfo
{
public:
	GeometryInfo(GeometryType type, Bool isSmall, Real height, Real majorRadius, Real minorRadius);
	GeometryInfo(const GeometryInfo &that);
	virtual ~GeometryInfo();
	Real getMajorRadius() const { return m_majorRadius; }
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
	Real getMaxHeightAbovePosition() const;
	void expandFootprint(Real radius);
	bool bfmeIntersects(const Coord3D &pos, Real angle, const GeometryInfo &other, const Coord3D &otherPos, Real otherAngle) const;
private:
	unsigned char m_pad04[0x10 - 0x04];
	Real m_majorRadius;		// +0x10
	Real m_boundingCircleRadius;	// +0x14
	unsigned char m_pad18[0x5C - 0x18];
};
class ModuleData;
class Rva0033B427Data
{
public:
	unsigned char m_pad00[0x30];
	Real m_range;				// +0x30
};
class Rva0033B3D7Data
{
public:
	unsigned char m_pad00[0x2C];
	Real m_range;				// +0x2C
};
class ModuleInfo
{
public:
	Int getCount() const { return ((const char *)m_end - (const char *)m_begin) / 20; }
	const ModuleData *getNthData(Int i) const;
private:
	const void *m_begin;
	const void *m_end;
	const void *m_storage;
};
class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_nameString; }
	Bool isEquivalentTo(const ThingTemplate *tt) const;
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindOf[t >> 5] & (1U << (t & 31)); }
	__forceinline Bool isKindOfB(KindOfType t) const { return (((const unsigned char *)m_kindOf)[t >> 3] & (1 << (t & 7))) != 0; }
	UnsignedInt getMaxSimultaneousOfType() const { return m_maxSimultaneousOfType; }
	Real friend_calcVisionRange() const { return m_visionRange; }
	UnsignedShort getRefundValue() const { return m_refundValue; }
	Int rva0033A69A(const Player *player, Int a, Int b) const;
	const ModuleData *rva0033B427(Int unused) const;
	const ModuleData *rva0033B3D7() const;
	const ModuleInfo &getBehaviorModuleInfo() const { return m_behaviorModuleInfo; }
private:
	unsigned char m_pad000[0x64];
	AsciiString m_nameString;		// +0x64
	unsigned char m_pad068[0xA0 - 0x68];
	GeometryInfo m_geometryInfo;	// +0xA0
	unsigned char m_pad0FC[0x108 - 0xFC];
	UnsignedInt m_kindOf[8];		// +0x108
	unsigned char m_pad128[0x2E4 - 0x128];
	ModuleInfo m_behaviorModuleInfo;	// +0x2E4
	unsigned char m_pad2F0[0x4AC - 0x2F0];
	Real m_visionRange;			// +0x4AC, ZH's name for addBibs' base range
	unsigned char m_pad4B0[0x5DC - 0x4B0];
	UnsignedShort m_refundValue;		// +0x5DC
	UnsignedShort m_pad5DE;
	UnsignedShort m_maxSimultaneousOfType;	// +0x5E0
};
class UpgradeTemplate
{
public:
	UpgradeType getUpgradeType() const { return m_type; }
private:
	unsigned char m_pad00[4];
	UpgradeType m_type;			// +0x04
};
struct UpgradeTemplateList
{
	const UpgradeTemplate **m_begin;
	const UpgradeTemplate **m_end;
	const UpgradeTemplate **m_capacity;
	UnsignedInt size() const { return (UnsignedInt)(m_end - m_begin); }
	const UpgradeTemplate *operator[](UnsignedInt i) const { return m_begin[i]; }
};
class CommandButton
{
public:
	GUICommandType getCommandType() const { return m_command; }
	UnsignedInt getOptions() const { return m_options; }
	const ThingTemplate *rva0035B570() const;		// the button's thing template
	const UpgradeTemplateList &getNeededUpgrades() const { return m_neededUpgrades; }
	Bool isAnyUpgradeEnough() const { return m_anyUpgrade; }
private:
	unsigned char m_pad00[0x14];
	GUICommandType m_command;		// +0x14
	unsigned char m_pad18[0x1C - 0x18];
	UnsignedInt m_options;			// +0x1C
	unsigned char m_pad20[0x28 - 0x20];
	UpgradeTemplateList m_neededUpgrades;	// +0x28
	Bool m_anyUpgrade;			// +0x34
};
class CommandSet
{
public:
	const CommandButton *getCommandButton(Int i) const;	// 0x00409EE8
};
class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *key);	// 0x0031D5F8, findCommandSet
};
class ControlBar : public Rva0031D5F8
{
public:
	const CommandSet *findCommandSet(const AsciiString *name)
	{
		return (const CommandSet *)rva0031D5F8(name);
	}
};
extern ControlBar *TheControlBar;
class Rva00392B10Interface
{
public:
	virtual AsciiString slot00() const = 0;
};
class BehaviorModuleInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0;
	virtual Rva00392B10Interface *slot11() = 0;	// +0x2C
};
class BfmeObjectModule
{
public:
	virtual void slot0() = 0;
private:
	unsigned int m_data[2];
};
class BehaviorModule : public BfmeObjectModule, public BehaviorModuleInterface
{
};
class ProductionUpdateInterface
{
public:
	virtual CanMakeType rva0049CFCD() const;					// +0x00
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual UnsignedInt countUnitTypeInQueue(const ThingTemplate *type) const;	// +0x1C
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void cancelAndRefundAllProduction();			// +0x3C
};
class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24();
	virtual void onSelling();					// +0x64
};
class Rva00346BC0
{
public:
	UnsignedInt m_bits[4];
};
struct Rva00391F4E : public Rva00346BC0
{
	Rva00391F4E(Int unused, Int bit1, Int bit2);
};
class Rva00391994
{
public:
	Bool rva00391994();
};
class ProductionUpdate
{
public:
	static ProductionUpdateInterface *getProductionUpdateInterfaceFromObject(Object *obj);
};
class Rva0028BD17Interface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual Bool slot06();						// +0x18
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual Bool slot23(ObjectID);			// +0x5C
};
class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void aiMoveToPositionEvenIfSleeping(const Coord3D *pos, CommandSourceType cmdSource);
};
class DozerAIInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29();
	virtual UnsignedInt slot30();					// +0x78
};
class AIUpdateInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91();
	virtual void slot92();
	virtual DozerAIInterface *getDozerAIInterface();		// +0x174
	virtual void slot94(); virtual void slot95(); virtual void slot96(); virtual void slot97();
	virtual void slot98(); virtual void slot99(); virtual void slot100(); virtual void slot101();
	virtual void slot102(); virtual void slot103(); virtual void slot104(); virtual void slot105();
	virtual void slot106(); virtual void slot107(); virtual void slot108(); virtual void slot109();
	virtual void slot110(); virtual void slot111(); virtual void slot112(); virtual void slot113();
	virtual void slot114(); virtual void slot115(); virtual void slot116(); virtual void slot117();
	virtual void slot118(); virtual void slot119(); virtual void slot120(); virtual void slot121();
	virtual void slot122(); virtual void slot123(); virtual void slot124(); virtual void slot125();
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int flags);	// +0x1F8
	Bool isPathAvailable(const Coord3D *destination) const;
	Bool isQuickPathAvailable(const Coord3D *destination) const;
	__forceinline void aiIdle(CommandSourceType cmdSource) { m_command.aiIdle(cmdSource); }
	__forceinline void aiMoveToPositionEvenIfSleeping(const Coord3D *pos, CommandSourceType cmdSource) { m_command.aiMoveToPositionEvenIfSleeping(pos, cmdSource); }
	Bool isMoving() const;
private:
	unsigned char m_pad04[0x20 - 0x04];
	AICommandInterface m_command;		// +0x20
};
class FoundationAIInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual Bool slot03();		// +0x0C, a set foundation is skipped by vslot 18
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int flags);	// +0x1C
};
class G00DFF080Obj
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual void addFactionBib(Object *factionBuilding, Bool highlight, Real extra = 0);	// +0x28
};
extern G00DFF080Obj *g_00DFF080;	// TheTerrainVisual
struct CreateMask
{
	CreateMask() { memset(m_words, 0, sizeof(m_words)); }
	void setBit(Int bit) { m_words[bit >> 5] |= 1U << (bit & 31); }
	UnsignedInt m_words[4];
};
enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};
class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04();
	virtual Real slot05() const;					// +0x14
	virtual void slot06(); virtual void slot07();
	virtual BodyDamageType getDamageState() const;		// +0x20
};
class Rva00294D61
{
public:
	void report(Object *owner, int setting);
};
class Thing
{
public:
	virtual ~Thing();
	const ThingTemplate *getTemplate() const { return m_template; }
	Drawable *getDrawable() const;
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
protected:
	const ThingTemplate *m_template;	// +0x004
};
class Object : public Thing
{
public:
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
	__forceinline Bool isKindOfB(KindOfType t) const { return m_template->isKindOfB(t); }
	Bool isEffectivelyDead() const { return m_isEffectivelyDead; }
	Bool testScriptStatusBit(ObjectScriptStatusBit b) const { return (m_scriptStatus & b) != 0; }
	AIUpdateInterface *getAI() const { return m_ai; }
	void *rva0028BD17() const;
	void *rva0028BC58(Int which);
	Player *getControllingPlayer() const;
	void setProducer(Object *obj);
	void *rva0028BCF4() const;
	void rva0028B4CE(PathfindLayerEnum layer);
	Int get45C() const { return m_45C; }
	const Coord3D *getPosition() const { return &m_position; }
	Real getOrientation() const { return m_orientation; }
	Relationship getRelationship(const Object *that) const;
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
	ObjectID getID() const { return m_id; }
	ObjectID get7C() const { return m_7C; }
	Bool testStatus(ObjectStatusTypes bit) const;
	void rva0028CDEB(const Rva00346BC0 &mask, Bool set);		// setStatus
	void setConstructionPercent(Real percent) { m_constructionPercent = percent; }
	ContainModuleInterface *getContain() const { return m_contain; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	const AsciiString *rva00290E67() const;		// the command set name
	Bool rva00290D2B(const UpgradeTemplate *upgrade) const;
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Real getBuildCost() const { return m_buildCost; }
	Bool rva0028C264(Int *killerID, Int which);
	void kill(DamageType damageType, DeathType deathType);
	Team *getTeam() const { return m_team; }
	void *rva0029439D();
private:
	unsigned char m_pad008[0x38 - 8];
	Coord3D m_position;			// +0x038
	Real m_orientation;			// +0x044
	unsigned char m_pad048[0x74 - 0x48];
	ObjectID m_id;				// +0x074
	unsigned char m_pad078[4];
	ObjectID m_7C;				// +0x07C, target link ID
	unsigned char m_pad080[0x94 - 0x80];
	unsigned m_statusBits[3];
	unsigned char m_pad0A0[0xA8 - 0xA0];
	GeometryInfo m_geometryInfo;		// +0x0A8
	unsigned char m_pad104[0x244 - 0x104];
	BehaviorModule **m_behaviors;		// +0x244, null-terminated
	unsigned char m_pad248[0x250 - 0x248];
	ContainModuleInterface *m_contain;	// +0x250
	BodyModuleInterface *m_body;		// +0x254
	AIUpdateInterface *m_ai;		// +0x258
	unsigned char m_pad25C[0x280 - 0x25C];
	Real m_constructionPercent;		// +0x280
	unsigned char m_pad284[0x304 - 0x284];
	Team *m_team;				// +0x304
	unsigned char m_pad308[0x324 - 0x308];
	Real m_buildCost;			// +0x324
	unsigned char m_pad328[0x437 - 0x328];
	unsigned char m_scriptStatus;		// +0x437
	Bool m_isEffectivelyDead : 1;		// +0x438 bit 0
	unsigned char m_pad439[0x45C - 0x439];
	Int m_45C;				// +0x45C
};
class Rva002A7461
{
public:
	bool rva002A7557(Rva002A7557In *p, int unused);
};
class Rva0037E6E8
{
public:
	Int rva0037E649(Int index, Object *obj);
};
class Rva0037E421
{
public:
	void *rva0037E7A5(int index);
	unsigned char rva0037E7BC(int index);
};
class Rva0039B7AD;
class Rva003B0D7C
{
public:
	void rva003B0D7C(int amount, Rva0039B7AD *score, bool flag);	// ZH's Money::deposit
};
class Money : public Rva003B0D7C
{
public:
	UnsignedInt countMoney() const { return m_money; }
private:
	unsigned char m_pad0[4];
	UnsignedInt m_money;			// +0x04
};
class ScoreKeeper
{
public:
	void addObjectLost(const Object *o);
private:
	unsigned char m_pad00[4];
};
class Player
{
public:
	Money *getMoney() { return &m_money; }
	void countObjectsByThingTemplate(Int numTmplates, const ThingTemplate * const *things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const;
	Int iterateObjects(Int (*func)(Object *, void *), void *userData) const;
	Team *getDefaultTeam() const { return m_defaultTeam; }
	void onStructureCreated(Object *builder, Object *structure);
	void onStructureConstructionComplete(Object *builder, Object *structure, Bool isRebuild);
	void onUnitCreated(Object *factory, Object *unit);
	Bool canBuild(const ThingTemplate *tmplate) const;
	Bool rva002AB87D(const UpgradeTemplate *upgrade) const;
	Color getPlayerColor() const { return m_color; }
	Int getPlayerIndex() const { return m_playerIndex; }
	void rva002AF614(void *points);
	ScoreKeeper *getScoreKeeper() { return &m_scoreKeeper; }
	Relationship getRelationship(const Team *that) const;
	unsigned char m_pad000[0x54];
	Int m_playerIndex;			// +0x054
	unsigned char m_pad058[0x60 - 0x58];
	Rva002A7461 m_rva060;			// +0x060
	unsigned char m_pad061[0x90 - 0x61];
	Money m_money;				// +0x090
	unsigned char m_pad098[0x280 - 0x98];
	Color m_color;				// +0x280
	unsigned char m_pad284[0x2EC - 0x284];
	Team *m_defaultTeam;			// +0x2EC
	unsigned char m_pad2F0[0x3BC - 0x2F0];
	ScoreKeeper m_scoreKeeper;		// +0x3BC
	unsigned char m_pad3C0[0x738 - 0x3C0];
	union
	{
		Rva0037E6E8 m_revivalCost;	// +0x738
		Rva0037E421 m_revivalTracker;	// +0x738
	};
};
class ObjectSellInfo
{
public:
	ObjectSellInfo( void ) : m_id( INVALID_OBJECT_ID ), m_sellFrame( 0 ) {}
	virtual ~ObjectSellInfo( void );
	__forceinline void deleteInstance() { ::delete this; }
	ObjectID m_id;				// +0x04
	UnsignedInt m_sellFrame;		// +0x08
};
typedef _STL::list< ObjectSellInfo * > ObjectSellList;
typedef ObjectSellList::iterator ObjectSellListIterator;
class BuildAssistant
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual void update( void );		// +0x28
	virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual Object *buildObjectNow(Object *constructorObject, const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer);	// +0x38
	virtual void slot15();
	virtual LegalBuildCode isLocationLegalToBuild(const Coord3D *worldPos, const ThingTemplate *build, Real angle, UnsignedInt options, Object *builderObject, Player *player);	// +0x40
	virtual Bool isLocationClearOfObjects(const Coord3D *worldPos, const ThingTemplate *build, Real angle, Object *builderObject, UnsignedInt options, Player *player, Bool flag);	// +0x44
	virtual Bool rva0039361E(const Coord3D *pos, const ThingTemplate *whatToBuild, Real angle, Object *builder, Player *unused);	// +0x48
	virtual void addBibs(const Coord3D *worldPos, const ThingTemplate *build);	// +0x4C
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual CanMakeType canMakeUnit(Object *builder, const ThingTemplate *whatToBuild, Int revivalIndex) const;	// +0x60
	virtual Bool isPossibleToMakeUnit(Object *builder, const ThingTemplate *whatToBuild, Int revivalIndex) const;	// +0x64
	virtual void sellObject(Object *obj);	// +0x68
	void iterateFootprint(const ThingTemplate *build, Real buildOrientation, const Coord3D *worldPos, Real sampleResolution, void (*func)(const Coord3D *samplePoint, void *userData), void *userData);
	Bool isRemovableForConstruction(Object *obj);
	void clearRemovableForConstruction(const ThingTemplate *whatToBuild, const Coord3D *pos, Real angle);
	Bool moveObjectsForConstruction(const ThingTemplate *whatToBuild, const Coord3D *pos, Real angle, Player *owningPlayer);
private:
	unsigned char m_pad04[0x0C - 0x04];
	ObjectSellList m_sellList;		// +0x0C
};
class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *statusBits, Bool flag);
};
extern ThingFactory *TheThingFactory;
class GlobalData
{
public:
	unsigned char m_pad000[0xA68];
	Real m_minDistFromEdgeOfMapForBuild;	// +0xA68
	Real m_supplyBuildBorder;		// +0xA6C
	Real m_allowedHeightVariationForBuilding;	// +0xA70
	unsigned char m_padA74[0xB94 - 0xA74];
	Real m_sellPercentage;			// +0xB94
	unsigned char m_padB98[0x1220 - 0xB98];
	Real m_1220;				// +0x1220, isLocationClearOfObjects' query margin
};
extern GlobalData *TheWritableGlobalData;
class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16();
	virtual const UnicodeString *fetch(const char *label, Bool *exists);	// +0x44
};
extern GameTextInterface *TheGameText;
class InGameUI
{
public:
#define IGUI_SLOTS10(n) virtual void s##n##0(); virtual void s##n##1(); virtual void s##n##2(); \
	virtual void s##n##3(); virtual void s##n##4(); virtual void s##n##5(); virtual void s##n##6(); \
	virtual void s##n##7(); virtual void s##n##8(); virtual void s##n##9();
	IGUI_SLOTS10(0) IGUI_SLOTS10(1) IGUI_SLOTS10(2) IGUI_SLOTS10(3) IGUI_SLOTS10(4)
	IGUI_SLOTS10(5) IGUI_SLOTS10(6) IGUI_SLOTS10(7) IGUI_SLOTS10(8) IGUI_SLOTS10(9)
#undef IGUI_SLOTS10
	virtual void s100(); virtual void s101(); virtual void s102(); virtual void s103();
	virtual void addFloatingText(const UnicodeString &text, const Coord3D *pos, Color color);	// +0x1A0
};
extern InGameUI *TheInGameUI;
class TerrainLogic
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04(); virtual void t05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;	// +0x18
	virtual void t07();
	virtual void getExtent(Region3D *extent) const;		// +0x20
	virtual void t09(); virtual void t10(); virtual void t11();
	virtual void getMaximumPathfindExtent(Region3D *extent) const;	// +0x30
	virtual void t13(); virtual void t14(); virtual void t15();
	virtual void t16(); virtual void t17(); virtual void t18();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ = NULL, Real *terrainZ = NULL, Int unused = 0);	// +0x4C
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, Bool onlyHealthyBridges);
};
extern TerrainLogic *TheTerrainLogic;
class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *object);
	void GetCellType(int pos, void *isValid, void *isBlocked, void *cellType, int layer);
	void *rva001E4461(int layer, int pos);
	Bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, Int unused);
};
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;		// +0x10
};
extern AI *TheAI;
extern PartitionManager *ThePartitionManager;
extern GameLogic *TheGameLogic;
enum DistanceCalculationType
{
	FROM_CENTER_2D,
	FROM_CENTER_3D,
	FROM_BOUNDINGSPHERE_2D,
	FROM_BOUNDINGSPHERE_3D
};
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual Bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *filter);
	Rva000421C8 *m_next;
};
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};
struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();
	unsigned int m_bits[7];
};
template <int NUMBITS> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual Bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
class Rva00261603Filter : public Rva000421C8
{
public:
	Rva00261603Filter(const Coord3D &pos, const GeometryInfo &geom, Real angle, Bool desired) throw();
	virtual Bool allow(Object *objOther);
private:
	Coord3D m_position;			// +0x08
	const GeometryInfo &m_geom;	// +0x14
	Real m_angle;				// +0x18
	Bool m_desiredCollisionResult;	// +0x1C
};
class Rva0029439DModule
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void slot024();
	virtual void slot025();
	virtual void slot026();
	virtual void slot027();
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void slot041();
	virtual void slot042();
	virtual void slot043();
	virtual void slot044();
	virtual void slot045();
	virtual void slot046();
	virtual void slot047();
	virtual void slot048();
	virtual void slot049();
	virtual void slot050();
	virtual void slot051();
	virtual void slot052();
	virtual void slot053();
	virtual void slot054();
	virtual void slot055();
	virtual void slot056();
	virtual void slot057();
	virtual void slot058();
	virtual void slot059();
	virtual void slot060();
	virtual void slot061();
	virtual void slot062();
	virtual void slot063();
	virtual void slot064();
	virtual void slot065();
	virtual void slot066();
	virtual void slot067();
	virtual void slot068();
	virtual void slot069();
	virtual void slot070();
	virtual void slot071();
	virtual void slot072();
	virtual void slot073();
	virtual void slot074();
	virtual void slot075();
	virtual void slot076();
	virtual void slot077();
	virtual void slot078();
	virtual void slot079();
	virtual void slot080();
	virtual void slot081();
	virtual void slot082();
	virtual void slot083();
	virtual void slot084();
	virtual void slot085();
	virtual void slot086();
	virtual void slot087();
	virtual void slot088();
	virtual void slot089();
	virtual void slot090();
	virtual void slot091();
	virtual void slot092();
	virtual void slot093();
	virtual void slot094();
	virtual void slot095();
	virtual void slot096();
	virtual void slot097();
	virtual void slot098();
	virtual void slot099();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual void slot112();
	virtual void slot113();
	virtual Bool slot114();
};
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual Bool allow(Object *obj);
};
class Rva0026118BFilter : public Rva000421C8
{
public:
	virtual Bool allow(Object *obj);
};
struct Rva0006EE7A
{
	Rva0006EE7A(int unused, int b1, int b2, int b3, int b4) throw();
	unsigned int m_bits[7];
};
class Rva00391D25Filter : public Rva000421C8
{
public:
	Rva00391D25Filter(const Coord3D *pos, Real radius) : m_pos(pos), m_radius(radius) {}
	virtual Bool allow(Object *obj);
private:
	const Coord3D *m_pos;	// +0x08
	Real m_radius;		// +0x0C
};
struct BfmeResultA
{
	void *m_value;
	~BfmeResultA();
};
class BfmeResultForwardB
{
public:
	BfmeResultA bfmeForwardResultB(int value);
};
struct BfmeCopyElementA
{
	BfmeCopyElementA *bfmeAssign(BfmeCopyElementA *source);
};
class BfmeThingTemplateShadowSelector
{
public:
	Bool usePluralShadowName() const;
};
Real GetGameLogicRandomValueReal(Real low, Real high, char *file, Int line);
#define BUILDASSISTANT_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\Common\\System\\BuildAssistant.cpp"
#define PI 3.14159265359f
class Vector3
{
public:
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	__forceinline void Rotate_Z(float angle) { Rotate_Z(sinf(angle), cosf(angle)); }
	void Rotate_Z(float s_angle, float c_angle)
	{
		float tmp_x = X;
		float tmp_y = Y;
		X = c_angle * tmp_x - s_angle * tmp_y;
		Y = s_angle * tmp_x + c_angle * tmp_y;
	}
	float X, Y, Z;
};
class DrawableList : public _STL::list<Drawable *>
{
public:
	~DrawableList() throw();
};
class PickAndPlayInfo;
class GameMessage
{
public:
	enum Type
	{
		MSG_BFME2_0x7DA = 0x7DA
	};
};
void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);
class Rva0028CBFD
{
public:
	void rva0028CBFD();
};
/** Update phase for the build assistant.  BFME2 sells at once: the refund, scaled by the
  * body's fraction, floats up from the structure as cash text, and the structure is killed
  * and scored instead of being destroyed */
struct ProductionCountData
{
	UnsignedInt count;
	const ThingTemplate *type;
};
static Int countInProduction( Object *obj, void *userData )
{
	ProductionUpdateInterface *pui = ProductionUpdate::getProductionUpdateInterfaceFromObject( obj );
	if( pui )
	{
		ProductionCountData *productionCountData = (ProductionCountData *)userData;
		productionCountData->count += pui->countUnitTypeInQueue( productionCountData->type );
	}
	return 1;
}
CanMakeType BuildAssistant::canMakeUnit( Object *builder, const ThingTemplate *whatToBuild, Int revivalIndex ) const
{
	if( builder == NULL )
		return CANMAKE_NO_PREREQ;
	if( whatToBuild == NULL && revivalIndex == -1 )
		return CANMAKE_NO_PREREQ;
	if( builder->isEffectivelyDead() )
		return CANMAKE_FACTORY_IS_DISABLED;
	Rva0028BD17Interface *x = (Rva0028BD17Interface *)builder->rva0028BD17();
	if( x && x->slot06() )
	{
		if( !(builder->isKindOf( KINDOF_156 ) && whatToBuild && whatToBuild->isKindOf( KINDOF_156 )) )
			return CANMAKE_FACTORY_IS_DISABLED;
	}
	Bool isRevival = revivalIndex != -1;
	if( builder->testScriptStatusBit( OBJECT_STATUS_SCRIPT_DISABLED ) || builder->testScriptStatusBit( OBJECT_STATUS_SCRIPT_UNPOWERED ) )
		return CANMAKE_FACTORY_IS_DISABLED;
	if( !isPossibleToMakeUnit( builder, whatToBuild, revivalIndex ) )
		return CANMAKE_NO_PREREQ;
	ProductionUpdateInterface *pu = (ProductionUpdateInterface *)builder->rva0028BC58( 0 );
	if( pu != NULL )
	{
		CanMakeType cmt = pu->rva0049CFCD();
		if( cmt != CANMAKE_OK )
			return cmt;
	}
	Player *player = builder->getControllingPlayer();
	Money *money = player->getMoney();
	UnsignedInt dozerAmount = 0;
	if( builder->isKindOf( KINDOF_DOZER ) || builder->isKindOf( KINDOF_15 ) )
	{
		AIUpdateInterface *ai = builder->getAI();
		DozerAIInterface *dozerAI = ai ? ai->getDozerAIInterface() : NULL;
		if( dozerAI )
			dozerAmount = dozerAI->slot30();
	}
	if( isRevival )
	{
		if( player->m_revivalCost.rva0037E649( revivalIndex, builder ) > money->countMoney() + dozerAmount )
			return CANMAKE_NO_MONEY;
		if( !player->m_rva060.rva002A7557( (Rva002A7557In *)player->m_revivalTracker.rva0037E7A5( revivalIndex ), 1 ) )
			return CANMAKE_7;
	}
	else
	{
		if( whatToBuild && !whatToBuild->isKindOf( KINDOF_157 ) )
		{
			if( (UnsignedInt)whatToBuild->rva0033A69A( player, (Int)builder, -1 ) > money->countMoney() + dozerAmount )
				return CANMAKE_NO_MONEY;
		}
		if( !player->m_rva060.rva002A7557( (Rva002A7557In *)whatToBuild, 1 ) )
			return CANMAKE_7;
	}
	if( whatToBuild && whatToBuild->getMaxSimultaneousOfType() != 0 )
	{
		const Bool ignoreDead = true;
		const Bool ignoreUnderConstruction = false;
		Int existingCount;
		player->countObjectsByThingTemplate( 1, &whatToBuild, ignoreDead, &existingCount, ignoreUnderConstruction );
		if( existingCount >= whatToBuild->getMaxSimultaneousOfType() )
			return CANMAKE_MAXED_OUT_FOR_PLAYER;
		ProductionCountData productionCountData;
		productionCountData.count = 0;
		productionCountData.type = whatToBuild;
		player->iterateObjects( countInProduction, &productionCountData );
		if( productionCountData.count + existingCount >= whatToBuild->getMaxSimultaneousOfType() )
			return CANMAKE_MAXED_OUT_FOR_PLAYER;
	}
	return CANMAKE_OK;
}
Bool BuildAssistant::isRemovableForConstruction(Object *obj)
{
	if (obj == 0)
		return false;
	if (obj->isKindOf(KINDOF_INERT))
		return false;
	if (obj->isKindOf(KINDOF_152))
		return false;
	if (obj->isKindOf(KINDOF_SHRUBBERY))
		return true;
	if (obj->isKindOf(KINDOF_CLEARED_BY_BUILD))
		return true;
	if (obj->isEffectivelyDead())
		return true;
	return false;
}
Bool BuildAssistant::isPossibleToMakeUnit( Object *builder, const ThingTemplate *whatToBuild, Int revivalIndex ) const
{
	if( builder == NULL )
		return FALSE;
	if( whatToBuild == NULL && revivalIndex == -1 )
		return FALSE;
	Bool isRevival = (revivalIndex != -1);
	if( whatToBuild )
	{
		for( BehaviorModule **m = builder->getBehaviorModules(); *m; ++m )
		{
			Rva00392B10Interface *bi = (*m)->slot11();
			if( bi == NULL )
				continue;
			if( bi->slot00() == whatToBuild->getName() )
				return TRUE;
		}
	}
	const CommandSet *commandSet = TheControlBar->findCommandSet( builder->rva00290E67() );
	if( commandSet == NULL )
		return FALSE;
	const CommandButton *commandButton = NULL;
	Int revivalCount = 0;
	for( Int i = 0; i < MAX_COMMANDS_PER_SET; i++ )
	{
		const CommandButton *button = commandSet->getCommandButton( i );
		if( button == NULL )
			continue;
		if( !isRevival )
		{
			if( (button->getCommandType() == GUI_COMMAND_UNIT_BUILD ||
				 button->getCommandType() == GUI_COMMAND_53 ||
				 button->getCommandType() == GUI_COMMAND_DOZER_CONSTRUCT) &&
				button->rva0035B570()->isEquivalentTo( whatToBuild ) )
			{
				Bool ok = TRUE;
				Bool needUpgrade = (button->getOptions() & NEED_UPGRADE) != 0;
				if( needUpgrade )
				{
					const UpgradeTemplateList &upgrades = button->getNeededUpgrades();
					Int count = 0;
					for( UnsignedInt j = 0; j < upgrades.size(); j++ )
					{
						const UpgradeTemplate *upgrade = upgrades[j];
						if( upgrade == NULL )
							continue;
						Bool has;
						if( upgrade->getUpgradeType() == UPGRADE_TYPE_OBJECT )
							has = builder->rva00290D2B( upgrade );
						else if( upgrade->getUpgradeType() == UPGRADE_TYPE_PLAYER )
							has = builder->getControllingPlayer()->rva002AB87D( upgrade );
						else
							continue;
						if( has )
						{
							count++;
							if( button->isAnyUpgradeEnough() )
								break;
						}
					}
					if( button->isAnyUpgradeEnough() )
						ok = count > 0;
					else
						ok = count == upgrades.size();
				}
				if( ok )
				{
					commandButton = button;
					break;
				}
			}
		}
		else if( button->getCommandType() == GUI_COMMAND_46 )
		{
			if( revivalCount == revivalIndex )
			{
				commandButton = button;
				break;
			}
			revivalCount++;
		}
	}
	if( commandButton == NULL )
		return FALSE;
	Player *player = builder->getControllingPlayer();
	if( !isRevival && !player->canBuild( commandButton->rva0035B570() ) )
		return FALSE;
	if( isRevival && !player->m_revivalTracker.rva0037E7BC( revivalIndex ) )
		return FALSE;
	return TRUE;
}
void BuildAssistant::sellObject( Object *obj )
{
	if( obj == NULL )
		return;
	if( obj->getTemplate()->isKindOf( KINDOF_STRUCTURE ) == FALSE )
		return;
	if( obj->isKindOf( KINDOF_NOT_SELLABLE ) )
		return;
	if( reinterpret_cast<Rva00391994 *>( obj )->rva00391994() == FALSE )
		return;
	if( obj->testStatus( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
		return;
	ObjectSellInfo *sellInfo = NULL;
	ObjectSellListIterator it;
	for( it = m_sellList.begin(); it != m_sellList.end(); ++it )
	{
		sellInfo = (*it);
		if( sellInfo->m_id == obj->getID() )
			break;
		else
			sellInfo = NULL;
	}
	if( sellInfo != NULL )
		return;
	obj->setConstructionPercent( 99.9f );
	sellInfo = new ObjectSellInfo;
	sellInfo->m_id = obj->getID();
	sellInfo->m_sellFrame = TheGameLogic->getFrame();
	m_sellList.push_front( sellInfo );
	obj->rva0028CDEB( Rva00391F4E( 0, OBJECT_STATUS_SOLD, OBJECT_STATUS_UNSELECTABLE ), TRUE );
	TheGameLogic->deselectObject( obj, PLAYERMASK_ALL, TRUE );
	Drawable *draw = obj->getDrawable();
	if( draw )
		draw->setAnimationLoopDuration( TOTAL_FRAMES_TO_SELL_OBJECT / 2 );
	ProductionUpdateInterface *production = (ProductionUpdateInterface *)obj->rva0028BC58( 0 );
	if( production )
		production->cancelAndRefundAllProduction();
	if( obj->getAI() )
		obj->getAI()->aiIdle( CMD_FROM_AI );
	ContainModuleInterface *contain = obj->getContain();
	if( contain )
		contain->onSelling();
}
void BuildAssistant::clearRemovableForConstruction( const ThingTemplate *whatToBuild,
													const Coord3D *pos, Real angle )
{
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange( pos,
		whatToBuild->getTemplateGeometryInfo().getBoundingCircleRadius() * 1.1f, FROM_BOUNDINGSPHERE_3D,
		&Rva00261603Filter( *pos, whatToBuild->getTemplateGeometryInfo(), angle, TRUE ), 0 );
	for( Object *them = iter.next(); them; them = iter.next() )
	{
		if( isRemovableForConstruction( them ) == TRUE && !them->isKindOf( KINDOF_58 ) )
			TheGameLogic->destroyObject( them );
	}
}
Bool BuildAssistant::rva0039361E( const Coord3D *pos, const ThingTemplate *whatToBuild, Real angle,
								  Object *builder, Player *unused )
{
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange( pos,
		whatToBuild->getTemplateGeometryInfo().getBoundingCircleRadius() * 1.1f, FROM_BOUNDINGSPHERE_3D,
		&Rva00261603Filter( *pos, whatToBuild->getTemplateGeometryInfo(), angle, TRUE ), 0 );
	for( Object *them = iter.next(); them; them = iter.next() )
	{
		if( !them->isKindOf( KINDOF_104 ) )
			continue;
		if( builder->getRelationship( them ) != ALLIES )
			continue;
		FoundationAIInterface *foundation = (FoundationAIInterface *)them->rva0028BCF4();
		if( foundation && foundation->slot03() )
			continue;
		Coord3D delta;
		delta.x = them->getPosition()->x;
		delta.y = them->getPosition()->y;
		delta.z = them->getPosition()->z;
		delta.x -= pos->x;
		delta.y -= pos->y;
		delta.z -= pos->z;
		Real dist = delta.length();
		if( dist < them->getTemplate()->getTemplateGeometryInfo().getMajorRadius() / 2.0f )
			return TRUE;
	}
	return FALSE;
}
void BuildAssistant::addBibs( const Coord3D *worldPos, const ThingTemplate *build )
{
	Real range = build->friend_calcVisionRange();
	range += 3*build->getTemplateGeometryInfo().getMajorRadius();
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange( worldPos, range, FROM_CENTER_3D,
		&Rva0004584D( *(BfmeFixedStorage0004543D *)&Rva00045411BitSet( 0, KINDOF_STRUCTURE ),
					  *(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE ), 0 );
	for( Object *them = iter.next(); them; them = iter.next() )
	{
		if( isRemovableForConstruction( them ) == TRUE )
			continue;
		if( them->isKindOf( KINDOF_2 ) )
			g_00DFF080->addFactionBib( them, TRUE );
	}
}
/** Passed to checkSampleBuildLocation while iterating a footprint. BFME2 extends Zero Hour's
	* map region, restriction flag and height range with the template being built, per-sample
	* water and land counts and position sums, and the builder's player index (target layout,
	* 0x50 bytes, isLocationLegalToBuild's frame at ebp-0x74). */
struct SampleBuildData
{
	const ThingTemplate *build;		// +0x00
	Bool requireWaterOrLand;		// +0x04
	Region3D mapRegion;			// +0x08
	Bool terrainRestricted;			// +0x20
	Real hiZ;				// +0x24
	Real loZ;				// +0x28
	Real waterSamples;			// +0x2C
	Real landSamples;			// +0x30
	Coord3D waterSum;			// +0x34
	Coord3D landSum;			// +0x40
	Int playerIndex;			// +0x4C
};
inline void addCoord3D( Coord3D *sum, const Coord3D *a )
{
	sum->x += a->x;
	sum->y += a->y;
	sum->z += a->z;
}
/** This will check the build conditions at the specified sample location point */
static void checkSampleBuildLocation( const Coord3D *samplePoint, void *userData )
{
	SampleBuildData *sampleData = (SampleBuildData *)userData;
	Bool isK188 = sampleData->build->isKindOf( KINDOF_188 ) != 0;
	Bool isK189 = sampleData->build->isKindOf( KINDOF_189 ) != 0;
	if( sampleData->terrainRestricted && !isK188 )
		return;
	Bool isValid;
	Bool isBlocked = FALSE;
	Int cellType;
	if( isK189 )
		TheAI->pathfinder()->GetCellType( (int)samplePoint, &isValid, &isBlocked, &cellType,
																			TheTerrainLogic->getHighestLayerForDestination( samplePoint, FALSE ) );
	else
		TheAI->pathfinder()->GetCellType( (int)samplePoint, &isValid, &isBlocked, &cellType, 1 );
	sampleData->terrainRestricted = FALSE;
	if( isValid )
	{
		if( isBlocked )
			sampleData->terrainRestricted = TRUE;
		else
		{
			switch( cellType )
			{
				case 0:
					break;
				case 5:
					break;
				case 4:
				{
					ObjectID id = (ObjectID)(Int)TheAI->pathfinder()->rva001E4461(
						TheTerrainLogic->getHighestLayerForDestination( samplePoint, FALSE ), (int)samplePoint );
					Object *obj = TheGameLogic->findObjectByID( id );
					if( obj == NULL || obj->getTemplate()->isKindOf( KINDOF_INERT ) )
						sampleData->terrainRestricted = TRUE;
					break;
				}
				case 2:
					sampleData->terrainRestricted = TRUE;
					break;
				case 1:
				case 7:
					if( !isK188 )
						sampleData->terrainRestricted = TRUE;
					break;
				default:
					sampleData->terrainRestricted = TRUE;
					break;
			}
		}
	}
	else
		sampleData->terrainRestricted = TRUE;
	Bool isWater = FALSE;
	if( isK188 )
	{
		isWater = TheTerrainLogic->isUnderwater( samplePoint->x, samplePoint->y );
		if( isWater )
		{
			sampleData->waterSamples += 1.0f;
			addCoord3D( &sampleData->waterSum, samplePoint );
		}
		else
		{
			sampleData->landSamples += 1.0f;
			addCoord3D( &sampleData->landSum, samplePoint );
		}
	}
	if( !isWater )
	{
		if( samplePoint->z < sampleData->loZ )
			sampleData->loZ = samplePoint->z;
		if( samplePoint->z > sampleData->hiZ )
			sampleData->hiZ = samplePoint->z;
	}
	if( TheWritableGlobalData->m_minDistFromEdgeOfMapForBuild > 0.0f )
	{
		if( samplePoint->x < sampleData->mapRegion.lo.x + TheWritableGlobalData->m_minDistFromEdgeOfMapForBuild
				|| samplePoint->x > sampleData->mapRegion.hi.x - TheWritableGlobalData->m_minDistFromEdgeOfMapForBuild
				|| samplePoint->y < sampleData->mapRegion.lo.y + TheWritableGlobalData->m_minDistFromEdgeOfMapForBuild
				|| samplePoint->y > sampleData->mapRegion.hi.y - TheWritableGlobalData->m_minDistFromEdgeOfMapForBuild )
		{
			sampleData->terrainRestricted = TRUE;
		}
	}
}  // end checkSampleBuildLocation
#define MAP_XY_FACTOR (10.0f)
static Real s_maxWaterLandSampleRatio = 6.0f;
extern PartitionManager *TheShroudManager;
/** Query if we can build at this location.  Note that 'build' may be null and is NOT required
	* to be valid to know if a location is legal to build at.  'builderObject' is used 
	* for queries that require a pathfind check and should be NULL if not required */
Bool Rva003919F6Connected(Object*a,Object*b)
{
 if(a==0||b==0)return false;
 if(!a->isKindOf((KindOfType)156)||!b->isKindOf((KindOfType)156))return false;
 if(a->get7C()==b->getID() || b->get7C()==a->getID())return true;
 Rva0028BD17Interface *x=(Rva0028BD17Interface*)a->rva0028BD17();
 if(x && x->slot23(b->getID()))return true;
 Rva0028BD17Interface *y=(Rva0028BD17Interface*)b->rva0028BD17();
 if(y && y->slot23(a->getID()))return true;
 return false;
}
class Rva00391667 : public Rva000421C8
{
public:
	Rva00391667(const void *pos);
	virtual Bool allow(Object *obj);
	Real m_range;				// +0x08
	Coord3D m_pos;				// +0x0C
};
class Rva0039161C : public Rva000421C8
{
public:
	Rva0039161C(const void *pos, const void *geom, Real angle, bool desired);
	virtual Bool allow(Object *obj);
	Coord3D m_pos;				// +0x08
	const void *m_geom;			// +0x14
	Real m_angle;				// +0x18
	bool m_desired;				// +0x1C
	bool m_1d;				// +0x1D
};
class Rva00261353Filter : public Rva000421C8
{
public:
	Rva00261353Filter(Int playerIndex) : m_playerIndex(playerIndex) {}
	virtual Bool allow(Object *obj);
	Int m_playerIndex;			// +0x08
};
class Module
{
	unsigned char m_pad00[0x18];
public:
	ObjectID m_18;				// +0x18
};
class CastleBehavior
{
public:
	static Module *rva000395708(Object *obj);
};
class PoolMember
{
public:
	void Rva00268902();
};
struct Rva00394173Node
{
	Rva00394173Node *m_next;
	Rva00394173Node *m_prev;
	ObjectID m_id;				// +0x08
};
class Rva00394173Member
{
public:
	Rva00394173Member(const Rva00394173Member &that);
	~Rva00394173Member() { ((PoolMember *)this)->Rva00268902(); }
	Rva00394173Node *m_head;
};
class Rva00394173Field
{
public:
	Rva00394173Member get() const;
};
struct Rva00394879Exit
{
	unsigned char m_pad00[0x14];
	Coord3D m_offset;			// +0x14
};
struct Rva00394879Door
{
	unsigned char m_pad00[0xC8];
	Coord3D m_offset;			// +0xC8
};
class ModuleData
{
public:
	virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
	virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
	virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
	virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
	virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
	virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
	virtual void m24();
	virtual const Rva00394879Exit *rva00394879Exit() const;	// +0x64
	virtual void m26(); virtual void m27(); virtual void m28();
	virtual const Rva00394879Door *rva00394879Door() const;	// +0x74
};
class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float val);
};
class Vector4
{
public:
	float X, Y, Z, W;
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
};
class Matrix3D
{
public:
	__forceinline void Make_Identity()
	{
		Row[0][0] = 1.0f; Row[0][1] = 0.0f; Row[0][2] = 0.0f; Row[0][3] = 0.0f;
		Row[1][0] = 0.0f; Row[1][1] = 1.0f; Row[1][2] = 0.0f; Row[1][3] = 0.0f;
		Row[2][0] = 0.0f; Row[2][1] = 0.0f; Row[2][2] = 1.0f; Row[2][3] = 0.0f;
	}
	__forceinline void Rotate_Z(float theta)
	{
		float tmp1, tmp2;
		float c = (float)cos(theta);
		float s = (float)sin(theta);
		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = c * tmp1 + s * tmp2;
		Row[0][1] = -s * tmp1 + c * tmp2;
		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = c * tmp1 + s * tmp2;
		Row[1][1] = -s * tmp1 + c * tmp2;
		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = c * tmp1 + s * tmp2;
		Row[2][1] = -s * tmp1 + c * tmp2;
	}
	static __forceinline void Transform_Vector(const Matrix3D &A, const Vector3 &in, Vector3 *out)
	{
		Vector3 tmp(0.0f, 0.0f, 0.0f);
		const Vector3 *v;
		if (out == &in)
		{
			tmp = in;
			v = &tmp;
		}
		else
		{
			v = &in;
		}
		out->X = A.Row[0][0] * v->X + A.Row[0][1] * v->Y + A.Row[0][2] * v->Z + A.Row[0][3];
		out->Y = A.Row[1][0] * v->X + A.Row[1][1] * v->Y + A.Row[1][2] * v->Z + A.Row[1][3];
		out->Z = A.Row[2][0] * v->X + A.Row[2][1] * v->Y + A.Row[2][2] * v->Z + A.Row[2][3];
	}
	Vector4 Row[3];
};
/** Is the footprint of 'build' at 'worldPos' clear of objects that would stop
  * the construction? Zero Hour's check (objects to remove for construction,
  * inert kinds, the builder and enemies) with BFME2's additions read off
  * retail 0x00394879: module data that supplies its own query range, the
  * shroud test for the builder's player, castle members of a KINDOF_120
  * builder, the player's ObjectID list option, and a final path and door
  * check from the template's exit or door offset. */
inline Bool Object::testStatus( ObjectStatusTypes bit ) const
{
	return ( m_statusBits[(UnsignedInt)bit >> 5] & ( 1 << ( bit & 31 ) ) ) != 0;
}
Bool BuildAssistant::isLocationClearOfObjects( const Coord3D *worldPos, const ThingTemplate *build, Real angle, Object *builderObject, UnsignedInt options, Player *player, Bool flag )
{
	Bool b20 = (options >> 5) & 1;
	Bool b40 = (options >> 6) & 1;
	Bool b100 = (options >> 8) & 1;
	Bool b200 = (options >> 9) & 1;
	Bool b400 = (options >> 10) & 1;
	Rva00391667 rangeFilter( worldPos );
	Rva0039161C collideFilter( worldPos, &build->getTemplateGeometryInfo(), angle, true );
	Real range;
	Rva000421C8 *filter;
	const Rva0033B3D7Data *data = (const Rva0033B3D7Data *)build->rva0033B3D7();
	if( data )
	{
		range = TheWritableGlobalData->m_1220 * 2.0f;
		rangeFilter.m_range = data->m_range;
		filter = &rangeFilter;
	}
	else
	{
		range = build->getTemplateGeometryInfo().getBoundingCircleRadius() + TheWritableGlobalData->m_1220;
		if( build->isKindOf( KINDOF_189 ) )
			collideFilter.m_1d = false;
		filter = &collideFilter;
	}
	BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange( worldPos, range, FROM_BOUNDINGSPHERE_3D, filter, 0 );
	Object *them;
	while( (them = iter.next()) != NULL )
	{
		if( builderObject && flag )
		{
			CellShroudStatus cs = them->getShroudStatusForPlayer( builderObject->getControllingPlayer()->m_playerIndex );
			if( cs == CELLSHROUD_3 || cs == CELLSHROUD_4 )
				continue;
		}
		if( isRemovableForConstruction( them ) == TRUE )
			continue;
		if( them->isKindOfB( KINDOF_12 ) || them->isKindOfB( KINDOF_INERT ) )
			continue;
		if( b100 && builderObject && builderObject->isKindOf( KINDOF_120 ) )
		{
			Module *m = CastleBehavior::rva000395708( them );
			if( m )
			{
				ObjectID id = m->m_18;
				if( id == builderObject->getID() )
					continue;
			}
			if( them == builderObject )
				continue;
			if( them->isKindOfB( KINDOF_DOZER ) )
				continue;
		}
		if( !build->isKindOf( KINDOF_104 ) && build->isKindOf( KINDOF_189 ) && them->isKindOfB( KINDOF_156 ) && them == builderObject )
			continue;
		if( them->testStatus( OBJECT_STATUS_98 ) )
			continue;
		if( them->isKindOfB( KINDOF_152 ) )
			continue;
		if( them->isKindOfB( KINDOF_2 ) )
		{
			if( b20 && builderObject && builderObject->getRelationship( them ) != ENEMIES )
				continue;
			return FALSE;
		}
		if( builderObject && builderObject->getRelationship( them ) == ENEMIES && !b200 )
			return FALSE;
		if( b200 && builderObject && builderObject->getRelationship( them ) == ENEMIES && them->isKindOfB( KINDOF_STRUCTURE ) )
			return FALSE;
	}
	if( b400 && builderObject )
	{
		Player *owner = builderObject->getControllingPlayer();
		if( owner )
		{
			Rva00394173Member list = ((const Rva00394173Field *)owner)->get();
			for( Rva00394173Node *node = list.m_head->m_next; node != list.m_head; node = node->m_next )
			{
				Object *obj = TheGameLogic->findObjectByID( node->m_id );
				if( obj && build->getTemplateGeometryInfo().bfmeIntersects( *worldPos, angle, obj->getGeometryInfo(), *obj->getPosition(), obj->getOrientation() ) )
					return FALSE;
			}
		}
	}
	if( b20 || b40 || b100 )
		return TRUE;
	Coord3D pt;
	pt.x = 0.0f;
	pt.y = 0.0f;
	pt.z = 0.0f;
	const ModuleInfo &info = build->getBehaviorModuleInfo();
	Int count = info.getCount();
	for( Int i = 0; i < count; ++i )
	{
		const ModuleData *md = info.getNthData( i );
		if( md )
		{
			const Rva00394879Exit *exitData = md->rva00394879Exit();
			if( exitData )
			{
				pt = exitData->m_offset;
				Vector3 dir( pt.x, pt.y, pt.z );
				Real len2 = dir.X * dir.X + dir.Y * dir.Y + dir.Z * dir.Z;
				if( len2 != 0.0f )
				{
					Real inv = WWMath::Inv_Sqrt( len2 );
					dir.X *= inv;
					dir.Y *= inv;
					dir.Z *= inv;
				}
				pt.x += dir.X * 20.0f;
				pt.y += dir.Y * 20.0f;
				pt.z += dir.Z * 20.0f;
				break;
			}
			const Rva00394879Door *doorData = md->rva00394879Door();
			if( doorData )
			{
				pt = doorData->m_offset;
				break;
			}
		}
	}
	if( pt.GetLength() != 0.0f )
	{
		Matrix3D tm;
		tm.Make_Identity();
		tm.Rotate_Z( angle );
		Vector3 out( 0.0f, 0.0f, 0.0f );
		Matrix3D::Transform_Vector( tm, Vector3( pt.x, pt.y, pt.z ), &out );
		out.X += worldPos->x;
		out.Y += worldPos->y;
		if( builderObject && builderObject->isKindOf( KINDOF_DOZER )
				&& !TheAI->pathfinder()->QuickDoesPathExist( builderObject, worldPos, (const Coord3D *)&out, 0 ) )
			return FALSE;
		Real dy = out.Y - worldPos->y;
		Coord2D dir;
		dir.x = out.X - worldPos->x;
		dir.y = dy;
		Real len = dir.length();
		GeometryInfo doorGeom( GEOMETRY_BOX, FALSE, 1.0f, len * 0.5, 0.5f );
		Real inv = 1.0f / len;
		Real doorAngle = atan2f( dir.x * inv, dy * inv );
		Coord3D center;
		center.x = (out.X + worldPos->x) * 0.5f;
		center.y = (out.Y + worldPos->y) * 0.5f;
		center.z = worldPos->z;
		Real doorRange = build->getTemplateGeometryInfo().getMajorRadius() * 2.0f;
		BfmeWideResult iter2 = ThePartitionManager->iterateObjectsInRange( worldPos, doorRange, FROM_CENTER_3D,
			Rva0004584D( *(BfmeFixedStorage0004543D *)&Rva00045411BitSet( 0, KINDOF_STRUCTURE ), *(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE )
				.link( &Rva00261353Filter( builderObject->getControllingPlayer()->m_playerIndex ) ), 0 );
		while( (them = iter2.next()) != NULL )
		{
			if( them->getGeometryInfo().bfmeIntersects( *them->getPosition(), them->getOrientation(), doorGeom, center, doorAngle ) )
				return FALSE;
		}
	}
	return TRUE;
}  // end isLocationClearOfObjects
