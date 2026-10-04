// cl: /O1 /DNDEBUG /MD /EHsc
//
// Vector deleting destructors (??_E), batch V07: the three 74-byte bodies of
// classes whose destructor is a header inline that only restores the vptr.
// For an array delete (flag bit 1) they run the eh vector destructor
// iterator (0x00629110) with the out-of-line copy of that destructor and the
// element size 4, then free through operator delete[] (0x0002FD80); for a
// single object the destructor is inlined (one vptr store) before operator
// delete (0x0002FD60).
//
//   ??_E        dtor        size  vtable#slot
//   0x000011EC  0x000011BD  0x4   0x00BBB52C#0  FXParticleSystem::ModuleTemplate
//   0x00001750  0x0049B47C  0x4   0x00BBB554#0  Snapshot
//   0x00005422  0x000053E7  0x4   0x00BBB910#0  Xfer
//
// Identity: each vtable is the one its matched constructors and destructor
// install (ModuleTemplate's in FXParticleSystem.cpp, ??_7Snapshot@@6B@
// pinned at 0x00BBB554, Xfer's constructor 0x000053DE and destructor
// 0x000053E7 in Xfer.cpp), and the array path hands that class's destructor
// to the iterator. Retail inlines all three destructors here, so they are
// header inlines; Xfer.cpp's out-of-line definition is the unit's own copy. The anchor (no retail counterpart) only makes this TU
// emit the vector deleting destructors.

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
void operator delete[](void *p);

namespace FXParticleSystem
{

// upstream layout: FXParticleSystem.cpp's ModuleTemplate (vtable only).
class ModuleTemplate
{
public:
	virtual ~ModuleTemplate() {}
};

}

// class-gate: allow Snapshot the canonical header's Snapshot is abstract, and the anchor must construct an array of it for the unit to emit the vector deleting destructor; this view keeps only the vtable and the header-inline destructor
// upstream layout: reference/shims/moduledata/Common/Snapshot.h (vtable only).
class Snapshot
{
public:
	virtual ~Snapshot() {}
};

// upstream layout: Xfer.cpp's Xfer (vtable only; abstract there).
class Xfer
{
public:
	virtual ~Xfer() {}
};

// ?<bfmeVectorDeleteAnchorV07> absent-from-retail
void bfmeVectorDeleteAnchorV07()
{
	new FXParticleSystem::ModuleTemplate[2];
	new Snapshot[2];
	new Xfer[2];
}
