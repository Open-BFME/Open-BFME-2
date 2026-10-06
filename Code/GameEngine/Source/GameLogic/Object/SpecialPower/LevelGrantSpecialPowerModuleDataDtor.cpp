// cl: /MD /GX /DNDEBUG /Oy-
// Rva0044ECCE is an address-derived base stand-in; its target class name is unproven.
//
// ??1LevelGrantSpecialPowerModuleData@@UAE@XZ, retail 0x004C2C22, 56 bytes.
// Dtor for the LevelGrantSpecialPower ModuleData (ctor rowed at 0x4C2AA0).
// Layout from the ctor TU and the chained table at 0x00C5C8D0 (Experience
// at +0xC8 plus RadiusEffect at +0xCC plus AcceptanceFilter at +0xD0 plus
// LevelFX at +0xD4 over the 0xC8-byte base). Teardown is the filter word at
// +0xD0 through the pinned 0x360D26 dtor then the base through the pinned
// 0x44ECCE dtor. BFME1 donor is
// LevelGrantSpecialPowerModuleDataConstructor.cpp destructor. Caller is the
// slot-0 scalar-deleting dtor at 0x4C2C06 (vtable 0x00C5C828).

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned char m_data[4];
};

class Rva0044ECCE
{
public:
	virtual ~Rva0044ECCE();

private:
	unsigned char m_pad[0xC8 - 4];
};

class __declspec(novtable) LevelGrantSpecialPowerModuleData : public Rva0044ECCE
{
public:
	virtual ~LevelGrantSpecialPowerModuleData();

private:
	int m_experience; // +0xC8
	float m_radiusEffect; // +0xCC
	Rva00360D26Member m_acceptanceFilter; // +0xD0
	int m_levelFX; // +0xD4
};

LevelGrantSpecialPowerModuleData::~LevelGrantSpecialPowerModuleData()
{
}
