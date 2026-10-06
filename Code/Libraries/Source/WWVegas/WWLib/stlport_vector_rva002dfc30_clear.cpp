// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_clear@?$vector@VRva002DFC30@@V?$allocator@VRva002DFC30@@@_STL@@@_STL@@IAEXXZ, retail 0x000C05EC, 30 bytes.
// Vector<Rva002DFC30> clear via rowed _Destroy 0x331FF1 and free 0x30830.
// Evidence: push [esi+4] push [esi] call 0x331FF1 mov esi [esi] test free; same 30B shape as rowed _M_clear 0xC05CE and 0xC060A; 6 callers unblocked.
#include <vector>
class Rva002DFC30
{
public:
	~Rva002DFC30();
	unsigned char m_data[0xC];
};
template void _STL::vector<Rva002DFC30>::_M_clear();
