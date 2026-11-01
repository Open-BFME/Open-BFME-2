// STLport4.5.3 reference; opaque address-derived record, target stride and container offsets.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740 (this
// unit's /O2 region default builds it for speed).
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>



// Element: retail's push_back reaches 0x0073E290, rowed as
// deque<Gen_t_008fb570_p8pod>::_M_push_back_aux_v
// (Rva008FB570DequePushBackAux.cpp), so this deque holds the same 8-byte POD.
struct Gen_t_008fb570_p8pod
{
	int value[2];
};

namespace _STL {
// Retail's 0x0060C9D9 is the rowed two-word copy _Construct<pair<const int, int> >;
// an inline forwarder reaches it with the same pushes, as in the provider unit.
template <> void _Construct<pair<const int, int>, pair<const int, int> >(
	pair<const int, int> *, const pair<const int, int> &);
template <> __declspec(dllimport) __forceinline void _Construct<Gen_t_008fb570_p8pod, Gen_t_008fb570_p8pod>(
	Gen_t_008fb570_p8pod *destination, const Gen_t_008fb570_p8pod &source)
{
	_Construct((pair<const int, int> *)destination, *(const pair<const int, int> *)&source);
}
// Defined by Rva008FB570DequePushBackAux.cpp (0x0073E290).
template <> void deque<Gen_t_008fb570_p8pod>::_M_push_back_aux_v(const Gen_t_008fb570_p8pod &);
}
template void _STL::deque<Gen_t_008fb570_p8pod>::push_back(const Gen_t_008fb570_p8pod &);
