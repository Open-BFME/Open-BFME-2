// cl: /O1 /MD /DNDEBUG /EHsc
//
// ??1RespawnBodyModuleData@@UAE@XZ, retail 0x004C1569 (53 bytes).
// Virtual dtor over vtable 0x00C5BA00 (slot 0 deleting dtor at 0x004C154D
// calls this body). Destroys the +0x64 filter through the pinned teardown
// at 0x00360D26 then calls the rowed ActiveBodyModuleData base dtor at
// 0x00256CB0. Layout from the rowed ctor TU at 0x004C14DF (base 0x64 via
// 0x004BF59F vtable 0xC5BA00 filter +0x64 CanRespawn +0x68). Shape follows
// SymbioticStructuresBodyModuleDataDtor at 0x002570F9 (identical 53B EH
// frame with +0x64 member plus base call and no derived vtable store).
class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

class __declspec(novtable) ActiveBodyModuleData
{
public:
	ActiveBodyModuleData();
	virtual ~ActiveBodyModuleData();

private:
	unsigned char m_opaque[0x64 - 4];
};

class __declspec(novtable) RespawnBodyModuleData : public ActiveBodyModuleData
{
public:
	virtual ~RespawnBodyModuleData();

private:
	Rva00360D26Member m_filter; // +0x64
};

RespawnBodyModuleData::~RespawnBodyModuleData()
{
}
