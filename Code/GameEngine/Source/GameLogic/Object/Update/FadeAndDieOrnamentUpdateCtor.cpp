// cl: /DNDEBUG /MD
//
// ??0FadeAndDieOrnamentUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x003A439D, 79 bytes. Frameless behavior-side ctor over the rowed
// UpdateModule base 0x253390: vtable C1AF60 plus secondaries BEFF90/C1AF54,
// OrnamentData member at +0x28 via explicit init() (pinned 0xC9251, 53B leaf
// with no callees) then 40-byte copy from moduleData+0x0C via memcpy
// (push-0xA/pop-ecx plus rep-movsd), and-zero at +0x20 plus float zero at
// +0x24 via xmm0-homed fzero (/arch:SSE emits retail xorps+movss). The rowed
// instance factory 0x24ED86 (news 0x50) is the sole raw caller. Row
// supersedes the ctor pin.

extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleOther@@@")[];  // folded vftable 0x00BEFF90 (80 classes), by the name its definer AttributeModifierPoolUpdate.cpp emits on the canonical BehaviorModule chain (data ledger: ...@@6BBehaviorModuleOther@@@)

extern "C" const void *const __identifier("??_7Rva003A4322@@6BRva003A4322_B2@@@")[];  // vftable 0x00C1AF54
// The retail table at RVA 0x0081AF60: 13 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003A4322@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@HijackerUpdate@@MAEXXZ")();
void __identifier("?name@Rva003A433BNamed@@QBEPBDXZ")();
void __identifier("?xfer@Rva003A4322@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@FadeAndDieOrnamentUpdate@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ")();
}
extern "C" const void *const vtbl_00C1AF60[13] = {
	(const void *)&__identifier("??_GRva003A4322@@UAEPAXI@Z"), // slot 0 0x003A43EC
	(const void *)&__identifier("?loadPostProcess@HijackerUpdate@@MAEXXZ"), // slot 1 0x004A40BB
	(const void *)&__identifier("?name@Rva003A433BNamed@@QBEPBDXZ"), // slot 2 0x003A433B
	(const void *)&__identifier("?xfer@Rva003A4322@@MAEXPAVXfer@@@Z"), // slot 3 0x003A4408
	(const void *)&__identifier("?getModuleNameKey@FadeAndDieOrnamentUpdate@@UBE?AW4NameKeyType@@XZ"), // slot 4 0x003A4358
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 5 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 6 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 7 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 8 0x000B3FD0
	(const void *)&__identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z"), // slot 9 0x0050B238
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 11 0x000D43D0
	(const void *)&__identifier("?getUpdatePhase@UpdateModule@@MBE?AW4SleepyUpdatePhase@@XZ"), // slot 12 0x0022C4CB
};

#include <string.h>

class Thing;
class ModuleData;
class Object;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

struct OrnamentData
{
	OrnamentData *init() throw();
	unsigned char m_pad[0x28];
};

struct FadeAndDieOrnamentUpdateModuleData
{
	unsigned char m_pad[0x0C];
	OrnamentData m_28;
};

class FadeAndDieOrnamentUpdate : public UpdateModule
{
public:
	FadeAndDieOrnamentUpdate(Thing *thing, const ModuleData *moduleData);

private:
	int m_20;
	float m_24;
	OrnamentData m_28;
};

// ??0FadeAndDieOrnamentUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x003A439D
FadeAndDieOrnamentUpdate::FadeAndDieOrnamentUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	m_vtable = (const void *)((unsigned int)vtbl_00C1AF60);
	m_secondary0C = (const void *)((unsigned int)__identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleOther@@@"));
	m_secondary10 = (const void *)((unsigned int)__identifier("??_7Rva003A4322@@6BRva003A4322_B2@@@"));
	m_28.init();
	const FadeAndDieOrnamentUpdateModuleData *data = (const FadeAndDieOrnamentUpdateModuleData *)m_moduleData;
	m_20 &= 0;
	m_24 = fzero;
	m_28 = data->m_28;
}
