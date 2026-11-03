// cl: /MD /GX /DNDEBUG
//
// ??0AODCrushCollideModuleData@@QAE@XZ, retail 0x004BBF89 (115 bytes).
// Standalone Collide-side ModuleData for the Army-of-the-Dead crush: nulls
// the tiered FX and ObjectCreationList slots, sets the DamageType and tier
// flags and zeroes the Damage floats matching the rowed single-table proc's
// table 0x0085A4A8 (SmallFXList at +0x08, SmallObjectCreationList at +0x0C,
// MediumFXList at +0x10, MediumObjectCreationList at +0x14, LargeFXList at
// +0x18, LargeObjectCreationList at +0x1C, DamageType at +0x20, Damage at
// +0x28), and builds the +0x2C filter member through the pinned 0x3623E5
// ctor. DevastateSpecialPowerModuleDataCtor precedent: virtual classes with
// a declared-only virtual dtor make the compiler emit the vtable store
// mid-init through the ??_7 pin at the true vtable 0x00C5A350, and the dtor
// is the sole unwindable giving the single state-0 store; /Oy- forces the
// ebp frame with the __EH_prolog prologue and /arch:SSE keeps the float
// zeros as xorps plus movss. The AODCrushCollide pool key at 0x4BBF69 sits
// in the same cluster; the ModuleData factory at 0x251056 (news 0x48) is
// the only raw caller. Supersedes the 0x4BBF89 ctor pin (row proves the
// body).

#include "../../../../../Include/GameLogic/Module/Rva003623E5Member.h"

// EH-driving shim (ToppleUpdateModuleDataCtor precedent): the retail body
// has an EH frame with a single state-0 store but makes no base call and
// declares no member with a dtor, so the unwindable is manufactured with an
// empty base whose dtor forwards to the body retail's funclet reaches.
// It emits zero code and covers the +0 vptr plus +4 gap ahead of the +0x08
// members below.
// Retail's state-0 funclet 0x0078F6E3 unwinds it through the Snapshot
// destructor fold 0x0049B47C, rowed here under its non-virtual spelling
// ??1Rva0040E3EEBase@@QAE@XZ (Rva0040E3EEFinish.cpp): forward to it.
class Rva0040E3EEBase
{
public:
	~Rva0040E3EEBase();
};

class AODCrushCollideEmptyBase
{
public:
	AODCrushCollideEmptyBase() {}
	~AODCrushCollideEmptyBase() { ((Rva0040E3EEBase *)this)->Rva0040E3EEBase::~Rva0040E3EEBase(); }

private:
	unsigned char m_pad[4];
};

class AODCrushCollideModuleData : public AODCrushCollideEmptyBase
{
public:
	AODCrushCollideModuleData();
	virtual ~AODCrushCollideModuleData();

private:
	void *m_smallFX; // +0x08
	void *m_smallOCL; // +0x0C
	void *m_mediumFX; // +0x10
	void *m_mediumOCL; // +0x14
	void *m_largeFX; // +0x18
	void *m_largeOCL; // +0x1C
	int m_damageType; // +0x20
	int m_deathType; // +0x24
	float m_damage; // +0x28
	Rva003623E5Member m_filter; // +0x2C
	int m_specialDamageType; // +0x30
	int m_specialDeathType; // +0x34
	float m_specialDamage; // +0x38
	int m_selfDamageType; // +0x3C
	int m_selfDeathType; // +0x40
	float m_selfDamage; // +0x44
};

// ??0AODCrushCollideModuleData@@QAE@XZ @0x4BBF89
AODCrushCollideModuleData::AODCrushCollideModuleData()
	: AODCrushCollideEmptyBase()
	, m_smallFX(0)
	, m_smallOCL(0)
	, m_mediumFX(0)
	, m_mediumOCL(0)
	, m_largeFX(0)
	, m_largeOCL(0)
	, m_damageType(1)
	, m_deathType(0)
	, m_damage(0.0f)
	, m_filter()
	, m_specialDamageType(1)
	, m_specialDeathType(0)
	, m_specialDamage(0.0f)
	, m_selfDamageType(1)
	, m_selfDeathType(0)
	, m_selfDamage(0.0f)
{
}
