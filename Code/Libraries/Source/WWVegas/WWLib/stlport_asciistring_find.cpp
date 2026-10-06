// cl: /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??$__find@PAVAsciiString@@PBD@_STL@@YAPAVAsciiString@@PAV1@0ABQBDABUrandom_access_iterator_tag@0@@Z @0x00136401 171B
// STLport 4.5.3 random-access __find over AsciiString for a const char* key.
// Retail calls StringBase<char>::compare(PBD) (row 0x000069B1) per element with
// the SGI 4x-unrolled loop plus remainder switch; the 27B caller 0x0007983D is
// the find wrapper that passes the tag local. Evidence: unrolled compare/test/je
// shape, trip_count (last-first)>>4 with 4B elements, tail switch on remainder.
#include <vector>
#include <algorithm>
template <typename T> class StringBase {
public:
    int compare(const char *s) const;
protected:
    char *m_data;
};
class AsciiString : public StringBase<char> {};
inline bool operator==(const AsciiString &a, const char *b) { return a.compare(b) == 0; }
template AsciiString *_STL::__find(AsciiString *, AsciiString *, const char *const &, const _STL::random_access_iterator_tag &);
template AsciiString *_STL::find(AsciiString *, AsciiString *, const char *const &);
