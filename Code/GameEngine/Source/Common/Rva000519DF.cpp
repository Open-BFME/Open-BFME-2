// cl: /MD
//
// ??0Rva000519DF@@QAE@PAPAXABVBfmePoolRef10@@@Z @0x000519DF 29B
// Pool-ref pair constructor: ecx receiver, two stack args (ret 8), stores
// *arg1 at [this] and copy-constructs [this+4] from arg2 (copy ctor rowed at
// 0x00051950); MSVC returns the receiver in eax. The ctor ABI (member-init
// order plus the eax return) is the identity; the class name stays
// address-derived.
#include "../../Include/Common/BfmePoolRef10.h"

class Rva000519DF
{
public:
	Rva000519DF(void **source, const BfmePoolRef10 &ref);

private:
	void *m_ptr0;
	BfmePoolRef10 m_ref4;
};

Rva000519DF::Rva000519DF(void **source, const BfmePoolRef10 &ref)
	: m_ptr0(*source), m_ref4(ref)
{
}
