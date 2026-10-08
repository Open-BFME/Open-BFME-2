// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
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
// through the one-drawable voice hand-off (message 0x7DA) instead of ZH's
// VoiceCreated sound.

#include <list>
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../GameLogicObjectLookupView.h"
#include "../PartitionRangeQueryCallView.h"

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
	KINDOF_DOZER = 14,
	KINDOF_15 = 15,
	KINDOF_30 = 30,
	KINDOF_CLEARED_BY_BUILD = 51,
	KINDOF_58 = 58,
	KINDOF_INERT = 89,
	KINDOF_104 = 104,
	KINDOF_149 = 149,
	KINDOF_152 = 152,
	KINDOF_NOT_SELLABLE = 154,
	KINDOF_156 = 156,
	KINDOF_157 = 157,
	KINDOF_189 = 189
};

// BFME2's object status bit names (the name table at .rdata 0x009A5F30).
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_UNSELECTABLE = 3,
	OBJECT_STATUS_SOLD = 19
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

// ZH's TOTAL_FRAMES_TO_SELL_OBJECT, LOGICFRAMES_PER_SECOND * 3.0f: retail
// keeps it as a dynamically initialized float (initializer 0x007AF1F7).
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
	LAYER_INVALID = 0
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

enum ObjectScriptStatusBit
{
	OBJECT_STATUS_SCRIPT_DISABLED = 0x01,
	OBJECT_STATUS_SCRIPT_UNPOWERED = 0x02
};

// Zero Hour's command type values for the two build commands; BFME2's 53
// also builds and 46 is the revival command (names not recovered).
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
class Team;
struct Rva002A7557In;

class Drawable
{
public:
	void setAnimationLoopDuration(UnsignedInt numFrames);
};

// Zero Hour's GeometryInfo name for the radius its clearRemovableForConstruction
// queries with; BFME2's template keeps it at geometry +0x14.
class GeometryInfo
{
public:
	Real getMajorRadius() const { return m_majorRadius; }
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
	Real getMaxHeightAbovePosition() const;

private:
	unsigned char m_pad00[0x10];
	Real m_majorRadius;		// +0x10
	Real m_boundingCircleRadius;	// +0x14
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_nameString; }
	Bool isEquivalentTo(const ThingTemplate *tt) const;
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindOf[t >> 5] & (1U << (t & 31)); }
	UnsignedInt getMaxSimultaneousOfType() const { return m_maxSimultaneousOfType; }
	Real friend_calcVisionRange() const { return m_visionRange; }
	UnsignedShort getRefundValue() const { return m_refundValue; }
	Int rva0033A69A(const Player *player, Int a, Int b) const;

private:
	unsigned char m_pad000[0x64];
	AsciiString m_nameString;		// +0x64
	unsigned char m_pad068[0xA0 - 0x68];
	GeometryInfo m_geometryInfo;	// +0xA0
	unsigned char m_pad0B8[0x108 - 0xB8];
	UnsignedInt m_kindOf[8];		// +0x108
	unsigned char m_pad128[0x4AC - 0x128];
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

// The upgrade list a NEED_UPGRADE button checks (+0x28): all of them must be
// complete unless the +0x34 flag accepts any one.
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

// The interface behind BehaviorModuleInterface slot 11; its first slot names
// a thing template the builder can always make (names not recovered).
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

// The 128-bit object status mask and the rowed two-bit constructor
// (0x00391F4E) that builds one.
class Rva00346BC0
{
public:
	UnsignedInt m_bits[4];
};

struct Rva00391F4E : public Rva00346BC0
{
	Rva00391F4E(Int unused, Int bit1, Int bit2);
};

// The rowed test whether an object's command set offers the sell command.
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
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
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

	__forceinline void aiIdle(CommandSourceType cmdSource) { m_command.aiIdle(cmdSource); }

private:
	unsigned char m_pad04[0x20 - 0x04];
	AICommandInterface m_command;		// +0x20
};

// What WB asserts as getFoundationAIInterface: its vslot 7 takes the AI
// construct's arguments.
class FoundationAIInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual Bool slot03();		// +0x0C, a set foundation is skipped by vslot 18
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int flags);	// +0x1C
};

// Zero Hour's TerrainVisual: slot 10 takes addFactionBib's (building,
// highlight, extra) arguments.
class G00DFF080Obj
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual void addFactionBib(Object *factionBuilding, Bool highlight, Real extra = 0);	// +0x28
};

extern G00DFF080Obj *g_00DFF080;	// TheTerrainVisual

// What ThingFactory::newObject takes: the initial status bits.
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

// BFME2's body module: vslot 5 is the fraction sold structures refund by,
// vslot 8 ZH's getDamageState.
class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04();
	virtual Real slot05() const;					// +0x14
	virtual void slot06(); virtual void slot07();
	virtual BodyDamageType getDamageState() const;		// +0x20
};

// Object::scoreTheKill in the WorldBuilder build.
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
	Relationship getRelationship(const Object *that) const;
	ObjectID getID() const { return m_id; }
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

private:
	unsigned char m_pad008[0x38 - 8];
	Coord3D m_position;			// +0x038
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id;				// +0x074
	unsigned char m_pad078[0xA8 - 0x78];
	GeometryInfo m_geometryInfo;		// +0x0A8
	unsigned char m_pad0C0[0x244 - 0xC0];
	BehaviorModule **m_behaviors;		// +0x244, null-terminated
	unsigned char m_pad248[0x250 - 0x248];
	ContainModuleInterface *m_contain;	// +0x250
	BodyModuleInterface *m_body;		// +0x254
	AIUpdateInterface *m_ai;		// +0x258
	unsigned char m_pad25C[0x280 - 0x25C];
	Real m_constructionPercent;		// +0x280
	unsigned char m_pad284[0x324 - 0x284];
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
	ScoreKeeper *getScoreKeeper() { return &m_scoreKeeper; }

	unsigned char m_pad000[0x60];
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
	virtual void slot16(); virtual void slot17();
	virtual Bool rva0039361E(const Coord3D *pos, const ThingTemplate *whatToBuild, Real angle, Object *builder, Player *unused);	// +0x48
	virtual void addBibs(const Coord3D *worldPos, const ThingTemplate *build);	// +0x4C
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual CanMakeType canMakeUnit(Object *builder, const ThingTemplate *whatToBuild, Int revivalIndex) const;	// +0x60
	virtual Bool isPossibleToMakeUnit(Object *builder, const ThingTemplate *whatToBuild, Int revivalIndex) const;	// +0x64
	virtual void sellObject(Object *obj);	// +0x68

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
	unsigned char m_pad000[0xB94];
	Real m_sellPercentage;			// +0xB94
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
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *object);
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

// Retail calls the list destructor out of line (the shared pointer-list
// destructor 0x00239AF4).
enum DistanceCalculationType
{
	FROM_CENTER_2D,
	FROM_CENTER_3D,
	FROM_BOUNDINGSPHERE_2D,
	FROM_BOUNDINGSPHERE_3D
};

// The partition filter base (ctor 0x000421C8, vftable 0x00BC26E0) and the
// would-collide filter (ctor 0x0027C2C9), as PartitionFilterWouldCollideCtor.cpp.
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual Bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// The 224-bit KindOf mask (unused, bit) constructor 0x00045411.
struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();
	unsigned int m_bits[7];
};

template <int NUMBITS> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

// vftable 0x00BC2908: every kind of the first mask and none of the second
// (ZH's PartitionFilterAcceptByKindOf).
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
	Rva00261603Filter(const Coord3D &pos, const GeometryInfo &geom, Real angle, Bool desired);
	virtual Bool allow(Object *objOther);

private:
	Coord3D m_position;			// +0x08
	const GeometryInfo &m_geom;	// +0x14
	Real m_angle;				// +0x18
	Bool m_desiredCollisionResult;	// +0x1C
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

// The rowed member every newly made object ends with (ZH's
// handlePartitionCellMaintenance).
class Rva0028CBFD
{
public:
	void rva0028CBFD();
};

//-------------------------------------------------------------------------------------------------
/** Update phase for the build assistant.  BFME2 sells at once: the refund, scaled by the
  * body's fraction, floats up from the structure as cash text, and the structure is killed
  * and scored instead of being destroyed */
// ------------------------------------------------------------------------------------------------
struct ProductionCountData
{
	UnsignedInt count;
	const ThingTemplate *type;
};

// countInProduction, retail 0x0039194F.
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

// BuildAssistant::canMakeUnit, retail 0x00391B08.
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

	// make sure we're not maxed out for this type of unit.
	if( whatToBuild && whatToBuild->getMaxSimultaneousOfType() != 0 )
	{
		const Bool ignoreDead = true;
		const Bool ignoreUnderConstruction = false;
		Int existingCount;
		player->countObjectsByThingTemplate( 1, &whatToBuild, ignoreDead, &existingCount, ignoreUnderConstruction );
		if( existingCount >= whatToBuild->getMaxSimultaneousOfType() )
			return CANMAKE_MAXED_OUT_FOR_PLAYER;

		// also check objects that are in production
		ProductionCountData productionCountData;
		productionCountData.count = 0;
		productionCountData.type = whatToBuild;
		player->iterateObjects( countInProduction, &productionCountData );
		if( productionCountData.count + existingCount >= whatToBuild->getMaxSimultaneousOfType() )
			return CANMAKE_MAXED_OUT_FOR_PLAYER;
	}

	return CANMAKE_OK;
}

// BuildAssistant::isRemovableForConstruction, retail 0x00391CE3.
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

// BuildAssistant::isPossibleToMakeUnit, retail 0x00392AD7 (vslot 25).
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

// BuildAssistant::sellObject, retail 0x003941FD (vslot 26).
void BuildAssistant::sellObject( Object *obj )
{
	// sanity
	if( obj == NULL )
		return;

	// we can only sell structures ... sanity check this
	if( obj->getTemplate()->isKindOf( KINDOF_STRUCTURE ) == FALSE )
		return;

	if( obj->isKindOf( KINDOF_NOT_SELLABLE ) )
		return;

	// BFME2: only an object whose command set offers the sell command
	if( reinterpret_cast<Rva00391994 *>( obj )->rva00391994() == FALSE )
		return;

	// an object under construction cannot be sold
	if( obj->testStatus( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
		return;

	// if object already has an entry in the sell list, we shouldn't try to sell it again
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

	// set the construction percent of this object just below 100.0% so we can start counting down
	obj->setConstructionPercent( 99.9f );

	// add this object to the list of objects being sold
	sellInfo = new ObjectSellInfo;
	sellInfo->m_id = obj->getID();
	sellInfo->m_sellFrame = TheGameLogic->getFrame();
	m_sellList.push_front( sellInfo );

	obj->rva0028CDEB( Rva00391F4E( 0, OBJECT_STATUS_SOLD, OBJECT_STATUS_UNSELECTABLE ), TRUE );

	// for everybody, unselect them at this time
	TheGameLogic->deselectObject( obj, PLAYERMASK_ALL, TRUE );

	Drawable *draw = obj->getDrawable();
	if( draw )
		draw->setAnimationLoopDuration( TOTAL_FRAMES_TO_SELL_OBJECT / 2 );

	// We also need to refund all production for the object at start-of-sell time
	ProductionUpdateInterface *production = (ProductionUpdateInterface *)obj->rva0028BC58( 0 );
	if( production )
		production->cancelAndRefundAllProduction();

	// Tell it to stop attacking or anything else it is doing
	if( obj->getAI() )
		obj->getAI()->aiIdle( CMD_FROM_AI );

	// Tell the contain module so it can decide what to do.
	ContainModuleInterface *contain = obj->getContain();
	if( contain )
		contain->onSelling();
}

// BuildAssistant::clearRemovableForConstruction, retail 0x003940B8.
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

// BuildAssistant vslot 18, retail 0x0039361E: whether an allied kind-104
// foundation whose vslot 3 interface test is clear lies within half its major
// radius of pos. Neither retail nor WB reads the fifth argument; its type is
// not evidenced and follows the (builder, player) tail of its siblings.
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

// BuildAssistant::buildObjectNow, retail 0x003952D8 (vslot 14).
Object *BuildAssistant::buildObjectNow( Object *constructorObject, const ThingTemplate *what,
										const Coord3D *pos, Real angle, Player *owningPlayer )
{

	// sanity
	if( what == NULL || pos == NULL )
		return NULL;

	if( owningPlayer == NULL )
		return NULL;

	if( !constructorObject->isKindOf( KINDOF_DOZER ) && !what->isKindOf( KINDOF_30 ) && !what->isKindOf( KINDOF_149 ) )
	{

		// clear out any objects from the building area that are "auto-clearable" when building
		clearRemovableForConstruction( what, pos, angle );

		moveObjectsForConstruction( what, pos, angle, owningPlayer );

	}

	// do the build
	if( constructorObject->isKindOf( KINDOF_DOZER ) )
	{
		AIUpdateInterface *ai = constructorObject->getAI();

		if( ai )
		{
			ai->aiIdle( CMD_FROM_AI ); // stop any current behavior.
			return ai->construct( what, pos, angle, owningPlayer, FALSE, 0 );
		}
		return NULL;

	}
	else if( constructorObject->isKindOf( KINDOF_104 ) )
	{
		FoundationAIInterface *foundation = (FoundationAIInterface *)constructorObject->rva0028BCF4();
		return foundation->construct( what, pos, angle, owningPlayer, FALSE, 0 );
	}
	else
	{

		CreateMask startingStatus;
		if( what->isKindOf( KINDOF_STRUCTURE ) )
			startingStatus.setBit( OBJECT_STATUS_UNDER_CONSTRUCTION );

		Object *obj = TheThingFactory->newObject( what, owningPlayer->getDefaultTeam(), &startingStatus, false );
		obj->setProducer( constructorObject );
		TheGameLogic->rva0023D0C2( obj, constructorObject->get45C() );

		// place on terrain surface
		Coord3D groundPos;
		groundPos.x = pos->x;
		groundPos.y = pos->y;
		groundPos.z = TheTerrainLogic->getGroundHeight( groundPos.x, groundPos.y );
		obj->setPosition( &groundPos );

		obj->setOrientation( angle );

		if( !obj->isKindOf( KINDOF_2 ) )
			obj->rva0028B4CE( TheTerrainLogic->getLayerForDestination( obj, pos ) );

		if( !obj->isKindOf( KINDOF_189 ) )
			TheAI->pathfinder()->AddObjectToPathfindMap( obj );

		// notify the player that this thing has come into existence
		if( obj->isKindOf( KINDOF_STRUCTURE ) )
		{
			owningPlayer->onStructureCreated( constructorObject, obj );
			if( !constructorObject->isKindOf( KINDOF_156 ) )
				owningPlayer->onStructureConstructionComplete( constructorObject, obj, FALSE );
		}
		else
		{
			owningPlayer->onUnitCreated( constructorObject, obj );

			DrawableList list;
			list.push_back( obj->getDrawable() );
			pickAndPlayUnitVoiceResponse( &list, GameMessage::MSG_BFME2_0x7DA, 0 );
		}

		reinterpret_cast<Rva0028CBFD *>( obj )->rva0028CBFD();

		return obj;

	}

}
