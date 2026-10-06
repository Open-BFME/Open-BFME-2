// cl: /DNDEBUG /MD
// ??$__uninitialized_fill_n@PAUBfmeStringRecord005D511F@@IU1@@_STL@@YAPAUBfmeStringRecord005D511F@@PAU1@IABU1@ABU__false_type@0@@Z retail 0x005D5241 37B.
// _STL::__uninitialized_fill_n<BfmeStringRecord005D511F>, retail 37 bytes. Dedicated TU
// so BfmeStringRecord005D511FConstruct cannot inline _Construct into this loop.
// Element stride is 0x14 via the dummy body below; _Construct is declared
// only and resolves through the rowed 0x005D51EE.
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

template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &)
{
	ForwardIter cur = first;
	for (; n > 0; --n, ++cur)
		_Construct(cur, x);
	return cur;
}

}

template BfmeStringRecord005D511F *_STL::__uninitialized_fill_n(BfmeStringRecord005D511F *, unsigned int, const BfmeStringRecord005D511F &, const _STL::__false_type &);
