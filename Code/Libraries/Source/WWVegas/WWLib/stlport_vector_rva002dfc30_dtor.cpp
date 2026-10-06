// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@VRva002DFC30@@V?$allocator@VRva002DFC30@@@_STL@@@_STL@@QAE@XZ, retail 0x0033D4AB, 63 bytes.
// Vector<Rva002DFC30> dtor EH via rowed _Destroy 0x00331FF1 and free 0x00030830.
// Evidence: EH_prolog and [ebp-4] 0 call Destroy or [ebp-4] -1 free; same 63B shape as rowed vector<Rva00153729> dtor 0x00153BED; caller at 0x0033DE68.
#include <vector>
class Rva002DFC30
{
public:
	~Rva002DFC30();
	unsigned char m_data[0xC];
};
template _STL::vector<Rva002DFC30>::~vector();
