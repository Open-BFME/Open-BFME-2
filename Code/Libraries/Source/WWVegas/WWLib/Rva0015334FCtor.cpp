// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0015334F@@QAE@XZ, retail 0x0015334F, 25 bytes.
// Default ctor zeroing +0 then Vector_base<BfmeE16> at +4 via rowed 0x211E58 with stack allocator temp.
// Evidence: and [esi] 0 plus lea eax [esp+7] push eax lea ecx [esi+4] call 0x211E58 plus mov eax esi; same shape as Rva004BA1B2 22B plus zeroing and Rva00506A34 voidptr plus vector; callers 0x153F49 0x215B00 0x215BEB 0x5AA28C.
#include <vector>
struct BfmeE16 { float x; float y; float z; float w; };
class Rva0015334F
{
	int m_00;
	_STL::vector<BfmeE16> m_04;
public:
	Rva0015334F();
};
Rva0015334F::Rva0015334F() : m_00(0)
{
}
