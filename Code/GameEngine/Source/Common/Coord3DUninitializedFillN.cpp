// cl: /MD
//
// ??$__uninitialized_fill_n@PAUCoord3D@@IU1@@_STL@@YAPAUCoord3D@@PAU1@IABU1@ABU__false_type@0@@Z @0x002CA849 37B: STLport __uninitialized_fill_n for 12-byte Coord3D.
// Retail null-guards the count then constructs each element out-of-line through the pinned Coord3D _Construct at 0x002CA82C with stride 0x0C.
// Callers 0x000CA1D3 (27B wrapper with false_type tag at ebp-1) and 0x002CDF8A (deque overflow fill path with tag at ebp+0x1B) pass (first n value tag) with add esp 0x10; returns the end pointer.
struct Coord3D
{
	float x, y, z;
	Coord3D(const Coord3D &that);
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
template Coord3D *_STL::__uninitialized_fill_n(Coord3D *, unsigned int, const Coord3D &, const _STL::__false_type &);
