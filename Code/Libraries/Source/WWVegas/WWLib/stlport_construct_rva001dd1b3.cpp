// cl: /DNDEBUG /MD
// ??$_Construct@URva001DD1B3@@U1@@_STL@@YAXPAURva001DD1B3@@ABU1@@Z @0x001DD3AA 18B
// Null-guarded placement copy over the 36-byte element whose real copy ctor
// is the rowed Rva001DD1B3 copy at 0x001DD1B3.
// Same 18B frameless shape as rowed _Construct 0x001DD2DC.
typedef unsigned int size_t;

inline void *operator new(size_t, void *place)
{
    return place;
}

struct Rva001DD1B3 {
    Rva001DD1B3(const Rva001DD1B3 &that);
};

namespace _STL {

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value)
{
    if (p)
        new (p) Rva001DD1B3(*(const Rva001DD1B3 *)&value);
}

}

template void _STL::_Construct(Rva001DD1B3 *, const Rva001DD1B3 &);
