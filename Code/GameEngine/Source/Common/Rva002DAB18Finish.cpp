// ??0Rva002DAB18@@QAE@XZ
// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /Ireference/shims/moduledata
//
// ??0Rva002DAB18@@QAE@XZ @0x002DAB18 (70B):
// Multiple-inheritance ctor: primary base Snapshot at +0 installs vtable
// 0x00BBB554 in line, secondary base SubsystemInterface at +4 is constructed
// by the pinned base ctor 0x001B4E63 (twin ??0SubsystemInterface@@QAE@XZ),
// then the derived vtables 0x00C03910 at +0 and 0x00C039A0 at +4 and the
// +0x10 member. Caller 0x00091A83.
// Finishing levers vs the banked attempt: the +4 subobject is a real secondary
// base (its ctor is the pinned 0x001B4E63), so the compiler emits the derived
// vptr stores itself; Snapshot's base cleanup arms the EH prologue, which
// puts the ecx restore right after the base call; and the +0x10 member is a
// struct with an inline zeroing ctor so its store is ordered after the vptr
// stores instead of being hoisted above them.
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "ascii_string.h"
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
class Rva002DAB18 : public Snapshot, public SubsystemInterface
{
public:
	Rva002DAB18();
	virtual ~Rva002DAB18();
private:
	AsciiString m_10;
};
Rva002DAB18::Rva002DAB18()
{
}

// ??1Rva002DAB18@@UAE@XZ, retail 0x002DAB6C, 79 bytes.
// Dual-vptr dtor: derived vtables 0x00C03910 at +0 and 0x00C039A0 at +4,
// AsciiString member at +0x10 via shared header (releaseBuffer rowed),
// secondary base via GameEngineDeletingBase dtor, primary Snapshot inline
// vptr restore to its native base table. Evidence: gap packet, callers, prev/next flags.
Rva002DAB18::~Rva002DAB18()
{
}
