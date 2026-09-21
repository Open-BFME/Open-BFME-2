// cl: /O1 /DNDEBUG /MD
//
// ??0GateProxyBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0024E2CC,
// 51 bytes. Dedicated TU: derived two-arg ctor running the pinned
// GateOpenAndClose base ctor (0x49889C) with the Thing plus ModuleData args,
// clearing the derived int at +0x4C, then installing the derived MI vtables
// at +0/+4/+0x10/+0x14 (pinned ??_7 set; +0x10 reuses the base-folded
// 0x00BEF248). Ret-8 thiscall, return-this tail. Recipe: the 18B
// GateProxyBehaviorModuleData ctor (base call plus derived vtable) widened to
// the MI behavior shape. Class identity is the GateProxyBehavior pool key
// (rowed at 0x24E30E); the base behavior ctor is rowed-pinned at 0x49889C.

class Thing;
class ModuleData;

class ProxyBaseA
{
public:
	virtual ~ProxyBaseA();
};

class ProxyBaseB
{
public:
	virtual ~ProxyBaseB();

private:
	unsigned char m_pad[8]; // +0x8..+0xF data under the +4 vptr
};

class ProxyBaseC
{
public:
	virtual ~ProxyBaseC();
};

class ProxyBaseD
{
public:
	virtual ~ProxyBaseD();
};

class GateOpenAndCloseBehavior : public ProxyBaseA, public ProxyBaseB, public ProxyBaseC, public ProxyBaseD
{
public:
	GateOpenAndCloseBehavior(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_pad[0x4C - 0x18];
};

class GateProxyBehavior : public GateOpenAndCloseBehavior
{
public:
	GateProxyBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~GateProxyBehavior();

private:
	int m_unk4C;
};

// ??0GateProxyBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x24E2CC
GateProxyBehavior::GateProxyBehavior(Thing *thing, const ModuleData *moduleData)
	: GateOpenAndCloseBehavior(thing, moduleData)
{
	m_unk4C &= 0;
}
