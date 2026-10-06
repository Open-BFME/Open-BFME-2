// cl: /DNDEBUG /MD /GX
//
// ??0FreeLifeBody@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004C18CA,
// 86 bytes. Body-side ctor (rowed instance factory 0x251676 news 0x114
// with this pinned 2-arg ctor as its sole raw caller at 0x2516A0).
//
// Shape: frameless RespawnBody-base call (rowed 0x4C12EB), then the module
// data pointer the base left at +0x04 is homed first, the +0x10C slot is
// or-assigned -1 ahead of the three derived vtable installs, and the three
// module-data fields (+0x6C/+0x70/+0x74) land at +0x104/+0x110/+0x100 after
// a false byte at +0x108. The base is declared without virtuals or a dtor
// so the derived ctor stays frameless. Row supersedes the ctor pin.

extern "C" const void *const vtbl_00C5AD78[];  // folded, 18 classes; via ??_7ActiveBody@@6BActiveBodyB1@@@
#pragma comment(linker, "/alternatename:_vtbl_00C5AD78=??_7ActiveBody@@6BActiveBodyB1@@@")

extern "C" const void *const vtbl_00C5BD88[];  // ??_7Rva004C1866@@6BRva004C1866_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C5BD88=??_7Rva004C1866@@6BRva004C1866_B2@@@")
extern "C" const void *const vtbl_00C5BE38[];  // ??_7Rva004C1866@@6BRva004C131B@@@
#pragma comment(linker, "/alternatename:_vtbl_00C5BE38=??_7Rva004C1866@@6BRva004C131B@@@")

class Thing;
class ModuleData;

struct FreeLifeBodyModuleData
{
	unsigned char m_pad00[0x6C];
	int m_6C;
	int m_70;
	bool m_74;
};

class RespawnBody
{
public:
	RespawnBody(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	unsigned char m_pad08[4];
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned char m_pad14[0x100 - 0x14];
};

class FreeLifeBody : public RespawnBody
{
public:
	FreeLifeBody(Thing *thing, const ModuleData *moduleData);

private:
	bool m_100;
	int m_104;
	bool m_108;
	int m_10C;
	int m_110;
};

// ??0FreeLifeBody@@QAE@PAVThing@@PBVModuleData@@@Z @0x004C18CA
FreeLifeBody::FreeLifeBody(Thing *thing, const ModuleData *moduleData)
	: RespawnBody(thing, moduleData)
{
	const FreeLifeBodyModuleData *data = (const FreeLifeBodyModuleData *)m_moduleData;
	m_10C |= -1;
	m_vtable = (const void *)((unsigned int)vtbl_00C5BE38);
	m_secondary0C = (const void *)((unsigned int)vtbl_00C5AD78);
	m_secondary10 = (const void *)((unsigned int)vtbl_00C5BD88);
	m_108 = false;
	m_110 = data->m_70;
	m_100 = data->m_74;
	m_104 = data->m_6C;
}
