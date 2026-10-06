// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva004E908C@GateOpenBehaviorList@@QAEXPAX@Z, retail 0x004E908C, 37 bytes.
// Gate list remove-one scan over the +0/+4 pointer range (same layout as
// rowed appendOnce 0x004E9353 in GateOpenAndCloseBehaviorCtor.cpp). Linear
// find for the item then rowed vector<void*>::erase 0x001FF51F. Callers at
// 0x004987D7 0x004993AC 0x004995AA unclaimed. Recipe is vector find-erase.

// ?erase@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QAEPAPAXPAPAX@Z
#include <vector>

class GateOpenBehaviorList
{
public:
	void rva004E908C(void *item);

private:
	void **m_begin; // +0
	void **m_end; // +4
};

void GateOpenBehaviorList::rva004E908C(void *item)
{
	void **finish = m_end;
	for (void **cur = m_begin; cur != finish; ++cur)
	{
		if (*cur == item)
		{
			((_STL::vector<void *, _STL::allocator<void *> > *)this)->erase(cur);
			return;
		}
	}
}
