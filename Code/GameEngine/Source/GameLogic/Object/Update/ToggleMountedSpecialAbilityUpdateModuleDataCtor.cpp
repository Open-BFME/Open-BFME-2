// cl: /O1 /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
//
// ??0ToggleMountedSpecialAbilityUpdateModuleData@@QAE@XZ, retail 0x004AE0AC, 67 bytes.
// ModuleData ctor over the pinned Rva0044EB54 intermediate base (0x44EB54,
// 0xC8 bytes, opaque). The chained proc 0x24F66F (rowed, on the rowed base
// proc 0x44ED95 plus table 0x00BEF770) plus the rowed ModuleData factory
// 0x24F6C5 (news 0xE0, sole caller) prove the class; the table gives the
// member names and offsets (OpacityTarget@C8/TriggerInstantlyOnCreate@CC/
// CancelDisguiseWhenDismounting@CD/MountedTemplate@D0/
// SynchronizeTimerOnSpecialPower@D4). Row supersedes the ctor pin.
//
// Scheduling (all probe-proven, in order tried): the retail vtable store sits
// second (right after the two flag bytes, before the float/int stores), but a
// virtual derived sinks the compiler vtable fourth, so the vtable is an
// explicit pointer-cast store with no virtuals declared. A _ReadWriteBarrier
// after the float store pins the vtable above the int/vector setups (bare
// setups hoist above an explicit vtable; the barrier is too coarse before the
// float because it traps xorps below the vtable). A sourced-before float
// pointer anchors the movss above the vector call setups (pure lea setups
// otherwise hoist above it). The 16-byte vector element is a stand-in: its
// Vector_base call resolves through the ICF-folded rowed 0x211E58 body, and
// the qualified explicit init call emits the bare call with no guard (the
// allocator temp materializes at [esp+7] exactly as retail). Row supersedes
// the ctor pin; the ??_7 vtable pin stands for identity.

#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeE16 { float x, y, z, w; };

static int s_vtableAnchor;

class Rva0044EB54
{
public:
	Rva0044EB54();
	virtual ~Rva0044EB54();

private:
	unsigned char m_opaque[0xC8 - 4];
};

class ToggleMountedSpecialAbilityUpdateModuleData : public Rva0044EB54
{
public:
	ToggleMountedSpecialAbilityUpdateModuleData();

private:
	float m_opacityTarget;	// +0xC8 OpacityTarget
	bool m_triggerInstantlyOnCreate;	// +0xCC TriggerInstantlyOnCreate
	bool m_cancelDisguiseWhenDismounting;	// +0xCD CancelDisguiseWhenDismounting
	const void *m_mountedTemplate;	// +0xD0 MountedTemplate
	unsigned char m_synchronizeTimerPad[12];	// +0xD4 SynchronizeTimerOnSpecialPower (_STL::vector<BfmeE16> raw; explicit body init)
};

// ??0ToggleMountedSpecialAbilityUpdateModuleData@@QAE@XZ @0x004AE0AC
ToggleMountedSpecialAbilityUpdateModuleData::ToggleMountedSpecialAbilityUpdateModuleData()
	: m_triggerInstantlyOnCreate(false),
	  m_cancelDisguiseWhenDismounting(false)
{
	float *opacity = &m_opacityTarget;
	*(const void **)this = (const void *)&s_vtableAnchor;
	*opacity = 0.0f;
	_ReadWriteBarrier();
	m_mountedTemplate = 0;
	_STL::vector<BfmeE16> &synchronizeTimer = (_STL::vector<BfmeE16> &)m_synchronizeTimerPad;
	synchronizeTimer._STL::vector<BfmeE16>::vector();
}
