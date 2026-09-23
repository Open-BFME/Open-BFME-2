// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0LaserUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00362EEE,
// 112 bytes. Frameless push-esi ctor (rowed instance factory 0x24D522 news
// 0x54 with this pinned 2-arg ctor as its raw caller).
//
// Shape follows the SlavedUpdate precedent over an opaque rowed base: the
// local Rva00362EC7 base is declared without virtuals or a dtor (its rowed
// TU keeps those) so the derived ctor stays frameless; vtable 0xC170E0 is
// a hand-placed store after the +0x24 byte. Zero idiom is an eax-homed int
// zero plus an xmm0-homed fzero local (/arch:SSE emits retail xorps+movss);
// the +0x3C 1.0f comes from the shared literal at 0x00BBB8D8 via a mid-body
// float local so retail's load lands between the float and int store groups.
// Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// Opaque intermediate; ctor resolves to the rowed base at 0x00362EC7.
class Rva00362EC7
{
public:
	Rva00362EC7(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;		// +0x00
	unsigned int m_04;			// +0x04
	unsigned int m_08;			// +0x08
};

class LaserUpdate : public Rva00362EC7
{
public:
	LaserUpdate(Thing *thing, const ModuleData *moduleData);

private:
	float m_0C;					// +0x0C
	float m_10;					// +0x10
	float m_14;					// +0x14
	float m_18;					// +0x18
	float m_1C;					// +0x1C
	float m_20;					// +0x20
	bool m_24;					// +0x24
	unsigned int m_28;			// +0x28
	unsigned int m_2C;			// +0x2C
	bool m_30;					// +0x30
	bool m_31;					// +0x31
	unsigned int m_34;			// +0x34
	unsigned int m_38;			// +0x38
	float m_3C;					// +0x3C
	unsigned int m_40;			// +0x40
	unsigned int m_44;			// +0x44
	unsigned int m_48;			// +0x48
	unsigned int m_4C;			// +0x4C
	unsigned int m_50;			// +0x50
};

// ??0LaserUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x00362EEE
LaserUpdate::LaserUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva00362EC7(thing, moduleData)
{
	float fzero = 0.0f;
	int zero = 0;
	m_24 = zero;
	m_vtable = (const void *)0x00C170E0;
	m_18 = fzero;
	m_1C = fzero;
	m_20 = fzero;
	m_0C = fzero;
	m_10 = fzero;
	m_14 = fzero;
	float one = 1.0f;
	_ReadWriteBarrier();
	m_28 = zero;
	m_2C = zero;
	m_30 = zero;
	m_34 = zero;
	m_38 = zero;
	m_31 = zero;
	m_40 = zero;
	m_44 = zero;
	m_48 = zero;
	m_4C = zero;
	m_50 = zero;
	m_3C = one;
}
