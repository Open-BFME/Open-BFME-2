// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ??0GateOpenAndCloseBehavior@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x0049889C, 200 bytes.
//
// GateOpenAndCloseBehavior behavior ctor. The class is multiple inheritance:
// a 4-byte polymorphic primary at +0 (identity open; its inline ctor installs
// the first vtable) plus UpdateModule at +4 (the rowed 0x253390 body).
// UpdateModule stores the module data at its +4 through the ObjectModule row,
// so the behavior reads its table values through [this+8]: OpenByDefault at
// module+8 picks count 1-or-3, ResetTimeInMilliseconds at module+0xC feeds the
// 100.0f divisor. The four vtable installs after the base call are explicit
// body stores (a compiler group would land before the body, ahead of the
// or-minus-one); their immediates are the retail-measured secondary slots.
// The new behavior registers itself into the global gate list at
// [0xDFEEF8]+0x940 through the rowed appendOnce helper; the list owner itself
// is unidentified so the access is a documented absolute. Row supersedes the
// same-name pin; the instance factory (0x24E28B, news 0x4C) stays green via
// the row, as does the appendOnce home TU.
//
// Schedule notes (all probe-proven): the or-minus-one stays first in source
// (Prone law); the 1-or-3 ternary reads openByDefault for the sete form; the
// quotient stays in st0 across the 100.0f store; the push-this for the tail
// call hoists on its own. /arch:SSE is load-bearing for the movss pair (the
// /O1 default emits an integer mov); the appendOnce home TU keeps its own
// flags in a separate shard (same-class-in-2-TUs precedent).

class Thing;
class ModuleData;

// GateOpenAndCloseModuleData layout from INI table 0xBF19F8: OpenByDefault
// at +8, ResetTimeInMilliseconds at +0xC (UpdateModuleData base runs to +8).
struct GateOpenAndCloseModuleData
{
	char m_base[8];
	bool m_openByDefault; // +8
	char m_pad09[3];
	unsigned int m_resetTimeInMilliseconds; // +0xC
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

// 4-byte polymorphic primary at +0. Inline ctor installs the first vtable
// ahead of the UpdateModule call; the implicit trivial dtor arms nothing
// (the single EH state completes with the UpdateModule construction, whose
// mirror carries the declared-only dtor).
class GatePrimary
{
public:
	GatePrimary() {}
	virtual void gatePrimaryFn() = 0;
};

class GateOpenBehaviorList
{
public:
	void appendOnce(void *item);
	void push_back(void *const &item);
private:
	void **m_begin;
	void **m_end;
};

struct GameLogicFrameLocal
{
	char m_pad[0x40];
	int m_gateObject; // +0x40
};

#define TheGameLogic (*(GameLogicFrameLocal *const *)0x00DFE78C)
#define GateListOwnerBlock (*(void *const *)0x00DFEEF8)

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
};

// ??0GateOpenAndCloseBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x49889C
GateOpenAndCloseBehavior::GateOpenAndCloseBehavior(Thing *thing, const ModuleData *moduleData)
	: GatePrimary(), UpdateModule(thing, moduleData)
{
	m_40 |= -1;
	const GateOpenAndCloseModuleData *data = *(const GateOpenAndCloseModuleData **)((char *)this + 8);
	*(unsigned int *)this = 0x00C50178;
	*(unsigned int *)((char *)this + 4) = 0x00C50144;
	*(unsigned int *)((char *)this + 0x10) = 0x00BEF248;
	*(unsigned int *)((char *)this + 0x14) = 0x00C50138;
	m_44 = 1;
	m_48 = false;
	m_28 = data->m_openByDefault ? 1 : 3;
	m_30 = true;
	m_38 = 100.0f / data->m_resetTimeInMilliseconds;
	m_34 = 100.0f;
	m_3C = TheGameLogic->m_gateObject;
	m_2C = 0;
	m_24 = 0;
	GateOpenBehaviorList *list = *(GateOpenBehaviorList **)((char *)GateListOwnerBlock + 0x940);
	list->appendOnce(this);
}
