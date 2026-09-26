// cl: /O1 /MD /GX /arch:SSE /DNDEBUG /Oy-
//
// ??0DamageFieldUpdateModuleData@@QAE@XZ, retail 0x00491102, 76 bytes.
// DamageField behavior's module data: the rowed chained proc 0x004910E7
// carries Radius at +0x10 plus ObjectFilter at +0x14 plus RequiredUpgrade
// at +0x18 on table 0x00C4D8A8, the rowed factory 0x0024D7C0 news 0x1C
// with this ctor as sole caller, and the ModuleFactory registration names
// the data class DamageFieldUpdate. Shape follows DevastateSpecialPower
// ModuleDataCtor (V5): the virtual base built by the rowed out-of-line
// 0x0048BC03 constructor (declared-only virtual dtor, the TU's first
// unwindable) arms state 0, the compiler installs the derived vtable
// 0x00C4D8E8 after the base call (slot0 is the scalar-deleting dtor
// 0x0049114E sitting right after this ctor, slot1 is the shared ret stub
// 0x004B3FD0; resolves through the ??_7 pin), the Radius zero and the
// ObjectFilter member constructed through the opaque 0x003623E5 pin stay
// stateless, and the RequiredUpgrade string copied from the empty global
// through the rowed 0x00365F0 copy ctor advances state 1 (AsciiString
// dtor via the 0x0036410 fold). Row supersedes the ctor pin.

class FireWeaponUpdateModuleData
{
public:
	FireWeaponUpdateModuleData();
	virtual ~FireWeaponUpdateModuleData();

private:
	unsigned char m_pad[0x10 - 4];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();

private:
	unsigned char m_data[4];
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

extern AsciiString g_emptyAsciiString;

class DamageFieldUpdateModuleData : public FireWeaponUpdateModuleData
{
public:
	DamageFieldUpdateModuleData();
	virtual ~DamageFieldUpdateModuleData();

private:
	int m_radius; // +0x10, Radius float per table 0xC4D8A8; int-kept:
		// retail zeroes it with the AND-zero idiom and a float member
		// would emit xorps plus movss under /arch:SSE (V1-proven)
	Rva003623E5Member m_objectFilter; // +0x14
	AsciiString m_requiredUpgrade; // +0x18
};

// ??0DamageFieldUpdateModuleData@@QAE@XZ @0x00491102
DamageFieldUpdateModuleData::DamageFieldUpdateModuleData()
	: m_radius(0)
	, m_requiredUpgrade(g_emptyAsciiString)
{
}
