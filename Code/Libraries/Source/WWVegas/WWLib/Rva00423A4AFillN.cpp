// cl: /DNDEBUG /MD
//
// ??$__uninitialized_fill_n@PAURva00423A4A@@IU1@@_STL@@YAPAURva00423A4A@@PAU1@IABU1@ABU__false_type@0@@Z @0x0042449C (37B).
// _STL::__uninitialized_fill_n<Rva00423A4A>, retail 37 bytes. Dedicated TU so
// _Construct cannot inline into this loop. Element stride is 0xC via dummy
// body; _Construct is declared only and resolves through the rowed 0x00423E83.
struct Rva00423A4A
{
	char _m[0xC];
public:
	Rva00423A4A(const Rva00423A4A &that);
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
// ??$__uninitialized_fill_n@PAURva00423A4A@@IU1@@_STL@@YAPAURva00423A4A@@PAU1@IABU1@@Z @0x004246EE (27B).
// Dispatches to the false_type overload above. Evidence: calls rowed
// 0x0042449C; caller 0x004249DA in 0x0042499E; unblocks 0x0042499E.
template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x)
{
	return __uninitialized_fill_n(first, n, x, __false_type());
}
}
template Rva00423A4A *_STL::__uninitialized_fill_n(Rva00423A4A *, unsigned int, const Rva00423A4A &);
template Rva00423A4A *_STL::__uninitialized_fill_n(Rva00423A4A *, unsigned int, const Rva00423A4A &, const _STL::__false_type &);
