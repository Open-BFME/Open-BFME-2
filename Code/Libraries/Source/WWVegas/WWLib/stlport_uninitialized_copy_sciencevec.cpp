// cl: /DNDEBUG /MD
//
// ??$__uninitialized_copy@PAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@PAV12@@_STL@@YAPAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@0@PAV10@00ABU__false_type@0@@Z @0x00339962 38B
// Unlock lane: _STL::__uninitialized_copy for vector<ScienceType> (12-byte
// vectors) range-loop calling rowed _Construct 0x001FF819. Stride 0xc.
// Callers 0x001FFA4B 0x001FFE20 0x00339FE8 0x0033A033 0x0033A0C4 0x0033A110.
// Sibling of rowed __uninitialized_fill_n 0x00339988.
enum ScienceType { SCIENCE_INVALID = -1 };
namespace _STL {
template <class T> class allocator;
template <class T, class Alloc> class vector {
	unsigned int m_body[3];
public:
	vector(const vector &other);
};
struct __false_type {};
template <class T1, class T2> void _Construct(T1 *p, const T2 &value);
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &) {
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(cur, *first);
	return cur;
}
}
typedef _STL::vector<ScienceType, _STL::allocator<ScienceType> > SciVec;
template SciVec *_STL::__uninitialized_copy(SciVec *, SciVec *, SciVec *, const _STL::__false_type &);
