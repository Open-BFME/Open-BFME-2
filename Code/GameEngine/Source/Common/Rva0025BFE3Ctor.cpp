// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0025BFE3@@QAE@XZ, retail 0x0025BFC7, 28 bytes.
// Default ctor for the Rva0025BFE3 base (vtable 0x007F5D30): constructs the
// vector<BfmeE16> at +4 via the rowed vector_base ctor at 0x00211E58 with a
// stack allocator temp (lea eax,[esp+7]). Same vtable and +4 layout as the
// dtor at 0x0025BFE3 in FreeMemberDeleters.cpp (which frees +4 via free for
// trivial 16-byte elements). Unblocks 4 callers that become ready.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
class Rva0025BFE3
{
public:
	Rva0025BFE3();
	virtual ~Rva0025BFE3();
private:
	_STL::vector<BfmeE16> m_vec04;
};
Rva0025BFE3::Rva0025BFE3() : m_vec04()
{
}
