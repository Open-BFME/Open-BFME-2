// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 members, each placed by a single masked whole-.text
// hit. BfmeAssignRecordN is a size-only placeholder for a real N-byte record
// with a non-trivial operator=: the placed bodies step by N and call that
// operator= (pinned by call-site address; the 24-byte one is the matched
// ProductionPrerequisite::operator=). It is spelled here as an AsciiString
// plus ints only to give it that shape. The pair row calls the AsciiString
// copy constructor, which ties its key. BfmeStringHeadRecordN is an N-byte
// record whose destructor the placed bodies inline as StringBase<char>::
// releaseBuffer on offset 0, which proves an AsciiString first member. The
// BfmeStringTailRecordN declarations below are also code-generation views with
// a trailing AsciiString, not complete application layouts. In particular,
// independent target copy/destruction evidence for BfmeStringTailRecord144 is
// modeled in stlport_stringtailrecord144_dtor.cpp and differs from this view.
// The assignable records spelled with ints first likewise follow only the
// placed helper layout; no application identity is inferred from their size.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
#include <map>

#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
bool operator==(const AsciiString &, const AsciiString &);
struct BfmeAssignRecord24 { AsciiString s; int a[5]; };
inline bool operator==(const BfmeAssignRecord24 &x, const BfmeAssignRecord24 &y) { return x.s == y.s; }
struct BfmeAssignRecord28 { AsciiString s; int a[6]; };
inline bool operator==(const BfmeAssignRecord28 &x, const BfmeAssignRecord28 &y) { return x.s == y.s; }
// This shape view supplies assignment helpers; the independently verified
// 71B destructor at0x0017330A owns destruction of the complete native record.
struct BfmeAssignRecord32 { AsciiString s; int a[7]; ~BfmeAssignRecord32(); BfmeAssignRecord32 &operator=(const BfmeAssignRecord32 &); };
inline bool operator==(const BfmeAssignRecord32 &x, const BfmeAssignRecord32 &y) { return x.s == y.s; }
struct BfmeAssignRecord36 { AsciiString s; int a[8]; BfmeAssignRecord36 &operator=(const BfmeAssignRecord36 &); };
inline bool operator==(const BfmeAssignRecord36 &x, const BfmeAssignRecord36 &y) { return x.s == y.s; }
struct BfmeAssignRecord44 { AsciiString s; int a[10]; };
inline bool operator==(const BfmeAssignRecord44 &x, const BfmeAssignRecord44 &y) { return x.s == y.s; }
struct BfmeAssignRecord52 { AsciiString s; int a[12]; };
inline bool operator==(const BfmeAssignRecord52 &x, const BfmeAssignRecord52 &y) { return x.s == y.s; }
struct BfmePod8 { int a[2]; };
struct BfmeAssignRecord84 { AsciiString s; int a[20]; BfmeAssignRecord84 &operator=(const BfmeAssignRecord84 &); };
inline bool operator==(const BfmeAssignRecord84 &x, const BfmeAssignRecord84 &y) { return x.s == y.s; }
struct BfmeStringHeadRecord148 { AsciiString s; int a[36]; };
inline bool operator==(const BfmeStringHeadRecord148 &x, const BfmeStringHeadRecord148 &y) { return x.s == y.s; }
struct BfmeStringHeadRecord160 { AsciiString s; int a[39]; };
inline bool operator==(const BfmeStringHeadRecord160 &x, const BfmeStringHeadRecord160 &y) { return x.s == y.s; }
struct BfmeStringHeadRecord184 { AsciiString s; int a[45]; };
inline bool operator==(const BfmeStringHeadRecord184 &x, const BfmeStringHeadRecord184 &y) { return x.s == y.s; }
struct BfmeAssignRecord40 { int a[9]; AsciiString s; };
inline bool operator==(const BfmeAssignRecord40 &x, const BfmeAssignRecord40 &y) { return x.s == y.s; }
struct BfmeAssignRecord80 { int a[19]; AsciiString s; };
inline bool operator==(const BfmeAssignRecord80 &x, const BfmeAssignRecord80 &y) { return x.s == y.s; }
struct BfmeAssignRecord104 { int a[25]; AsciiString s; };
inline bool operator==(const BfmeAssignRecord104 &x, const BfmeAssignRecord104 &y) { return x.s == y.s; }
struct BfmeAssignRecord172 { int a[42]; AsciiString s; BfmeAssignRecord172 &operator=(const BfmeAssignRecord172 &); };
inline bool operator==(const BfmeAssignRecord172 &x, const BfmeAssignRecord172 &y) { return x.s == y.s; }
// Only the native0x90 stride is used by these algorithm instantiations.
// Native destruction and assignment are provided by their verified owners.
struct BfmeStringTailRecord144 { unsigned char body[0x90]; ~BfmeStringTailRecord144(); BfmeStringTailRecord144 &operator=(const BfmeStringTailRecord144 &); };
bool operator==(const BfmeStringTailRecord144 &x, const BfmeStringTailRecord144 &y);
// Native __destroy_aux at 0x4CC15D strides 156 bytes but calls the rowed
// owner-at-offset-zero destructor 0x10F149. Do not emit the implicit trailing
// AsciiString destructor from this historical copy/code-generation view.
struct BfmeStringTailRecord156 { int a[38]; AsciiString s; ~BfmeStringTailRecord156(); };
inline bool operator==(const BfmeStringTailRecord156 &x, const BfmeStringTailRecord156 &y) { return x.s == y.s; }
struct BfmeStringTailRecord180 { int a[44]; AsciiString s; };
inline bool operator==(const BfmeStringTailRecord180 &x, const BfmeStringTailRecord180 &y) { return x.s == y.s; }
namespace _STL {
// Declared only: defined by their owning TUs. Declaring these explicit
// specializations before the whole-class instantiations below suppresses
// emission here; this file's bodies keep calling them by the same names.
template <> void _Destroy<BfmeAssignRecord32 *>(BfmeAssignRecord32 *, BfmeAssignRecord32 *);
template <> BfmeAssignRecord32 *vector<BfmeAssignRecord32, allocator<BfmeAssignRecord32> >::erase(BfmeAssignRecord32 *, BfmeAssignRecord32 *);
template <> BfmeAssignRecord172 *vector<BfmeAssignRecord172, allocator<BfmeAssignRecord172> >::erase(BfmeAssignRecord172 *, BfmeAssignRecord172 *);
}
template class _STL::vector<BfmeAssignRecord24, _STL::allocator<BfmeAssignRecord24> >;
template class _STL::vector<BfmeAssignRecord28, _STL::allocator<BfmeAssignRecord28> >;
// Emit the recovered record32 algorithms without unrelated vector APIs.
namespace _STL {
template BfmeAssignRecord32 *__copy_backward<BfmeAssignRecord32 *, BfmeAssignRecord32 *, int>(BfmeAssignRecord32 *, BfmeAssignRecord32 *, BfmeAssignRecord32 *, const random_access_iterator_tag &, int *);
template void fill<BfmeAssignRecord32 *, BfmeAssignRecord32>(BfmeAssignRecord32 *, BfmeAssignRecord32 *, const BfmeAssignRecord32 &);
template BfmeAssignRecord32 *__copy_backward_ptrs<BfmeAssignRecord32 *, BfmeAssignRecord32 *>(BfmeAssignRecord32 *, BfmeAssignRecord32 *, BfmeAssignRecord32 *, const __false_type &);
template BfmeAssignRecord32 *__copy<BfmeAssignRecord32 *, BfmeAssignRecord32 *, int>(BfmeAssignRecord32 *, BfmeAssignRecord32 *, BfmeAssignRecord32 *, const random_access_iterator_tag &, int *);
template BfmeAssignRecord32 *__copy_ptrs<BfmeAssignRecord32 *, BfmeAssignRecord32 *>(BfmeAssignRecord32 *, BfmeAssignRecord32 *, BfmeAssignRecord32 *, __false_type);
}
template class _STL::vector<BfmeAssignRecord36, _STL::allocator<BfmeAssignRecord36> >;
template class _STL::vector<BfmeAssignRecord44, _STL::allocator<BfmeAssignRecord44> >;
template class _STL::vector<BfmeAssignRecord52, _STL::allocator<BfmeAssignRecord52> >;
template struct _STL::pair<const AsciiString, BfmePod8>;
template class _STL::vector<BfmeAssignRecord84, _STL::allocator<BfmeAssignRecord84> >;
template class _STL::vector<BfmeStringHeadRecord148, _STL::allocator<BfmeStringHeadRecord148> >;
template class _STL::vector<BfmeStringHeadRecord160, _STL::allocator<BfmeStringHeadRecord160> >;
template class _STL::vector<BfmeStringHeadRecord184, _STL::allocator<BfmeStringHeadRecord184> >;
template class _STL::vector<BfmeAssignRecord40, _STL::allocator<BfmeAssignRecord40> >;
template class _STL::vector<BfmeAssignRecord80, _STL::allocator<BfmeAssignRecord80> >;
template class _STL::vector<BfmeAssignRecord104, _STL::allocator<BfmeAssignRecord104> >;
template class _STL::vector<BfmeAssignRecord172, _STL::allocator<BfmeAssignRecord172> >;
namespace _STL {
template void __destroy_aux<BfmeStringTailRecord144 *>(BfmeStringTailRecord144 *, BfmeStringTailRecord144 *, const __false_type &);
template void _Destroy<BfmeStringTailRecord144 *>(BfmeStringTailRecord144 *, BfmeStringTailRecord144 *);
template BfmeStringTailRecord144 *__copy<BfmeStringTailRecord144 *, BfmeStringTailRecord144 *, int>(BfmeStringTailRecord144 *, BfmeStringTailRecord144 *, BfmeStringTailRecord144 *, const random_access_iterator_tag &, int *);
template void _Destroy<BfmeStringTailRecord144>(BfmeStringTailRecord144 *);
}
template class _STL::vector<BfmeStringTailRecord156, _STL::allocator<BfmeStringTailRecord156> >;
template class _STL::vector<BfmeStringTailRecord180, _STL::allocator<BfmeStringTailRecord180> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??$_Destroy@PAVRva0036105B@@@_STL@@YAXPAVRva0036105B@@0@Z=??$_Destroy@PAUBfmeStringHeadRecord148@@@_STL@@YAXPAUBfmeStringHeadRecord148@@0@Z")

// Both assignment spellings designate the existing45B native body51C3F.
#pragma comment(linker, "/alternatename:??4BfmeStringTailRecord144@@QAEAAU0@ABU0@@Z=??4Rva00051C3F@@QAEAAV0@ABV0@@Z")
