// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport

// CameraMarker range copy for the FlammableUpdate file cluster.
// Explicit vector instantiation pulls the STLport __copy<CameraMarker*>
// core, which retail calls at 0x0048C897 (47 bytes) from the assign wrapper
// at 0x00288A5C. /O1 is load-bearing: without it the loop enregisters
// pointers (61 bytes); with it the frame keeps the EBP shape and the
// stack-slot updates exactly as retail. The element is a size-faithful
// 8-byte view (next link plus name word); only its address and the
// declared-only copy assignment feed codegen here, and that assignment
// resolves through the rowed ??4CameraMarker at 0x28876F. Unclaimed
// sibling emissions ride along (explicit-instantiation TUs are exempt
// from the unmatched check, stlport_vector_pair precedent).

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

struct CameraMarker
{
	~CameraMarker();
	CameraMarker &operator=(const CameraMarker &src);

	CameraMarker *m_next;
	void *m_name;
};

template class _STL::vector<CameraMarker, _STL::allocator<CameraMarker> >;
