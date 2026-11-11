// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata /D_STLP_NO_EXCEPTIONS
// stlport
// STLport 4.5.3 APIs isolated from stlport_asciistring_record_bodies.cpp.
// Preserve the existing size/code-generation views and native call pins;
// these declarations do not establish complete application record layouts.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{ return a < b ? b : a; }
}
#include <vector>
#include "ascii_string.h"

struct BfmeAssignRecord28 { AsciiString s; int a[6]; BfmeAssignRecord28 &operator=(const BfmeAssignRecord28 &); };
#include "../../../../GameEngine/Source/Common/ScoredKillTrackerView.h"
struct BfmeAssignRecord104 { int a[25]; AsciiString s; BfmeAssignRecord104 &operator=(const BfmeAssignRecord104 &); };
struct BfmeAssignRecord172 { int a[42]; AsciiString s; BfmeAssignRecord172 &operator=(const BfmeAssignRecord172 &); };

// The original reserve callers use their existing destruction owners.
namespace _STL {
template <> void _Destroy<ScoredKillTracker *>(ScoredKillTracker *, ScoredKillTracker *);
}
struct Rva003B8B61Elem;
void __cdecl Rva003B8B61Destroy(Rva003B8B61Elem *first, Rva003B8B61Elem *last, int unused);
namespace _STL { template <> __declspec(dllimport) __forceinline void __destroy_aux<BfmeAssignRecord104 *>(BfmeAssignRecord104 *first, BfmeAssignRecord104 *last, const __false_type &) { __false_type tag; ((void (__cdecl *)(BfmeAssignRecord104 *, BfmeAssignRecord104 *, const __false_type &))(void (__cdecl *)(Rva003B8B61Elem *, Rva003B8B61Elem *, int))&Rva003B8B61Destroy)(first, last, tag); } }

// These recovered APIs still depend on unresolved native record copy/destruction
// contracts. Keep their original implementations and flags isolated from the
// independent algorithms in stlport_asciistring_record_bodies.cpp.
namespace _STL {
template void vector<ScoredKillTracker, allocator<ScoredKillTracker> >::reserve(unsigned int);
template void vector<BfmeAssignRecord172, allocator<BfmeAssignRecord172> >::reserve(unsigned int);
template void vector<BfmeAssignRecord104, allocator<BfmeAssignRecord104> >::reserve(unsigned int);
template void vector<BfmeAssignRecord28, allocator<BfmeAssignRecord28> >::push_back(const BfmeAssignRecord28 &);
}
