// cl: /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAVFXList@@IV1@@_STL@@YAPAVFXList@@PAV1@IABV1@ABU__false_type@0@@Z @0x005655DC (37B).
// _STL::__uninitialized_fill_n<FXList> retail 37 bytes. Dedicated TU
// so FXList _Construct stays out-of-line. Evidence: loop calls rowed
// _Construct 0x0052C2F3 stride 0x08 caller 0x00565B36 same shape as rowed
// 0x0056561E.
class FXList
{
	char _m[8];

public:
	FXList(const FXList &that);
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

template FXList *_STL::__uninitialized_fill_n(FXList *, unsigned int, const FXList &, const _STL::__false_type &);
