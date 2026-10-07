// ?attemptDamage@ActiveBody@@UAEXPAVDamageInfo@@@Z
// partial score=0.8 date=2026-10-07
// cl: /O1 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
// stlport
// ActiveBody.cpp -- ActiveBody members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function (vtable
// pairing); retail supplies the bytes. Zero Hour's setDamageState
// (GameLogic/Object/Body/ActiveBody.cpp) as a switch over the state with the
// thresholds held in the body itself.
//
// Layout (target evidence, matching Body/ActiveBodyDamageState.cpp): the body
// module interface is the second base at +0x10, so this body runs with ecx at
// +0x10; health +0x18, max health +0x20, damaged and really-damaged ratios
// +0x24/+0x28. The health change is interface slot 32 (+0x80); the final
// call is slot 21 (+0x54) of the primary vtable with a zero argument.

#include <string.h>
#include <list>
#include "ascii_string.h"
#include "Common/BfmeAudioEventPrefix136.h"

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

enum BodyDamageType { BODY_PRISTINE, BODY_DAMAGED, BODY_REALLYDAMAGED, BODY_RUBBLE };
enum VeterancyLevel { LEVEL_REGULAR, LEVEL_VETERAN, LEVEL_ELITE, LEVEL_HEROIC };
enum ArmorSetType { ARMORSET_VETERAN, ARMORSET_ELITE, ARMORSET_HERO };
enum MaxHealthChangeType { SAME_CURRENTHEALTH, PRESERVE_RATIO };

enum DamageType { DAMAGE_4 = 4, DAMAGE_6 = 6, DAMAGE_HEALING = 7, DAMAGE_UNRESISTABLE = 8, DAMAGE_23 = 0x17 };
enum KindOfType { KINDOF_4 = 4, KINDOF_220 = 0x220, KINDOF_14A = 0x14A };
enum ObjectID { INVALID_ID = 0 };
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_4 = 4,
	OBJECT_STATUS_8 = 8,
	OBJECT_STATUS_24 = 24,
	OBJECT_STATUS_60 = 0x3C,
	OBJECT_STATUS_65 = 0x41,
	OBJECT_STATUS_77 = 0x4D,
	OBJECT_STATUS_83 = 0x53
};

// class-gate: allow Coord3D the bone-position array is built and torn down through BFME 2's out-of-line empty Coord3D constructor and destructor (the eh vector iterators push 0x0047A6A9 and 0x000B3FD0); the canonical data-only header cannot declare them; same three floats
struct Coord3D
{
	float x, y, z;
	Coord3D();
	~Coord3D();
};

class Matrix3D;
class ParticleSystemTemplate;

enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };

class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
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
class Snapshot;

// Xfer as the matched BFME 2 xfer bodies view it (BodyModuleXfer.cpp,
// ProductionUpdateQueue.cpp): MSVC groups the operator== overloads in reverse,
// so Version is +0x28, AsciiString +0x6C, float +0x70, unsigned int +0x78,
// int +0x7C, unsigned short +0x80 and bool +0x90.
class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);	// 0x0060C36E
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

// The cdecl enum and ID transfers, rowed at 0x00305E12, 0x00305E2A,
// 0x00305EBA, 0x0030600A and 0x003060B2.
void XferBodyDamageType(Xfer *xfer, Int *value);
void XferBodySideDestroyedType(Xfer *xfer, Int *value);
void XferDamageFXType(Xfer *xfer, Int *value);
void XferParticleSystemID(Xfer *xfer, Int *value);
void XferObjectID(Xfer *xfer, ObjectID *value);

// The particle system's setters, rowed under placeholder names: position copy
// 0x001F3899 and attached object 0x001F3C43.
struct Rva001F3899Arg
{
	int m_00;
	int m_04;
	int m_08;
};
class Rva001F3899Slot
{
public:
	void set(const Rva001F3899Arg &arg);
};
struct Rva001F3C43Arg;
class Rva001F3C43Slot
{
public:
	void set(const Rva001F3C43Arg *arg);
};

class Object;
class Drawable;
class ParticleSystem
{
public:
	ParticleSystemID getSystemID() const { return m_systemID; }
	void setPosition(const Coord3D *pos)
	{
		((Rva001F3899Slot *)this)->set(*(const Rva001F3899Arg *)pos);
	}
	void attachToObject(const Object *obj)
	{
		((Rva001F3C43Slot *)this)->set((const Rva001F3C43Arg *)obj);
	}

private:
	char m_pad00[0xA8];
	ParticleSystemID m_systemID;	// +0xA8
};
ParticleSystem *Make001FCBD7();

// The 12-byte handle: the out-of-line unlink is 0x0004CBC0, which the handle's
// destructor calls only for a live system.
class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
};
class BfmeParticleSystemHandleBase
{
public:
	~BfmeParticleSystemHandleBase()
	{
		if (m_system)
			((RvaSmartPtr12 *)this)->rva0004CBC0();
	}
	ParticleSystem *m_system;
	BfmeParticleSystemHandleBase *m_previous;
	BfmeParticleSystemHandleBase *m_next;
};
class BfmeParticleSystemHandle : public BfmeParticleSystemHandleBase
{
public:
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make001FCBD7();
	}
};

class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate, bool createSlaves);
};
extern ParticleSystemManager *TheParticleSystemManager;

extern Int GetGameClientRandomValue(Int lo, Int hi, char *file, Int line);
#define GameClientRandomValue(lo, hi) \
	GetGameClientRandomValue((lo), (hi), __FILE__, __LINE__)

// BodyParticleSystem: BFME 2 drops Zero Hour's memory pool, so the 12-byte
// entry is a plain new with a vptr (vtable VA 0x00C5AEB0, whose only slot is
// the rowed scalar deleting destructor 0x004BDA0C named after its address).
class Rva004BDA0C
{
public:
	virtual ~Rva004BDA0C();

	ParticleSystemID m_particleSystemID;	// +0x04
	Rva004BDA0C *m_next;			// +0x08
};
typedef Rva004BDA0C BodyParticleSystem;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);	// 0x000B2235
};

class DamageInfoInput
{
public:
	UnsignedInt m_field00;			// +0x00
	ObjectID m_sourceID;			// +0x04
	UnsignedInt m_field08;			// +0x08
	DamageType m_damageType;		// +0x0C
	Int m_damageFXType;			// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	Bool m_kill;				// +0x20
	unsigned char m_pad21[0x28 - 0x21];
	Int m_creationType;			// +0x28
};

// DamageInfo is 0x7C bytes (constructor 0x00263895); its vtable 0x00BF9200
// holds one slot, the xfer rowed at 0x004D6F86.
class DamageInfo
{
public:
	virtual void xfer(Xfer *xfer);		// slot 0
	DamageInfoInput in;			// +0x04
	unsigned char m_pad30[0x70 - 0x30];
	Real m_actualDamageDealt;		// +0x70
	Real m_actualDamageClipped;		// +0x74
	unsigned char m_pad78[4];
};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo);					// +0x00
	virtual void onHealing(DamageInfo *damageInfo);					// +0x04
	virtual void onBodyDamageStateChange(DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState);	// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
	virtual DamageModuleInterface *getDamage();	// +0x10
};

class BehaviorModule
{
public:
	unsigned char m_pad00[0x0C];
	BehaviorModuleInterface m_iface;	// +0x0C
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;	// 0x006BD7C0
};

// The Object's geometry (+0xA8) as the rowed BFME 1 donor helpers view it:
// the shape at an index (0x006BD980) over 0x24-byte shapes named at +0x1C,
// and the named-shape flag update (0x006BF450).
struct BfmeShapeE15
{
	unsigned char m_pad00[0x1C];
	AsciiString m_name;			// +0x1C
	unsigned char m_pad20[4];
};
class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(int i);
	Int getNumShapes() const { return m_finish - m_start; }

	unsigned char m_pad00[0x2C];
	BfmeShapeE15 *m_start;			// +0x2C
	BfmeShapeE15 *m_finish;			// +0x30
};
class BfmeStrF9;
class BfmeObjF9
{
public:
	void rva0087FA50(const BfmeStrF9 &name, char flag);
};
struct BfmeCopyElementA;

class ThingTemplate
{
public:
	UnsignedInt testKindOf(Int k) const { return m_kindOf[k >> 5] & (1U << (k & 31)); }
	const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
	Real getStructureRubbleHeight() const { return (Real)m_structureRubbleHeight; }

	unsigned char m_pad000[0xA0];
	GeometryInfo m_geometryInfo;		// +0xA0
	unsigned char m_pad0A1[0x108 - 0xA1];
	UnsignedInt m_kindOf[0x10];		// +0x108
	unsigned char m_pad148[0x5F7 - 0x148];
	signed char m_structureRubbleHeight;	// +0x5F7
	unsigned char m_pad5F8[0x632 - 0x5F8];
	Bool m_byte632;				// +0x632
};

class BodyModuleInterface;
class ActiveBody;

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};

enum CommandSourceType { CMD_FROM_PLAYER, CMD_FROM_SCRIPT, CMD_FROM_AI };
enum DisabledType { DISABLED_8 = 8 };
enum NameKeyType { NAMEKEY_INVALID = 0 };

// The AICommandInterface base at AIUpdateInterface +0x20: its idle command
// (an AICommandParms 0x53 through slot 0) is emitted out of line from this
// unit at 0x004BFD27 and rowed under that address.
class Rva004BFD27
{
public:
	void rva004BFD27(CommandSourceType cmdSource);
};

class AIUpdateInterface
{
public:
	virtual void a000(); virtual void a001(); virtual void a002(); virtual void a003();
	virtual void a004(); virtual void a005(); virtual void a006(); virtual void a007();
	virtual void a008(); virtual void a009(); virtual void a010(); virtual void a011();
	virtual void a012(); virtual void a013(); virtual void a014(); virtual void a015();
	virtual void a016(); virtual void a017(); virtual void a018(); virtual void a019();
	virtual void a020(); virtual void a021(); virtual void a022(); virtual void a023();
	virtual void a024(); virtual void a025(); virtual void a026(); virtual void a027();
	virtual void a028(); virtual void a029(); virtual void a030(); virtual void a031();
	virtual void a032(); virtual void a033(); virtual void a034(); virtual void a035();
	virtual void a036(); virtual void a037(); virtual void a038(); virtual void a039();
	virtual void a040(); virtual void a041(); virtual void a042(); virtual void a043();
	virtual void a044(); virtual void a045(); virtual void a046(); virtual void a047();
	virtual void a048(); virtual void a049(); virtual void a050(); virtual void a051();
	virtual void a052(); virtual void a053(); virtual void a054(); virtual void a055();
	virtual void a056(); virtual void a057(); virtual void a058(); virtual void a059();
	virtual void a060(); virtual void a061(); virtual void a062(); virtual void a063();
	virtual void a064(); virtual void a065(); virtual void a066(); virtual void a067();
	virtual void a068(); virtual void a069(); virtual void a070(); virtual void a071();
	virtual void a072(); virtual void a073(); virtual void a074(); virtual void a075();
	virtual void a076(); virtual void a077(); virtual void a078(); virtual void a079();
	virtual void a080(); virtual void a081(); virtual void a082(); virtual void a083();
	virtual void a084(); virtual void a085(); virtual void a086(); virtual void a087();
	virtual void a088(); virtual void a089(); virtual void a090(); virtual void a091();
	virtual void a092(); virtual void a093(); virtual void a094(); virtual void a095();
	virtual void a096(); virtual void a097(); virtual void a098(); virtual void a099();
	virtual void a100(); virtual void a101(); virtual void a102(); virtual void a103();
	virtual void a104(); virtual void a105(); virtual void a106(); virtual void a107();
	virtual void a108(); virtual void a109();
	virtual Bool isIdle() const;			// +0x1B8

	// The state-machine test 0x002632C7 is rowed returning int; callers test al.
	int rva002632C7() const;
	unsigned char rva002632C7Bool() const { return (unsigned char)rva002632C7(); }
	void rva002632E1();				// 0x002632E1
	Rva004BFD27 *getCommandInterface() { return (Rva004BFD27 *)&m_commandInterface; }

	unsigned char m_pad04[0x20 - 0x04];
	void *m_commandInterface;		// +0x20: AICommandInterface vptr
	unsigned char m_pad24[0x34 - 0x24];
	Int m_field34;				// +0x34
};

// The pieces of the containing object's contain module that attemptDamage
// reaches: slot 26 passes the damage on, slot 31 returns a helper whose slot
// 14 runs when the damage was clipped, slot 69 counts (with a zero argument).
class Rva004BFE07ContainHelper : public VSlots<14>
{
public:
	virtual void onClippedDamage(Object *obj);	// +0x38
};
class ContainModuleInterface : public VSlots<26>
{
public:
	virtual void onContainedDamage(Object *obj, ActiveBody *body, DamageInfo *damageInfo);	// +0x68
	virtual void c27(); virtual void c28(); virtual void c29(); virtual void c30();
	virtual Rva004BFE07ContainHelper *getDamageHelper();	// +0x7C
	virtual void c32(); virtual void c33(); virtual void c34(); virtual void c35();
	virtual void c36(); virtual void c37(); virtual void c38(); virtual void c39();
	virtual void c40(); virtual void c41(); virtual void c42(); virtual void c43();
	virtual void c44(); virtual void c45(); virtual void c46(); virtual void c47();
	virtual void c48(); virtual void c49(); virtual void c50(); virtual void c51();
	virtual void c52(); virtual void c53(); virtual void c54(); virtual void c55();
	virtual void c56(); virtual void c57(); virtual void c58(); virtual void c59();
	virtual void c60(); virtual void c61(); virtual void c62(); virtual void c63();
	virtual void c64(); virtual void c65(); virtual void c66(); virtual void c67();
	virtual void c68();
	virtual UnsignedInt getContainCount(Int arg);	// +0x114
};

// What Object 0x0028C1A9 returns (for the object 0x002931F5 resolves from a
// damager with status 65): slot 3 decides whether the damage kills, slot 8
// is then told about the victim.
class Rva0028C1A9Result
{
public:
	virtual void r0(); virtual void r1(); virtual void r2();
	virtual Bool shouldKill(Object *victim);	// +0x0C
	virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7();
	virtual void onKill(Object *victim);		// +0x20
};

class Rva004BFE07Flagged
{
public:
	unsigned char m_pad00[0x5C];
	Bool m_byte5C;				// +0x5C
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

	unsigned char m_pad00[0x54];
	Int m_playerIndex;			// +0x54
};

class Module;

class Object
{
public:
	Bool isKindOf(KindOfType kindOf) const;	// 0x0006F039
	Bool testStatus(ObjectStatusTypes bit) const;	// 0x0004E536
	void setEffectivelyDead(Bool dead);		// 0x0028D2FB
	Bool rva0028F518();				// 0x0028F518
	void setStatus(ObjectStatusTypes bit, Bool set);	// 0x0023DB0E
	void rva0028AB75(Bool flag);			// 0x0028AB75
	void rva0028ABFC(Real z);			// 0x0028ABFC: the geometry's height
	void rva0029895A(BfmeCopyElementA *geom);	// 0x0029895A: copy in a geometry
	Bool addAttributeModifierToPool(const AsciiString &name, Int duration);	// 0x0028EA91
	void removeAttributeModifierFromPool(const AsciiString &name);		// 0x0028EB42
	AIUpdateInterface *getAI() const { return m_ai; }
	Bool testStatusBit(Int bit) const { return (m_status >> bit) & 1; }
	Int getMultiLogicalBonePosition(const char *boneNamePrefix, Int maxBones, Coord3D *positions,
		Matrix3D *transforms, Bool convertToWorld, Int extra) const;	// 0x0028BF81
	const ThingTemplate *getTemplate() const { return m_template; }
	Int getID() const { return m_id; }
	Bool testStatusBit6() const { return (m_status >> 6) & 1; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Drawable *getDrawable() const;			// 0x005508E2
	Object *getContainedBy() const { return m_containedBy; }
	ContainModuleInterface *getContain() const { return m_contain; }
	Object *rva002931F5(Bool flag);			// 0x002931F5
	void *rva0028C1A9() const;			// 0x0028C1A9
	Bool rva0028D491() const;			// 0x0028D491
	void rva0028B1D4(Int damageInfo, Int victim) const;	// 0x0028B1D4
	Player *getControllingPlayer() const;		// 0x0028AFA9
	void setDisabledUntil(DisabledType type, UnsignedInt frame);	// 0x00290114
	void rva00298517(DamageInfo *damageInfo);	// 0x00298517: onDie
protected:
	friend class ActiveBody;
	Module *findModule(NameKeyType key) const;	// 0x0028B6D6
public:
	const Coord3D *getPosition() const { return (const Coord3D *)m_cachedPos; }

	void *m_vptr;
	const ThingTemplate *m_template;	// +0x04
	Real m_transform[3][4];			// +0x08: rows, translation in column 3
	Real m_cachedPos[3];			// +0x38
	unsigned char m_pad44[0x74 - 0x44];
	Int m_id;			// +0x74
	unsigned char m_pad78[0x94 - 0x78];
	UnsignedInt m_status;			// +0x94
	unsigned char m_pad98[0xA8 - 0x98];
	BfmeObjE15 m_geometry;			// +0xA8
	unsigned char m_padDC[0x10C - 0xDC];
	unsigned char m_kindOfMask[0x4C];	// +0x10C
	unsigned char m_pad158[0x244 - 0x158];
	BehaviorModule **m_behaviors;		// +0x244
	unsigned char m_pad248[0x250 - 0x248];
	ContainModuleInterface *m_contain;	// +0x250
	BodyModuleInterface *m_body;		// +0x254
	AIUpdateInterface *m_ai;		// +0x258
	Rva004BFE07Flagged *m_field25C;		// +0x25C
	unsigned char m_pad260[0x274 - 0x260];
	Object *m_containedBy;			// +0x274
	unsigned char m_pad278[0x280 - 0x278];
	Int m_field280;				// +0x280
	unsigned char m_pad284[0x438 - 0x284];
	UnsignedInt m_flags438;			// +0x438
};

// The promotion sound references of a Drawable (keyed lookups rowed in
// DrawableKeyedLookups.cpp) and the Object a Drawable belongs to (+0xFC).
class Rva002390CB
{
public:
	Rva002390CB(const Rva002390CB &other);
	~Rva002390CB() { if (m_04.referent != 0) m_04.referent->Release_Ref(); }
	char m_pad00[4];
	OpaqueRefElement4 m_04;
};
class Drawable
{
public:
	Rva002390CB rva004BE152();		// key 0x31
	Rva002390CB rva004BE16B();		// key 0x32
	Rva002390CB rva004BE184();		// key 0x33
	Rva002390CB rva004BE120();		// the damaged sound
	Rva002390CB rva004BE139();		// the really-damaged sound
	Object *getObject() const { return m_object; }

	unsigned char m_pad00[0xFC];
	Object *m_object;			// +0xFC
};

// Audio event setters rowed by address: 0x002D9C2F assigns the sound
// reference, 0x002D9531 the Object ID.
class Rva002D9C2F { public: OpaqueRefElement4 &rva002D9C2F(const OpaqueRefElement4 &other); };
class Rva002D9531 { public: void rva002D9531(int v); };

class AudioManager : public VSlots<25>
{
public:
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd) = 0;	// +0x64
};
extern AudioManager *TheAudio;

class InGameUI : public VSlots<70>
{
public:
	virtual Int getSelectCount();				// +0x118
	virtual void u71(); virtual void u72(); virtual void u73(); virtual void u74();
	virtual Drawable *getFirstSelectedDrawable();		// +0x12C
};
extern InGameUI *TheInGameUI;

class ControlBar
{
public:
	void markUIDirty() { m_UIDirty = true; }

	unsigned char m_pad00[0x28];
	Bool m_UIDirty;				// +0x28
};
extern ControlBar *TheControlBar;

class DOTManager
{
public:
	UnsignedInt rva0043B72D(Int id);	// 0x0043B72D
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	Object *findObjectByID(ObjectID id);	// 0x00049DC5

	unsigned char m_pad00[0x40];
	UnsignedInt m_frame;			// +0x40
	unsigned char m_pad44[0x174 - 0x44];
	DOTManager *m_dotManager;		// +0x174
};
extern GameLogic *TheGameLogic;

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *obj);	// 0x002E7178
	void RemoveObjectFromPathfindMap(Object *obj);	// 0x002E718A
};
class AIData
{
public:
	unsigned char m_pad00[0x64];
	Bool m_enableRepulsors;			// +0x64
};
class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	const AIData *getAiData() const { return m_aiData; }

	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder;		// +0x10
	unsigned char m_pad14[4];
	AIData *m_aiData;			// +0x18
};
extern AI *TheAI;

class GlobalData
{
public:
	unsigned char m_pad000[0xAD4];
	Real m_healthBonus[4];			// +0xAD4: by veterancy level
	Real m_defaultStructureRubbleHeight;	// +0xAE4
};
extern GlobalData *TheWritableGlobalData;

// The damage state for the current health, rowed at 0x004BDA29 under an
// address name: Zero Hour's calcDamageState order (rubble at zero health,
// then the really-damaged and damaged ratios of max health) on the body's own
// fields, without the division. Its only caller is setCorrectDamageState
// below, which keeps ecx across the call: MSVC does that only for a callee
// already compiled in the same unit, so the calc is defined here.
class Rva004BDA29
{
public:
	Int rva004BDA29() const;

private:
	void *m_vptr;
	unsigned char m_pad04[0x14];
	Real m_health;				// +0x18
	unsigned char m_pad1C[4];
	Real m_maxHealth;			// +0x20
	Real m_damagedThresh;			// +0x24
	Real m_reallyDamagedThresh;		// +0x28
};

// The rubble-state object reset (0x004BDA67), rowed under an address name.
class Rva004BDA67
{
public:
	void rva004BDA67();
};

class DamageFX
{
public:
	Bool rva003608DF(Int damageType, Real amount, const Object *source, const Object *victim);	// 0x003608DF
};

class Rva003605D5	// DamageFX throttle-time lookup (Zero Hour getDamageFXThrottleTime)
{
public:
	Int rva003605D5(Int damageType, Int source);	// 0x003605D5
};

class ObjectCreationList
{
public:
	void create(void *primary, void *secondary, void *lifetime);	// 0x001F08D3
};

struct DamageCreation
{
	ObjectCreationList *m_ocl;		// +0x00
	Int m_type;				// +0x04
	Int m_stage;				// +0x08: 0, or the damage stage 1-4
};

class Armor
{
public:
	Real adjustDamage(const DamageInfoInput *input, const Object *obj, Bool flag) const;	// 0x001D90A1

private:
	void *m_name;
};

// attemptDamage's helpers, rowed or pinned under these names: the damage
// record copy (0x003427DD), the kill report on the damager (0x00294D61), the
// damage-dealt report (0x0028B749), the attacked-by flag on the victim's
// player (0x002AA1E4) and the empty Object hook at 0x0047A69C (the shared
// 3-byte ret 4 folded under many names).
class Rva003427DD { public: Rva003427DD &operator=(const Rva003427DD &other); };
class Rva00294D61 { public: void report(Object *victim, Int flag); };
class Rva0028B749Host { public: void rva0028B749(Int victim, Real ratio); };
class Rva002AA201IndexedByteField { public: void set(int index); };
class Gen_003bcb40 { public: void m(Int frame); };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

// The static masks: a KindOfMaskType (0x4C bytes; three-bit constructor
// 0x00265254, intersection test 0x00263546) and an ObjectStatusMaskType
// (0x10 bytes; three-bit init 0x0044EAF3, rowed as a this-returning member,
// and any-bit test 0x00331682).
class Rva00265254
{
public:
	Rva00265254(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4) throw();
private:
	unsigned int m_bits[19];
};
class Rva00263546 { public: bool rva00263546(const Rva00263546 *other) const; };
class Rva0044EAF3
{
public:
	Rva0044EAF3 *rva0044EAF3(int a, unsigned int b, unsigned int c, unsigned int d) throw();
	unsigned int m_bits[4];
};
class Rva00331682Holder { public: bool test(const void *other) const; };

class KindOfMaskType : public Rva00265254
{
public:
	KindOfMaskType(unsigned int a, unsigned int b, unsigned int c, unsigned int d) : Rva00265254(a, b, c, d) {}
	Bool anyIntersectionWith(const void *bits) const
	{
		return ((const Rva00263546 *)this)->rva00263546((const Rva00263546 *)bits);
	}
};
class ObjectStatusMaskType : public Rva0044EAF3
{
public:
	ObjectStatusMaskType(int a, unsigned int b, unsigned int c, unsigned int d) { rva0044EAF3(a, b, c, d); }
	Bool testForAny(const void *bits) const { return ((const Rva00331682Holder *)this)->test(bits); }
};

// The one-drawable list handed to the unit voice response (its destructor
// is the shared pointer-list destructor 0x00239AF4, called out of line).
class DrawableList : public _STL::list<Drawable *>
{
public:
	~DrawableList() throw();
};
class PickAndPlayInfo;
class GameMessage
{
public:
	enum Type { MSG_BFME2_0x7E0 = 0x7E0 };
};
void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

struct BfmeDelayedLuaEvent
{
	unsigned char m_pad00[0x0C];
	Int m_value;				// +0x0C
	unsigned char m_pad10[4];
	Int m_type;				// +0x14
};
struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();
	void *m_vtable;
	BfmeDelayedLuaEvent m_events[3];
};
class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

class ActiveBodyModuleData
{
public:
	unsigned char m_pad00[0x1C];
	UnsignedInt m_damagedDisableFrames;		// +0x1C
	UnsignedInt m_reallyDamagedDisableFrames;	// +0x20
	UnsignedInt m_damageDelayFrames;		// +0x24
	unsigned char m_pad28[0x30 - 0x28];
	AsciiString m_damagedAttributeModifier;		// +0x30
	AsciiString m_reallyDamagedAttributeModifier;	// +0x34
	unsigned char m_pad38[0x48 - 0x38];
	const FXList *m_healingFX;		// +0x48
	unsigned char m_pad4C[0x51 - 0x4C];
	Bool m_byte51;				// +0x51
	unsigned char m_pad52[0x54 - 0x52];
	const FXList *m_clippedDamageFX;	// +0x54
};

// The armor-set flags are BitFlags<21> in BFME 2: its setBitByName is rowed
// at 0x004BE0F1; the set-bit count (0x0028F528), the name of a set bit
// (0x004BE0C7) and the CRC transfer of the raw bits (0x004BE722) are rowed
// under address names.
class Rva0028F528
{
public:
	Int rva0028F528();
};
class Rva004BE0C7
{
public:
	void *rva004BE0C7(UnsignedInt i);
};
class Rva004BE722
{
public:
	void rva004BE722(void *xfer);
};

template <int NUMBITS> class BitFlags
{
public:
	enum { NUMWORDS = (NUMBITS + 31) / 32 };

	Int count() { return ((Rva0028F528 *)this)->rva0028F528(); }
	const char *getBitNameIfSet(Int i) { return (const char *)((Rva004BE0C7 *)this)->rva004BE0C7(i); }
	Bool setBitByName(const char *token);
	void clear() { memset(m_bits, 0, sizeof(m_bits)); }
	void xfer(Xfer *xfer);

private:
	UnsignedInt m_bits[NUMWORDS];
};
typedef BitFlags<21> ArmorSetFlags;

// BodyModule: the primary base (BehaviorModule then the damage scalar at
// +0x14); its xfer is primary slot 3, rowed at 0x0058B043.
class BodyModule
{
public:
	virtual void m00(); virtual void m01(); virtual void m02();
protected:
	virtual void xfer(Xfer *xfer);				// +0x0C
public:
	virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
	virtual void onDelete();				// +0x20
	virtual void m09(); virtual void m10(); virtual void m11();
	virtual void m12();
	virtual void rva004BE69C();				// +0x34
	virtual void m14(); virtual void m15();
	virtual void m16();
	virtual void validateArmorAndDamageFX() const;		// +0x44
	virtual void doDamageFX(const DamageInfo *damageInfo) = 0;	// +0x48
	virtual void m19();
	virtual void deleteAllParticleSystems();		// +0x50
	virtual void rvaSlot21(Int arg);			// +0x54
	virtual void rva004BF9ED();				// +0x58

protected:
	const ActiveBodyModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
	void *m_vptr0C;
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);	// +0x00
	virtual void attemptHealing(DamageInfo *damageInfo);	// +0x04
	virtual Real estimateDamage(DamageInfoInput &damageInfo) const;	// +0x08
	virtual void i03();
	virtual Real getHealth() const;				// +0x10
	virtual Real getHealthRatio() const;			// +0x14
	virtual Real getMaxHealth() const;			// +0x18
	virtual void i07();
	virtual void i08();
	virtual void setDamageState(BodyDamageType newState);	// +0x24
	virtual void i10();
	virtual void onVeterancyLevelChanged(VeterancyLevel oldLevel, VeterancyLevel newLevel);	// +0x2C
	virtual void setArmorSetFlag(ArmorSetType ast);		// +0x30
	virtual void clearArmorSetFlag(ArmorSetType ast);	// +0x34
	virtual void i14(); virtual void i15();
	virtual void i16(); virtual void i17(); virtual void i18(); virtual void i19();
	virtual void i20();
	virtual void setInitialHealth(Real initialPercent, Bool directional);	// +0x54
	virtual void setMaxHealth(Real maxHealth, MaxHealthChangeType healthChangeType);	// +0x58
	virtual void i23();
	virtual void i24(); virtual void i25(); virtual void i26(); virtual void i27();
	virtual void i28(); virtual void i29(); virtual void i30(); virtual void i31();
	virtual void internalChangeHealth(Real delta, DamageInfo *damageInfo);	// +0x80
	virtual void i33(); virtual void i34(); virtual void i35();
	virtual void rvaSlot36();				// +0x90
	virtual void i37(); virtual void i38();
	virtual void rvaSlot39(BodyDamageType state);		// +0x9C
	virtual void rvaSlot40(Real health, Bool healing);	// +0xA0
};

class ActiveBody : public BodyModule, public BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
	virtual void attemptHealing(DamageInfo *damageInfo);
	virtual Real estimateDamage(DamageInfoInput &damageInfo) const;
	virtual void setDamageState(BodyDamageType newState);
	virtual void onVeterancyLevelChanged(VeterancyLevel oldLevel, VeterancyLevel newLevel);
	virtual void internalChangeHealth(Real delta, DamageInfo *damageInfo);

	virtual void rva004BE69C();
	virtual void onDelete();
	void setCorrectDamageState(Bool arg);
	void rva004BFB1C(Real amount, const Coord3D *pos);	// 0x004BFB1C
	void rva004BFCD4(Real amount, DamageInfo *damageInfo);

protected:
	virtual void xfer(Xfer *xfer);
	static Bool shouldRetaliate(Object *obj);
	virtual void doDamageFX(const DamageInfo *damageInfo);
	virtual void createParticleSystems(const AsciiString &boneBaseName,
		const ParticleSystemTemplate *systemTemplate, Int maxSystems);

private:
	const ActiveBodyModuleData *getActiveBodyModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

	Real m_damageScalar;			// +0x14
	Real m_currentHealth;			// +0x18
	Real m_prevHealth;			// +0x1C
	Real m_maxHealth;			// +0x20
	Real m_damagedRatio;			// +0x24
	Real m_reallyDamagedRatio;		// +0x28
	Real m_initialHealth;			// +0x2C
	BodyDamageType m_curDamageState;	// +0x30
	Int m_field34;				// +0x34
	UnsignedInt m_nextDamageFXTime;		// +0x38
	Int m_lastDamageFXDone;			// +0x3C
	DamageInfo m_lastDamageInfo;		// +0x40
	UnsignedInt m_lastDamageTimestamp;	// +0xBC
	UnsignedInt m_lastHealingTimestamp;	// +0xC0
	Bool m_frontCrushed;			// +0xC4
	Bool m_backCrushed;			// +0xC5
	Bool m_lastDamageCleared;		// +0xC6
	Bool m_indestructible;			// +0xC7
	BodyParticleSystem *m_particleSystems;	// +0xC8
	Real m_damageStateValues[4];		// +0xCC
	Bool m_damageStateFlags[4];		// +0xDC
	DamageCreation *m_damageCreationBegin;	// +0xE0
	DamageCreation *m_damageCreationEnd;	// +0xE4
	unsigned char m_padE8[4];
	ObjectID m_linkedObjectID;		// +0xEC
	ArmorSetFlags m_curArmorSetFlags;	// +0xF0
	const void *m_curArmorSet;		// +0xF4
	Armor m_curArmor;			// +0xF8
	DamageFX *m_curDamageFX;		// +0xFC
};

static inline const Real &healthMin(const Real &a, const Real &b)
{
	return b < a ? b : a;
}

// ActiveBody::attemptDamage, retail 0x004BFE07 (2107B): BodyModuleInterface
// slot 0. Zero Hour's order (validate the armor, sanity and indestructible
// early outs, clear the outputs, skip the effectively dead, armor-adjust,
// healing goes to attemptHealing, damage scalar unless unresistable, change
// health, record the damage, damage modules, damage-state change, death,
// damage FX, repulsors) with the BFME 2 additions the bytes show: kind 0x14A
// and status 60 early outs, the containing object's contain module told
// first, a damager with status 65 able to turn the hit into a kill, damage
// types 6 and 23 clipped to leave one health point unless the object is
// masked out (the static kind and status masks), the directional branch for
// type 4, the disable timers and Drawable damage sounds on a state change,
// the unit voice response (message 0x7E0) on dropping under 35%, the
// RespawnUpdate check before onDie, the linked object dying along, the
// damage-dealt report on the damager and the Lua object event.
void ActiveBody::attemptDamage(DamageInfo *damageInfo)
{
	validateArmorAndDamageFX();

	Object *obj = getObject();
	const ActiveBodyModuleData *md = getActiveBodyModuleData();
	if (damageInfo == 0)
		return;
	if (m_indestructible)
		return;
	if (obj->isKindOf(KINDOF_14A))
		return;
	if (obj->testStatus(OBJECT_STATUS_60) && damageInfo->in.m_damageType != DAMAGE_UNRESISTABLE)
		return;

	Object *container = obj->getContainedBy();
	if (container && !obj->getTemplate()->testKindOf(55) && container->getContain())
		container->getContain()->onContainedDamage(obj, this, damageInfo);

	damageInfo->m_actualDamageDealt = 0.0f;
	damageInfo->m_actualDamageClipped = 0.0f;

	if (obj->m_flags438 & 1)
		return;

	Real amount = m_curArmor.adjustDamage(&damageInfo->in, obj, false);
	switch (damageInfo->in.m_damageType)
	{
	case DAMAGE_HEALING:
		if (!damageInfo->in.m_kill)
			attemptHealing(damageInfo);
		return;
	}
	if (damageInfo->in.m_damageType != DAMAGE_UNRESISTABLE)
		amount *= m_damageScalar;

	Object *damager = TheGameLogic->findObjectByID(damageInfo->in.m_sourceID);
	if (damager && damager->testStatus(OBJECT_STATUS_65))
	{
		Object *resolved = damager->rva002931F5(false);
		if (resolved)
		{
			Rva0028C1A9Result *result = (Rva0028C1A9Result *)resolved->rva0028C1A9();
			if (result && result->shouldKill(obj))
			{
				damageInfo->in.m_kill = true;
				result->onKill(obj);
			}
		}
	}

	Rva004BFE07ContainHelper *helper = 0;
	Bool clipped = false;
	if (amount > 0.0f || damageInfo->in.m_kill)
	{
		Object *outer = obj->getContainedBy();
		if (outer)
			helper = outer->getContain()->getDamageHelper();

		static const KindOfMaskType s_unclippedKinds(0, 0x81, 0x67, 0x69);
		static const ObjectStatusMaskType s_unclippedStatus(0, 0x3A, 0x3D, 0x5A);
		if (obj->getAI() && md->m_byte51
			&& !((const Rva00331682Holder *)&s_unclippedStatus)->test(&obj->m_status)
			&& !((const Rva00263546 *)&s_unclippedKinds)->rva00263546((const Rva00263546 *)obj->m_kindOfMask)
			&& (damageInfo->in.m_damageType == DAMAGE_6 || damageInfo->in.m_damageType == DAMAGE_23)
			&& !(obj->m_field25C && obj->m_field25C->m_byte5C)
			&& (!outer || helper))
		{
			Real limit = getHealth() - 1.0f;
			Real clippedAmount = healthMin(limit, amount);
			if (clippedAmount != amount)
			{
				amount = clippedAmount;
				clipped = true;
			}
		}

		BodyDamageType oldState = m_curDamageState;
		if (damageInfo->in.m_kill)
			amount = m_currentHealth;

		if (damageInfo->in.m_damageType == DAMAGE_4)
			rva004BFCD4(amount, damageInfo);

		internalChangeHealth(0.0f - amount, damageInfo);

		if (md->m_damageDelayFrames > 0)
			((Gen_003bcb40 *)obj)->m(TheGameLogic->getFrame() + md->m_damageDelayFrames);

		damageInfo->m_actualDamageDealt = amount;
		damageInfo->m_actualDamageClipped = m_prevHealth - m_currentHealth;

		if (m_lastDamageTimestamp != TheGameLogic->getFrame() && m_lastDamageTimestamp != TheGameLogic->getFrame() - 1)
		{
			*(Rva003427DD *)&m_lastDamageInfo = *(const Rva003427DD *)damageInfo;
			m_lastDamageCleared = false;
			m_lastDamageTimestamp = TheGameLogic->getFrame();
		}
		else
		{
			Object *srcObj1 = TheGameLogic->findObjectByID(m_lastDamageInfo.in.m_sourceID);
			Object *srcObj2 = TheGameLogic->findObjectByID(damageInfo->in.m_sourceID);
			if (srcObj2)
			{
				if (srcObj1)
				{
					if (srcObj2->getTemplate()->testKindOf(9) || srcObj2->getTemplate()->testKindOf(8)
						|| srcObj2->rva0028D491())
					{
						*(Rva003427DD *)&m_lastDamageInfo = *(const Rva003427DD *)damageInfo;
						m_lastDamageCleared = false;
						m_lastDamageTimestamp = TheGameLogic->getFrame();
					}
				}
				else
				{
					*(Rva003427DD *)&m_lastDamageInfo = *(const Rva003427DD *)damageInfo;
					m_lastDamageCleared = false;
					m_lastDamageTimestamp = TheGameLogic->getFrame();
				}
			}
		}

		Object *srcObj = 0;
		if (m_lastDamageInfo.in.m_sourceID != INVALID_ID)
		{
			srcObj = TheGameLogic->findObjectByID(m_lastDamageInfo.in.m_sourceID);
			if (srcObj)
				((Rva002AA201IndexedByteField *)obj->getControllingPlayer())->set(srcObj->getControllingPlayer()->getPlayerIndex());
		}

		if (m_currentHealth < m_prevHealth)
		{
			for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
			{
				DamageModuleInterface *d = (*m)->m_iface.getDamage();
				if (d)
					d->onDamage(damageInfo);
			}

			if (damager)
				damager->rva0028B1D4((Int)damageInfo, (Int)obj);
		}

		if (m_curDamageState != oldState)
		{
			for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
			{
				DamageModuleInterface *d = (*m)->m_iface.getDamage();
				if (d)
					d->onBodyDamageStateChange(damageInfo, oldState, m_curDamageState);
			}

			if (m_curDamageState == BODY_DAMAGED && md->m_damagedDisableFrames > 0.0f)
				obj->setDisabledUntil(DISABLED_8, TheGameLogic->getFrame() + md->m_damagedDisableFrames);
			else if (m_curDamageState == BODY_REALLYDAMAGED && md->m_reallyDamagedDisableFrames > 0.0f)
				obj->setDisabledUntil(DISABLED_8, TheGameLogic->getFrame() + md->m_reallyDamagedDisableFrames);

			Drawable *draw = obj->getDrawable();
			if (draw)
			{
				if (m_curDamageState == BODY_DAMAGED)
				{
					BfmeAudioEventPrefix136 damaged(draw->rva004BE120().m_04, 0);
					((Rva002D9531 *)&damaged)->rva002D9531(obj->getID());
					TheAudio->addAudioEvent(&damaged);
				}
				else if (m_curDamageState == BODY_REALLYDAMAGED)
				{
					BfmeAudioEventPrefix136 reallyDamaged(draw->rva004BE139().m_04, 0);
					((Rva002D9531 *)&reallyDamaged)->rva002D9531(obj->getID());
					TheAudio->addAudioEvent(&reallyDamaged);
				}
			}

			if (m_linkedObjectID)
			{
				Object *linked = TheGameLogic->findObjectByID(m_linkedObjectID);
				if (linked && linked->getBodyModule())
					linked->getBodyModule()->rvaSlot39(m_curDamageState);
			}
		}

		if (m_prevHealth / m_maxHealth >= 0.35f && m_currentHealth / m_maxHealth < 0.35f && m_currentHealth > 0.0f)
		{
			DrawableList drawList;
			drawList.push_back(obj->getDrawable());
			pickAndPlayUnitVoiceResponse(&drawList, GameMessage::MSG_BFME2_0x7E0, 0);
		}

		if (clipped || (m_currentHealth <= 0.0f && m_prevHealth > 0.0f))
		{
			if (damager)
				((Rva00294D61 *)damager)->report(obj, 1);

			if (!clipped)
			{
				static NameKeyType s_respawnKey = TheNameKeyGenerator->nameToKey("RespawnUpdate");
				if (!obj->findModule(s_respawnKey))
				{
					Object *outerObj = obj->getContainedBy();
					Bool contained = outerObj != 0;
					if (contained && outerObj->getContain() && outerObj->getContain()->getContainCount(0) < 2)
						contained = false;

					obj->rva00298517(damageInfo);

					if (m_linkedObjectID)
					{
						Object *linked = TheGameLogic->findObjectByID(m_linkedObjectID);
						if (linked)
						{
							linked->rva00298517(damageInfo);
							linked->setEffectivelyDead(true);
						}
					}

					if (!contained && damageInfo->in.m_sourceID != INVALID_ID
						&& !obj->getTemplate()->testKindOf(25) && !obj->getTemplate()->testKindOf(89))
						rva004BF9ED();
				}
			}
		}

		if (damager)
		{
			Real ratio = damageInfo->m_actualDamageClipped / m_maxHealth;
			if (ratio > 1.0f)
				ratio = 1.0f;
			if (ratio > 0.0f)
				((Rva0028B749Host *)damager)->rva0028B749((Int)obj, ratio);
		}

		BfmeDelayedLuaEventList events;
		if (srcObj)
		{
			events.m_events[0].m_value = srcObj->getID();
			events.m_events[0].m_type = 3;
		}
		((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva003360D2(0, obj, &events);
	}

	doDamageFX(damageInfo);

	if (TheAI->getAiData()->m_enableRepulsors && obj->getTemplate()->testKindOf(45))
		obj->setStatus(OBJECT_STATUS_8, true);

	if (clipped)
	{
		if (helper)
			helper->onClippedDamage(obj);
		if (obj->getAI()->rva002632C7Bool())
			obj->getAI()->rva002632E1();
		obj->getAI()->getCommandInterface()->rva004BFD27(CMD_FROM_AI);
		if (md && md->m_clippedDamageFX)
			FXList::doFXObj(md->m_clippedDamageFX, obj, 0);
	}
}
