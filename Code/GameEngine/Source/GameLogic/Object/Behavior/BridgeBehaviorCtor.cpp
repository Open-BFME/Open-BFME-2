// cl: /O1 /DNDEBUG /MD /Oi
// ??0BridgeBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00457472 196B.
// Recovered from the banked attempt reverse/attempts/0x00457472.cpp (0.97).
// That bank already carried the lever that finishes the body: writing the
// third Mid-slot store (+0x28) through a local int* instead of the volatile
// char-cast pins it ahead of the freelist call-setup cluster. With it in
// place the whole 196B matches retail byte for byte -- the "3 bytes at +0x01,
// base-ctor arg push order" wall recorded in the bank note is gone, because
// push [ebp+0xc] then push [ebp+8] was already the order this source emits.
// Evidence: base-ctor call 0x00253390, Rva0029FB3BMember::init 0x0029FB3B
// and reset 0x0026549E, six explicit secondary vtable installs, memset zero
// cluster at +0x2C, nested 4x3 loops over +0xA3C/+0xA6C/+0xA9C/+0xACC.
extern "C" const void *const vtbl_00C409DC[];  // ??_7BridgeBehavior@@6BRva0024A797@@@
#pragma comment(linker, "/alternatename:_vtbl_00C409DC=??_7BridgeBehavior@@6BRva0024A797@@@")

extern "C" const void *const vtbl_00C40920[];  // ??_7BridgeBehavior@@6BMiBase1@@@
#pragma comment(linker, "/alternatename:_vtbl_00C40920=??_7BridgeBehavior@@6BMiBase1@@@")

extern "C" const void *const vtbl_00C40914[];  // ??_7BridgeBehavior@@6BUpdateModuleInterfaceData@@@
#pragma comment(linker, "/alternatename:_vtbl_00C40914=??_7BridgeBehavior@@6BUpdateModuleInterfaceData@@@")

extern "C" const void *const vtbl_00C408FC[];  // ??_7BridgeBehavior@@6BBridgeBehaviorInterface@@@
#pragma comment(linker, "/alternatename:_vtbl_00C408FC=??_7BridgeBehavior@@6BBridgeBehaviorInterface@@@")

extern "C" const void *const vtbl_00C408F0[];  // ??_7BridgeBehavior@@6BDamageModuleInterface@@@
#pragma comment(linker, "/alternatename:_vtbl_00C408F0=??_7BridgeBehavior@@6BDamageModuleInterface@@@")

extern "C" const void *const vtbl_00C408EC[];  // ??_7BridgeBehavior@@6BDieModuleInterface@@@
#pragma comment(linker, "/alternatename:_vtbl_00C408EC=??_7BridgeBehavior@@6BDieModuleInterface@@@")

extern "C" const void *const vtbl_00C40818[];  // folded, 7 classes; via ??_7BfmeCtor001B3A20@@6BBfmeCtorFirstBase001B3A20@@@
#pragma comment(linker, "/alternatename:_vtbl_00C40818=??_7BfmeCtor001B3A20@@6BBfmeCtorFirstBase001B3A20@@@")

extern "C" const void *const vtbl_00BE2B78[];  // folded, 10 classes; via ??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE2B78=??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@")

class Thing;
class ModuleData;

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


class Rva0029FB3BMember
{
public:
	void init(void *context);
	void reset();
	void *m_head;
};

extern "C" void *memset(void *dst, int val, unsigned int size);

class BridgeBehavior : public UpdateModule
{
	void *m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_a3C[4][3];
	int m_a6C[4][3];
	int m_a9C[4][3];
	int m_aCC[4][3];
	bool m_FC;
	bool m_FD;
	char m_padFE[2];
	Rva0029FB3BMember m_free; // +0x100
	int m_104;
public:
	BridgeBehavior(Thing *thing, const ModuleData *moduleData);
};

BridgeBehavior::BridgeBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	*(volatile unsigned int *)((char *)this + 0x20) = ((unsigned int)vtbl_00C40818);
	*(volatile unsigned int *)((char *)this + 0x24) = ((unsigned int)vtbl_00BE2B78);
	int *p28 = (int *)((char *)this + 0x28);
	*p28 = 0x00C1C780;
	void *context = (void *)((char *)&moduleData + 3);
	Rva0029FB3BMember *free = &m_free;
	*(unsigned int *)this = ((unsigned int)vtbl_00C409DC);
	*(unsigned int *)((char *)this + 0x0C) = ((unsigned int)vtbl_00C40920);
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)vtbl_00C40914);
	*(unsigned int *)((char *)this + 0x20) = ((unsigned int)vtbl_00C408FC);
	*(unsigned int *)((char *)this + 0x24) = ((unsigned int)vtbl_00C408F0);
	*(unsigned int *)((char *)this + 0x28) = ((unsigned int)vtbl_00C408EC);
	free->init(context);
	free->reset();
	m_FD = false;
	memset(&m_2C, 0, 16);
	m_FC = false;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
		{
			m_a3C[i][j] = 0;
			m_a6C[i][j] = 0;
			m_a9C[i][j] = 0;
			m_aCC[i][j] = 0;
		}
	m_104 = 0;
}
