// cl: /MD
//
// ??$uninitialized_fill_n@PAUCoord3D@@IU1@@_STL@@YAPAUCoord3D@@PAU1@IABU1@@Z @0x000CA1D3 27B: STLport uninitialized_fill_n for 12-byte Coord3D.
// Forwards (first n value) to the rowed 4-arg __uninitialized_fill_n at 0x002CA849 with a false_type tag temporary at ebp-1. Chain lane: caller of the just-landed worker.
struct Coord3D
{
	float x, y, z;
	Coord3D(const Coord3D &that);
};
namespace _STL
{
struct __false_type {};
template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &);
template <class ForwardIter, class Size, class T>
ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T &x)
{
	__false_type tag;
	return __uninitialized_fill_n(first, n, x, tag);
}
}
template Coord3D *_STL::uninitialized_fill_n(Coord3D *, unsigned int, const Coord3D &);
