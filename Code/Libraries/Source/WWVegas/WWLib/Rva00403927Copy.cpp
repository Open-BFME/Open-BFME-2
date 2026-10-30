// cl: /DNDEBUG /MD
// ??$__copy@PAVRva00403927@@PAV1@H@_STL@@YAPAVRva00403927@@PAV1@00ABUrandom_access_iterator_tag@0@PAH@Z @0x004039E0 50B
// _STL::__copy<Rva00403927> random-access loop, retail 50 bytes. Count via
// idiv by stride 0x14, per-element operator= through the rowed 0x00403927.
// Called by the 29B forwarding wrapper at 0x00403BD2 (copy dispatch with tag
// and NULL distance). Dedicated TU so the operator= call stays external.
// stlport
class AsciiString;
#include <vector>

class Rva00403927
{
public:
    Rva00403927(const Rva00403927 &other);
    Rva00403927 &operator=(const Rva00403927 &other);
private:
    int m_00;
    int m_04;
    _STL::vector<AsciiString> m_names;
};


template Rva00403927 *_STL::__copy(Rva00403927 *, Rva00403927 *, Rva00403927 *, const random_access_iterator_tag &, int *);
