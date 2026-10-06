// cl: /DNDEBUG /MD
//
// ??$_Construct@VRva0054103E@@V1@@_STL@@YAXPAVRva0054103E@@ABV1@@Z @0x0054106D (18B).
// _STL::_Construct<Rva0054103E, Rva0054103E>, retail 18 bytes. Dedicated TU
// so Rva0054103ECopy.cpp cannot see this body. Null-checks the destination
// then thiscall-copy-constructs into it via the rowed copy ctor at 0x54103E.
// Evidence: called per element by uninit copies at 0x0054111B/0x005411FC and
// insert bodies at 0x0054181C/0x00541DBA/0x00541E09/0x00541E1B; 0x14 element
// size with Region2D member proven by the copy ctor.

typedef unsigned int size_t;

inline void *operator new(size_t, void *place)
{
	return place;
}

class Rva0054103E
{
public:
	Rva0054103E(const Rva0054103E &that);
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

template void _STL::_Construct(Rva0054103E *, const Rva0054103E &);
