// cl: /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAVRva0052BE33@@IV1@@_STL@@YAPAVRva0052BE33@@PAV1@IABV1@ABU__false_type@0@@Z @0x00565685 (37B).
// _STL::__uninitialized_fill_n<Rva0052BE33> retail 37 bytes. Dedicated TU
// so Rva0052BE33 _Construct stays out-of-line. Evidence: loop calls rowed
// _Construct 0x0052C392 stride 0x14 caller 0x00565D59 same shape as rowed
// 0x0056561E and FXList fill 0x005655DC.
class Rva0052BE33
{
	char _m[20];

public:
	Rva0052BE33(const Rva0052BE33 &that);
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

template Rva0052BE33 *_STL::__uninitialized_fill_n(Rva0052BE33 *, unsigned int, const Rva0052BE33 &, const _STL::__false_type &);
