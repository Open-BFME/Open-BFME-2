// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0040B1F3Fill@@YAPAVRva0040AF66@@PAV1@IABV1@@Z @ 0x0040B1F3 (37B). Fill range of Rva0040AF66 via Construct helper.
// Evidence: retail loops calling the verified STLport _Construct 0x0040B17B stride 0x68 count in edi jbe; caller 0x0040B956; same 37B shape as rowed 0x0040B1A8.
#include <vector>

class Rva0040AF66
{
public:
	Rva0040AF66(const Rva0040AF66 &other);
private:
	char m_pad[0x68];
};

namespace _STL {
template <> void _Construct<Rva0040AF66, Rva0040AF66>(Rva0040AF66 *, const Rva0040AF66 &);
}

Rva0040AF66 *__cdecl Rva0040B1F3Fill(Rva0040AF66 *first, unsigned int count, const Rva0040AF66 &val)
{
	Rva0040AF66 *cur = first;
	for (unsigned int n = count; n > 0; --n) {
		_STL::_Construct(cur, val);
		++cur;
	}
	return cur;
}
