// cl: /EHsc /MD
//
// ?Rva005CD813Visit@@YAXPAX@Z retail 0x005CD813 46B visit list via stack Visitor.
// Evidence: callee 0x005CCD36 rowed Rva005CCD36::rva005CCD36(Visitor*); temp vtable data 0x00875008; caller 0x005CD8A5 pushes one ptr cdecl void.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
struct Visitor005CCCD0
{
	virtual bool visit(TargetRef00217D4C *p);
	virtual ~Visitor005CCCD0() {}
};
#include "../../Include/Common/Rva005CCD36.h"
class Rva005CD813Visitor : public Visitor005CCCD0
{
public:
	Rva005CD813Visitor();
	virtual ~Rva005CD813Visitor() {}
	virtual bool visit(TargetRef00217D4C *p) { return true; }
};
// ??0Rva005CD813Visitor@@QAE@XZ @0x005CD7B4 9B: the visitor's default
// constructor, storing its vtable 0x00C75008; retail keeps this standalone
// copy (no direct caller) and inlines it into Rva005CD813Visit.
Rva005CD813Visitor::Rva005CD813Visitor()
{
}
void __cdecl Rva005CD813Visit(void *p)
{
	Rva005CD813Visitor v;
	((Rva005CCD36 *)p)->rva005CCD36(&v);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?visit@Visitor005CCCD0@@UAE_NPAUTargetRef00217D4C@@@Z=?Rva005CD78BGet@@YGEPAX@Z")
