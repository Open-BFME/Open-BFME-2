// cl: /O1 /DNDEBUG /MD
//
// ??0SymbioticStructuresBody@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x004C0AF1, 83 bytes. Frameless body ctor over the pinned
// ActiveBody base (0x4BF6A1): re-stores the primary vtable slot and the
// +0x0C/+0x10 secondary slots (address-of TU-local dummies, DIR32-masked),
// constructs the +0x108 member via the pinned 0x3B31AD construct call,
// zeroes +0x100/+0x104, then CRT memset over the member. The rowed instance
// factory 0x251520 is the sole caller. Row supersedes the ctor pin.

#include <string.h>

class Thing;
class ModuleData;

static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

class ActiveBody
{
public:
	ActiveBody(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	char m_pad04[0x0C - 0x04];
	const void *m_p0C;
	const void *m_p10;
	char m_pad14[0x100 - 0x14];
};

class Rva003B31ADMember
{
public:
	Rva003B31ADMember *construct();
};

class SymbioticStructuresBody : public ActiveBody
{
public:
	SymbioticStructuresBody(Thing *thing, const ModuleData *moduleData);

private:
	int m_100;
	int m_104;
	Rva003B31ADMember m_108;
};

// ??0SymbioticStructuresBody@@QAE@PAVThing@@PBVModuleData@@@Z @0x4C0AF1
SymbioticStructuresBody::SymbioticStructuresBody(Thing *thing, const ModuleData *moduleData)
	: ActiveBody(thing, moduleData)
{
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_108.construct();
	m_104 = 0;
	m_100 = 0;
	memset(&m_108, 0, 4);
}
