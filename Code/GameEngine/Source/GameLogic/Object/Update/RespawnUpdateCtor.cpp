// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0RespawnUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004AF096,
// 128 bytes. Behavior-side ctor (rowed instance factory 0x24F8F6 news
// 0x44 with this pinned 2-arg ctor as its sole raw caller at 0x24F91D).
//
// Shape follows the SlaveWatcherBehavior precedent over the same rowed
// UpdateModule base 0x253390: EH prologue via /GX plus the declared-only
// base dtor, a minus-one-homed local (or-ecx) plus a zero-homed local,
// the setWakeFrame arg pushes hoisted above the stores (no intervening
// call), minus-one at +0x28/+0x34/+0x38/+0x3C, the three derived vtable
// installs, zeros at +0x2C/+0x30/+0x24, byte zeros at +0x40/+0x41, minus-
// one float at +0x20 via the pooled -1.0f literal (/arch:SSE movss), and
// the setWakeFrame tail (protected IAEX Object-uint spelling resolves via
// the existing pin at 0x44DF71). Row supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	~UpdateModule();

protected:
	void setWakeFrame(Object *object, unsigned int frame);

	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class RespawnUpdate : public UpdateModule
{
public:
	RespawnUpdate(Thing *thing, const ModuleData *moduleData);

private:
	float m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned int m_30;
	unsigned int m_34;
	unsigned int m_38;
	unsigned int m_3C;
	unsigned char m_40;
	unsigned char m_41;
};

// ??0RespawnUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x004AF096
RespawnUpdate::RespawnUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	float negOne = -1.0f;
	int minusOne = -1;
	int zero = 0;
	m_34 = minusOne;
	m_38 = minusOne;
	m_3C = minusOne;
	m_28 = minusOne;
	m_vtable = (const void *)0x00C556B0;
	m_secondary0C = (const void *)0x00BEFF90;
	m_secondary10 = (const void *)0x00C556A4;
	m_2C = zero;
	m_30 = zero;
	m_40 = zero;
	m_20 = negOne;
	m_41 = zero;
	m_24 = zero;
	setWakeFrame(m_object, 0x3FFFFFFF);
}
