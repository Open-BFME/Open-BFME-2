// cl: /DNDEBUG /MD
//
// ??0PillageModule@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00484F0D, 46 bytes.
// Pillage behavior ctor over the pinned Rva00588FFA base (sole-caller
// opaque (Thing*,ModuleData*) base over rowed BehaviorModule 0x253330,
// vtable 0x00C700C4): and-zeroes the unknown member at +0x18, then
// installs vtable 0x00C4A51C at +0 and rewrites the folded slots at +0xC
// (0x00C70008, shared with the base) and +0x10 (0x00C4A514). All three
// immediates are link-time constants kept literal. Pool key 0x484F76;
// behavior instance factory 0x24C77B news 0x1C (sole caller). Row
// supersedes the ctor pin.

extern "C" const void *const vtbl_00C4A514[];  // ??_7Rva00484F5D@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C4A514=??_7Rva00484F5D@@6B@")
extern "C" const void *const vtbl_00C4A51C[];  // ??_7Rva00484F5D@@6BRva0049B47C@@@
#pragma comment(linker, "/alternatename:_vtbl_00C4A51C=??_7Rva00484F5D@@6BRva0049B47C@@@")
extern "C" const void *const vtbl_00C70008[];  // ??_7Rva00484F5D@@6BMiBase1@@@
#pragma comment(linker, "/alternatename:_vtbl_00C70008=??_7Rva00484F5D@@6BMiBase1@@@")

class Thing;
class ModuleData;

class Rva00588FFA
{
public:
	Rva00588FFA(Thing *thing, const ModuleData *data);

private:
	unsigned char m_pad[0x18];
};

class PillageModule : public Rva00588FFA
{
public:
	PillageModule(Thing *thing, const ModuleData *data);

private:
	int m_bfme18; // +0x18 unknown member, and-zeroed
};

// ??0PillageModule@@QAE@PAVThing@@PBVModuleData@@@Z @0x484F0D
PillageModule::PillageModule(Thing *thing, const ModuleData *data)
	: Rva00588FFA(thing, data)
{
	*(unsigned int *)this = ((unsigned int)vtbl_00C4A51C);
	*(unsigned int *)((char *)this + 0x0C) = ((unsigned int)vtbl_00C70008);
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)vtbl_00C4A514);
	m_bfme18 = 0;
}
