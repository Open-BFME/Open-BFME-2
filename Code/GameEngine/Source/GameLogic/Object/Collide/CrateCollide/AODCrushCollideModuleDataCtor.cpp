// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
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

class Rva003623E5Member
{
public:
	Rva003623E5Member();

private:
	int m_x;
};

// EH-driving shim (ToppleUpdateModuleDataCtor precedent): the retail body
// has an EH frame with a single state-0 store but makes no base call and
// declares no member with a dtor, so the unwindable is manufactured with an
// empty base carrying a declared-only (never defined, never linked) dtor.
// It emits zero code and covers the +0 vptr plus +4 gap ahead of the +0x08
// members below.
class AODCrushCollideEmptyBase
{
public:
	AODCrushCollideEmptyBase() {}
	~AODCrushCollideEmptyBase();

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
	int m_24; // +0x24
	float m_damage; // +0x28
	Rva003623E5Member m_filter; // +0x2C
	int m_30; // +0x30
	int m_34; // +0x34
	float m_38; // +0x38
	int m_3C; // +0x3C
	int m_40; // +0x40
	float m_44; // +0x44
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
	, m_24(0)
	, m_damage(0.0f)
	, m_filter()
	, m_30(1)
	, m_34(0)
	, m_38(0.0f)
	, m_3C(1)
	, m_40(0)
	, m_44(0.0f)
{
}
