// cl: /DNDEBUG /MD /GX
//
// ??0ToppleUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004A8201,
// 157 bytes. Behavior-side ctor (rowed instance factory 0x24F080 news
// 0x58 with this pinned 2-arg ctor as its sole raw caller at 0x24F0A7).
//
// Shape follows the OneRingPenaltyUpdate precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a two-phase +0x20 slot via sourced-before address-take, an
// eax-homed int zero plus an xmm0-homed float zero (/arch:SSE emits
// retail xorps+movss), the setWakeFrame arg pushes hoisted above the
// stores (no intervening call), the three derived vtable installs, float
// zeros at +0x40/+0x24/+0x3C/+0x28/+0x2C/+0x30/+0x34/+0x54, int zeros at
// +0x44/+0x38/+0x4C/+0x50, a byte zero at +0x48, and the setWakeFrame tail
// (protected IAEX Object-uint spelling resolves via the existing pin at
// 0x44DF71). Row supersedes the ctor pin.

extern "C" const void *const vtbl_00C40818[];  // folded, 7 classes; via ??_7BfmeCtor001B3A20@@6BBfmeCtorFirstBase001B3A20@@@
#pragma comment(linker, "/alternatename:_vtbl_00C40818=??_7BfmeCtor001B3A20@@6BBfmeCtorFirstBase001B3A20@@@")
extern "C" const void *const vtbl_00C5A260[];  // folded, 4 classes; via ??_7AODCrushCollide@@6BCollideDtorB2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C5A260=??_7AODCrushCollide@@6BCollideDtorB2@@@")

extern "C" const void *const vtbl_00C53848[];  // ??_7Rva004A8091@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C53848=??_7Rva004A8091@@6B@")
extern "C" const void *const vtbl_00C53860[];  // ??_7Rva004A8091@@6BRva0024A797_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C53860=??_7Rva004A8091@@6BRva0024A797_B2@@@")
extern "C" const void *const vtbl_00C5386C[];  // ??_7Rva004A8091@@6BRva0024A797_Root@@@
#pragma comment(linker, "/alternatename:_vtbl_00C5386C=??_7Rva004A8091@@6BRva0024A797_Root@@@")

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class ToppleUpdate : public UpdateModule
{
public:
	ToppleUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_20;
	float m_24;
	float m_28;
	float m_2C;
	float m_30;
	float m_34;
	unsigned int m_38;
	float m_3C;
	float m_40;
	unsigned int m_44;
	unsigned char m_48;
	unsigned int m_4C;
	unsigned int m_50;
	float m_54;
};

// ??0ToppleUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004A8201
ToppleUpdate::ToppleUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float fzero = 0.0f;
	int *slot20 = (int *)&m_20;
	*slot20 = (int)((unsigned int)vtbl_00C40818);
	int zero = 0;
	m_vtable = (const void *)((unsigned int)vtbl_00C5386C);
	m_secondary0C = (const void *)((unsigned int)vtbl_00C5A260);
	m_secondary10 = (const void *)((unsigned int)vtbl_00C53860);
	m_20 = (const void *)((unsigned int)vtbl_00C53848);
	m_40 = fzero;
	m_48 = zero;
	m_44 = zero;
	m_24 = fzero;
	m_3C = fzero;
	m_28 = fzero;
	m_2C = fzero;
	m_30 = fzero;
	m_34 = fzero;
	m_38 = zero;
	m_4C = zero;
	m_50 = zero;
	m_54 = fzero;
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}
