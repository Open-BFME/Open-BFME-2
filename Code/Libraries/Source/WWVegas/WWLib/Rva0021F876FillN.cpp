// cl: /O1 /DNDEBUG /MD
// ??$__uninitialized_fill_n@PAVRva0021F876@@IV1@@_STL@@YAPAVRva0021F876@@PAV1@IABV1@ABU__false_type@0@@Z @0x0021FA6D 37B
// _STL::__uninitialized_fill_n<Rva0021F876> retail 37 bytes. Dedicated TU so
// no local _Construct definition can inline into this loop. Element stride is
// 0x20 via the dummy body below; _Construct is declared only and resolves
// through the rowed 0x0021FA1A. Called by 0x00220170 in 0x00220105; unblocks
// 0x00220105. (Rva00564C58FillN.cpp precedent.)
class Rva0021F876
{
	char _m[0x20];

public:
	Rva0021F876(const Rva0021F876 &that);
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

template Rva0021F876 *_STL::__uninitialized_fill_n(Rva0021F876 *, unsigned int, const Rva0021F876 &, const _STL::__false_type &);
