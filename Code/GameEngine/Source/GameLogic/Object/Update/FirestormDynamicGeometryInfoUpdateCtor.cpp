// cl: /O1 /MD /DNDEBUG
// Identity: ModuleFactory registers this module as "AnimatedParticleSysBoneClientUpdate" (addModule pairs
// the name with its factories); formerly misnamed FirestormDynamicGeometryInfoUpdate.
// Trial: ??0AnimatedParticleSysBoneClientUpdate@@QAE@PAVThing@@PBVModuleData@@@Z.
// Base 0x00362EC7 (pinned opaque); and-zeroed slot then hand-placed vtable
// (novtable). Factory stub order names it.
class Thing;
class ModuleData;

extern "C" char FirestormDynamicGeometryInfoUpdate_vftable;

// Opaque intermediate; ctor resolves to the opaque pin at 0x00362EC7.
class Rva00362EC7
{
public:
	Rva00362EC7(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00362EC7();

protected:
	unsigned char m_pad0[8];
	int m_i0C;
	unsigned char m_pad1[0x20 - 0x10];
};

// ??1Rva00362EC7@@ present-unmatched
Rva00362EC7::~Rva00362EC7()
{
}

class __declspec(novtable) AnimatedParticleSysBoneClientUpdate : public Rva00362EC7
{
public:
	AnimatedParticleSysBoneClientUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AnimatedParticleSysBoneClientUpdate();
};

AnimatedParticleSysBoneClientUpdate::AnimatedParticleSysBoneClientUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva00362EC7(thing, moduleData)
{
	m_i0C = 0;
	*reinterpret_cast<char **>(this) = &FirestormDynamicGeometryInfoUpdate_vftable;
}

// ??1AnimatedParticleSysBoneClientUpdate@@ present-unmatched
AnimatedParticleSysBoneClientUpdate::~AnimatedParticleSysBoneClientUpdate()
{
}
