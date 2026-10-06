// cl: /MD /DNDEBUG
//
// ??1DefectorSpecialPowerModuleData@@UAE@XZ @0x004C8AB0 5B.
// DefectorSpecialPowerModuleData dtor (ctor rowed at 0x004C2A6A in
// DefectorSpecialPowerModuleDataCtor.cpp, vtable 0x0085E7A8 slot0
// ??_G at 0x004C2A84). Trivial tail-jmp to the rowed SpecialPowerModuleData base
// dtor 0x0049334F. No vptr stores: novtable suppresses the derived
// store retail lacks. Identity is the ctor TU plus sole caller
// 0x004C2A84 (28B ??_G). Shape follows SiegeDeployHordeSpecialPower
// ModuleDataDtor (novtable empty body tail-jmp).

class SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();
};

class __declspec(novtable) DefectorSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	virtual ~DefectorSpecialPowerModuleData();
};

DefectorSpecialPowerModuleData::~DefectorSpecialPowerModuleData()
{
}
