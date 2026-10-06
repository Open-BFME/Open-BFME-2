// cl: /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAVRva0052BEF0@@IV1@@_STL@@YAPAVRva0052BEF0@@PAV1@IABV1@ABU__false_type@0@@Z @0x00565770 (37B).
// _STL::__uninitialized_fill_n<Rva0052BEF0> retail 37 bytes. Dedicated TU
// so Rva0052BEF0 _Construct stays out-of-line. Evidence: loop calls rowed
// _Construct 0x0052C431 stride 0x0C caller 0x005660E6 same shape as rowed
// 0x0056561E and FXList fill 0x005655DC.
class Rva0052BEF0
{
	char _m[12];

public:
	Rva0052BEF0(const Rva0052BEF0 &that);
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

template Rva0052BEF0 *_STL::__uninitialized_fill_n(Rva0052BEF0 *, unsigned int, const Rva0052BEF0 &, const _STL::__false_type &);
