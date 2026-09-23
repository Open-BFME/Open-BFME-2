// cl: /O1 /DNDEBUG /MD /Oi
//
// ??0W3DDebrisDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x000B1C41,
// 86 bytes. Behavior-side ctor completing the W3DDebrisDraw file-unit
// (poolkey rowed at 0xB1C97; behavior factory rowed at 0x6482B news 0x48
// with this pinned 2-arg ctor; dtor rowed at 0xB1CE2; setAnimNames rowed
// at 0xB207F).
//
// Shape: frameless single-base ctor over the rowed DrawModule base 0xB19A1
// (W3DPropDraw donor spelling, human-readable pin) with two explicit vtable
// stores at +0/+0xC via byte-wise pointer casts (Defector precedent:
// explicit stores, no virtuals declared anywhere so no vtable is emitted
// here; all immediates are DIR32-masked in comparison), then zero/ones via
// immediates and register eax, or-minus-one at +0x14, and memset trio at
// +0x28 (memset with /Oi inlines to plain stosd x3, no call, zero new pins).
// The first +0xC store is volatile (Assault volatile-first-store precedent:
// a redundant same-slot pair survives iff the first is volatile) and two
// _ReadWriteBarrier intrinsics (zero bytes, MarkerType precedent) pin the
// xor below the volatile store and the or below the +0x10 store. Flat
// classes throughout keep the body frameless. Factory news 0x48 fits the
// +0x44 tail. Zero new pins (base resolves via the existing DrawModule pin).

class Thing;
class ModuleData;
extern "C" void *memset(void *, int, unsigned int);
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class DrawModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);
private:
	unsigned char m_pad[0x28];
};

class W3DDebrisDraw : public DrawModule
{
public:
	W3DDebrisDraw(Thing *thing, const ModuleData *moduleData);
private:
	int m_28[3];
	int m_34;
	int m_38;
	int m_3C;
	unsigned char m_40;
	int m_44;
};

// ??0W3DDebrisDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0x000B1C41
W3DDebrisDraw::W3DDebrisDraw(Thing *thing, const ModuleData *moduleData) :
	DrawModule(thing, moduleData)
{
	*(volatile unsigned int *)((char *)this + 0xC) = 0x00C6FFFC;
	_ReadWriteBarrier();
	*(unsigned int *)this = 0x00BC97A8;
	*(unsigned int *)((char *)this + 0xC) = 0x00BC97A0;
	*(unsigned int *)((char *)this + 0x10) = 0;
	_ReadWriteBarrier();
	*(unsigned int *)((char *)this + 0x14) |= 0xFFFFFFFF;
	*(unsigned int *)((char *)this + 0x18) = 0;
	*(unsigned int *)((char *)this + 0x1C) = 0;
	*(unsigned int *)((char *)this + 0x20) = 0;
	*(unsigned int *)((char *)this + 0x24) = 0;
	m_34 = 0;
	m_38 = 0;
	m_3C = 0;
	m_40 = 0;
	m_44 = 0;
	memset(m_28, 0, 12);
}
