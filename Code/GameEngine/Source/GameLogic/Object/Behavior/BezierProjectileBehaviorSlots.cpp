// cl: /DNDEBUG /MD /GX -Ireference/open-bfme-1/game/GameEngine/Source/Common /ICode/Libraries/Include /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_bezierprojectilebehavior
// stlport
//
// BezierProjectileBehavior overrides on the two interface vtables its ctor
// (installs 0x00C41E04 +0, 0x00C53570 +0x0C, 0x00C41DF8 +0x10, see the matched
// dtor 0x0045BF6E) puts at +0x20 (0x00C41DE0, the projectile interface) and
// +0x24 (0x00C41DC8). Each is compiled with its subobject this. Names are by
// address. Layout from the dtor and the BFME 1 donor
// BezierProjectileBehavior_handle.cpp: m_object +0x08, the launcher ID at
// +0x28 (slot 2 of 0x00C41DE0 is the shared [this+8] getter 0x0030F45F),
// +0x38 passed through, the launch helper at +0x40 and the 12-byte path vector
// at +0x44.
//
// ?rva0045BF06@BezierProjectileBehavior@@UAE_NPAVObject@@@Z, retail
// 0x0045BF06, 104 bytes: +0x20 slot 4; false on an empty path, no helper, or
// a victim of KindOf 0x6D (bit 13 of the template word +0x114) or dead (Object +0x438 bit 0); otherwise the
// helper 0x002CBA7C with the launcher found by ID, the owner, the victim and
// +0x38. Close to the donor's handle(), without its status test.
// ?rva0045BF06@BezierProjectileBehavior@@W3AE_NPAVObject@@@Z, retail
// 0x0045C01E, 8 bytes: +0x24 slot 1, the this-4 adjustor thunk to it
// (emitted with the vftables in BezierProjectileBehaviorDtor.cpp).
// ?rva0045B4C0@BezierProjectileBehavior@@UAEXPAVObject@@HH@Z, retail
// 0x0045B4C0, 34 bytes: +0x24 slot 0; +0x20 slot 3 (0x0045CD6E) on the victim
// when +0x20 slot 4 accepts it.
// ?rva0045B4E2@BezierProjectileBehavior@@UAEXH@Z, retail 0x0045B4E2, 15
// bytes: +0x20 slot 5; kills the owner (damage type 8, death type 0).
// ?projectileLaunchAtObjectOrPosition@BezierProjectileBehavior@@UAEXPAVObject@@PBUCoord3D@@0HHPBURva0045B936Arg@@PAVRva002CBA7C@@PBVMatrix3D@@@Z,
// retail 0x0045B936, 197 bytes: +0x20 slot 0, the shape of ZH
// MissileAIUpdate::projectileLaunchAtObjectOrPosition plus a transform
// argument: stores the launcher ID (+0x28) and bonus condition (+0x74), the
// victim ID (+0x38), arg 6's +4 (+0x3C) and the helper (+0x40), places the
// projectile by the transform or the pinned cdecl 0x002CA753 (whose
// null-launcher destroyObject opening is ZH positionProjectileForLaunch),
// copies the launcher's (else its own) position to +0x2C, runs primary slot
// 13 (0x0045BB8A) on the victim, then sets condition bit 4*32+26 and status 5.

// BezierProjectileBehavior's class views: one spelling shared by every file of this TU.
// Retail calls free directly (the game allocator), not through the CRT
// import: read the CRT headers without dllimport.
// Target uses an embedded GeometryInfo at +0xA8; its full size is not
// established here. This accessor preserves that offset without inventing it.
#define _CRTIMP
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <math.h>
#include <vector>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Common/PartitionRangeQueryCallView.h"
#include "../../../Common/GameLogicObjectLookupView.h"
#include "matrix3d.h"
#include "../../../Common/Thing/thing.h"

enum NameKeyType
{
	NK_UNKNOWN = 0
};

#include "../../../../Include/Common/ObjectModule.h"

enum WeaponSlotType { BFME_WEAPON_SLOT_0 };

// LINK: 0x002CBA7C is rowed as WeaponTemplate::shouldProjectileCollideWith (WeaponTemplateShouldProjectileCollideWith.cpp)
// and 0x002CA753 as Weapon::positionProjectileForLaunch (Weapon_positionProjectileForLaunch_Rva002CA753.cpp).
#include "../../../../Include/GameLogic/Weapon.h"

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1
};

#include "../../../../Include/Common/TeamBFME2.h"

class PooledString;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
#include "../../../../Include/Common/BfmeXfer.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Player;
// a victim of KindOf bit 13 or dead (Object +0x438 bit 0); otherwise the
class ModuleData;
class FXList;

// The native erase call at +0x9A reaches 0x002A133B, the rowed twelve-byte
// POD range erase. vector<Coord3D>::erase owns a different body at 0x00081A24.
// Use the existing carrier only for this representation-preserving operation;
// retain the Coord3D vector's construction, layout and lifetime below.
struct Gen_p12pod { int a[3]; };
namespace _STL {
template <> Gen_p12pod *vector<Gen_p12pod, allocator<Gen_p12pod> >::erase(Gen_p12pod*, Gen_p12pod*);
}

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	Rva000421C8 *link(Rva000421C8 *next); // 0x00625790
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next; // +0x04
};
// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};
// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj; // +0x08
};
// vftable 0x00BFBC90, allow 0x00260EB1: +0x08 the object, +0x0C
// relationship flags, +0x10 whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
	: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj; // +0x08
	int m_flags; // +0x0C
	bool m_match; // +0x10
	char m_pad11[0x3];
};

extern PartitionManager *ThePartitionManager;

enum DamageType
{
	DAMAGE_RVA0045C026_8 = 8
};

enum DeathType
{
	DEATH_NORMAL = 0,
	DEATH_RVA0045C026_10 = 10
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_RVA0045C026_4 = 4,
	OBJECT_STATUS_5 = 5
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0,
	CELLSHROUD_FOGGED = 1
};

enum CommandSourceType { COMMAND_SOURCE_2 = 2 };

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum SleepyUpdatePhase;

class Drawable
{
public:
	void setDrawableHidden(bool hidden); // 0x00271601
	void fadeOut(unsigned int frames); // 0x00270756
	void fadeIn(unsigned int frames); // 0x002707A8
	void rva00272D77(unsigned int a, unsigned int b); // 0x00272D77
};

class ThingTemplate
{
public:
	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[4];	// +0x108
};

// This partial geometry view reads +0x10 inline in the retail update. Keep
// its helper distinct from the generic accessor emitted by +0x18 views.
class GeometryInfo
{
public:
	bool CollidesWith(const Coord3D &, float, const GeometryInfo &, const Coord3D &, float) const;
	float getMaxHeightAbovePosition() const;
	float projectileCollisionRadius() const { return radius; }
	char m_pad00[0x10];
	float radius; // +0x10
};

// The model-condition words at Object +0x10C.
struct BezierModelFlags
{
	unsigned words[19];
	__forceinline unsigned test(int i) const { return words[i >> 5] & (1u << (i & 31)); }
	__forceinline void set(int i) { words[i >> 5] |= 1u << (i & 31); }
};

class AICommandInterface
{
public:
	void rva0045003E(int v, CommandSourceType src);
	void aiIdle(CommandSourceType src);
};
struct ObjectAI
{
	char m_pad[0x20];
	AICommandInterface m_ai; // +0x20
};

class Object : public Thing
{
public:
	void rva0028EC68(int what, void *source, int value);	// 0x0028EC68
	void kill(DamageType damageType, DeathType deathType);	// 0x002984D4
	Drawable *getDrawable() const;	// 0x005508E2
	void setStatus(ObjectStatusTypes bit, bool flag);	// 0x0023DB0E
	void rva0028AE6D();
	int rva0028B511() const;
	void setLayer(PathfindLayerEnum layer);
	Int rva0028F4EF();		// 0x0028F4EF
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;	// 0x0028D2A2
	void updateShroudNow();		// 0x0028C11A
	void rva0023D3AF(void *frame);	// 0x0023D3AF
	ObjectID getID() const { return m_id; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getWeaponBonusCondition copy loses to the first-in-order copy. No flags touched.
	unsigned int bfme_getWeaponBonusCondition_a1a45() const { return m_380; }
	ObjectAI *getAI() const { return m_ai258; }
	__forceinline void setModelConditionBit(int bit)
	{
		if (m_modelConditionFlags.test(bit) == 0)
		{
			m_modelConditionFlags.set(bit);
			rva0028AE6D();
		}
	}
	// Model condition 122 (+0x118 bit 26), notifying through 0x0028AE6D.
	__forceinline void setModelConditionState122()
	{
		if (m_modelConditionFlags.test(122))
			return;
		m_modelConditionFlags.set(122);
		rva0028AE6D();
	}
	__forceinline void setNextPosition(const Coord3D *p) { m_nextPositionValid = true; m_nextPosition = *p; }
	__forceinline UnsignedInt isKindOf(Int kind) const
	{
		return m_template->m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	unsigned char m_pad060[0x74 - 0x60];
	ObjectID m_id;				// +0x74
	ObjectID m_producerID;			// +0x78
	unsigned char m_pad07C[0xA8 - 0x7C];
	GeometryInfo m_geometry;		// +0xA8
	unsigned char m_padBC[0x10C - 0xBC];
	BezierModelFlags m_modelConditionFlags;	// +0x10C
	unsigned char m_pad158[0x198 - 0x158];
	Coord3D m_nextPosition;			// +0x198
	unsigned char m_pad1A4[2];
	bool m_nextPositionValid;		// +0x1A6
	unsigned char m_pad1A7[0x258 - 0x1A7];
	ObjectAI *m_ai258;			// +0x258
	void *m_25C;				// +0x25C
	unsigned char m_pad260[0x304 - 0x260];
	Team *m_team;				// +0x304
	unsigned char m_pad308[0x380 - 0x308];
	unsigned int m_380;			// +0x380
	unsigned char m_pad384[0x438 - 0x384];
	unsigned char m_438;			// +0x438
};

extern GameLogic *TheGameLogic;

// Match the recovered 0x002CAB3A provider's hidden-result ABI.
struct TargetCoord
{
	float x, y, z;
	TargetCoord() {}
	TargetCoord(float a, float b, float c) : x(a), y(b), z(c) {}
	TargetCoord(const Coord3D &p) : x(p.x), y(p.y), z(p.z) {}
};

class WeaponTemplate
{
public:
	bool shouldProjectileCollideWith(const Object *launcher, const Object *owner, const Object *victim, ObjectID victimID) const;
	TargetCoord adjustTargetPositionOnVictim(Object *source, Object *victim, Bool flag);	// 0x002CAB3A
	Real getMinimumAttackRange() const;	// 0x002C92FA
	__declspec(dllimport) __forceinline Real getWeaponSpeed() const { return m_weaponSpeed; }
	__declspec(dllimport) __forceinline Real getMinWeaponSpeed() const { return m_minWeaponSpeed; }
	Real getMaxWeaponSpeed() const { return m_maxWeaponSpeed; }
	__declspec(dllimport) __forceinline Bool isScaleWeaponSpeed() const { return m_scaleWeaponSpeed; }
	const AsciiString &getName() const { return m_name; }
	char m_pad00[0x8];
	AsciiString m_name;			// +0x08
	char m_pad0C[0x68 - 0x0C];
	Real m_weaponSpeed;			// +0x68
	Real m_minWeaponSpeed;			// +0x6C
	Real m_maxWeaponSpeed;			// +0x70
	Bool m_scaleWeaponSpeed;		// +0x74
	char m_pad75[0x131 - 0x75];
	bool m_hitStoredTarget;			// +0x131 fire at the victim
};

class WeaponStore
{
public:
	void handleProjectileDetonation(const WeaponTemplate *tmpl, const Coord3D *launchPos, const Object *source, const Coord3D *pos, int bonus); // 0x002CE8AA
	void rva002CE964(const WeaponTemplate *tmpl, const Object *source, const Object *victim); // 0x002CE964
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
	void createAndFireTempWeapon(const WeaponTemplate *tmpl, const Object *source, const Coord3D *pos);
};

extern WeaponStore *TheWeaponStore;

class TerrainLogic
{
public:
	virtual ~TerrainLogic();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);	// +0x18
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal, Bool clip);
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);	// 0x002802FE
	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, Bool flag);
};
extern TerrainLogic *TheTerrainLogic;

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float);
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
	unsigned char m_data[0x1C];
};

// Member names follow the INI field table 0x00841B58 (buildFieldParse 0x0045B5E3).
// Float widths follow the constructor's native MOVSS stores.
struct BezierProjectileBehaviorModuleData
{
	BezierProjectileBehaviorModuleData();
	const void *m_vtable;
	unsigned int m_unused04;
	float m_firstHeight, m_secondHeight, m_firstPercentIndent, m_secondPercentIndent;	// +0x08 to +0x14
	bool m_crushStyle;			// +0x18
	bool m_dieOnImpact;			// +0x19
	int m_bounceCount;			// +0x1C
	float m_bounceDistance;			// +0x20
	float m_bounceFirstHeight, m_bounceSecondHeight;	// +0x24, +0x28
	float m_bounceFirstPercentIndent, m_bounceSecondPercentIndent;	// +0x2C, +0x30
	float m_curveFlattenMinDist;		// +0x34
	unsigned int m_finalStuckTime;		// +0x38
	int m_preLandingStateTime;		// +0x3C
	unsigned int m_invisibleFrames;		// +0x40
	unsigned int m_fadeInTime;		// +0x44
	bool m_tumbleRandomly;			// +0x48
	bool m_orientToFlightPath;		// +0x49
	bool m_detonateCallsKill;		// +0x4A
	unsigned int m_garrisonHitKillCount;	// +0x4C
	Rva0024C7B3Member m_garrisonHitKillRequiredKindOf;	// +0x50
	Rva0024C7B3Member m_garrisonHitKillForbiddenKindOf;	// +0x6C
	unsigned int m_garrisonHitKillFX;	// +0x88
	float m_flightPathAdjustDistPerSecond;	// +0x8C
	bool m_ignoreTerrainHeight;		// +0x90
	float m_firstPercentHeight;		// +0x94
	float m_secondPercentHeight;		// +0x98
	const FXList *m_groundHitFX;		// +0x9C
	const FXList *m_groundBounceFX;		// +0xA0
	const WeaponTemplate *m_groundHitWeapon;	// +0xA4
	const WeaponTemplate *m_groundBounceWeapon;	// +0xA8
	int m_preLandingEmotion;		// +0xAC (-1 for none)
	float m_preLandingEmotionRadius;	// +0xB0
	bool m_preLandingEmotionAffectsAllies;	// +0xB4
	int m_postLandingStateTime;		// +0xB8
	int m_postLandingEmotion;		// +0xBC (-1 for none)
	float m_postLandingEmotionRadius;	// +0xC0 the radius
};

class BfmeThingDI;

class BfmeNodeDI;
class Gen_001EFD20
{
public:
	bool bfmeIsNew(const BfmeThingDI *thing) const;
private:
	int m_bfmeHead[31]; // +0x00
	BfmeNodeDI *m_bfmeList; // +0x7C
};

template <int NUMBITS> class BitFlags;
typedef BitFlags<11> DisabledMaskType;

class BehaviorModuleInterface
{
public:
	virtual void getBody() = 0;
};

// Slots 10 and 11 of each module's primary vftable hold 0x000D43D0
// (xor eax,eax; ret); their names are not recovered.
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual void gap10() = 0;
	virtual void gap11() = 0;
};

// Retail's UpdateModule-interface vftable (0x00841DF8 for this class) holds
// update, then UpdateModule's getDisabledTypesToProcess (0x00253376) and
// 0x0044DF8D.
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
	virtual DisabledMaskType getDisabledTypesToProcess() const = 0;
	virtual void rva0044DF8D(UpdateSleepTime sleep) = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();	// 0x0024A797
	virtual DisabledMaskType getDisabledTypesToProcess() const;
	virtual void rva0044DF8D(UpdateSleepTime sleep);
	virtual void xfer(Xfer *xfer);	// 0x0044DF9F, Snapshot's slot 3
protected:
	virtual SleepyUpdatePhase getUpdatePhase() const;	// primary slot 12, 0x0022C4CB
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);	// 0x0044DF71
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

struct Rva0045B936Arg;
class Rva002CBA7C;

// The projectile interface at +0x20 (vtable 0x00C41DE0) and the interface at
// +0x24 (0x00C41DC8); +0x24 slot 1 is the this-4 adjustor thunk to +0x20 slot 4,
// which this class's vftables emit. Slot 2 of 0x00C41DE0 is the shared [this+8] getter 0x0030F45F.
class BezierProjectileBehaviorSecondaryBase0
{
public:
	virtual void projectileLaunchAtObjectOrPosition(Object *victim, const Coord3D *victimPos, Object *launcher, int wslot,
		int specificBarrel, const Rva0045B936Arg *arg6, Rva002CBA7C *helper, const Matrix3D *mtx) = 0;
	virtual void gap1() = 0;
	virtual ObjectID getLauncherID() const = 0;
	virtual bool rva0045CD6E(Object *victim) = 0;
	virtual bool rva0045BF06(Object *victim) = 0;
	virtual void rva0045B4E2(int unused) = 0;
};

class BezierProjectileBehaviorSecondaryBase1
{
public:
	virtual void rva0045B4C0(Object *victim, int a2, int a3) = 0;
	virtual bool rva0045BF06(Object *victim) = 0;
};

class PoolMember
{
public:
	void Rva00268902() throw();
};

struct Rva0029FB3BAlloc
{
	Rva0029FB3BAlloc() {}
	~Rva0029FB3BAlloc() {}
};

// The ID list's base; its allocator-taking ctor is rowed at 0x0029FB3B.
class Rva0029FB3BMember
{
public:
	Rva0029FB3BMember(const Rva0029FB3BAlloc &alloc);
	__declspec(dllimport) __forceinline ~Rva0029FB3BMember() { ((PoolMember *)this)->Rva00268902(); }
	void init(void *context);
	void reset();
private:
	void *m_node; // +0x00
};

class ObjectIDList : public Rva0029FB3BMember
{
public:
	explicit ObjectIDList(const Rva0029FB3BAlloc &alloc = Rva0029FB3BAlloc()) : Rva0029FB3BMember(alloc) {}
};

// Primary vftable 0x00C41E04: slot 0 ??_G 0x0045C959, slot 3 xfer 0x0045CA8E, slot 4
// getModuleNameKey 0x0045BFD9, slot 13 projectileFireAtObjectOrPosition 0x0045BB8A.
class BezierProjectileBehavior : public UpdateModule, public BezierProjectileBehaviorSecondaryBase0, public BezierProjectileBehaviorSecondaryBase1
{
public:
	BezierProjectileBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~BezierProjectileBehavior();
	virtual NameKeyType getModuleNameKey() const;
	virtual UpdateSleepTime update();	// 0x0045C226
	virtual void projectileLaunchAtObjectOrPosition(Object *victim, const Coord3D *victimPos, Object *launcher, int wslot,
		int specificBarrel, const Rva0045B936Arg *arg6, Rva002CBA7C *helper, const Matrix3D *mtx);
	virtual void projectileFireAtObjectOrPosition(Object *victim, const Coord3D *victimPos);
	virtual bool rva0045CD6E(Object *victim);
	virtual bool rva0045BF06(Object *victim);
	virtual void rva0045B4C0(Object *victim, int a2, int a3);
	virtual void rva0045B4E2(int unused);
	void rva0045B9FB(Object *other);
	void rva0045C026();
	void rva0045C812(const Object *obj);
	void rva0045C975(int unused);
	void rva0045CC72(int flag);
	int bfmeCost(void) const; // sleep time: awake while the path has points
	Bool isNotInHitList(const Object *other) const
	{
		return ((const Gen_001EFD20 *)this)->bfmeIsNew((const BfmeThingDI *)other);
	}
protected:
	virtual void xfer(Xfer *xfer);
private:
	Bool calcFlightPath(Bool recalcNumSegments);	// 0x0045B5F4
	const BezierProjectileBehaviorModuleData *getBezierProjectileBehaviorModuleData() const
	{
		return (const BezierProjectileBehaviorModuleData *)m_moduleData;
	}

	ObjectID m_launcherID;		// +0x28
	Coord3D m_launchPos;		// +0x2C
	ObjectID m_victimID;		// +0x38
	WeaponTemplate *m_weapon;	// +0x3C
	const WeaponTemplate *m_detonationWeaponTmpl;	// +0x40
	_STL::vector<Coord3D> m_flightPath; // +0x44, end +0x48, capacity +0x4C: twelve-byte path elements
	Coord3D m_flightPathStart;	// +0x50
	Coord3D m_flightPathEnd;	// +0x5C
	Real m_flightPathSpeed;		// +0x68
	Int m_flightPathSegments;	// +0x6C
	Int m_currentFlightPathStep;	// +0x70 path cursor
	UnsignedInt m_extraBonusFlags;	// +0x74 launcher bonus condition
	Int m_bounceCount;		// +0x78
	ObjectIDList m_list7C;		// +0x7C
	Bool m_hasDetonated;		// +0x80
	Real m_heightScale;		// +0x84
};

struct Rva0045B936Arg
{
	int m_00;
	WeaponTemplate *m_04;
};

// Scalar coordinate storage reproduces the native copies and SSE operations.
// This adapter is a local compiler-shape view, not an original class identity.
struct Rva0045B9FBPoint : Coord3D
{
	Rva0045B9FBPoint(const Coord3D &r) { x = r.x; y = r.y; z = r.z; }
	void sub(const Coord3D &r) { x -= r.x; y -= r.y; z -= r.z; }
	void add(const Coord3D &r) { x += r.x; y += r.y; z += r.z; }
	void scale(float k) { x *= k; y *= k; z *= k; }
};

// This is the existing shared table alias used by Aim/Physics module data;
// this unit adds neither an alias definition nor a guessed virtual contract.
extern "C" const void *const __identifier("??_7ObjectHelperModuleData@@6B@")[];

// ?rva0045BF06@BezierProjectileBehavior@@UAE_NPAVObject@@@Z @0x0045BF06
bool BezierProjectileBehavior::rva0045BF06(Object *victim)
{
	if (m_flightPath.size() <= 0)
		return false;
	if (m_detonationWeaponTmpl == 0)
		return false;
	if (victim)
	{
		if (victim->isKindOf(0x6D) != 0)
			return false;
		// Native BF06 checks byte +0x438 bit 0 directly; it is not the
		// independently owned Object::isEffectivelyDead operation.
		if ((victim->m_438 & 1) != 0)
			return false;
	}
	Object *launcher = TheGameLogic->findObjectByID(getLauncherID());
	Object *owner = m_object;
	ObjectID extra = m_victimID;
	return m_detonationWeaponTmpl->shouldProjectileCollideWith(launcher, owner, victim, extra);
}

// ?rva0045B4C0@BezierProjectileBehavior@@UAEXPAVObject@@HH@Z @0x0045B4C0
void BezierProjectileBehavior::rva0045B4C0(Object *victim, int, int)
{
	if (rva0045BF06(victim))
		rva0045CD6E(victim);
}

// ?rva0045B4E2@BezierProjectileBehavior@@UAEXH@Z @0x0045B4E2
void BezierProjectileBehavior::rva0045B4E2(int)
{
	m_object->kill(DAMAGE_RVA0045C026_8, DEATH_NORMAL);
}

// ?projectileLaunchAtObjectOrPosition@BezierProjectileBehavior@@UAEXPAVObject@@PBUCoord3D@@0HHPBURva0045B936Arg@@PAVRva002CBA7C@@PBVMatrix3D@@@Z @0x0045B936
void BezierProjectileBehavior::projectileLaunchAtObjectOrPosition(Object *victim, const Coord3D *victimPos, Object *launcher, int wslot,
	int specificBarrel, const Rva0045B936Arg *arg6, Rva002CBA7C *helper, const Matrix3D *mtx)
{
	m_launcherID = launcher ? launcher->getID() : INVALID_OBJECT_ID;
	m_extraBonusFlags = launcher ? launcher->bfme_getWeaponBonusCondition_a1a45() : 0;
	m_victimID = victim ? victim->getID() : INVALID_OBJECT_ID;
	m_weapon = arg6->m_04;
	m_bounceCount = 0;
	m_detonationWeaponTmpl = (const WeaponTemplate *)helper;
	Object *obj = m_object;
	if (mtx)
		obj->setTransformMatrix(mtx);
	else
		Weapon::positionProjectileForLaunch(obj, launcher, (WeaponSlotType)wslot, specificBarrel);
	m_launchPos = launcher ? *launcher->getPosition() : *obj->getPosition();
	projectileFireAtObjectOrPosition(victim, victimPos);
	obj->setModelConditionBit(4 * 32 + 26);
	obj->setStatus(OBJECT_STATUS_5, true);
}

// Clean donor: Open-BFME-1 575ba2b0, BezierProjectileBehaviorModuleDataCtorThunk.cpp.
// Native45B4F1..45B5E3 is the complete242B constructor; the next17B body is
// the separately rowed buildFieldParse. BFME2 widens both curve members to
// the existing28B constructor24C7B3 and adds the fields afterAC. Float widths
// below follow native MOVSS stores; unexplained fields retain offset names.
BezierProjectileBehaviorModuleData::BezierProjectileBehaviorModuleData()
	: m_vtable(__identifier("??_7ObjectHelperModuleData@@6B@")), m_firstHeight(0), m_secondHeight(0),
	  m_firstPercentIndent(0), m_secondPercentIndent(0),
	  m_crushStyle(false), m_dieOnImpact(false), m_bounceCount(0),
	  m_bounceDistance(0), m_bounceFirstHeight(0), m_bounceSecondHeight(0), m_bounceFirstPercentIndent(0), m_bounceSecondPercentIndent(0), m_curveFlattenMinDist(0),
	  m_finalStuckTime(0), m_preLandingStateTime(0), m_invisibleFrames(0), m_fadeInTime(0),
	  m_tumbleRandomly(false), m_orientToFlightPath(true), m_detonateCallsKill(false), m_garrisonHitKillCount(0)
{
	m_garrisonHitKillFX = 0;
	m_flightPathAdjustDistPerSecond = 0.0f;
	m_ignoreTerrainHeight = false;
	m_firstPercentHeight = 0.33f;
	m_secondPercentHeight = 0.66f;
	m_groundHitFX = 0;
	m_groundBounceFX = 0;
	m_groundHitWeapon = 0;
	m_groundBounceWeapon = 0;
	m_preLandingEmotion = -1;
	m_preLandingEmotionRadius = 0.0f;
	m_preLandingEmotionAffectsAllies = true;
	m_postLandingStateTime = 0;
	m_postLandingEmotion = -1;
	m_postLandingEmotionRadius = 0.0f;
}

// ?rva0045B9FB@BezierProjectileBehavior@@QAEXPAVObject@@@Z @0x0045B9FB
// 336 bytes. Primary caller 0x0045CD6E and WB counterpart 0x011816A0
// establish the collision-step relationship. BFME 1's matched Bezier caller
// (donor cee35b7d8) supports that relationship, not the unknown method name.
void BezierProjectileBehavior::rva0045B9FB(Object *other)
{
	if (!other)
		return;
	int idx = m_flightPath.size() - 1 < (unsigned int)m_currentFlightPathStep ? m_flightPath.size() - 1 : m_currentFlightPathStep;
	Object *obj = m_object;
	Rva0045B9FBPoint cur(obj->m_cachedPos);
	Coord3D *bezierPathPoint = m_flightPath.begin() + (idx - 1 < 0 ? 0 : idx - 1);
	Rva0045B9FBPoint delta(*bezierPathPoint);
	delta.sub(cur);
	delta.scale(0.1f);
	float angle = obj->m_cachedAngle;
	GeometryInfo *geom = &obj->m_geometry;
	int i = 0;
	bool collision = true;
	while (collision && i++ <= 12)
	{
		cur.add(delta);
		collision = geom->CollidesWith(cur, angle, other->m_geometry,
			other->m_cachedPos, other->m_cachedAngle);
	}
	cur.sub(delta);
	obj->setPosition(&cur);
}
