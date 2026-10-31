// cl: /O1 /MD
// ?rva0033A68A@Rva0033A68A@@QAEPAVOverridable@@XZ @0x0033A68A 16B
// Final-override-or-self: calls rowed friend_getFinalOverride at 0x00288609
// and returns its result, or this when it is null. Callers at 0x0033A6AA and
// 0x0033AA2D use the result as the template (word at +0x5DA, float +0x4DC).
// Opaque Rva name: the Overridable subclass behind this is unproven.
#include "../../Include/Common/Overridable.h"

class Rva0033A68A
{
public:
	Overridable *rva0033A68A();
};

Overridable *Rva0033A68A::rva0033A68A()
{
	const Overridable *finalOverride = ((const Overridable *)this)->friend_getFinalOverride();
	return finalOverride ? (Overridable *)finalOverride : (Overridable *)this;
}
