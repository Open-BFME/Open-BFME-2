// cl: /DNDEBUG /MD
//
// ??0RiderChangeContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0047E268,
// 120 bytes. Behavior ctor over the pinned SiegeEngineContain base 0x47C21E
// with four zeros at +0x138/+0x13C/+0x140/+0x144 and ten vtable stores at
// +0/+0xC/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34/+0xFC (address-of
// TU-local dummies, DIR32-masked). The rowed name getter at 0x47E325
// proves the class; the rowed instance factory 0x24BD28 (news 0x148) is
// the sole raw caller. Row supersedes the ctor pin.

class Thing;
class ModuleData;

static int s_vtable;
extern "C" const void *const __identifier("??_7AODHordeContain@@6BIface0C@@@")[];
static int s_secondary10;
static int s_secondary20;
extern "C" const void *const __identifier("??_7HordeSiegeEngineContain@@6BIface24@@@")[];
extern "C" const void *const __identifier("??_7AODHordeContain@@6BIface28@@@")[];
extern "C" const void *const __identifier("??_7AODHordeContain@@6BIface2C@@@")[];
static int s_secondary30;
static int s_secondary34;
extern "C" const void *const __identifier("??_7AODHordeContain@@6BIfaceFC@@@")[];

// Opaque SiegeEngineContain base (0x138); ctor resolves to its pin.
class Xfer;
class SiegeEngineContain
{
public:
	SiegeEngineContain(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
	char m_unrecovered04[ 0x138 - 0x04 ]; // +0x04
};

class RiderChangeContain : public SiegeEngineContain
{
public:
	RiderChangeContain(Thing *thing, const ModuleData *moduleData);

private:
	int m_138;
	int m_13C;
	int m_140;
	unsigned char m_144;
};

// ??0RiderChangeContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x0047E268
RiderChangeContain::RiderChangeContain(Thing *thing, const ModuleData *moduleData) :
	SiegeEngineContain(thing, moduleData)
{
	m_138 = 0;
	m_13C = 0;
	m_144 = 0;
	m_140 = 0;
	*(const void **)this = &s_vtable;
	*(const void **)((char *)this + 0xC) = __identifier("??_7AODHordeContain@@6BIface0C@@@");
	*(const void **)((char *)this + 0x10) = &s_secondary10;
	*(const void **)((char *)this + 0x20) = &s_secondary20;
	*(const void **)((char *)this + 0x24) = __identifier("??_7HordeSiegeEngineContain@@6BIface24@@@");
	*(const void **)((char *)this + 0x28) = __identifier("??_7AODHordeContain@@6BIface28@@@");
	*(const void **)((char *)this + 0x2C) = __identifier("??_7AODHordeContain@@6BIface2C@@@");
	*(const void **)((char *)this + 0x30) = &s_secondary30;
	*(const void **)((char *)this + 0x34) = &s_secondary34;
	*(const void **)((char *)this + 0xFC) = __identifier("??_7AODHordeContain@@6BIfaceFC@@@");
}
