// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 members, each placed by a single masked whole-.text
// hit. BfmeAssignRecordN is a size-only placeholder for a real N-byte record
// with a non-trivial operator=: the placed bodies step by N and call that
// operator= (pinned by call-site address; the 24-byte one is the matched
// ProductionPrerequisite::operator=). It is spelled here as an AsciiString
// plus ints only to give it that shape. The pair row calls the AsciiString
// copy constructor, which ties its key. No retail caller is claimed.
#include <vector>
#include <map>

template<class T> class StringBase {
    void *m_data;
    void releaseBuffer();
public:
    StringBase();
    StringBase(const StringBase &);
    StringBase &operator=(const StringBase &);
protected:
    __forceinline ~StringBase() { releaseBuffer(); }
};
class AsciiString : private StringBase<char> {
public:
    __forceinline AsciiString() {}
    __forceinline AsciiString(const AsciiString &o) : StringBase<char>(o) {}
    __forceinline ~AsciiString() {}
    AsciiString &operator=(const AsciiString &);
};
bool operator<(const AsciiString &, const AsciiString &);
bool operator==(const AsciiString &, const AsciiString &);
struct BfmeAssignRecord24 { AsciiString s; int a[5]; };
inline bool operator==(const BfmeAssignRecord24 &x, const BfmeAssignRecord24 &y) { return x.s == y.s; }
struct BfmeAssignRecord28 { AsciiString s; int a[6]; };
inline bool operator==(const BfmeAssignRecord28 &x, const BfmeAssignRecord28 &y) { return x.s == y.s; }
struct BfmeAssignRecord32 { AsciiString s; int a[7]; };
inline bool operator==(const BfmeAssignRecord32 &x, const BfmeAssignRecord32 &y) { return x.s == y.s; }
struct BfmeAssignRecord36 { AsciiString s; int a[8]; };
inline bool operator==(const BfmeAssignRecord36 &x, const BfmeAssignRecord36 &y) { return x.s == y.s; }
struct BfmeAssignRecord44 { AsciiString s; int a[10]; };
inline bool operator==(const BfmeAssignRecord44 &x, const BfmeAssignRecord44 &y) { return x.s == y.s; }
struct BfmeAssignRecord52 { AsciiString s; int a[12]; };
inline bool operator==(const BfmeAssignRecord52 &x, const BfmeAssignRecord52 &y) { return x.s == y.s; }
struct BfmePod8 { int a[2]; };
template class _STL::vector<BfmeAssignRecord24, _STL::allocator<BfmeAssignRecord24> >;
template class _STL::vector<BfmeAssignRecord28, _STL::allocator<BfmeAssignRecord28> >;
template class _STL::vector<BfmeAssignRecord32, _STL::allocator<BfmeAssignRecord32> >;
template class _STL::vector<BfmeAssignRecord36, _STL::allocator<BfmeAssignRecord36> >;
template class _STL::vector<BfmeAssignRecord44, _STL::allocator<BfmeAssignRecord44> >;
template class _STL::vector<BfmeAssignRecord52, _STL::allocator<BfmeAssignRecord52> >;
template struct _STL::pair<const AsciiString, BfmePod8>;
