// cl: /O1 /DNDEBUG /MD
//
// ??0UpgradeSoundSelectorClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00252CB5, 40 bytes. Behavior-side ctor completing the
// UpgradeSoundSelectorClientBehavior file-unit (poolkey rowed at 0x252CDF,
// name getter rowed at 0x252D24, behavior instance factory rowed at
// 0x254BF7 news 0x34 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the rowed Rva00252B68 base 0x252B68
// (opaque intermediate, do-not-name precedent: the base class identity is
// unproven, so the TU reuses the row's own spelling purely for call
// resolution) with three explicit body stores in retail order (+0xC, +0,
// +0xC) via byte-wise pointer casts (no virtuals declared anywhere so no
// vtable is emitted here; all three immediates are DIR32-masked in
// comparison). The redundant first +0xC store survives only as volatile
// (volatile-first-store law: the plain triple folds to two stores, volatile
// emits identical mov bytes). Zero new pins (base resolves via the rowed
// Rva00252B68 spelling).

class Thing;
class ModuleData;

class Rva00252B68
{
public:
	Rva00252B68(Thing *thing, const ModuleData *moduleData);
};

class UpgradeSoundSelectorClientBehavior : public Rva00252B68
{
public:
	UpgradeSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);
};

// ??0UpgradeSoundSelectorClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00252CB5
UpgradeSoundSelectorClientBehavior::UpgradeSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData) :
	Rva00252B68(thing, moduleData)
{
	*(unsigned int volatile *)((char *)this + 0xC) = 0x00BE2B78;
	*(unsigned int *)this = 0x00BEFEB0;
	*(unsigned int *)((char *)this + 0xC) = 0x00BEFEA4;
}
