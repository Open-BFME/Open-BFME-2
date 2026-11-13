// cl: /EHsc /MD
//
// ?hasListeners@@YA_NPAX@Z retail 0x005CD841 54B visit list via stack Visitor with bool result.
// Evidence: callee 0x005CCD36 rowed visit caller 0x005CD8C2 tests al sibling of 0x005CD813 vtable 0x0087500C bool at +4.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
// Slot 0 is the base visit (bound by Rva005CD813Visit.cpp to retail's row), not
// pure, as the other Visitor005CCCD0 views declare it: one table copy.
#include "../../Include/Common/Visitor005CCCD0.h"
#include "../../Include/Common/Rva005CCD36.h"
class HasListenersVisitor : public Visitor005CCCD0
{
public:
	HasListenersVisitor();
	virtual ~HasListenersVisitor() {}
	virtual bool visit(TargetRef00217D4C *target) { m_found = true; return true; }
	bool m_found;
};
// ??0HasListenersVisitor@@QAE@XZ @0x005CD801 9B: the visitor's default
// constructor, storing its vtable 0x00C7500C; retail keeps this standalone
// copy (no direct caller) and inlines it into Rva005CD841Find.
HasListenersVisitor::HasListenersVisitor()
{
}
bool __cdecl hasListeners(void *listeners)
{
	HasListenersVisitor visitor;
	visitor.m_found = false;
	((Rva005CCD36 *)listeners)->rva005CCD36(&visitor);
	return visitor.m_found;
}
