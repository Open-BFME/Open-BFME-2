// cl: /O1 /MD /DNDEBUG
//
// ??1GiantBirdSlowDeathBehaviorModuleData@@UAE@XZ, retail 0x00461FED, 5 bytes.
// GiantBirdSlowDeathBehaviorModuleData dtor (ctor rowed at 0x00461F7F in
// GiantBirdSlowDeathBehaviorModuleDataCtor.cpp, vtable 0x00C42E98).
// Trivial tail-jmp to the rowed SlowDeathBehaviorModuleData base dtor
// 0x0045E4A5. No vptr stores: novtable suppresses the derived store retail
// lacks. Identity is the ctor TU plus the base jmp caller shape.
// Shape follows SiegeDeployHordeSpecialPowerModuleDataDtor (novtable empty
// body tail-jmp).

class SlowDeathBehaviorModuleData
{
public:
	virtual ~SlowDeathBehaviorModuleData();
};

class __declspec(novtable) GiantBirdSlowDeathBehaviorModuleData : public SlowDeathBehaviorModuleData
{
public:
	virtual ~GiantBirdSlowDeathBehaviorModuleData();
};

GiantBirdSlowDeathBehaviorModuleData::~GiantBirdSlowDeathBehaviorModuleData()
{
}
