// cl: /O1 /DNDEBUG /MD
//
// ??$__uninitialized_copy@PAURva000AB419Element@@PAU1@@_STL@@YAPAURva000AB419Element@@PAU1@00ABU__false_type@0@@Z @0x000A9E67 (38B).
// _STL::__uninitialized_copy<Rva000AB419Element> retail 38 bytes. Dedicated TU
// so Rva000AB419Element _Construct stays out-of-line. Evidence: loop calls pinned
// _Construct 0x000A9E0A stride 0x10 callers 0x000AB004/0x000AB04F same shape as rowed
// 38B copy 0x000A9E1C and sibling fill_n 0x000A9E8D; neighbours 0x000A9E42/0x000A9E8D.
struct Rva000AB419Element
{
	int a[4];

public:
	Rva000AB419Element(const Rva000AB419Element &that);
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

// ?__uninitialized_copy@_STL@@YAPAURva000AB419Element@@PAU2@00ABU__false_type@0@@Z present-unmatched
template Rva000AB419Element *_STL::__uninitialized_copy(Rva000AB419Element *,
	Rva000AB419Element *, Rva000AB419Element *, const _STL::__false_type &);
