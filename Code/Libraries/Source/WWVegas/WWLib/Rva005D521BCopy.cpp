// cl: /DNDEBUG /MD
// ??$__uninitialized_copy@PBUBfmeStringRecord005D511F@@PAU1@@_STL@@YAPAUBfmeStringRecord005D511F@@PBU1@0PAU1@ABU__false_type@0@@Z retail 0x005D521B 38B.
// _STL::__uninitialized_copy<BfmeStringRecord005D511F> 38B. Dedicated TU so the
// rowed _Construct 0x005D51EE cannot inline into this loop (same pattern as Rva005D5241FillN).
// Element stride is 0x14 via the dummy body below; _Construct is declared only.
// Evidence: loop calls rowed Construct 0x005D51EE and advances both pointers by 0x14;
// same shape as rowed 38B sibling 0x00569079 (20-byte PBU variant); callers 0x005D54D2 0x005D551D.
struct BfmeStringRecord005D511F
{
	char _m[0x14];

public:
	BfmeStringRecord005D511F(const BfmeStringRecord005D511F &that);
};

namespace _STL
{

struct __false_type {};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(&*cur, *first);
	return cur;
}

}

template BfmeStringRecord005D511F *_STL::__uninitialized_copy(const BfmeStringRecord005D511F *, const BfmeStringRecord005D511F *, BfmeStringRecord005D511F *, const _STL::__false_type &);
