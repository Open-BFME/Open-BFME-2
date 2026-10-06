// cl: /MD
// stlport
//
// ?rva0041A241@BfmeNarrowRecord0041A5D2@@QAEPAXI@Z @0x0041A241, 28B:
// deleting-dtor-shaped helper for the two-string record: destroys it via the
// rowed dtor 0x0041A200, then frees with rowed ??3 when flags bit0 is set.
// Retail has no EH frame, so this TU uses plain /O1 /MD (the /EHs dtor TU
// would add state stores around the throwing dtor call).
#include <memory>
#include <string>
#include "BfmeNarrowRecord0041A5D2.h"
void *BfmeNarrowRecord0041A5D2::rva0041A241(unsigned int flags)
{
	this->~BfmeNarrowRecord0041A5D2();
	if (flags & 1)
		operator delete(this);
	return this;
}
