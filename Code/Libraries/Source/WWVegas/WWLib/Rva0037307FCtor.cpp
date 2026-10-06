// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0037307F@Rva0037307F@@QAE@XZ @0x0037307F 23B:
// Default ctor: vector<BfmeE16> at +0 via rowed Vector_base 0x00211E58,
// bool at +0xC cleared. Same recipe as Rva00586D8E at 0x00586D8E (vector
// at +8 via same base plus flag clear). Caller at 0x003738A2; landing
// unblocks 0x00373871. BfmeE16 is the 16B size stand-in.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva0037307F
{
public:
	Rva0037307F();
private:
	_STL::vector<BfmeE16> m_vec; // +0
	bool m_flag; // +0x0C
};

Rva0037307F::Rva0037307F()
	: m_vec(_STL::allocator<BfmeE16>())
{
	m_flag = false;
}
