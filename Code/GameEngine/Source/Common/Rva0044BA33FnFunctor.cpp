// cl: /O1 /MD
// A functor over a plain function pointer, vtable VA 0x00C3ED7C (slot 0 the
// shared scalar deleting destructor 0x005FAA31, slot 1 the call):
//  - ??0Rva0044BA33@@QAE@ABQ6AXXZ@Z, retail 0x0044BA33 (24B, RET 4): zero
//    +4, install the vtable, copy the function pointer into +8; the
//    TargetRef-holding constructors 0x00517345/0x0044BDA2 have this shape
//    with an AddRef.
//  - ?invoke@Rva0044BA33@@UAEXXZ, retail 0x0044BA4B (3B): tail-jump through
//    the stored pointer.
// Owner names are address-derived.
typedef void (*Rva0044BA33Fn)();

#include "../../Include/Common/Rva0007DF07.h"

struct Rva0044BA33 : public Rva0007DF07
{
	// Empty destructor: retail's vtable 0x0083ED7C slot 0 is the ICF-shared
	// deleting dtor 0x005FAA31, whose destructor 0x004E84A4 only stores the
	// vtable.
	virtual ~Rva0044BA33() {}
	virtual void invoke() { m_fn(); }
	Rva0044BA33Fn m_fn;
	Rva0044BA33(const Rva0044BA33Fn &fn);
};

Rva0044BA33::Rva0044BA33(const Rva0044BA33Fn &fn)
{
	m_fn = fn;
}
