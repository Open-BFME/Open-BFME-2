// cl: /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAVRva002E0A0A@@IV1@@_STL@@YAPAVRva002E0A0A@@PAV1@IABV1@ABU__false_type@0@@Z @0x0052C229 (37B).
// _STL::__uninitialized_fill_n<Rva002E0A0A>, retail 37 bytes. Dedicated TU
// so no local _Construct definition can inline into this loop. Element
// stride is 0x28 via the dummy body below; _Construct is declared only
// and resolves through the rowed 0x0052C1D6. Caller 0x0052D184.
// Sibling Rva00564C58FillN same recipe same flags.
class Rva002E0A0A
{
	char _m[0x28];

public:
	Rva002E0A0A(const Rva002E0A0A &that);
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

template Rva002E0A0A *_STL::__uninitialized_fill_n(Rva002E0A0A *, unsigned int, const Rva002E0A0A &, const _STL::__false_type &);
