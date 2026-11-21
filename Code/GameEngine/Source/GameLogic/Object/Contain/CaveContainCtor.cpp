// cl: /DNDEBUG /MD
//
// ??0CaveContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00466630, 125 bytes.
// CaveContain behavior ctor over the pinned OpenContain base (0x4649F8,
// thing plus data): volatile-first double-store at +0xFC around two
// and-zeros at +0x104/+0x108, the primary vtable slot and eight secondary
// slots at +0x0C/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34, then the second
// +0xFC store and a trailing one byte at +0x100 (the final vptrs are the
// class's own tables by their retail store immediates; the transient first
// +0xFC value, overwritten before any call, stays a TU-local dummy).
// The rowed pool key at 0x4663FF and the rowed
// instance factory 0x24B797 (sole caller, news 0x10C) prove the class. Row
// supersedes the ctor pin.

class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" const void *const __identifier("??_7Rva00588FFAIface10@@6B@")[];
extern "C" const void *const __identifier("??_7CaveContain@@6BObjectModule@@@")[];  // vftable 0x00C43CB8
extern "C" const void *const __identifier("??_7CaveContain@@6BBehaviorModuleInterface@@@")[];  // vftable 0x00C43BF8
extern "C" const void *const __identifier("??_7CaveContain@@6BUpdateModule@@@")[];  // vftable 0x00C43BE8
extern "C" const void *const __identifier("??_7CaveContain@@6BContainModuleInterface@@@")[];  // vftable 0x00C43A70
extern "C" const void *const __identifier("??_7CaveContain@@6BCollideModuleInterface@@@")[];  // vftable 0x00C46064
extern "C" const void *const __identifier("??_7CaveContain@@6BDieModuleInterface@@@")[];  // vftable 0x00C43A6C
extern "C" const void *const __identifier("??_7CaveContain@@6BDamageModuleInterface@@@")[];  // vftable 0x00C58790
extern "C" const void *const __identifier("??_7CaveContain@@6BExitInterface@@@")[];  // vftable 0x00C43380
extern "C" const void *const __identifier("??_7CaveContain@@6BCreateModuleInterface@@@")[];  // vftable 0x00C43A5C
extern "C" const void *const __identifier("??_7CaveContain@@6B@")[];  // vftable 0x00C43A54

// Opaque OpenContain base (0xFC); ctor resolves to its pin.
class OpenContain
{
public:
	OpenContain(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_pad[0xFC];
};

class CaveContain : public OpenContain
{
public:
	CaveContain(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_FC;
	unsigned char m_100;
	unsigned char m_pad101[3];
	int m_104;
	int m_108;
};

// ??0CaveContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x466630
CaveContain::CaveContain(Thing *thing, const ModuleData *moduleData)
	: OpenContain(thing, moduleData)
{
	*(const void * volatile *)&m_FC = __identifier("??_7Rva00588FFAIface10@@6B@");
	_ReadWriteBarrier();
	m_104 = 0;
	m_108 = 0;
	*(const void **)this = __identifier("??_7CaveContain@@6BObjectModule@@@");
	*(const void **)((char *)this + 0xC) = __identifier("??_7CaveContain@@6BBehaviorModuleInterface@@@");
	*(const void **)((char *)this + 0x10) = __identifier("??_7CaveContain@@6BUpdateModule@@@");
	*(const void **)((char *)this + 0x20) = __identifier("??_7CaveContain@@6BContainModuleInterface@@@");
	*(const void **)((char *)this + 0x24) = __identifier("??_7CaveContain@@6BCollideModuleInterface@@@");
	*(const void **)((char *)this + 0x28) = __identifier("??_7CaveContain@@6BDieModuleInterface@@@");
	*(const void **)((char *)this + 0x2C) = __identifier("??_7CaveContain@@6BDamageModuleInterface@@@");
	*(const void **)((char *)this + 0x30) = __identifier("??_7CaveContain@@6BExitInterface@@@");
	*(const void **)((char *)this + 0x34) = __identifier("??_7CaveContain@@6BCreateModuleInterface@@@");
	m_FC = __identifier("??_7CaveContain@@6B@");
	m_100 = 1;
}
