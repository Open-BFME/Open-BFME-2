// cl: /MD /DNDEBUG
// ??0SwayClientUpdate@@QAE@PAVThing@@PBVModuleData@@@Z at retail 0x004C908B
// (79B). Dedicated TU.
//
// Identity: the vftable this ctor installs (0x00C5EA8C) carries the
// "SwayClientUpdate" pool key 0x004C90E0 (slot 4), the rowed
// SwayClientUpdate::loadPostProcess 0x004C9593 (slot 1) and
// SwayClientUpdate::clientUpdate 0x004C923B (slot 12), and the
// SwayClientUpdate factory stub (0x0025298F, a 0x2C new) is its caller. The
// member stores are Zero Hour's SwayClientUpdate ctor initializers plus the
// two BFME floats at +0x24/+0x28. It was named by address (Rva004C908B)
// after the 2026-09-20 re-home took the LaserUpdate name away from it.

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

class __declspec(novtable) SwayClientUpdate : public Rva00362EC7
{
public:
	SwayClientUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~SwayClientUpdate();

};

SwayClientUpdate::SwayClientUpdate(Thing *thing, const ModuleData *moduleData)
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
