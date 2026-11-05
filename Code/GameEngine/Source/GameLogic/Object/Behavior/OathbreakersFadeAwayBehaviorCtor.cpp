// cl: /GX /DNDEBUG /MD
//
// ??0OathbreakersFadeAwayBehavior@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x004B8A8A, 59 bytes. Dedicated TU: the behavior ctor runs the
// rowed UpdateModule base ctor (thing plus data, this in ecx per the
// single-inheritance vptr-at-zero layout), then installs the behavior vtable,
// re-stores the inherited +0x0C/+0x10 secondary slots with literals, clears
// the fading flag and defaults the fade timer to 1.0f (shared literal pool).
// The TU-local base carries a declared-only virtual dtor: vptr at +0 keeps
// the base call this-direct (no lea) and the derived declared-only virtual
// dtor emits the vtable store in position, both with zero EH code (AODCrush
// frameless precedent). Class identity is the tight behavior cluster:
// rowed pool key 0x4B8A02 plus literal name getter 0x4B8A22 plus the
// FadeOutTime proc 0x4B8A79 ending exactly where this ctor begins, the 56B
// instance factory 0x25095E sole-calling it, and the BFME1
// OathbreakersFadeAwayBehavior class.

extern "C" const void *const __identifier("??_7AttributeModifierPoolUpdate@@6BBehaviorModuleOther@@@")[];  // folded vftable 0x00BEFF90 (80 classes), by its data-ledger name

extern "C" const void *const __identifier("??_7OathbreakersFadeAwayBehavior@@6BRva004B89C4_B2@@@")[];  // ??_7OathbreakersFadeAwayBehavior@@6BRva004B89C4_B2@@@

class Thing;
class ModuleData;

// Opaque UpdateModule base; ctor resolves to its row. Single inheritance
// with a declared-only virtual dtor puts the vptr (and the base) at +0, so
// the base call takes this directly. Slots mirror the retail stores.
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class OathbreakersFadeAwayBehavior : public UpdateModule
{
public:
	OathbreakersFadeAwayBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~OathbreakersFadeAwayBehavior();
	const char *name() const;
	virtual NameKeyType getModuleNameKey() const;
	void rva004B8B0F();

protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_20;
	float m_24;
};

// ??0OathbreakersFadeAwayBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
OathbreakersFadeAwayBehavior::OathbreakersFadeAwayBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_20 = false;
	m_24 = 1.0f;
}
