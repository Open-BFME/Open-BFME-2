// cl: /EHsc- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_fill_n@PAV?$vector@URva002BC339Value@@V?$allocator@URva002BC339Value@@@_STL@@@_STL@@IV12@@_STL@@ @0x002BB785 37B.
// Target bytes at 0x002BB785 count down over 12-byte vector elements, calls the
// element _Construct at 0x002BAE2A, and returns first+n. Its caller is the
// rowed public fill_n wrapper at 0x002BBC5F (call at +0x11). The typed
// instantiation is independently anchored by the vector<vector<Rva002BC339Value>>
// count constructor at 0x002BC339; only the inner vector's 12-byte STLport
// storage stride is claimed here. The no-exception specialization follows the
// vendored STLport _uninitialized.h worker with its exception cleanup disabled.
#include <vector>

struct Rva002BC339Value
{
	int m_words[3];
};

typedef _STL::vector<Rva002BC339Value, _STL::allocator<Rva002BC339Value> > Rva002BC339InnerVector;

namespace _STL
{
template<> void _Construct<Rva002BC339InnerVector, Rva002BC339InnerVector>(
	Rva002BC339InnerVector *, const Rva002BC339InnerVector &);

template<>
Rva002BC339InnerVector *__uninitialized_fill_n<
	Rva002BC339InnerVector *, unsigned int, Rva002BC339InnerVector>(
	Rva002BC339InnerVector *first, unsigned int n,
	const Rva002BC339InnerVector &value, const __false_type &)
{
	Rva002BC339InnerVector *cur = first;
	for (; n > 0; --n, ++cur)
		_Construct(&*cur, value);
	return cur;
}
}
