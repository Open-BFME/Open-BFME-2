// cl: /DNDEBUG /MD
// ??$__uninitialized_fill_n@PAURva00511E48@@IU1@@_STL@@YAPAURva00511E48@@PAU1@IABU1@ABU__false_type@0@@Z @0x00511E48 37B:
// _STL::__uninitialized_fill_n<Rva00511E48> stride 8 via dup _Construct
// 0x00511CB9 (true _Construct<pair<const AsciiString,char>> at 0x0021A9B7)
// called through dup cast per TreeKey00242F5EFillN precedent so the gate
// resolves to the dup address. Retail loops n times calling _Construct,
// advances by 8, returns end. Caller 0x00511F58/27 (3-arg wrapper).
// Dedicated TU so the call stays external.
struct Rva00511E48
{
	char _m[8];
public:
	Rva00511E48(const Rva00511E48 &that);
};
void __cdecl dup_00511CB9(void);
typedef void (__cdecl *Rva00511E48ConstructFn)(Rva00511E48 *, const Rva00511E48 &);
namespace _STL
{
struct __false_type {};
template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &)
{
	ForwardIter cur = first;
	for (; n > 0; --n, ++cur)
		((Rva00511E48ConstructFn)&dup_00511CB9)(cur, x);
	return cur;
}
// ??$__uninitialized_fill_n@PAURva00511E48@@IU1@@_STL@@YAPAURva00511E48@@PAU1@IABU1@@Z @0x00511F58 27B:
// Dispatches to the false_type overload above. Evidence: calls rowed
// 0x00511E48; caller 0x00512000/105 unblocks.
template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x)
{
	return __uninitialized_fill_n(first, n, x, __false_type());
}
}
template Rva00511E48 *_STL::__uninitialized_fill_n(Rva00511E48 *, unsigned int, const Rva00511E48 &);
template Rva00511E48 *_STL::__uninitialized_fill_n(Rva00511E48 *, unsigned int, const Rva00511E48 &, const _STL::__false_type &);
