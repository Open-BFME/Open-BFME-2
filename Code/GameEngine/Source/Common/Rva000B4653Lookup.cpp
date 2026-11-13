// cl: /MD /EHsc /DNDEBUG
//
// ?rva000B4653@Rva000B4653@@QAEPAXH@Z @0x000B4653 29B: masked-index read.
// When the unsigned argument is below (m_0 & 7), resolves the pinned
// 0x000B2361 slot dispatcher on this and returns the slot's pointer;
// otherwise returns null. Honest address-derived names; boundary
// verified (frameless at 0xB4653, ret 4 at end).


#include "../../Include/Common/Rva000B2361.h"
class Rva000B4653
{
public:
	void *rva000B4653(int a);

private:
	int m_0;
};

inline __declspec(noinline) void *Rva000B4653::rva000B4653(int a)
{
	if ((unsigned int)a < (unsigned int)(m_0 & 7))
		return *(void**)(((Rva000B2361*)this)->rva000B2361(a));
	return 0;
}
static void *(Rva000B4653::*s_anchor_000B4653)(int) = &Rva000B4653::rva000B4653;
