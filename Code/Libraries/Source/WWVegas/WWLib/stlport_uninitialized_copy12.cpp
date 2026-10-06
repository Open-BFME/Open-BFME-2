// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport __uninitialized_copy over vector<BfmePod88> elements: stride-12
// range copy through the rowed _Construct at 0x00500B11, sibling of the
// fill_n batch in stlport_uninitialized_fill_n12.cpp. Same recipe as
// stlport_construct_stl_types2.cpp (explicit instantiation; BfmePod88 is a
// size stand-in). _STLP_NO_EXCEPTIONS drops the TRY/UNWIND so the body is
// the plain frameless loop.
#include <memory>
#include <vector>

struct BfmePod88
{
	char m_body[88];
};

typedef _STL::vector<BfmePod88, _STL::allocator<BfmePod88> > Pod88Vec;

template Pod88Vec *_STL::__uninitialized_copy<const Pod88Vec *, Pod88Vec *>(const Pod88Vec *, const Pod88Vec *, Pod88Vec *, const _STL::__false_type &);
