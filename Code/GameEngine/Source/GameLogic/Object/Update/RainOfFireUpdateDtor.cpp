// cl: /O1 /arch:SSE /DNDEBUG /MD /GX
//
// ??1RainOfFireUpdate@@UAE@XZ, retail 0x004AC24D, 91 bytes.
// Dtor reinstalls primary 0x00854C74 plus secondaries 0x00854BB8/0x00854BA8
// plus +0x20 slot 0x00854BA0 then zeroes +0x2C and calls honest setter
// 0x004AC18D with 0.0 then rowed base 0x0024A797. Layout is the rowed
// 0x38-byte class (Rva0024A797 base 0x20 plus +0x20 secondary plus frame
// plus four floats); caller is the slot-0 deleting dtor at 0x004AC5D9.
// Recipe is the PartTheHeavensUpdateDtor MI pattern with the setter ride.

class Thing;
class ModuleData;
class Object;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
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

class Rva0024A797 : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~Rva0024A797();

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class Secondary20
{
public:
	virtual void setFloat(float v);
};

class RainOfFireUpdate : public Rva0024A797, public Secondary20
{
public:
	virtual ~RainOfFireUpdate();
	void rva004AC18D(float value);

private:
	unsigned int m_frame;
	float m_state28;
	float m_state2C;
	float m_state30;
	float m_state34;
};

RainOfFireUpdate::~RainOfFireUpdate()
{
	m_state2C = 0.0f;
	rva004AC18D(0.0f);
}
