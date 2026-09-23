// cl: /O1 /DNDEBUG /MD /arch:SSE
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
	void init();
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
	m_vtable = (const void *)0x00C1AF60;
	m_secondary0C = (const void *)0x00BEFF90;
	m_secondary10 = (const void *)0x00C1AF54;
	m_28.init();
	const FadeAndDieOrnamentUpdateModuleData *data = (const FadeAndDieOrnamentUpdateModuleData *)m_moduleData;
	m_20 &= 0;
	m_24 = fzero;
	m_28 = data->m_28;
}
