// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@VRva004E32F2@@V?$allocator@VRva004E32F2@@@_STL@@@_STL@@QAEXABVRva004E32F2@@@Z, retail 0x00566BB4, 55 bytes.
// STLport 4.5.3 vector<Rva004E32F2>::push_back.
// Evidence: chain lane calls just-landed _M_insert_overflow 0x00566ACA plus rowed _Construct 0x0052D4A2; same 55B shape as rowed 0x005662CC.
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

class Rva004E32F2
{
public:
	Rva004E32F2(const Rva004E32F2 &o);
	virtual ~Rva004E32F2();
private:
	char m_pad[0x14];
};

namespace _STL
{
template <> void _Construct<Rva004E32F2, Rva004E32F2>(Rva004E32F2 *, const Rva004E32F2 &);
}

template void _STL::vector<Rva004E32F2>::push_back(const Rva004E32F2 &);
