// cl: /MD
//
// ??$__uninitialized_fill_n@PAVRva001ED03C@@IV1@@_STL@@YAPAVRva001ED03C@@PAV1@IABV1@ABU__false_type@0@@Z @0x001ED244 (37B).
// _STL::__uninitialized_fill_n<Rva001ED03C> retail 37 bytes. Dedicated TU
// so Rva001ED03C _Construct stays out-of-line. Evidence: chain via rowed
// _Construct 0x001ED1F1 stride 0x24 caller 0x001ED4E4 same shape as rowed
// Coord3D fill 0x002CA849 and Rva0052BEF0 fill 0x00565770.
class Rva001ED03C
{
	char m_body[0x24];

public:
	Rva001ED03C(const Rva001ED03C &that);
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

template Rva001ED03C *_STL::__uninitialized_fill_n(Rva001ED03C *, unsigned int, const Rva001ED03C &, const _STL::__false_type &);
