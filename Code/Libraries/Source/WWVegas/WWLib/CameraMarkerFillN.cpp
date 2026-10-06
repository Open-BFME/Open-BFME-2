// cl: /DNDEBUG /MD
// ??$__uninitialized_fill_n@PAUCameraMarker@@IU1@@_STL@@YAPAUCameraMarker@@PAU1@IABU1@ABU__false_type@0@@Z @0x00424D8C 37B
// _STL::__uninitialized_fill_n<CameraMarker> retail 37 bytes stride 0x18 calling rowed _Construct<Rva0042476C> 0x00424BF4. Evidence: caller 0x0042537B in wrapper 0x0042536A; callee rowed; neighbours same dir.
class Rva0042476C
{
	char _m[0x18];

public:
	Rva0042476C(const Rva0042476C &that);
};

struct CameraMarker
{
	char _m[0x18];
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
		_Construct((Rva0042476C *)cur, (const Rva0042476C &)x);
	return cur;
}

}

template CameraMarker *_STL::__uninitialized_fill_n(CameraMarker *, unsigned int, const CameraMarker &, const _STL::__false_type &);
