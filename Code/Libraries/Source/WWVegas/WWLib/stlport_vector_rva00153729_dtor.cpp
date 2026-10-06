// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@URva00153729@@V?$allocator@URva00153729@@@_STL@@@_STL@@QAE@XZ, retail 0x00153BED, 63 bytes.
// Vector<Rva00153729> dtor EH via rowed _Destroy 0x153BB6 and free 0x30830.
// Evidence: EH_prolog and [ebp-4] 0 call 0x153BB6 or [ebp-4] -1 free; same 63B shape as rowed vector<Rva005F8F96> dtor 0x1536EA; caller at 0x153D41.
#include <vector>
struct Rva00153729
{
	~Rva00153729();
};
template _STL::vector<Rva00153729>::~vector();
