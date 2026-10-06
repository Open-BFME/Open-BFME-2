// cl: /MD /DNDEBUG
// ??0Rva004C908B@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x004C908B
// (79B). Dedicated TU.
//
// Re-homed 2026-09-20: this row was landed as
// ??0LaserUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, but the LaserUpdate
// factory (?friend_newModuleInstance@LaserUpdate@@..., 0x000649EE) calls
// 0x000CA752 -- the ONLY direct caller of that body in all of .text --
// and the destructor at 0x000CA8C1 installs the same vtable (0xBCBD60)
// the 0xCA752 ctor installs. A factory call site naming the symbol
// outranks stub-order inference, so 0xCA752 is the LaserUpdate ctor and
// this 79B body (vtable 0xC5EA8C, opaque base 0x362EC7, 44-byte class
// per its factory's 0x2C alloc at 0x0025298F) belongs to another,
// currently unidentified update class. It keeps an address-derived
// opaque name so the verified bytes stay claimed without asserting an
// identity the evidence does not support.

class Thing;
class ModuleData;

// Rva004C908B_vftable: matched references place it at VA 0xc5ea8c (retail .rdata value -26).
extern "C" char Rva004C908B_vftable = -26;

// Opaque intermediate; ctor resolves to the opaque row at 0x00362EC7.
class Rva00362EC7
{
public:
	Rva00362EC7(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00362EC7();

protected:
	unsigned char m_pad0[8];
	float m_f0C;
	float m_f10;
	float m_f14;
	float m_f18;
	float m_f1C;
	short m_w20;
	unsigned char m_b22;
	unsigned char m_b23;
	float m_f24;
	float m_f28;
};

class __declspec(novtable) Rva004C908B : public Rva00362EC7
{
public:
	Rva004C908B(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva004C908B();

};

Rva004C908B::Rva004C908B(Thing *thing, const ModuleData *moduleData)
	: Rva00362EC7(thing, moduleData)
{
	m_w20 = -1;
	*reinterpret_cast<char **>(this) = &Rva004C908B_vftable;
	m_f0C = 0.0f;
	m_f10 = 0.0f;
	m_f14 = 0.0f;
	m_f18 = 0.0f;
	m_f1C = 0.0f;
	m_b22 = 1;
	m_b23 = 0;
	m_f24 = 0.0f;
	m_f28 = 0.0f;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0SwayClientUpdate@@QAE@PAVThing@@PBVModuleData@@@Z=??0Rva004C908B@@QAE@PAVThing@@PBVModuleData@@@Z")
