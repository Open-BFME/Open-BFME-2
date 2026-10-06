// cl: /MD /EHsc /DNDEBUG
//
// ??1SlaughterHordeContainModuleData@@UAE@XZ, retail 0x004810D5, 62 bytes.
// Slaughter horde ModuleData dtor: stores vtable 0x00C48DC0 (DIR32, pin
// ??_7SlaughterHordeContainModuleData at 0x00C48DC0 whose slot0 is the
// scalar-deleting dtor at 0x00481113 calling here), destroys the +0xD8
// filter member through the rowed 0x00360D26 dtor, then calls the rowed
// GarrisonContainModuleData base dtor at 0x00257507 directly (direct-Garrison
// precedent from ProductionQueueHordeContainModuleDataDtor and
// HordeSiegeEngineContainModuleDataDtor: the HordeGarrison 0x28 bytes are
// pad, its 5B jmp dtor at 0x00257A05 inlines away). Layout from the pinned
// ctor at 0x0048104D (base 0x0047A251, vtable store 0xC48DC0, float at +0xD4,
// Rva member at +0xD8 via 0x003623E5 pin, bitset reset at +0xDC via rowed
// 0x0024CA24 reaching the 0xEC size the Citadel ctor reuses as base). Called
// by the 0x00481113 deleting dtor and the Citadel dtor at 0x004811E6 via
// base call 0x0048121E path. Same EH 0/-1 shape as rowed Garrison dtor.

class Rva00360D26Member
{
public:
	~Rva00360D26Member();

private:
	int m_x;
};

class GarrisonContainModuleData
{
public:
	virtual ~GarrisonContainModuleData();

private:
	unsigned char m_pad[0xAC - 4];
};

class SlaughterHordeContainModuleData : public GarrisonContainModuleData
{
public:
	virtual ~SlaughterHordeContainModuleData();

private:
	unsigned char m_padAC[0xD4 - 0xAC];
	float m_floatD4;
	Rva00360D26Member m_filterD8;
	unsigned char m_padDC[0xEC - 0xDC];
};

SlaughterHordeContainModuleData::~SlaughterHordeContainModuleData()
{
}
