// cl: /DNDEBUG /MD
//
// _STL::_Construct<Rva004F6352, Rva004F6352>, retail 0x004F6A76,
// 18 bytes. Dedicated TU so Rva004F6352Assign.cpp cannot see this body.
// Null-checks the destination then thiscall-copy-constructs into it via
// rowed copy ctor 0x004F62DE. Callers 0x004F6B1E 0x004F6B44 0x004F8F61
// 0x004F93E7 are uninitialized-copy walks with stride 0xC.

typedef unsigned int size_t;

inline void *operator new(size_t, void *place)
{
	return place;
}

struct Rva004F6352
{
	Rva004F6352(const Rva004F6352 &that);
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

template void _STL::_Construct(Rva004F6352 *, const Rva004F6352 &);
