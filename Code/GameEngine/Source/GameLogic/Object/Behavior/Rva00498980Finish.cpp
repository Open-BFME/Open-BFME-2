// cl: /DNDEBUG /MD
//
// ?rva00498980@GateOpenAndCloseBehavior@@QAE_NXZ @0x00498980 (87B):
// Gate open/close state test. ModuleData at +8, state at +0x28, timer at
// +0x34. Case 2: (100 - percent) >= m_34; case 1: true; case 0: m_34 >
// percent; default false. Retail lays the true block first, so the source
// cases are ordered 2, 1, 0. Evidence: rowed win/timer callers, m_28 state
// values 0/1/2 from GateOpenAndCloseBehaviorCtorShard, /arch:SSE fcomi shape.
class Thing;
class ModuleData;
struct GateOpenAndCloseModuleData
{
	char m_base[8];
	bool m_openByDefault;
	char m_pad09[3];
	unsigned int m_resetTimeInMilliseconds;
	unsigned int m_percent;
};
class BehaviorModuleBase
{
public:
	virtual void unusedBase();
	int m_a;
	int m_b;
};
class BehaviorModuleOther
{
public:
	virtual void unusedOther();
};
class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};
class UpdateModuleInterface
{
public:
	virtual void update();
};
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	virtual void update();
};
class GatePrimary
{
public:
	GatePrimary() {}
	virtual void gatePrimaryFn() = 0;
};
class GateOpenAndCloseBehavior : public GatePrimary, public UpdateModule
{
	int m_24;
	int m_28;
	int m_2C;
	bool m_30;
	float m_34;
	float m_38;
	int m_3C;
	int m_40;
	int m_44;
	bool m_48;
public:
	GateOpenAndCloseBehavior(Thing *thing, const ModuleData *moduleData);
	bool rva00498980();
};
bool GateOpenAndCloseBehavior::rva00498980()
{
	GateOpenAndCloseModuleData *data = *(GateOpenAndCloseModuleData **)((char *)this + 8);
	switch (m_28)
	{
	case 2:
		if ((float)(100 - data->m_percent) >= m_34)
			return true;
		return false;
	case 1:
		return true;
	case 0:
		if (m_34 > (float)data->m_percent)
			return true;
		return false;
	default:
		return false;
	}
}
