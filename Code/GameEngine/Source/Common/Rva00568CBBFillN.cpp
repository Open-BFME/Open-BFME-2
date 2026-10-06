// cl: /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAVRva00568A20@@IV1@@_STL@@YAPAVRva00568A20@@PAV1@IABV1@ABU__false_type@0@@Z @0x00568CBB (37B).
// _STL::__uninitialized_fill_n<Rva00568A20> retail 37 bytes. Dedicated TU
// so Rva00568A20 _Construct stays out-of-line. Evidence: loop calls rowed
// _Construct 0x00568C83 stride 0xC caller 0x0056A252 same 37B shape as rowed
// fill_n 0x00565685 and siblings at 0x000BBB83.
class Rva00568A20
{
	char _m[12];

public:
	Rva00568A20(const Rva00568A20 &that);
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

template Rva00568A20 *_STL::__uninitialized_fill_n(Rva00568A20 *, unsigned int, const Rva00568A20 &, const _STL::__false_type &);
