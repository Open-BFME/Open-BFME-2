// cl: /O1 /MD /DNDEBUG
//
// ??1SiegeDeployHordeSpecialPowerModuleData@@UAE@XZ, retail 0x004C64E9, 5 bytes.
// SiegeDeployHordeSpecialPowerModuleData dtor (ctor rowed at 0x004C64D3 in
// SiegeDeployHordeSpecialPowerModuleDataCtor.cpp, vtable 0x0085DAB0).
// Trivial tail-jmp to the rowed AIUpdateModuleData base dtor 0x00494BE4.
// No vptr stores: novtable suppresses the derived store retail lacks.
// Identity is the ctor TU plus sole caller UNCLAIMED 0x004C5683 (28B ??_G).
// Shape follows ReplaceSelfUpgradeDtor (novtable empty body tail-jmp).

class AIUpdateModuleData
{
public:
	virtual ~AIUpdateModuleData();
};

class __declspec(novtable) SiegeDeployHordeSpecialPowerModuleData : public AIUpdateModuleData
{
public:
	virtual ~SiegeDeployHordeSpecialPowerModuleData();
};

SiegeDeployHordeSpecialPowerModuleData::~SiegeDeployHordeSpecialPowerModuleData()
{
}
