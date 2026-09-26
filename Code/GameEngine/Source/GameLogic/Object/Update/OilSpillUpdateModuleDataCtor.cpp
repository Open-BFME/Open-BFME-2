// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0OilSpillUpdateModuleData@@QAE@XZ, retail 0x0048C16C (37 bytes).
// Frameless derived ctor over the Breadcrumb table 0x00C4C2A8
// (BreadcrumbName at +0x10 plus IgnitionWeaponName at +0x14 plus
// IgnitionWeaponSpacing at +0x18 plus OilSpillFX at +0x1C). Identity is the
// table plus the rowed OilSpillUpdate pool key at 0x0048C25E in the same
// cluster plus the rowed factory 0x0024CFDF (news 0x20, sole caller) plus
// the rowed chained proc 0x0048C151. Shape follows the HordeGarrison
// precedent: the opaque pinned base ctor 0x0048BC03 builds the 0x10 base and
// the derived overwrites the shared vtable slot via pointer-cast (Defector
// law). Integer zeros share one xorred register under /O1 and the float zero
// uses xorps plus movss under /arch:SSE. Vtable 0x00C4C2F8 is DIR32-masked
// (pinned ??_7 for identity; slot0 is the scalar-deleting dtor 0x0048C1DB).
// This row supersedes the ctor pin.
//
// Scheduling lever (RebuildHole/WeaponFire/DeployStyle address-take law,
// fourth instance): retail wants both xor regs, then vtable, then zeros. A
// plain source order sinks the vtable below the zeros, while a barrier pins
// it above the xor (too coarse). Three sourced-before pointer locals (one
// per int store that must stay below the vtable) commit exactly those stores
// to source position, folding to addressing mode with zero emitted bytes,
// while the reg-only xorps plus xor float above the vtable and the float
// store waits last. 37 of 37.

class FireWeaponUpdateModuleData
{
public:
	FireWeaponUpdateModuleData();

private:
	unsigned char m_pad[0x10];
};

class OilSpillUpdateModuleData : public FireWeaponUpdateModuleData
{
public:
	OilSpillUpdateModuleData();

private:
	int m_breadcrumbName;			// +0x10
	int m_ignitionWeaponName;		// +0x14
	float m_ignitionWeaponSpacing;	// +0x18
	int m_oilSpillFX;				// +0x1C
};

// ??0OilSpillUpdateModuleData@@QAE@XZ @0x48C16C
OilSpillUpdateModuleData::OilSpillUpdateModuleData()
	: FireWeaponUpdateModuleData()
{
	int *breadcrumbName = &m_breadcrumbName;
	int *ignitionWeaponName = &m_ignitionWeaponName;
	int *oilSpillFX = &m_oilSpillFX;
	*(unsigned int *)this = 0x00C4C2F8;
	*breadcrumbName = 0;
	*ignitionWeaponName = 0;
	*oilSpillFX = 0;
	m_ignitionWeaponSpacing = 0.0f;
}
