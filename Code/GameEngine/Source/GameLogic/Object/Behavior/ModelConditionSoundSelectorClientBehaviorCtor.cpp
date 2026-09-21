// cl: /O1 /DNDEBUG /MD
//
// ??0ModelConditionSoundSelectorClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00254B82, 42 bytes. ModelConditionSoundSelectorClientBehavior
// behavior ctor over the rowed Rva00252B68 intermediate base (0x252B68,
// thing plus data): re-stores the primary vtable slot (the behavior vtable
// 0x007F3220, whose slot0 is the rowed ??_G 0x254C2F and whose slot2 is the
// rowed name getter 0x254BF1) and the +0x0C secondary slot (secondary vtable
// 0x007F3210). The first +0x0C store carries the base-secondary value
// 0x007E2B78 and is overwritten by the derived secondary vtable in body
// order; the class declares no virtuals of its own so the stores land from
// explicit members in source order. The base ctor spelling resolves to its
// row. Recipe: PlayerHealSpecialPowerCtor.cpp opaque-base pattern with the
// SoundSelector file-unit (pool key rowed at 0x00254BAC starting exactly
// where this ctor ends plus name getter rowed at 0x00254BF1; the instance
// factory at 0x00255C26 is the sole raw caller).

class Thing;
class ModuleData;

// Opaque intermediate base; ctor resolves to its row. The explicit m_vtable
// member stands in for the inherited vptr so body order is source order.
class Rva00252B68
{
public:
	Rva00252B68(Thing *thing, const ModuleData *moduleData);

protected:
	const void *m_vtable;
	unsigned char m_pad04[0x0C - 4];
	const void *m_p0C;
};

class ModelConditionSoundSelectorClientBehavior : public Rva00252B68
{
public:
	ModelConditionSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0ModelConditionSoundSelectorClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x254B82
ModelConditionSoundSelectorClientBehavior::ModelConditionSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData)
	: Rva00252B68(thing, moduleData)
{
	// Pointer-then-direct: the sourced-before address take commits the
	// first +0x0C store to source position (FreeLife precedent); a second
	// direct store to the same member survives while direct-direct would
	// be eaten by the dead-store eliminator.
	const void **p0C = &m_p0C;
	*p0C = reinterpret_cast<const void *>(0x00BE2B78);
	m_vtable = reinterpret_cast<const void *>(0x00BF3220);
	m_p0C = reinterpret_cast<const void *>(0x00BF3210);
}
