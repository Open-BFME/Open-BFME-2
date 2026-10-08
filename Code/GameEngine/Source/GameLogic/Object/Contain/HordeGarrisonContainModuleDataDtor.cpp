// cl: /O1 /DNDEBUG /MD
//
// ??1HordeGarrisonContainModuleData@@UAE@XZ retail 0x00257A05 5 bytes.
// HordeGarrisonContainModuleData's virtual dtor is a 5-byte jmp to the rowed
// GarrisonContainModuleData base dtor at 0x00257507, `this` unchanged: the
// derived data (ctor 0x0047A251, vtable 0x00BF4328, 0xD4 bytes from factory
// 0x0024BAD1) adds nothing needing teardown and retail stores no vptr
// (novtable, as the HordeGarrisonContain dtor 0x0047A147 does). Called by the
// deleting dtor 0x002579E9 (ContainModuleDeletingDtors.cpp) and the unwind
// funclets of the module-data factories.

class GarrisonContainModuleData
{
public:
	virtual ~GarrisonContainModuleData();
};

class __declspec(novtable) HordeGarrisonContainModuleData : public GarrisonContainModuleData
{
public:
	virtual ~HordeGarrisonContainModuleData();
};

HordeGarrisonContainModuleData::~HordeGarrisonContainModuleData()
{
}
