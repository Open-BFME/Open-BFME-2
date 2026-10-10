// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00566AB7@Rva00566AB7@@QAEXABUBfmePod88@@@Z retail 0x00566AB7 8B
// Evidence: unlock lane; callee push_back Pod88 0x004E3BA1; unblocks 0x004E324D; prev vector Pod32 same flags; add ecx 0x20 plus jmp tail.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
struct BfmePod88 { int a[22]; };
class Rva00566AB7
{
public:
	void rva00566AB7(const BfmePod88 &v);
private:
	char m_pad00[0x20];
	_STL::vector<BfmePod88> m_vec20;
};
void Rva00566AB7::rva00566AB7(const BfmePod88 &v)
{
	m_vec20.push_back(v);
}
