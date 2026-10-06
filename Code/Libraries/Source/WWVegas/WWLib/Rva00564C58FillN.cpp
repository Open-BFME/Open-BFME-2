// cl: /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAVRva003A6F70@@IV1@@_STL@@YAPAVRva003A6F70@@PAV1@IABV1@ABU__false_type@0@@Z @0x00564C58 (37B).
// _STL::__uninitialized_fill_n<Rva003A6F70>, retail 37 bytes. Dedicated TU
// so no local _Construct definition can inline into this loop. Element
// stride is 0x20 via the dummy body below; _Construct is declared only
// and resolves through the rowed 0x0052BD04. Unblocks 0x00565DA2.

class Rva003A6F70
{
	char _m[0x20];

public:
	Rva003A6F70(const Rva003A6F70 &that);
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

template Rva003A6F70 *_STL::__uninitialized_fill_n(Rva003A6F70 *, unsigned int, const Rva003A6F70 &, const _STL::__false_type &);
