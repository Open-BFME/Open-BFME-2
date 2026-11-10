// cl: /DNDEBUG /MD
//
// ??0AnimalAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0047ECA8
// (121 bytes). Behavior ctor over the rowed AIUpdateInterface base (0x26E9BD,
// thing plus data): installs the six behavior vtable slots (+0x00/+0x0C/+0x10/
// +0x20/+0x24 via explicit members naming the class's own tables by their
// retail store immediates; +0x3E4 double-stored C1C780-then-C47B84, the
// transient first value a TU-local dummy) plus zeros at +0x3E8/+0x3F8/+0x3F9
// plus float zeros at +0x3EC/+0x3F0/+0x3F4. The class declares no virtuals of
// its own: the stores land from explicit members in body order (AssaultTransport
// precedent with volatile-first-store for the redundant +0x3E4 pair). Row
// supersedes the sole-caller pin; the instance factory at 0x24BE95 is the
// single raw caller; vtable 0x847B98 slot4 holds the rowed AnimalAIUpdate
// poolkey 0x47EC1A.

class Thing;
class ModuleData;

extern "C" const void *const __identifier("??_7AnimalAIUpdate@@6BRva0026E836_Root@@@")[];  // vftable 0x00C47B98
extern "C" const void *const __identifier("??_7AnimalAIUpdate@@6BRva0026E836_M1@@@")[];  // vftable 0x00BFA3C0
extern "C" const void *const __identifier("??_7AnimalAIUpdate@@6BRva0026E836_B2@@@")[];  // vftable 0x00C47B8C
extern "C" const void *const __identifier("??_7AnimalAIUpdate@@6BRva0026E836_M3@@@")[];  // vftable 0x00C47B88
extern "C" const void *const __identifier("??_7AnimalAIUpdate@@6BRva0026E836_M4@@@")[];  // vftable 0x00C52F88
extern "C" const void *const __identifier("??_7Rva003F498ACallback@@6B@")[];
extern "C" const void *const __identifier("??_7AnimalAIUpdate@@6B@")[];  // vftable 0x00C47B84

class AIUpdateInterface
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;			// +0x00
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;			// +0x0C
	const void *m_p10;			// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_p20;			// +0x20
	const void *m_p24;			// +0x24
	unsigned char m_pad28[0x3E4 - 0x28];
	const void *m_p3E4;			// +0x3E4
	int m_3E8;				// +0x3E8
	float m_3EC;				// +0x3EC
	float m_3F0;				// +0x3F0
	float m_3F4;				// +0x3F4
	unsigned char m_3F8;			// +0x3F8
	unsigned char m_3F9;			// +0x3F9
};

class AnimalAIUpdate : public AIUpdateInterface
{
public:
	AnimalAIUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0AnimalAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x47ECA8
AnimalAIUpdate::AnimalAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData)
{
	*(const void * volatile *)&m_p3E4 = __identifier("??_7Rva003F498ACallback@@6B@");
	m_p3E4 = __identifier("??_7AnimalAIUpdate@@6B@");
	m_3E8 = 0;
	m_3F8 = 0;
	m_3F9 = 0;
	m_vtable = __identifier("??_7AnimalAIUpdate@@6BRva0026E836_Root@@@");
	m_p0C = __identifier("??_7AnimalAIUpdate@@6BRva0026E836_M1@@@");
	m_p10 = __identifier("??_7AnimalAIUpdate@@6BRva0026E836_B2@@@");
	m_p20 = __identifier("??_7AnimalAIUpdate@@6BRva0026E836_M3@@@");
	m_p24 = __identifier("??_7AnimalAIUpdate@@6BRva0026E836_M4@@@");
	m_3F4 = 0.0f;
	m_3F0 = 0.0f;
	m_3EC = 0.0f;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x0026E9BD -> ??0AIUpdateInterface@@QAE@PAVThing@@PBVModuleData@@@Z (defined by Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AIUpdateInterfaceCtor.cpp)
#pragma comment(linker, "/alternatename:??0Rva0026E9BDBase@@QAE@PAVThing@@PBVModuleData@@@Z=??0AIUpdateInterface@@QAE@PAVThing@@PBVModuleData@@@Z")
