// cl: /DNDEBUG /MD
// ??$copy@PAVRva00403927@@PAV1@@_STL@@YAPAVRva00403927@@PAV1@00@Z @0x00403BD2 29B
// _STL::copy<Rva00403927> forwarding wrapper, retail 29 bytes. Pushes NULL
// distance and a tag local, then calls the rowed 5-arg __copy at 0x004039E0.
// Dedicated TU so the __copy call stays external. Called by 0x004043C2.
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

namespace _STL
{
template <class InputIter, class OutputIter, class Distance>
__declspec(noinline) OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &, Distance *);

template <>
Rva00403927 *copy<Rva00403927 *, Rva00403927 *>(Rva00403927 *first, Rva00403927 *last, Rva00403927 *result)
{
    random_access_iterator_tag tag;
    return __copy(first, last, result, tag, (int *)0);
}
}
