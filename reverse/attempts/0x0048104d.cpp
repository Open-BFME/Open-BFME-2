// ??0SlaughterHordeContainModuleData@@QAE@XZ
// partial score=0.89 date=2026-09-23
// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
// stlport
//
// ??0SlaughterHordeContainModuleData@@QAE@XZ, retail 0x0048104D (136 bytes).
// SlaughterHorde garrison data: the rowed HordeGarrisonContain base ctor
// runs first (0x47A251, factory news 0xD4), CashBackPercent at +0xD4 loads
// from g_bfmeK1253, CanAlwaysEnter at +0xD8 builds through the opaque
// 0x3623E5 pin, StatusRequiredForCanAlwaysEnter at +0xDC resets through
// the rowed bitset<128>::reset at 0x0024CA24, and two 28B FixedStorage
// temps from the prototype at 0x00DFEFA4 feed the filter through the
// 0x362087 pin (ret 0x38). Own table 0x008487F8 proves every field; the
// SlaughterHordeContain data factory at 0x0024C071 news 0xEC and calls
// this ctor as sole caller. Shape follows RespawnBodyModuleDataCtor
// (virtual base plus virtual derived with declared-only dtors arms the
// same two EH states over the same temps; the compiler installs this
// TU's vtable through the ??_7 pin at 0x00C48DC0, whose slot0 is the
// scalar-deleting dtor at 0x481113).
// WALL (121/136): the float init perturbs head scheduling; retail orders
// base, float-load, state0, filter-setup, vtable, float-store,
// filter-call, but every probed shape emits base, state0, vtable,
// float-load, filter-setup, float-store, filter-call (floatless diagnostic
// reproduces the RespawnUpdate head exactly, so the float init alone pins
// the vtable early and the load late; explicit/implicit filter init,
// const/non-const extern, /G6//G7 all inert; non-virtual base introduces
// a +4 this-adjust; mid-base ctor refuses to inline).

#include <bitset>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

extern float g_bfmeK1253;

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);

private:
	int m_x;
};

// Virtual base plus virtual derived with declared-only dtors (no code):
// the base contributes the vptr at +0 so the base call takes this with no
// displacement, and the derived vtable store lands mid-init through the
// ??_7 pin (RespawnBodyModuleDataCtor precedent, which arms the same two
// EH states over the same 0xDFEFA4 temps).
class HordeGarrisonContainModuleData
{
public:
	HordeGarrisonContainModuleData();
	virtual ~HordeGarrisonContainModuleData();

private:
	unsigned char m_pad[0xD4 - 4]; // +0x04..+0xD3, real HordeGarrison base
};

class SlaughterHordeContainModuleData : public HordeGarrisonContainModuleData
{
public:
	SlaughterHordeContainModuleData();
	virtual ~SlaughterHordeContainModuleData();

private:
	float m_cashBackPercent; // +0xD4, CashBackPercent
	Rva003623E5Member m_canAlwaysEnter; // +0xD8, CanAlwaysEnter
	unsigned long m_statusRequired[4]; // +0xDC, StatusRequiredForCanAlwaysEnter bitset<128>
};

// ??0SlaughterHordeContainModuleData@@QAE@XZ @0x48104D
SlaughterHordeContainModuleData::SlaughterHordeContainModuleData()
	: m_cashBackPercent(g_bfmeK1253)
	, m_canAlwaysEnter()
{
	((_STL::bitset<128> *)m_statusRequired)->reset();
	m_canAlwaysEnter.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
