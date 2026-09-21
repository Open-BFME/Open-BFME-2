// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0OilSpillUpdateModuleData@@QAE@XZ, retail 0x0048C16C, 37 bytes.
// Frameless derived ctor over the Breadcrumb table 0xC4C2A8
// (BreadcrumbName@10, IgnitionWeaponName@14, IgnitionWeaponSpacing@18,
// OilSpillFX@1C). Identity is the table plus the OilSpillUpdate poolkey
// 0x48C25E in the same cluster plus factory 0x24CFDF (news 0x20, sole
// caller) plus rowed chained proc 0x48C151. Shape follows HordeGarrison
// precedent: the opaque pinned base ctor 0x48BC03 builds the 0x10 base; the
// derived overwrites the shared vtable slot via pointer-cast (Defector law:
// a source-written store lands in position, here 4th after the base call
// while the xor reg-ops hoist above it per the scheduling laws); integer
// zeros share one xorred register under /O1 and the float zero uses
// xorps plus movss under /arch:SSE. Vtable 0x00C4C2F8 is DIR32-masked
// (pinned ??_7 for identity; slot0 is the scalar-deleting dtor 0x48C1DB).

class Rva0048BC03Base
{
public:
	Rva0048BC03Base();

private:
	unsigned char m_pad[0x10];
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class OilSpillUpdateModuleData : public Rva0048BC03Base
{
public:
	OilSpillUpdateModuleData();

private:
	int m_breadcrumbName; // +0x10
	int m_ignitionWeaponName; // +0x14
	float m_ignitionWeaponSpacing; // +0x18
	int m_oilSpillFX; // +0x1C
};

// ??0OilSpillUpdateModuleData@@QAE@XZ @0x48C16C
OilSpillUpdateModuleData::OilSpillUpdateModuleData()
	: Rva0048BC03Base()
{
	m_ignitionWeaponSpacing = 0.0f;
	*(unsigned int *)this = 0x00C4C2F8;
	m_breadcrumbName = 0;
	m_ignitionWeaponName = 0;
	m_oilSpillFX = 0;
}
