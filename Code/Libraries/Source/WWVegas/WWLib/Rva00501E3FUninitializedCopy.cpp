// cl: /O1 /DNDEBUG /MD
// ??$__uninitialized_copy@PAURva00501E3FElement@@PAU1@@_STL@@YAPAURva00501E3FElement@@PAU1@00ABU__false_type@0@@Z @0x005008A0 38B STLport non-POD copy stride 0x14 via _Construct 0x00500873.
// Evidence: callee rowed _Construct StlportConstructFamily.cpp; callers 0x00500DA0 0x00501A7C unclaimed.
struct Rva00501E3FElement
{
	char _m[0x14];

	Rva00501E3FElement(const Rva00501E3FElement &that);
};

namespace _STL
{

struct __false_type {};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last,
	ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(cur, *first);
	return cur;
}

}

// ?_STL::__uninitialized_copy present-unmatched
template Rva00501E3FElement *_STL::__uninitialized_copy(Rva00501E3FElement *,
	Rva00501E3FElement *, Rva00501E3FElement *, const _STL::__false_type &);
