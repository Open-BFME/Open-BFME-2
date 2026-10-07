// cl: /O1 /EHsc /MD /arch:SSE /Ireference/shims/bfme2_ascii
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
#include "ascii_string.h"

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

enum BodyDamageType { BODY_PRISTINE, BODY_DAMAGED, BODY_REALLYDAMAGED, BODY_RUBBLE };

enum DamageType { DAMAGE_HEALING = 7 };
enum KindOfType { KINDOF_220 = 0x220 };
enum ObjectID { INVALID_ID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_UNDER_CONSTRUCTION = 2, OBJECT_STATUS_24 = 24 };

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
	unsigned char m_pad14[0x28 - 0x14];
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
	virtual void d00();
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

class ThingTemplate
{
public:
	UnsignedInt testKindOf(Int k) const { return m_kindOf[k >> 5] & (1U << (k & 31)); }

	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[0x10];		// +0x108
	unsigned char m_pad148[0x632 - 0x148];
	Bool m_byte632;				// +0x632
};

class BodyModuleInterface;

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

	unsigned char m_pad04[0x34 - 0x04];
	Int m_field34;				// +0x34
};

class Object
{
public:
	Bool isKindOf(KindOfType kindOf) const;	// 0x0006F039
	Bool testStatus(ObjectStatusTypes bit) const;	// 0x0004E536
	void setEffectivelyDead(Bool dead);		// 0x0028D2FB
	Bool rva0028F518();				// 0x0028F518
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

	void *m_vptr;
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad08[0x74 - 0x08];
	Int m_id;			// +0x74
	unsigned char m_pad78[0x94 - 0x78];
	UnsignedInt m_status;			// +0x94
	unsigned char m_pad98[0x244 - 0x98];
	BehaviorModule **m_behaviors;		// +0x244
	unsigned char m_pad248[0x254 - 0x248];
	BodyModuleInterface *m_body;		// +0x254
	AIUpdateInterface *m_ai;		// +0x258
	unsigned char m_pad25C[0x280 - 0x25C];
	Int m_field280;				// +0x280
	unsigned char m_pad284[0x438 - 0x284];
	UnsignedInt m_flags438;			// +0x438
};

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
	Int m_field08;				// +0x08
};

class Armor
{
public:
	Real adjustDamage(const DamageInfoInput *input, const Object *obj, Bool flag) const;	// 0x001D90A1

private:
	void *m_name;
};

class ActiveBodyModuleData
{
public:
	unsigned char m_pad00[0x30];
	AsciiString m_damagedAttributeModifier;		// +0x30
	AsciiString m_reallyDamagedAttributeModifier;	// +0x34
	unsigned char m_pad38[0x48 - 0x38];
	const FXList *m_healingFX;		// +0x48
	unsigned char m_pad4C[0x51 - 0x4C];
	Bool m_byte51;				// +0x51
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
	virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
	virtual void m12();
	virtual void rva004BE69C();				// +0x34
	virtual void m14(); virtual void m15();
	virtual void m16();
	virtual void validateArmorAndDamageFX();		// +0x44
	virtual void doDamageFX(const DamageInfo *damageInfo) = 0;	// +0x48
	virtual void m19(); virtual void m20();
	virtual void rvaSlot21(Int arg);			// +0x54

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
	virtual void i02(); virtual void i03();
	virtual Real getHealth() const;				// +0x10
	virtual Real getHealthRatio() const;			// +0x14
	virtual Real getMaxHealth() const;			// +0x18
	virtual void i07();
	virtual void i08();
	virtual void setDamageState(BodyDamageType newState);	// +0x24
	virtual void i10(); virtual void i11();
	virtual void i12(); virtual void i13(); virtual void i14(); virtual void i15();
	virtual void i16(); virtual void i17(); virtual void i18(); virtual void i19();
	virtual void i20(); virtual void i21(); virtual void i22(); virtual void i23();
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
	virtual void attemptHealing(DamageInfo *damageInfo);
	virtual void setDamageState(BodyDamageType newState);
	virtual void internalChangeHealth(Real delta, DamageInfo *damageInfo);

	virtual void rva004BE69C();

protected:
	virtual void xfer(Xfer *xfer);
	static Bool shouldRetaliate(Object *obj);
	virtual void doDamageFX(const DamageInfo *damageInfo);
	virtual void createParticleSystems(const AsciiString &boneBaseName,
		const ParticleSystemTemplate *systemTemplate, Int maxSystems);

private:
	const ActiveBodyModuleData *getActiveBodyModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

	unsigned char m_pad14[4];
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

// ActiveBody::setDamageState, retail 0x004BDAA9.
void ActiveBody::setDamageState(BodyDamageType newState)
{
	switch (newState)
	{
	case BODY_PRISTINE:
		internalChangeHealth(m_maxHealth - m_currentHealth, 0);
		break;
	case BODY_DAMAGED:
		internalChangeHealth(m_damagedRatio * m_maxHealth - m_currentHealth, 0);
		break;
	case BODY_REALLYDAMAGED:
		internalChangeHealth(m_reallyDamagedRatio * m_maxHealth - m_currentHealth, 0);
		break;
	case BODY_RUBBLE:
		internalChangeHealth(0.0f - m_currentHealth, 0);
		break;
	}
	rvaSlot21(0);
}

// ActiveBody::attemptHealing, retail 0x004BEE21 (484B): BodyModuleInterface
// slot 1. Zero Hour shape (validate armor, hand non-healing damage to
// attemptDamage, armor-adjust the amount, change health, record the healing
// frame, tell the damage modules about the heal and any damage-state change,
// then the damage FX) with the BFME 2 additions the bytes show: an early out
// when module data +0x51 is set and the Object has kind 0x220; the "can it
// be healed" test on template byte +0x632, template kinds 150/22/24 and
// Object +0x438 bit 0; the healing FX of module data +0x48 (skipped for
// template kind 7 and status bit 6); the DOT manager notification; and the
// damage state handed on to the body of the linked object at +0xEC.
void ActiveBody::attemptHealing(DamageInfo *damageInfo)
{
	validateArmorAndDamageFX();

	const ActiveBodyModuleData *md = getActiveBodyModuleData();
	Object *obj = getObject();
	if (md->m_byte51 && obj->isKindOf(KINDOF_220))
		return;

	if (damageInfo == 0)
		return;

	if (damageInfo->in.m_damageType != DAMAGE_HEALING)
	{
		attemptDamage(damageInfo);
		return;
	}

	const ThingTemplate *tmpl = obj->getTemplate();
	if (!tmpl->m_byte632 && !tmpl->testKindOf(150) && !tmpl->testKindOf(22) && !tmpl->testKindOf(24)
		&& (obj->m_flags438 & 1))
		return;

	damageInfo->m_actualDamageDealt = 0.0f;
	damageInfo->m_actualDamageClipped = 0.0f;

	Real amount = m_curArmor.adjustDamage(&damageInfo->in, getObject(), false);
	if (amount > 0.0f)
	{
		BodyDamageType oldState = m_curDamageState;
		internalChangeHealth(amount, damageInfo);

		damageInfo->m_actualDamageDealt = amount;
		damageInfo->m_actualDamageClipped = m_prevHealth - m_currentHealth;
		m_lastHealingTimestamp = TheGameLogic->getFrame();

		if (m_currentHealth > m_prevHealth)
		{
			for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
			{
				DamageModuleInterface *d = (*m)->m_iface.getDamage();
				if (d)
					d->onHealing(damageInfo);
			}

			if (!obj->getTemplate()->testKindOf(7) && md->m_healingFX && !obj->testStatusBit6())
				FXList::doFXObj(md->m_healingFX, obj, 0);

			TheGameLogic->m_dotManager->rva0043B72D(obj->getID());
		}

		if (m_curDamageState != oldState)
		{
			for (BehaviorModule **m = obj->getBehaviorModules(); *m; ++m)
			{
				DamageModuleInterface *d = (*m)->m_iface.getDamage();
				if (d)
					d->onBodyDamageStateChange(damageInfo, oldState, m_curDamageState);
			}

			if (m_linkedObjectID)
			{
				Object *linked = TheGameLogic->findObjectByID(m_linkedObjectID);
				if (linked && linked->getBodyModule())
					linked->getBodyModule()->rvaSlot39(m_curDamageState);
			}
		}
	}

	doDamageFX(damageInfo);
}

// ActiveBody::doDamageFX, retail 0x004BED62 (191B): primary vtable slot 18.
// Zero Hour's throttled damage FX, except that BFME 2 takes the FX damage
// type straight from DamageInfoInput +0x10, records the throttle only when
// DamageFX 0x003608DF reports it played something, and then runs the
// damage-creation list (+0xE0, 12-byte entries): each entry whose type
// matches DamageInfoInput +0x28 and whose third word is clear creates its
// ObjectCreationList on this Object.
void ActiveBody::doDamageFX(const DamageInfo *damageInfo)
{
	DamageFX *fx = m_curDamageFX;
	Int type = damageInfo->in.m_damageFXType;
	if (fx)
	{
		UnsignedInt now = TheGameLogic->getFrame();
		if (type == m_lastDamageFXDone && m_nextDamageFXTime > now)
			return;
		Object *source = TheGameLogic->findObjectByID(damageInfo->in.m_sourceID);
		if (fx->rva003608DF(type, damageInfo->m_actualDamageDealt, source, getObject()))
		{
			m_lastDamageFXDone = type;
			m_nextDamageFXTime = ((Rva003605D5 *)m_curDamageFX)->rva003605D5(type, (Int)source) + now;
		}
	}

	for (DamageCreation *it = m_damageCreationBegin; it != m_damageCreationEnd; ++it)
	{
		DamageCreation c = *it;
		if (c.m_type == damageInfo->in.m_creationType && c.m_field08 == 0 && c.m_ocl)
			c.m_ocl->create(getObject(), 0, 0);
	}
}

// ActiveBody::createParticleSystems, retail 0x004BE24A (421B): primary vtable
// slot 19. The BFME 1 donor shape: up to maxSystems systems, each on a random
// bone not used yet (a used-bone array instead of Zero Hour's shrinking
// range), each recorded on the body's particle-system list at +0xC8.
void ActiveBody::createParticleSystems(const AsciiString &boneBaseName,
	const ParticleSystemTemplate *systemTemplate, Int maxSystems)
{
	Object *us = getObject();
	if (systemTemplate == 0)
		return;

	enum { MAX_BONES = 16 };
	Coord3D bonePositions[MAX_BONES];
	Int numBones = us->getMultiLogicalBonePosition(boneBaseName.str(), MAX_BONES, bonePositions, 0, false, 0);
	if (numBones == 0)
		return;
	if (numBones < maxSystems)
		maxSystems = numBones;

	Bool usedBoneIndices[MAX_BONES] = {};
	for (Int i = 0; i < maxSystems; ++i)
	{
#line 1514 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Body\\ActiveBody.cpp"
		Int boneIndex = GameClientRandomValue(0, numBones - 1);
		for (Int j = 0; j < numBones; ++j)
		{
			if (usedBoneIndices[boneIndex] != true)
			{
				const Coord3D *pos = &bonePositions[boneIndex];
				usedBoneIndices[boneIndex] = true;
				if (pos)
				{
					BfmeParticleSystemHandle particleSystem =
						TheParticleSystemManager->createParticleSystem(systemTemplate, true);
					if (particleSystem)
					{
						particleSystem->setPosition(pos);
						particleSystem->attachToObject(us);

						BodyParticleSystem *newEntry = new BodyParticleSystem;
						newEntry->m_particleSystemID = particleSystem->getSystemID();
						newEntry->m_next = m_particleSystems;
						m_particleSystems = newEntry;
					}
				}
				break;
			}
			boneIndex = (boneIndex + 1) % numBones;
		}
	}
}

static inline const Real &healthMax(const Real &a, const Real &b)
{
	return a > b ? a : b;
}

// ActiveBody::internalChangeHealth, retail 0x004BF005 (385B): BodyModuleInterface
// slot 32. Zero Hour's clamp-and-reevaluate with the BFME 2 additions the BFME 1
// donor shares: the four per-state values at +0xCC (cleared at full health,
// reset from the max health when recovering from zero, worn down by healing),
// a second state word at +0x34 that also triggers the visual re-evaluation
// (interface slot 36), and the linked object at +0xEC that receives the new
// health (its body's slot 40) and this object's +0x280.
void ActiveBody::internalChangeHealth(Real delta, DamageInfo *damageInfo)
{
	m_prevHealth = m_currentHealth;
	m_currentHealth += delta;

	Real maxHealth = m_maxHealth;
	if (m_currentHealth > maxHealth)
	{
		m_currentHealth = maxHealth;
		for (Int i = 0; i < 4; ++i)
			m_damageStateValues[i] = 0.0f;
	}
	else if (m_prevHealth == 0.0f)
	{
		Real v = getMaxHealth() * 0.25f;
		v = v * 0.75f - 1.0f;
		for (Int i = 0; i < 4; ++i)
			m_damageStateValues[i] = v;
	}
	else if (delta > 0.0f)
	{
		Real reduce = delta * 0.25f;
		reduce *= 0.75f;
		for (Int i = 0; i < 4; ++i)
		{
			m_damageStateValues[i] -= reduce;
			m_damageStateValues[i] = healthMax(0.0f, m_damageStateValues[i]);
		}
	}

	if (m_currentHealth < 0.0f)
		m_currentHealth = 0.0f;

	BodyDamageType oldState = m_curDamageState;
	Int oldField34 = m_field34;
	rvaSlot21(0);

	Object *us = getObject();
	if (m_curDamageState != oldState || m_field34 != oldField34)
	{
		if (m_currentHealth <= 0.0f || !us->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
			rvaSlot36();
	}

	us->setEffectivelyDead(m_currentHealth <= 0.0f);

	if (m_linkedObjectID)
	{
		Object *other = TheGameLogic->findObjectByID(m_linkedObjectID);
		if (other)
		{
			BodyModuleInterface *body = other->getBodyModule();
			if (body)
			{
				body->rvaSlot40(m_currentHealth, delta > 0.0f);
				other->m_field280 = getObject()->m_field280;
			}
		}
	}
}

// ActiveBody::shouldRetaliate, retail 0x004BE056 (113B). Zero Hour's
// retaliation predicate in BFME 2 form: two template kind early-outs (173
// and 2), the AI must exist with nothing at its +0x34 and be idle, Object
// 0x0028F518 must say no, a stealthed object (status bit 15) must be
// detected (bit 17), and the object must not have status 24.
Bool ActiveBody::shouldRetaliate(Object *obj)
{
	const ThingTemplate *tmpl = obj->getTemplate();
	if (tmpl->testKindOf(173))
		return false;
	if (tmpl->testKindOf(2))
		return false;

	AIUpdateInterface *ai = obj->getAI();
	if (ai != 0 && ai->m_field34 != 0)
		return false;
	AIUpdateInterface *aiForIdle = obj->getAI();
	if (aiForIdle == 0 || !aiForIdle->isIdle())
		return false;

	if (obj->rva0028F518())
		return false;

	if (obj->testStatusBit(15) && !obj->testStatusBit(17))
		return false;

	if (obj->testStatus(OBJECT_STATUS_24))
		return false;
	return true;
}

// ActiveBody primary vtable slot 13, retail 0x004BE69C (134B): apply the
// module data's damaged (+0x30) or really-damaged (+0x34) attribute modifier
// for the current damage state and remove the other; the BFME 1 donor at its
// 0x0020EB40 has the same switch.
void ActiveBody::rva004BE69C()
{
	const ActiveBodyModuleData *md = getActiveBodyModuleData();
	switch (m_curDamageState)
	{
	case BODY_DAMAGED:
		if (!((const StringBase<char> &)md->m_damagedAttributeModifier).isEmpty())
			getObject()->addAttributeModifierToPool(md->m_damagedAttributeModifier, -1);
		break;
	case BODY_REALLYDAMAGED:
		if (!((const StringBase<char> &)md->m_damagedAttributeModifier).isEmpty())
			getObject()->removeAttributeModifierFromPool(md->m_damagedAttributeModifier);
		if (!((const StringBase<char> &)md->m_reallyDamagedAttributeModifier).isEmpty())
			getObject()->addAttributeModifierToPool(md->m_reallyDamagedAttributeModifier, -1);
		return;
	default:
		if (!((const StringBase<char> &)md->m_damagedAttributeModifier).isEmpty())
			getObject()->removeAttributeModifierFromPool(md->m_damagedAttributeModifier);
		break;
	}
	if (!((const StringBase<char> &)md->m_reallyDamagedAttributeModifier).isEmpty())
		getObject()->removeAttributeModifierFromPool(md->m_reallyDamagedAttributeModifier);
}

// BitFlags<21>::xfer, retail 0x004BE781 (315B), the armor-set flags' transfer
// called from ActiveBody::xfer. Zero Hour's BitFlags::xfer (count and the
// names of the set bits on save; clear and set by name on load, throwing on an
// unknown name) with BFME 2's test order: the +0x10 Xfer test sends the raw
// bits through 0x004BE722 first, then save, and every other mode loads.
template <int NUMBITS>
void BitFlags<NUMBITS>::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;

	if (xfer->IsLightCRC())
	{
		((Rva004BE722 *)this)->rva004BE722(xfer);
	}
	else if (xfer->IsStoring())
	{
		Int c = count();
		*xfer == c;
		for (Int i = 0; i < NUMBITS; ++i)
		{
			const char *bitName = getBitNameIfSet(i);
			if (bitName == 0)
				continue;
			AsciiString bitNameA = bitName;
			*xfer == bitNameA;
			--c;
		}
	}
	else
	{
		clear();
		Int c;
		*xfer == c;
		AsciiString string;
		for (Int i = 0; i < c; ++i)
		{
			*xfer == string;
			Bool ok = setBitByName(string.str());
			if (ok == false)
				throw XferException(0, 0);
		}
	}
}

// ActiveBody::xfer, retail 0x004BF1E8 (551B): primary slot 3. Zero Hour's
// field order with BFME 2's changes: the base class goes first and the +0x10
// Xfer test ends the transfer there; the damaged ratios, the side-destroyed
// state (+0x34) and the damage state values and flags (+0xCC/+0xDC) are new;
// the enums go through their cdecl transfers; the last damage info is its own
// vtable's slot 0; the particle systems are skipped under the +0x0C test and
// their load throws XferException 5 on a non-empty list; the linked object
// (+0xEC) follows the armor-set flags.
void ActiveBody::xfer(Xfer *xfer)
{
	BodyModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 1);
	*xfer == version;

	*xfer == m_currentHealth;
	*xfer == m_prevHealth;
	*xfer == m_maxHealth;
	*xfer == m_damagedRatio;
	*xfer == m_reallyDamagedRatio;
	*xfer == m_initialHealth;
	XferBodyDamageType(xfer, (Int *)&m_curDamageState);
	XferBodySideDestroyedType(xfer, &m_field34);
	*xfer == m_nextDamageFXTime;
	XferDamageFXType(xfer, &m_lastDamageFXDone);
	DamageInfo *lastDamageInfo = &m_lastDamageInfo;
	lastDamageInfo->xfer(xfer);
	*xfer == m_lastDamageTimestamp;
	*xfer == m_lastHealingTimestamp;
	*xfer == m_frontCrushed;
	*xfer == m_backCrushed;
	*xfer == m_lastDamageCleared;
	*xfer == m_indestructible;

	if (!xfer->IsCRC())
	{
		BodyParticleSystem *system;
		UnsignedShort particleSystemCount = 0;
		for (system = m_particleSystems; system; system = system->m_next)
			particleSystemCount++;
		*xfer == particleSystemCount;

		if (xfer->IsStoring())
		{
			for (system = m_particleSystems; system; system = system->m_next)
				XferParticleSystemID(xfer, (Int *)&system->m_particleSystemID);
		}
		else
		{
			ParticleSystemID particleSystemID;
			if (m_particleSystems != 0)
				throw XferException(5, 0);
			for (UnsignedShort i = 0; i < particleSystemCount; ++i)
			{
				XferParticleSystemID(xfer, (Int *)&particleSystemID);
				BodyParticleSystem *newEntry = new BodyParticleSystem;
				newEntry->m_particleSystemID = particleSystemID;
				newEntry->m_next = m_particleSystems;
				m_particleSystems = newEntry;
			}
		}
	}

	for (Int i = 0; i < 4; ++i)
	{
		*xfer == m_damageStateValues[i];
		*xfer == m_damageStateFlags[i];
	}
	m_curArmorSetFlags.xfer(xfer);
	XferObjectID(xfer, &m_linkedObjectID);
}
