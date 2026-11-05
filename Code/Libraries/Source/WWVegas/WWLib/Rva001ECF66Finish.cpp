// cl: /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
//
// ?rva001ECF66/Rva001ECF66, retail 0x001ECF66, 96 bytes: STLport vector
// range copy-ctor over the 36-byte BfmeRecord001ECAF9 element. The
// __uninitialized_copy callee keeps a visible __declspec(noinline) body so
// MSVC 7.1 proves the __false_type tag is not retained and packs it onto the
// dead incoming-argument slot [ebp+0xB]; a declaration-only callee forces a
// fresh frame slot and one extra push (97 B). get_allocator and _Vector_base(n)
// are ICF aliases pinned at their rowed bodies.

#include <vector>

struct GeometryShape;
struct BfmeRecord001ECAF9
{
	char m_pad[36];
};

namespace _STL
{
template <> class vector<GeometryShape, allocator<GeometryShape> >
{
public:
	allocator<GeometryShape> get_allocator() const;
};
template <> class _Vector_base<GeometryShape, allocator<GeometryShape> >
{
public:
	_Vector_base(unsigned int count, const allocator<GeometryShape> &alloc);
	~_Vector_base();
	GeometryShape *m_begin;
	GeometryShape *m_finish;
};
template <>
void _Construct(BfmeRecord001ECAF9 *p, const BfmeRecord001ECAF9 &v);
template <>
inline __declspec(noinline) BfmeRecord001ECAF9 *__uninitialized_copy(
	BfmeRecord001ECAF9 *first, BfmeRecord001ECAF9 *last,
	BfmeRecord001ECAF9 *dest, const __false_type &tag)
{
	BfmeRecord001ECAF9 *cur = dest;
	for (; first != last; ++first, ++cur)
		_Construct(&*cur, *first);
	return cur;
}
}

class Rva001ECF66 : public _STL::_Vector_base<GeometryShape, _STL::allocator<GeometryShape> >
{
public:
	Rva001ECF66(const Rva001ECF66 &src);
};

Rva001ECF66::Rva001ECF66(const Rva001ECF66 &src)
	: _STL::_Vector_base<GeometryShape, _STL::allocator<GeometryShape> >(
		(unsigned int)(((BfmeRecord001ECAF9 *)src.m_finish) - ((BfmeRecord001ECAF9 *)src.m_begin)),
		((const _STL::vector<GeometryShape, _STL::allocator<GeometryShape> > &)src).get_allocator())
{
	m_finish = (GeometryShape *)_STL::__uninitialized_copy(
		(BfmeRecord001ECAF9 *)src.m_begin,
		(BfmeRecord001ECAF9 *)src.m_finish,
		(BfmeRecord001ECAF9 *)m_begin,
		_STL::__false_type());
}
