// cl: /O1 /GX /DNDEBUG /MD
//
// ??0RebuildHoleExposeDieUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00486768 (42 bytes). Dedicated TU: the behavior ctor runs the pinned
// Die-family intermediate base ctor (thing plus data, this in ecx per the
// single-inheritance vptr-at-zero layout), then installs the behavior
// vtable 0x00C4AE54 and re-stores the inherited +0x0C/+0x10 secondary slots
// with literals (Oathbreakers behavior precedent). The TU-local base
// carries a declared-only virtual dtor: vptr at +0 keeps the base call
// this-direct (no lea) and the derived declared-only virtual dtor emits
// the vtable store in position, both with zero EH code so the body stays
// frameless with callee-cleaned args. Class identity is the tight
// RebuildHole cluster: the rowed ModuleData proc 0x48675D ends exactly
// where this ctor begins, the 56B Update instance factory 0x24CAE0
// sole-calls it right before the rowed ModuleData factory, and the rowed
// ModuleData ctor plus factory plus pool key close the file-unit. True
// size 42 corrects the 39B park note which cut the ret.

class Thing;
class ModuleData;

// Opaque Die-family behavior intermediate base; ctor resolves to its pin.
// Single inheritance with a declared-only virtual dtor puts the vptr (and
// the base) at +0, so the base call takes this directly. Slots mirror the
// retail stores.
class Rva0045CEBDUpdate
{
public:
	Rva0045CEBDUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0045CEBDUpdate();

protected:
	void *m_owner;
	int m_pad08;
	const void *m_secondary0C;
	const void *m_secondary10;
};

class RebuildHoleExposeDieUpdate : public Rva0045CEBDUpdate
{
public:
	RebuildHoleExposeDieUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~RebuildHoleExposeDieUpdate();
};

// ??0RebuildHoleExposeDieUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x486768
RebuildHoleExposeDieUpdate::RebuildHoleExposeDieUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva0045CEBDUpdate(thing, moduleData)
{
	m_secondary0C = reinterpret_cast<const void *>(0x00C4A650);
	m_secondary10 = reinterpret_cast<const void *>(0x00C4AE50);
}
