// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??1InvisibilitySpecialPowerModuleData@@UAE@XZ @0x004C24DF (56B): virtual destructor.
// Destroys the pool-aware filter at +0x138 through 0x00360D26 then calls the
// SpecialPower intermediate base dtor at 0x0049334F. Layout from the matched
// EH ctor 0x004C244D in MobNexusContainModuleDataCtor.cpp (opaque 0x7C base
// plus 0x9C nugget at +0x7C plus float at +0x134 plus filter at +0x138 plus
// int at +0x13C for 0x140 total matching the 0x002518CB factory news).
// Identity: vtable 0x00C5C558 (??_7 pin) installed by the ctor mid-init plus
// the ??_G caller at 0x004C24C3 (slot 0). No derived vptr store in retail so
// novtable suppresses it (HelixContainModuleDataDtor precedent). The +0x7C
// nugget has no dtor call in retail so it stays trivial padding here.

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned char m_data[4];
};

class SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_pad[0x7C - 4];
};

class __declspec(novtable) InvisibilitySpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	virtual ~InvisibilitySpecialPowerModuleData();

private:
	unsigned char m_nugget[0x9C]; // +0x7C (trivial: retail emits no call for it)
	unsigned char m_pad118[0x134 - 0x118]; // +0x118
	float m_broadcastRadius; // +0x134
	Rva00360D26Member m_objectFilter; // +0x138
	int m_duration; // +0x13C
};

InvisibilitySpecialPowerModuleData::~InvisibilitySpecialPowerModuleData()
{
}
