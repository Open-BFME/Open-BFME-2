// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/Libraries/Include/Lib
// stlport
// ??0Object@@QAE@PBVThingTemplate@@PBUCreateMask@@PAVTeam@@W4ObjectID@@@Z
// Object::Object retail 0x00298EA9 3525 bytes RET 0x14 (four arguments plus
// the hidden most-derived flag of a class with a virtual base).
//
// Reconstructed from the banked attempt (reverse/attempts/0x00298ea9.cpp,
// Zero Hour Object::Object donor; WorldBuilder twin 0x00CBA4F0). The real
// STLport list/vector/map headers are required: their allocator temporaries
// take the dead template slot [ebp+0xB] and the hidden most-derived flag slot
// is then free for the spilled module cursor, as in retail (the private
// _STL views placed them in the flag slot and grew the frame). Retail tests
// the guarding-helper key guard (bit 8) with byte operations because the
// constant 0x100 is also the defection kind-of test on dword +0x118 (bit 136,
// read as byte +0x119 bit 0); the same holds for the repulsor 0x2000 test and
// the firing-tracker data guard (bit 13). The m_249 module-kind query result
// is held in a local (cmp eax ebx) and the attack-priority team name goes
// through the prototype getter (receiver before the return slot push).
// Callees use their ledger spellings: map<int void*> ctor 0x0033C432 with the
// rowed Rva002913EB clear, bitset<128>::reset 0x0024CA24, protected setID,
// getNthName returning BFMERetailAsciiString, and GameLogic::rva0023CAD9 /
// registerObject (declared in the canonical GameLogic view).

#include <list>
#include <vector>
#include <map>
#include "ascii_string.h"
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#include "Common/Snapshot.h"
#include "Coord3D.h"
#include "../../Common/GameLogicObjectLookupView.h"

#pragma intrinsic(memset)
template <> bool StringBase<char>::isEmpty() const throw();

class Team;
class Player;
class Object;
class Thing;
class ModuleData;
class Module;
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ModuleType { MODULETYPE_BEHAVIOR = 0 };

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	Overridable *m_nextOverride;				// +0x04
};

class BFMERetailAsciiString : public AsciiString
{
};

struct ModuleInfoEntry { unsigned char m_data[20]; };
class ModuleInfo
{
public:
	int getCount() const { return m_end - m_begin; }
	BFMERetailAsciiString getNthName(int i) const;
	const ModuleData *getNthData(int i) const;
	ModuleInfoEntry *m_begin;
	ModuleInfoEntry *m_end;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad008[0x10 - 0x8];
	float m_10;						// +0x10
	unsigned char m_pad014[0xA0 - 0x14];
	unsigned char m_geometryInfo[0x5C];			// +0xA0
	unsigned char m_0fc[0xC];				// +0xFC
	unsigned int m_kindOf[5];				// +0x108
	unsigned char m_pad11C[0x2E4 - 0x11C];
	ModuleInfo m_behaviorModuleInfo;			// +0x2E4
	unsigned char m_pad2EC[0x4AC - 0x2EC];
	float m_visionRange;					// +0x4AC
	float m_shroudClearingRange;				// +0x4B0
	float friend_calcVisionRange() const { return m_visionRange; }
	float friend_calcShroudClearingRange() const { return m_shroudClearingRange; }
	float friend_calcShroudRange() const { return m_shroudRange; }
	unsigned char m_pad4B4[0x4CC - 0x4B4];
	float m_shroudRange;					// +0x4CC
	unsigned char m_pad4D0[0x554 - 0x4D0];
	unsigned int m_occlusionDelay;				// +0x554
};
class Rva0033A951 { public: bool rva0033A951(); };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class ModuleDataBase
{
public:
	virtual void slot0();
	NameKeyType m_moduleTagNameKey;
};

// Helper module data: vftable 0x00C4ED70 and the tag key at +4.
class ObjectHelperModuleData : public ModuleDataBase
{
public:
	ObjectHelperModuleData() {}
	virtual ~ObjectHelperModuleData() {}
	void setModuleTagNameKey(NameKeyType key) { m_moduleTagNameKey = key; }
};

class BehaviorModule;
class BodyModuleInterface;
class ContainModuleInterface;
class AIUpdateInterface;

class BehaviorModuleInterface
{
public:
	virtual BodyModuleInterface *getBody();
	virtual void s1();
	virtual ContainModuleInterface *getContain();
	virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
	virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
	virtual void s18();
	virtual AIUpdateInterface *getAIUpdateInterface();
};

class BehaviorModule
{
public:
	virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
	virtual NameKeyType getModuleNameKey() const;
	virtual void onObjectCreated();
	unsigned char m_pad04[8];
	BehaviorModuleInterface m_interface;		// +0x0C
};

class ModuleFactory
{
public:
	Module *newModule(Thing *thing, const AsciiString &name, const ModuleData *data, ModuleType type);
};
extern ModuleFactory *TheModuleFactory;

class ObjectSMCHelper { public: ObjectSMCHelper(Thing *thing, const ModuleData *data); unsigned char m_data[0x24]; };
class ObjectRecoveryHelper { public: ObjectRecoveryHelper(Thing *thing, const ModuleData *data); unsigned char m_data[0x20]; };
class ObjectRepulsorHelper { public: ObjectRepulsorHelper(Thing *thing, const ModuleData *data); unsigned char m_data[0x20]; };
class ObjectDefectionHelper { public: ObjectDefectionHelper(Thing *thing, const ModuleData *data); unsigned char m_data[0x30]; };
class Rva004DF418 { public: Rva004DF418(Thing *thing, const ModuleData *data); unsigned char m_data[0x28]; };
class ObjectWeaponStatusHelper { public: ObjectWeaponStatusHelper(Thing *thing, const ModuleData *data); unsigned char m_data[0x20]; };
class FiringTracker { public: FiringTracker(Thing *thing, const ModuleData *data); unsigned char m_data[0x5C]; };
class Rva004DD7E3 { public: Rva004DD7E3(int obj); unsigned char m_data[0x4C]; };
class Rva0039ADF3 { public: Rva0039ADF3(Object *obj); unsigned char m_data[0x40]; };

class Rva00291775AsciiField
{
public:
	AsciiString get() const;
	unsigned char m_pad000[0x228];
	int m_initialTeamAttitude;				// +0x228
};
struct AsciiNotEmpty
{
	static bool test(const AsciiString &s) { return !((const StringBase<char> *)&s)->isEmpty(); }
};
class AttackPriorityInfo { public: unsigned char m_pad[4]; AsciiString m_name; };
class ScriptEngine { public: const AttackPriorityInfo *getAttackInfo(const AsciiString &name); };
extern ScriptEngine *TheScriptEngine;

struct ObjectTeamView
{
	unsigned char m_pad00[0x30];
	Rva00291775AsciiField *m_prototype;		// +0x30
	Rva00291775AsciiField *getPrototype() const { return m_prototype; }
};

class AIUpdateInterface
{
public:
	void rva0026DE3B(int attitude);
	unsigned char m_pad00[0x70];
	const AttackPriorityInfo *m_attackInfo;	// +0x70
};

extern GameLogic *TheGameLogic;
class Rva004381B0 { public: void rva004381B0(float value); };

struct AIDataView { unsigned char m_pad[0x64]; bool m_enableRepulsors; };
struct AIView { unsigned char m_pad[0x18]; AIDataView *m_aiData; };
extern AIView *TheAI;

struct DefaultTeamPlayer { unsigned char m_pad[0x2EC]; Team *m_defaultTeam; };
struct PlayerListView { unsigned char m_pad[0x18]; DefaultTeamPlayer *m_neutral; };
extern PlayerListView *ThePlayerList;

class Radar { public: void addObject(Object *obj); };
extern Radar *TheRadar;

class ObjectFilter { public: bool testTemplate(const ThingTemplate *tt, const Player *a, const Player *b); };
struct Rva00DFE758View { unsigned char m_pad[0xEB4]; ObjectFilter m_filter; };
extern Rva00DFE758View *g_00DFE758;

class Thing
{
public:
	Thing(const ThingTemplate *thingTemplate);
	virtual ~Thing();
	const ThingTemplate *m_template;			// +0x04
	unsigned char m_pad08[0x58];
};

class BfmeCtorFirstBase001B3A20
{
public:
	virtual void slot() = 0;
};
class BfmeCtorVirtualBase001B3A20
{
public:
	virtual void slot() = 0;
};
class BfmeCtor001B3A20 : public BfmeCtorFirstBase001B3A20, public virtual BfmeCtorVirtualBase001B3A20
{
public:
	BfmeCtor001B3A20() throw();
};
struct Rva00BFC2B8Base { virtual void base06CSlot0(); };
struct Rva00BFC290Base { virtual void base070Slot0(); };

template <int N> class BitFlags;
struct CreateMask;
template <int N> class BitFlags
{
public:
	BitFlags();
	BitFlags(const BitFlags &that);
	unsigned int m_bits[(N + 31) / 32];
};
class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &that);
	virtual ~GeometryInfo();
	unsigned char m_data[0x58];
};
struct ZeroCoord3D { float x, y, z; ZeroCoord3D() { x = 0.0f; y = 0.0f; z = 0.0f; } };
struct ZeroCoord2D { float x, y; ZeroCoord2D() { x = 0.0f; y = 0.0f; } };
struct ZeroICoord2D { int x, y; ZeroICoord2D() { x = 0; y = 0; } };
struct ZeroICoord3D { int x, y, z; ZeroICoord3D() { x = 0; y = 0; z = 0; } };
class Rva0042526Member { public: Rva0042526Member(); unsigned char m_data[0x4C]; };
class Vector4 { public: __forceinline Vector4() {} float X, Y, Z, W; };
class Matrix3D { public: __forceinline Matrix3D() {} Vector4 Row[3]; };
class Rva002913EB
{
public:
	void rva002913EB();
};
class Rva001EAE6FHelper { public: Rva001EAE6FHelper() { clear80(); } Rva001EAE6FHelper *clear80() throw(); unsigned char m_data[0x80]; };
class WeaponSet { public: WeaponSet(); virtual ~WeaponSet(); unsigned char m_data[0x3C]; };
namespace _STL {
template <unsigned _Bits> class bitset
{
public:
	bitset() { reset(); }
	bitset<_Bits> &reset();
	unsigned long m_words[(_Bits + 31) / 32];
};
}
class Rva0028C58B { public: Rva0028C58B() { rva0028C58B(); } Rva0028C58B *rva0028C58B(); unsigned char m_data[0x14]; };
class TTriggerInfo { public: TTriggerInfo(); unsigned char m_data[8]; };

struct CameraMarker
{
	~CameraMarker();
	CameraMarker *m_next;
	AsciiString m_name;
};
struct BfmePod124 { int a[31]; };
struct CreateMask { BitFlags<117> m_status; };
class Rva004E04FD { public: Rva004E04FD(); ~Rva004E04FD(); unsigned char m_data[0x18]; };

class Object : public Thing, public Snapshot, public BfmeCtor001B3A20, public Rva00BFC2B8Base, public Rva00BFC290Base
{
public:
	Object(const ThingTemplate *tt, const CreateMask *mask, Team *team, ObjectID id);

	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void DoXfer(Xfer *xfer);
	virtual void slot();
	virtual void base06CSlot0();
	virtual void base070Slot0();
	virtual ~Object();

protected:
	void setID(ObjectID id);
public:
	void setTeam(Team *team);
	Module *findModule(NameKeyType key) const;
	void *rva0028BD92(int kind);
	void rva0028DCC4();

	ObjectID m_id;						// +0x74
	ObjectID m_producerID;					// +0x78
	ObjectID m_builderID;					// +0x7C
	int m_80;						// +0x80
	void *m_drawable;					// +0x84
	AsciiString m_name;					// +0x88
	int m_8c;						// +0x8C
	int m_90;						// +0x90
	BitFlags<117> m_status;					// +0x94
	Rva004DD7E3 *m_a4;					// +0xA4
	GeometryInfo m_geometryInfo;				// +0xA8
	GeometryInfo *m_geometryClone;				// +0x104
	const unsigned char *m_108;				// +0x108
	Rva0042526Member m_10c;					// +0x10C
	Matrix3D m_158;						// +0x158
	int m_188;						// +0x188
	unsigned char m_pad18C[0x18];
	bool m_1a4;						// +0x1A4
	bool m_1a5;						// +0x1A5
	bool m_1a6;						// +0x1A6
	void *m_group;						// +0x1A8
	float m_1ac;						// +0x1AC
	float m_visionRange;					// +0x1B0
	float m_shroudClearingRange;				// +0x1B4
	float m_1b8;						// +0x1B8
	float m_shroudRange;					// +0x1BC
	float m_1c0;						// +0x1C0
	float m_1c4;						// +0x1C4
	BitFlags<11> m_disabledMask;				// +0x1C8
	unsigned int m_disabledTillFrame[11];			// +0x1CC
	unsigned int m_1f8[11];					// +0x1F8
	void *m_224;						// +0x224
	void *m_228, *m_22c, *m_230, *m_234, *m_238, *m_23c;	// +0x228
	void *m_firingTracker;					// +0x240
	BehaviorModule **m_behaviors;				// +0x244
	bool m_248;						// +0x248
	bool m_249;						// +0x249
	Module *m_24c;						// +0x24C
	ContainModuleInterface *m_contain;			// +0x250
	BodyModuleInterface *m_body;				// +0x254
	AIUpdateInterface *m_ai;				// +0x258
	BehaviorModule *m_physics;				// +0x25C
	void *m_radarData;					// +0x260
	Rva0039ADF3 *m_experienceTracker;			// +0x264
	_STL::map<int, void *> m_268;				// +0x268
	Object *m_containedBy;					// +0x274
	ObjectID m_xferContainedByID;				// +0x278
	unsigned int m_containedByFrame;			// +0x27C
	float m_constructionPercent;				// +0x280
	Rva001EAE6FHelper m_upgrades;				// +0x284
	ObjectTeamView *m_team;				// +0x304
	AsciiString m_originalTeamName;				// +0x308
	int m_indicatorColor;					// +0x30C
	ZeroCoord3D m_healthBoxOffset;			// +0x310
	ZeroCoord2D m_31c;					// +0x31C
	float m_324;						// +0x324
	ZeroICoord2D m_328;					// +0x328
	WeaponSet m_weaponSet;					// +0x330
	_STL::bitset<128> m_370;				// +0x370
	int m_380;						// +0x380
	unsigned char m_384[6];					// +0x384
	unsigned char m_pad38A[2];
	ZeroCoord3D m_38c;					// +0x38C
	void *m_398;						// +0x398
	void *m_39c;						// +0x39C
	void *m_3a0;						// +0x3A0
	Rva0028C58B m_3a4;					// +0x3A4
	int m_3b8;						// +0x3B8
	int m_3bc;						// +0x3BC
	TTriggerInfo m_triggerInfo[7];				// +0x3C0
	int m_3f8;						// +0x3F8
	ZeroICoord3D m_3fc;					// +0x3FC
	_STL::list<CameraMarker> m_408;				// +0x408
	int m_40c;						// +0x40C
	int m_410;						// +0x410
	ZeroCoord2D m_414;					// +0x414
	AsciiString m_41c;					// +0x41C
	AsciiString m_420;					// +0x420
	AsciiString m_424;					// +0x424
	unsigned int m_428;					// +0x428
	int m_42c;						// +0x42C
	int m_430;						// +0x430
	bool m_434;						// +0x434
	bool m_435;						// +0x435
	bool m_436, m_437, m_438, m_439, m_43a, m_43b, m_43c;	// +0x436
	_STL::list<BfmePod124> m_440;				// +0x440
	float m_444;						// +0x444
	int m_448;						// +0x448
	int m_44c;						// +0x44C
	void *m_450;						// +0x450
	bool m_454, m_455, m_456;				// +0x454
	int m_458, m_45c, m_460, m_464;				// +0x458
	Rva004E04FD m_468;					// +0x468
	bool m_480;						// +0x480
	int m_484;						// +0x484
	int m_488;						// +0x488
	bool m_48c;						// +0x48C
	int m_490;						// +0x490
	AsciiString m_494;					// +0x494
	int m_498;						// +0x498
	int m_49c;						// +0x49C
	int m_4a0;						// +0x4A0
	_STL::vector<int> m_4a4;				// +0x4A4
	bool m_4b0;						// +0x4B0
	_STL::vector<const ModuleData *> m_4b4;		// +0x4B4
	unsigned int m_4c0;					// +0x4C0
	void *m_4c4;						// +0x4C4
	int m_4c8;						// +0x4C8
	int m_4cc;						// +0x4CC
};

Object::Object(const ThingTemplate *tt, const CreateMask *mask, Team *team, ObjectID id) :
	Thing(tt),
	m_id(INVALID_OBJECT_ID),
	m_producerID(INVALID_OBJECT_ID),
	m_builderID(INVALID_OBJECT_ID),
	m_80(0),
	m_drawable(0),
	m_8c(0),
	m_90(0),
	m_status(mask->m_status),
	m_a4(0),
	m_geometryInfo(*(const GeometryInfo *)tt->m_geometryInfo),
	m_geometryClone(&m_geometryInfo),
	m_108(tt->m_0fc),
	m_188(0),
	m_1a4(false),
	m_1a5(false),
	m_1a6(false),
	m_group(0),
	m_1ac(0.0f),
	m_1b8(0.0f),
	m_1c0(0.0f),
	m_1c4(0.0f),
	m_224(0), m_228(0), m_22c(0), m_230(0), m_234(0), m_238(0), m_23c(0),
	m_firingTracker(0),
	m_behaviors(0),
	m_248(false),
	m_249(false),
	m_contain(0),
	m_body(0),
	m_ai(0),
	m_physics(0),
	m_radarData(0),
	m_experienceTracker(0),
	m_containedBy(0),
	m_xferContainedByID(INVALID_OBJECT_ID),
	m_containedByFrame(0),
	m_constructionPercent(-1.0f),
	m_team(0),
	m_indicatorColor(0),
	m_324(0.0f),
	m_380(0),
	m_398(0),
	m_39c(0),
	m_3a0(0),
	m_3b8(0),
	m_3bc(0),
	m_3f8(0),
	m_40c(1),
	m_410(0),
	m_42c(0),
	m_430(0),
	m_435(false), m_436(false), m_437(false), m_438(false), m_439(false), m_43a(false), m_43b(false), m_43c(false),
	m_444(0.0f),
	m_448(0),
	m_44c(0),
	m_450(0),
	m_454(false), m_455(false), m_456(false),
	m_458(0), m_45c(0), m_460(0), m_464(0),
	m_480(false),
	m_484(0),
	m_488(0),
	m_48c(false),
	m_490(-1),
	m_498(1),
	m_49c(-1),
	m_4a0(0),
	m_4b0(false),
	m_4c0(TheGameLogic ? TheGameLogic->getFrame() : 0),
	m_4c4(0),
	m_4c8(0),
	m_4cc(0)
{
	((Rva002913EB *)&m_268)->rva002913EB();

	int i;
	for (i = 0; i < 11; i++)
	{
		m_disabledTillFrame[i] = 0;
		m_1f8[i] = 0;
	}
	memset(m_384, 0xFF, sizeof(m_384));

	if (TheGameLogic == 0 || tt == 0)
		return;

	tt = (const ThingTemplate *)((Overridable *)tt)->friend_getFinalOverride();

	m_visionRange = tt->friend_calcVisionRange();
	m_shroudClearingRange = tt->friend_calcShroudClearingRange();
	if (m_shroudClearingRange == -1.0f)
		m_shroudClearingRange = m_visionRange;
	m_shroudRange = tt->friend_calcShroudRange();

	if (!(m_template->m_kindOf[0] & 4))
		m_a4 = new Rva004DD7E3((int)this);

	AsciiString modName;

	if (id == INVALID_OBJECT_ID)
		setID((ObjectID)TheGameLogic->rva0023CAD9());
	else
		setID(id);

	int totalModules = tt->m_behaviorModuleInfo.getCount() + 7;
	m_behaviors = new BehaviorModule *[totalModules + 1];
	for (i = 0; i <= totalModules; i++)
		m_behaviors[i] = 0;
	BehaviorModule **curB = m_behaviors;
	const ModuleInfo &mi = tt->m_behaviorModuleInfo;

	setTeam(team ? team : ThePlayerList->m_neutral->m_defaultTeam);

	static const NameKeyType smcHelperModuleDataTagNameKey = TheNameKeyGenerator->nameToKey("ModuleTag_SMCHelper");
	static ObjectHelperModuleData smcModuleData;
	smcModuleData.setModuleTagNameKey(smcHelperModuleDataTagNameKey);
	m_230 = new ObjectSMCHelper((Thing *)this, (const ModuleData *)&smcModuleData);
	*curB++ = (BehaviorModule *)m_230;

	static const NameKeyType recoveryHelperModuleDataTagNameKey = TheNameKeyGenerator->nameToKey("ModuleTag_RecoveryHelper");
	static ObjectHelperModuleData recoveryModuleData;
	recoveryModuleData.setModuleTagNameKey(recoveryHelperModuleDataTagNameKey);
	m_22c = new ObjectRecoveryHelper((Thing *)this, (const ModuleData *)&recoveryModuleData);
	*curB++ = (BehaviorModule *)m_22c;

	if (TheAI != 0 && TheAI->m_aiData->m_enableRepulsors && (m_template->m_kindOf[1] & 0x2000))
	{
		static const NameKeyType repulsorHelperModuleDataTagNameKey = TheNameKeyGenerator->nameToKey("ModuleTag_RepulsorHelper");
		static ObjectHelperModuleData repulsorModuleData;
		repulsorModuleData.setModuleTagNameKey(repulsorHelperModuleDataTagNameKey);
		m_228 = new ObjectRepulsorHelper((Thing *)this, (const ModuleData *)&repulsorModuleData);
		*curB++ = (BehaviorModule *)m_228;
	}

	if (!(tt->m_kindOf[0] & 0x40) && !(tt->m_kindOf[3] & 2) && !(tt->m_kindOf[4] & 0x100))
	{
		static const NameKeyType defectionModuleDataTagNameKey = TheNameKeyGenerator->nameToKey("ModuleTag_DefectionHelper");
		static ObjectHelperModuleData defectionModuleData;
		defectionModuleData.setModuleTagNameKey(defectionModuleDataTagNameKey);
		m_238 = new ObjectDefectionHelper((Thing *)this, (const ModuleData *)&defectionModuleData);
		*curB++ = (BehaviorModule *)m_238;
	}

	static const NameKeyType guardingHelperModuleDataTagNameKey = TheNameKeyGenerator->nameToKey("ModuleTag_GuardingHelper");
	static ObjectHelperModuleData guardingModuleData;
	guardingModuleData.setModuleTagNameKey(guardingHelperModuleDataTagNameKey);
	m_23c = new Rva004DF418((Thing *)this, (const ModuleData *)&guardingModuleData);
	*curB++ = (BehaviorModule *)m_23c;

	if (((Rva0033A951 *)tt)->rva0033A951())
	{
		static const NameKeyType weaponStatusModuleDataTagNameKey = TheNameKeyGenerator->nameToKey("ModuleTag_WeaponStatusHelper");
		static ObjectHelperModuleData weaponStatusModuleData;
		weaponStatusModuleData.setModuleTagNameKey(weaponStatusModuleDataTagNameKey);
		m_234 = new ObjectWeaponStatusHelper((Thing *)this, (const ModuleData *)&weaponStatusModuleData);
		*curB++ = (BehaviorModule *)m_234;

		static const NameKeyType firingTrackerModuleDataTagNameKey = TheNameKeyGenerator->nameToKey("ModuleTag_FiringTrackerHelper");
		static ObjectHelperModuleData firingTrackerModuleData;
		firingTrackerModuleData.setModuleTagNameKey(firingTrackerModuleDataTagNameKey);
		m_firingTracker = new FiringTracker((Thing *)this, (const ModuleData *)&firingTrackerModuleData);
		*curB++ = (BehaviorModule *)m_firingTracker;
	}

	for (int modIdx = 0; modIdx < mi.getCount(); ++modIdx)
	{
		modName = mi.getNthName(modIdx);
		if (modName.isEmpty())
			continue;

		BehaviorModule *newMod = (BehaviorModule *)TheModuleFactory->newModule((Thing *)this, modName, mi.getNthData(modIdx), MODULETYPE_BEHAVIOR);
		*curB++ = newMod;

		BehaviorModuleInterface *bmi = &newMod->m_interface;
		BodyModuleInterface *body = bmi->getBody();
		if (body)
			m_body = body;

		ContainModuleInterface *contain = bmi->getContain();
		if (contain)
			m_contain = contain;

		AIUpdateInterface *ai = bmi->getAIUpdateInterface();
		if (ai)
			m_ai = ai;

		static NameKeyType key_PhysicsUpdate = TheNameKeyGenerator->nameToKey("PhysicsBehavior");
		if (newMod->getModuleNameKey() == key_PhysicsUpdate)
			m_physics = newMod;

		static NameKeyType key_StealthUpdate = TheNameKeyGenerator->nameToKey("StealthUpdate");
		if (newMod->getModuleNameKey() == key_StealthUpdate)
			m_4b4.push_back((const ModuleData *)newMod);
	}

	*curB = 0;

	static NameKeyType key_SquishCollide = TheNameKeyGenerator->nameToKey("SquishCollide");
	if (findModule(key_SquishCollide))
		m_248 = true;

	static NameKeyType key_EmotionTrackerUpdate = TheNameKeyGenerator->nameToKey("EmotionTrackerUpdate");
	m_24c = findModule(key_EmotionTrackerUpdate);

	void *kind2AModule = rva0028BD92(0x2a);
	if (kind2AModule)
		m_249 = true;

	AIUpdateInterface *ai = m_ai;
	if (ai)
	{
		ai->rva0026DE3B(m_team->m_prototype->m_initialTeamAttitude);
		if (m_team && m_team->m_prototype && AsciiNotEmpty::test(m_team->m_prototype->get()))
		{
			AsciiString name = m_team->getPrototype()->get();
			const AttackPriorityInfo *info = TheScriptEngine->getAttackInfo(name);
			if (info && !((const StringBase<char> *)&info->m_name)->isEmpty())
				ai->m_attackInfo = info;
		}
	}

	m_experienceTracker = new Rva0039ADF3(this);

	for (BehaviorModule **b = m_behaviors; *b; ++b)
		(*b)->onObjectCreated();

	m_434 = (tt->m_kindOf[0] >> 1) & 1;
	m_435 = true;

	TheRadar->addObject(this);
	TheGameLogic->registerObject(this);

	m_428 = tt->m_occlusionDelay + TheGameLogic->getFrame();

	if (g_00DFE758->m_filter.testTemplate(tt, 0, 0))
		((Rva004381B0 *)TheGameLogic->getManager178())->rva004381B0(tt->m_10);

	rva0028DCC4();
}
