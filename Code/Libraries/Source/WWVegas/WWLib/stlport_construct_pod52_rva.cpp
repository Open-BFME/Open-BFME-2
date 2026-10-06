// cl: /DNDEBUG /MD
// ??$_Construct@UBfmePod52@@U1@@_STL@@YAXPAUBfmePod52@@ABU1@@Z @0x001DD2DC 18B
// Null-guarded placement copy over the 52-byte element whose real copy ctor
// is the rowed Rva001DD0A0 copy at 0x001DD0A0 (twin-pinned as BfmePod52 copy).
// Same 18B frameless shape as rowed _Construct 0x004AE915.
typedef unsigned int size_t;

inline void *operator new(size_t, void *place)
{
    return place;
}

struct BfmePod52 {
    BfmePod52(const BfmePod52 &that);
};

struct Rva001DD0A0 {
    Rva001DD0A0(const Rva001DD0A0 &that);
};

namespace _STL {

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value)
{
    if (p)
        new (p) Rva001DD0A0(*(const Rva001DD0A0 *)&value);
}

}

template void _STL::_Construct(BfmePod52 *, const BfmePod52 &);
