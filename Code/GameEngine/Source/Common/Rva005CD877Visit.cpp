// cl: /EHsc /MD
//
// ?Rva005CD877Visit@@YAXPAX@Z retail 0x005CD877 46B visit list via stack Visitor.
// Evidence: callee 0x005CCD36 rowed visit caller 0x005CD8A5 pushes one ptr cdecl void sibling of 0x005CD813 vtable 0x00875010.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
#include "../../Include/Common/Visitor005CCCD0.h"
#include "../../Include/Common/Rva005CCD36.h"
class Rva005CD877Visitor : public Visitor005CCCD0
{
public:
	Rva005CD877Visitor();
	virtual ~Rva005CD877Visitor() {}
	virtual bool visit(TargetRef00217D4C *p) { return true; }
};
// ??0Rva005CD877Visitor@@QAE@XZ @0x005CD80A 9B: the visitor's default
// constructor, storing its vtable 0x00C75010; retail keeps this standalone
// copy (no direct caller) and inlines it into Rva005CD877Visit.
Rva005CD877Visitor::Rva005CD877Visitor()
{
}
void __cdecl Rva005CD877Visit(void *p)
{
	Rva005CD877Visitor v;
	((Rva005CCD36 *)p)->rva005CCD36(&v);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?visit@Visitor005CCCD0@@UAE_NPAUTargetRef00217D4C@@@Z=?Rva005CD762Get@@YGEPAX@Z")
