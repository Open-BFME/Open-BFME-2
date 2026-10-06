// cl: /DNDEBUG /MD
//
// ??$_Construct@VRva00469BEA@@V1@@_STL@@YAXPAVRva00469BEA@@ABV1@@Z @0x0046A9FF (18B).
// _STL::_Construct<Rva00469BEA, Rva00469BEA>, retail 18 bytes. Dedicated TU
// so Rva00469BEACtor.cpp cannot see this body. Null-checks the destination
// then thiscall-copy-constructs into it via the rowed copy ctor at 0x00469D33.
// Evidence: called per element by 0x0046AC30 (which allocates 0x24 and
// constructs at +0x10); 0x10 element size with Rva00469155 member proven by
// the copy ctor. Caller 0x0046AC44.

typedef unsigned int size_t;

inline void *operator new(size_t, void *place)
{
	return place;
}

class Rva00469BEA
{
public:
	Rva00469BEA(const Rva00469BEA &that);
};

namespace _STL
{

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value)
{
	if (p)
		new (p) T1(value);
}

}

template void _STL::_Construct(Rva00469BEA *, const Rva00469BEA &);
