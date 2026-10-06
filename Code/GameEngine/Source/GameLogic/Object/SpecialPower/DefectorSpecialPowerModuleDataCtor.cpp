// cl: /MD /DNDEBUG
//
// ??0DefectorSpecialPowerModuleData@@QAE@XZ, retail 0x004C2A6A (26 bytes).
// Frameless trivial ctor over the pinned SpecialPower base (0x4930A0):
// overwrites the base vptr slot with the explicit vtable 0x00C5E7A8 first
// (ElvenWood precedent: pointer-cast write, no virtuals declared anywhere
// so no vtable is emitted here), then zeroes the FatCursorRadius float at
// +0x7C (/arch:SSE keeps the float zero as xorps plus movss, ReflectDamage
// precedent). Flat classes throughout (no declared dtors anywhere) keep the
// body frameless. Field identity is the rowed base-call buildFieldParse
// table 0x00C5C764 holding exactly FatCursorRadius at +0x7C, matching BFME1's
// DefectorSpecialPowerModuleData table. The ctor body is shared with the
// Bounty factory 0x251DCC (same size, same trivial shape, SlotToLock
// shared-fold precedent); this row proves the body. Row supersedes the
// 0x4C2A6A ctor pin.

extern "C" const void *const vtbl_00C5E7A8[];  // folded, 2 classes; via ??_7CombineHordeSpecialPowerModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C5E7A8=??_7CombineHordeSpecialPowerModuleData@@6B@")

class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();

private:
	unsigned char m_pad[0x7C];
};

class DefectorSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	DefectorSpecialPowerModuleData();

private:
	float m_fatCursorRadius;	// +0x7C
};

// ??0DefectorSpecialPowerModuleData@@QAE@XZ @0x4C2A6A
DefectorSpecialPowerModuleData::DefectorSpecialPowerModuleData()
	: SpecialPowerModuleData()
{
	*(unsigned int *)this = ((unsigned int)vtbl_00C5E7A8);
	m_fatCursorRadius = 0.0f;
}
