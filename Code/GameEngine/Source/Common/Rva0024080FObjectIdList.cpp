// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfmelist /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>

// ?Rva0024080FAdd@@YAXPAXPAV?$list@HV?$allocator@H@_STL@@@_STL@@@Z, RVA 0x0024080F, 34 bytes.
// Address-based callback; retail tests two pointer arguments, reads an integer at first-argument offset 0x74, and appends it to the second argument's list<int>. Stored as a callback at 0x002487F0.
void __cdecl Rva0024080FAdd(void *object, _STL::list<int> *ids)
{
	if (object == 0 || ids == 0)
		return;
	int id = *(int *)((char *)object + 0x74);
	ids->push_back(id);
}
