// cl: /O1 /DNDEBUG /MD
//
// ??$__uninitialized_copy@PAURva000AB3E2Element@@PAU1@@_STL@@YAPAURva000AB3E2Element@@PAU1@00ABU__false_type@0@@Z @0x000A9E1C (38B).
// _STL::__uninitialized_copy<Rva000AB3E2Element> retail 38 bytes. Dedicated TU
// so Rva000AB3E2Element _Construct stays out-of-line. Evidence: loop calls pinned
// _Construct 0x000A9DF8 stride 0x18 callers 0x000AAF4A/0x000AAF95 same shape as rowed
// 38B copies 0x000ADE67 and 0x004C3121; neighbours 0x000A9DF3/0x000A9E42.
struct Rva000AB3E2Element
{
	int a[6];

public:
	Rva000AB3E2Element(const Rva000AB3E2Element &that);
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

// ?__uninitialized_copy@_STL@@YAPAURva000AB3E2Element@@PAU2@00ABU__false_type@0@@Z present-unmatched
template Rva000AB3E2Element *_STL::__uninitialized_copy(Rva000AB3E2Element *,
	Rva000AB3E2Element *, Rva000AB3E2Element *, const _STL::__false_type &);
