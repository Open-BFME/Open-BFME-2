// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva00568F04@Rva00568F04@@QAEXPAX@Z @0x00568F04 42B: linear find-erase over vector at +0x58
// Same recipe as GateOpenBehaviorList::rva004E908C; rowed vector<void*>::erase at 0x001FF51F.
// Callers at 0x0056A096 0x0056916B unclaimed; neighbours 0x00568EE6 0x00568F2E give flags.
#include <vector>

class Rva00568F04
{
public:
	void rva00568F04(void *item);

private:
	char _pad[0x58];
	void **m_begin; // +0x58
	void **m_end; // +0x5C
};

void Rva00568F04::rva00568F04(void *item)
{
	void **cur = m_begin;
	void **finish = m_end;
	for (; cur != finish; ++cur)
	{
		if (*cur == item)
		{
			((::_STL::vector<void *, _STL::allocator<void *> > *)(void *)((char *)this + 0x58))->erase(cur);
			return;
		}
	}
}
