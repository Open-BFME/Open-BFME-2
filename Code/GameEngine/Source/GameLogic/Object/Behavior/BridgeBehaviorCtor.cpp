// cl: /DNDEBUG /MD /Oi
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
extern "C" const void *const __identifier("??_7SecondaryModuleBase@FXParticleSystem@@6B@")[];  // folded vftable 0x00C1C780 (35 classes), by its data-ledger name

// The retail table at RVA 0x008409DC: 13 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GBridgeBehavior@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@Rva00497805@@MAEXXZ")();
void __identifier("?GetSnapshotName@BridgeBehavior@@MBEPBDXZ")();
void __identifier("?xfer@BridgeBehavior@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@BridgeBehavior@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?rva00456A3E@Rva00456A3E@@QAEXXZ")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
}
extern "C" const void *const vtbl_00C409DC[13] = {
	(const void *)&__identifier("??_GBridgeBehavior@@UAEPAXI@Z"), // slot 0 0x00457536
	(const void *)&__identifier("?loadPostProcess@Rva00497805@@MAEXXZ"), // slot 1 0x00497805
	(const void *)&__identifier("?GetSnapshotName@BridgeBehavior@@MBEPBDXZ"), // slot 2 0x004571EE
	(const void *)&__identifier("?xfer@BridgeBehavior@@MAEXPAVXfer@@@Z"), // slot 3 0x00457E72
	(const void *)&__identifier("?getModuleNameKey@BridgeBehavior@@UBE?AW4NameKeyType@@XZ"), // slot 4 0x004571A9
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 5 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 6 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 7 0x000B3FD0
	(const void *)&__identifier("?rva00456A3E@Rva00456A3E@@QAEXXZ"), // slot 8 0x00456A3E
	(const void *)&__identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z"), // slot 9 0x0050B238
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 11 0x000D43D0
	(const void *)&__identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ"), // slot 12 0x0022C4CB
};

extern "C" const void *const __identifier("??_7BridgeBehavior@@6BMiBase1@@@")[];  // vftable 0x00C40920

extern "C" const void *const __identifier("??_7BridgeBehavior@@6BUpdateModule@@@")[];  // ??_7BridgeBehavior@@6BUpdateModule@@@

extern "C" const void *const __identifier("??_7BridgeBehavior@@6BBridgeBehaviorInterface@@@")[];  // vftable 0x00C408FC

extern "C" const void *const __identifier("??_7BridgeBehavior@@6BDamageModuleInterface@@@")[];  // vftable 0x00C408F0

extern "C" const void *const __identifier("??_7BridgeBehavior@@6BDieModuleInterface@@@")[];  // vftable 0x00C408EC

extern "C" const void *const vtbl_00C40818[];  // folded, 7 classes; via ??_7BfmeCtor001B3A20@@6BBfmeCtorFirstBase001B3A20@@@
#pragma comment(linker, "/alternatename:_vtbl_00C40818=??_7BfmeCtor001B3A20@@6BBfmeCtorFirstBase001B3A20@@@")

extern "C" const void *const __identifier("??_7DamageModuleInterface@@6B@")[];  // folded vftable 0x00BE2B78 (10 classes), by its data-ledger name

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

#include <string.h>

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
	*(volatile unsigned int *)((char *)this + 0x24) = ((unsigned int)__identifier("??_7DamageModuleInterface@@6B@"));
	int *p28 = (int *)((char *)this + 0x28);
	*p28 = ((unsigned int)__identifier("??_7SecondaryModuleBase@FXParticleSystem@@6B@"));
	void *context = (void *)((char *)&moduleData + 3);
	Rva0029FB3BMember *free = &m_free;
	*(unsigned int *)this = ((unsigned int)vtbl_00C409DC);
	*(unsigned int *)((char *)this + 0x0C) = ((unsigned int)__identifier("??_7BridgeBehavior@@6BMiBase1@@@"));
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)__identifier("??_7BridgeBehavior@@6BUpdateModule@@@"));
	*(unsigned int *)((char *)this + 0x20) = ((unsigned int)__identifier("??_7BridgeBehavior@@6BBridgeBehaviorInterface@@@"));
	*(unsigned int *)((char *)this + 0x24) = ((unsigned int)__identifier("??_7BridgeBehavior@@6BDamageModuleInterface@@@"));
	*(unsigned int *)((char *)this + 0x28) = ((unsigned int)__identifier("??_7BridgeBehavior@@6BDieModuleInterface@@@"));
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
