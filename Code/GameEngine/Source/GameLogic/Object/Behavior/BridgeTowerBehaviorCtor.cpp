// cl: /O1 /DNDEBUG /MD
//
// ??0BridgeTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00458704,
// 85 bytes. Behavior-side ctor completing the BridgeTowerBehavior file-unit
// (poolkey rowed at 0x45876C, dtor rowed at 0x4586C7 in the ZH-donor TU,
// instance factory rowed at 0x24ACC8 with news 0x24 and this pinned 2-arg
// ctor as its sole raw caller).
//
// Retail diverges from the ZH donor (which only clears m_bridgeID): the BFME2
// body stores the +0x10/+0x14/+0x18 secondary slots twice (first triple, then
// the vtable-fold triple), zeroes +0x1C/+0x20, and installs the primary
// vtable plus +0x0C between the two triples. The first triple survives
// through volatile-first stores (AnnounceBirthAndDeath precedent); the second
// triple plus vtable are plain body-order stores over an explicit m_vtable
// member (no virtuals, no vtable emission). Row supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_vtable;
static int s_secondary0C;
static int s_first10;
static int s_first14;
static int s_first18;
static int s_second10;
static int s_second14;
static int s_second18;

// BehaviorModule base; ctor resolves to its row. Protected slots mirror the
// retail stores; the explicit m_vtable member stands in for the inherited
// vptr so body order is source order.
class BehaviorModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	int m_04;
	int m_08;
	const void *m_0C;
};

class BridgeTowerBehavior : public BehaviorModule
{
public:
	BridgeTowerBehavior(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_10;
	const void *m_14;
	const void *m_18;
	int m_1C;
	int m_20;
};

// ??0BridgeTowerBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00458704
BridgeTowerBehavior::BridgeTowerBehavior(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData)
{
	*(const void * volatile *)&m_10 = &s_first10;
	*(const void * volatile *)&m_14 = &s_first14;
	*(const void * volatile *)&m_18 = &s_first18;
	_ReadWriteBarrier();
	m_1C = 0;
	m_20 = 0;
	m_vtable = &s_vtable;
	m_0C = &s_secondary0C;
	m_10 = &s_second10;
	m_14 = &s_second14;
	m_18 = &s_second18;
}
