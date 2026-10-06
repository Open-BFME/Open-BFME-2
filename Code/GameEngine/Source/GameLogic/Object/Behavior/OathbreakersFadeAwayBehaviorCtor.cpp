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

extern "C" const void *const vtbl_00BEFF90[];  // folded, 80 classes; via ??_7AIGateUpdate@@6BBehaviorModuleOther@@@
#pragma comment(linker, "/alternatename:_vtbl_00BEFF90=??_7AIGateUpdate@@6BBehaviorModuleOther@@@")

extern "C" const void *const vtbl_00C59280[];  // ??_7Rva004B89C4@@6BRva004B89C4_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C59280=??_7Rva004B89C4@@6BRva004B89C4_B2@@@")

class Thing;
class ModuleData;

// Opaque UpdateModule base; ctor resolves to its row. Single inheritance
// with a declared-only virtual dtor puts the vptr (and the base) at +0, so
// the base call takes this directly. Slots mirror the retail stores.
class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	void *m_owner;
	int m_pad08;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned char m_pad14[0x20 - 0x14];
};

class OathbreakersFadeAwayBehavior : public UpdateModule
{
public:
	OathbreakersFadeAwayBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~OathbreakersFadeAwayBehavior();

private:
	bool m_fading;
	float m_fadeTimer;
};

// ??0OathbreakersFadeAwayBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
OathbreakersFadeAwayBehavior::OathbreakersFadeAwayBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_secondary0C = reinterpret_cast<const void *>(((unsigned int)vtbl_00BEFF90));
	m_secondary10 = reinterpret_cast<const void *>(((unsigned int)vtbl_00C59280));
	m_fading = false;
	m_fadeTimer = 1.0f;
}
