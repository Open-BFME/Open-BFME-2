// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0020DAE0@@YAXPAX@Z 0x0020DAE0 41B remove ptr from global vector via erase
// Evidence: retail loads begin end from g_00DFE1AC g_00DFE1B0 then calls rowed vector voidptr erase 0x001FF51F; callers 0x00285766 0x00286FC6 0x004ABFCF use cdecl pop cleanup
#include <vector>

extern _STL::vector<void *> g_00DFE1AC;

void __cdecl Rva0020DAE0(void *p)
{
	void **begin = *(void **volatile *)&g_00DFE1AC;
	void **end = *(void **volatile *)((char *)&g_00DFE1AC + 4);
	for (void **it = begin; it != end; ++it) {
		if (*it == p) {
			g_00DFE1AC.erase(it);
			return;
		}
	}
}
