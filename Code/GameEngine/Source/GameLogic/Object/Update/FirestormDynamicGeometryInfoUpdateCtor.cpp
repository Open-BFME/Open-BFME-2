// cl: /O1 /MD /DNDEBUG
// Identity: ModuleFactory registers this module as "AnimatedParticleSysBoneClientUpdate" (addModule pairs
// the name with its factories); formerly misnamed FirestormDynamicGeometryInfoUpdate.
// Trial: ??0AnimatedParticleSysBoneClientUpdate@@QAE@PAVThing@@PBVModuleData@@@Z.
// Base 0x00362EC7 (pinned opaque); and-zeroed slot then hand-placed vtable
// (novtable). Factory stub order names it.
class Thing;
class ModuleData;

// FirestormDynamicGeometryInfoUpdate_vftable: retail table 0x00C5EA50 (15 ClientUpdate slots). Own the complete
// initialized table instead of a one-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a rowed body at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva00362EE3@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@DrawModule@@MAEXXZ")();
void __identifier("?Rva004C9008Get@@YAHXZ")();
void __identifier("?xfer@BehaviorModule@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@AnimatedParticleSysBoneClientUpdate@@UBE?AW4NameKeyType@@XZ")();
void __identifier("?vslot51@DrawModule@@UAEPAXXZ")();
void __identifier("?vslot12@BodyModule@@UAE_NXZ")();
void __identifier("?clientUpdate@AnimatedParticleSysBoneClientUpdate@@UAEXXZ")();
extern const void *const FirestormDynamicGeometryInfoUpdate_vftable[15] = {
	(const void *)&__identifier("??_GRva00362EE3@@UAEPAXI@Z"), //  0 0x003630E6
	(const void *)&__identifier("?loadPostProcess@DrawModule@@MAEXXZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva004C9008Get@@YAHXZ"), //  2 0x004C9008
	(const void *)&__identifier("?xfer@BehaviorModule@@MAEXPAVXfer@@@Z"), //  3 0x004C9C7D
	(const void *)&__identifier("?getModuleNameKey@AnimatedParticleSysBoneClientUpdate@@UBE?AW4NameKeyType@@XZ"), //  4 0x004C900E
	(const void *)&__identifier("?loadPostProcess@DrawModule@@MAEXXZ"), //  5 0x000B3FD0
	(const void *)&__identifier("?loadPostProcess@DrawModule@@MAEXXZ"), //  6 0x000B3FD0
	(const void *)&__identifier("?loadPostProcess@DrawModule@@MAEXXZ"), //  7 0x000B3FD0
	(const void *)&__identifier("?loadPostProcess@DrawModule@@MAEXXZ"), //  8 0x000B3FD0
	(const void *)&__identifier("?vslot51@DrawModule@@UAEPAXXZ"), //  9 0x000D43D0
	(const void *)&__identifier("?vslot51@DrawModule@@UAEPAXXZ"), // 10 0x000D43D0
	(const void *)&__identifier("?vslot12@BodyModule@@UAE_NXZ"), // 11 0x0050B5C6
	(const void *)&__identifier("?clientUpdate@AnimatedParticleSysBoneClientUpdate@@UAEXXZ"), // 12 0x004C9053
	(const void *)&__identifier("?vslot51@DrawModule@@UAEPAXXZ"), // 13 0x000D43D0
	(const void *)&__identifier("?vslot51@DrawModule@@UAEPAXXZ")  // 14 0x000D43D0
};
}

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
	*reinterpret_cast<const void *const **>(this) = FirestormDynamicGeometryInfoUpdate_vftable;
}

// ??1AnimatedParticleSysBoneClientUpdate@@ present-unmatched
AnimatedParticleSysBoneClientUpdate::~AnimatedParticleSysBoneClientUpdate()
{
}
