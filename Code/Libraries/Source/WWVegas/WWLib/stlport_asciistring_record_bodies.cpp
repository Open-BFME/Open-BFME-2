// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include <map>

#include "ascii_string.h"
// Suppress this TU's non-retail copy of ?erase@?$vector@VScoredKillTracker@@V?$allocator@VScoredKillTracker@@@_STL@@@_STL@@QAEPA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ScoredKillTracker;
namespace _STL { template <> ScoredKillTracker * vector<ScoredKillTracker,allocator<ScoredKillTracker> >::erase(ScoredKillTracker *,ScoredKillTracker *); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAUBfmeStringTailRecord156@@IU1@@_STL@@YAPAUBfmeStringTailRecord:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringTailRecord156;
namespace _STL { template <> BfmeStringTailRecord156 * __uninitialized_fill_n<BfmeStringTailRecord156 *,unsigned int,BfmeStringTailRecord156>(BfmeStringTailRecord156 *,unsigned int,BfmeStringTailRecord156 const &,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAUBfmeStringTailRecord156@@PAU1@@_STL@@YAPAUBfmeStringTailRecord1:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringTailRecord156;
namespace _STL { template <> BfmeStringTailRecord156 * __uninitialized_copy<BfmeStringTailRecord156 *,BfmeStringTailRecord156 *>(BfmeStringTailRecord156 *,BfmeStringTailRecord156 *,BfmeStringTailRecord156 *,__false_type const &); }
// Suppress this TU's non-retail copy of ?erase@?$vector@UBfmeAssignRecord104@@V?$allocator@UBfmeAssignRecord104@@@_STL@@@_STL@@QAE:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeAssignRecord104;
namespace _STL { template <> BfmeAssignRecord104 * vector<BfmeAssignRecord104,allocator<BfmeAssignRecord104> >::erase(BfmeAssignRecord104 *,BfmeAssignRecord104 *); }
// Suppress this TU's non-retail copy of ??1?$vector@UBfmeAssignRecord172@@V?$allocator@UBfmeAssignRecord172@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeAssignRecord172;
namespace _STL { template <> vector<BfmeAssignRecord172,allocator<BfmeAssignRecord172> >::~vector(); }
// Suppress this TU's non-retail copy of ??1?$vector@VScoredKillTracker@@V?$allocator@VScoredKillTracker@@@_STL@@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ScoredKillTracker;
namespace _STL { template <> vector<ScoredKillTracker,allocator<ScoredKillTracker> >::~vector(); }
bool operator<(const AsciiString &, const AsciiString &);
bool operator==(const AsciiString &, const AsciiString &);
struct BfmeAssignRecord24 { AsciiString s; int a[5]; BfmeAssignRecord24 &operator=(const BfmeAssignRecord24 &); };
inline bool operator==(const BfmeAssignRecord24 &x, const BfmeAssignRecord24 &y) { return x.s == y.s; }
// Native copy/fill callers reach the separately verified record assignments.
// These size-only views supply algorithm strides, not assignment layouts;
// declare the owners so implicit assignments cannot compete with them.
struct BfmeAssignRecord28 { AsciiString s; int a[6]; BfmeAssignRecord28 &operator=(const BfmeAssignRecord28 &); };
inline bool operator==(const BfmeAssignRecord28 &x, const BfmeAssignRecord28 &y) { return x.s == y.s; }
// This shape view supplies assignment helpers; the independently verified
// 71B destructor at0x0017330A owns destruction of the complete native record.
struct BfmeAssignRecord32 { AsciiString s; int a[7]; ~BfmeAssignRecord32(); BfmeAssignRecord32 &operator=(const BfmeAssignRecord32 &); };
inline bool operator==(const BfmeAssignRecord32 &x, const BfmeAssignRecord32 &y) { return x.s == y.s; }
struct BfmeAssignRecord36 { AsciiString s; int a[8]; BfmeAssignRecord36 &operator=(const BfmeAssignRecord36 &); };
inline bool operator==(const BfmeAssignRecord36 &x, const BfmeAssignRecord36 &y) { return x.s == y.s; }
#include "../../../../GameEngine/Include/GameLogic/CarryoverUnit.h"
#include "../../../../GameEngine/Source/Common/ScoredKillTrackerView.h"
struct BfmeAssignRecord52 { AsciiString s; int a[12]; BfmeAssignRecord52 &operator=(const BfmeAssignRecord52 &); ~BfmeAssignRecord52(); };
inline bool operator==(const BfmeAssignRecord52 &x, const BfmeAssignRecord52 &y) { return x.s == y.s; }
struct BfmeAssignRecord84 { AsciiString s; int a[20]; BfmeAssignRecord84 &operator=(const BfmeAssignRecord84 &); };
inline bool operator==(const BfmeAssignRecord84 &x, const BfmeAssignRecord84 &y) { return x.s == y.s; }
struct BfmeStringHeadRecord148 { AsciiString s; int a[36]; BfmeStringHeadRecord148() {} BfmeStringHeadRecord148(const BfmeStringHeadRecord148 &); };
inline bool operator==(const BfmeStringHeadRecord148 &x, const BfmeStringHeadRecord148 &y) { return x.s == y.s; }
struct BfmeStringHeadRecord160 { AsciiString s; int a[39]; };
inline bool operator==(const BfmeStringHeadRecord160 &x, const BfmeStringHeadRecord160 &y) { return x.s == y.s; }
// Native184B stride; this algorithm view performs no member accesses.
struct BfmeStringHeadRecord184 { unsigned char body[184]; ~BfmeStringHeadRecord184(); BfmeStringHeadRecord184 &operator=(const BfmeStringHeadRecord184 &); };
bool operator==(const BfmeStringHeadRecord184 &x, const BfmeStringHeadRecord184 &y);
// The 40-byte camera-track key; its assignment is rowed at 0x00540053
// (StlSweepW4Rva00540053.cpp).
class Rva0054000B { public: Rva0054000B &operator=(const Rva0054000B &other); private: char m_pad[40]; };
// Forward and backward copies use the same opaque element and assignment.
struct Rva0051FC54Element { unsigned char bytes[80]; Rva0051FC54Element &operator=(const Rva0051FC54Element &); };
struct BfmeAssignRecord104 { int a[25]; AsciiString s; BfmeAssignRecord104 &operator=(const BfmeAssignRecord104 &); };
inline bool operator==(const BfmeAssignRecord104 &x, const BfmeAssignRecord104 &y) { return x.s == y.s; }
// Retail's range destroy for this record (0x003B8E13) passes a tag to the
// stride-0x68 loop 0x003B8B61, rowed as Rva003B8B61Destroy; forwarding the
// loop there makes this TU's _Destroy copy retail's body.
struct Rva003B8B61Elem;
void __cdecl Rva003B8B61Destroy(Rva003B8B61Elem *first, Rva003B8B61Elem *last, int unused);
namespace _STL { template <> __declspec(dllimport) __forceinline void __destroy_aux<BfmeAssignRecord104 *>(BfmeAssignRecord104 *first, BfmeAssignRecord104 *last, const __false_type &) { __false_type tag; ((void (__cdecl *)(BfmeAssignRecord104 *, BfmeAssignRecord104 *, const __false_type &))(void (__cdecl *)(Rva003B8B61Elem *, Rva003B8B61Elem *, int))&Rva003B8B61Destroy)(first, last, tag); } }
struct BfmeAssignRecord172 { int a[42]; AsciiString s; BfmeAssignRecord172 &operator=(const BfmeAssignRecord172 &); };
inline bool operator==(const BfmeAssignRecord172 &x, const BfmeAssignRecord172 &y) { return x.s == y.s; }
// The native range worker at1EAF5E walks 0xAC-byte records and invokes
// virtual slot0 with argument0. This size-only assignment view cannot emit
// its destruction. The native worker reads only first/last; preserve the
// caller's existing unused tag argument while naming its rowed owner.
class Rva001EAF5EElement;
void rva001EAF5E(Rva001EAF5EElement *, Rva001EAF5EElement *);
namespace _STL { template <> __declspec(dllimport) __forceinline void __destroy_aux<BfmeAssignRecord172 *>(BfmeAssignRecord172 *first, BfmeAssignRecord172 *last, const __false_type &) { __false_type tag; ((void (__cdecl *)(BfmeAssignRecord172 *, BfmeAssignRecord172 *, const __false_type &))(void (__cdecl *)(Rva001EAF5EElement *, Rva001EAF5EElement *))&rva001EAF5E)(first, last, tag); } }

// Declared only: each helper below is a byte-verified retail body rowed under
// another name (bound by /alternatename at the end of this file). These
// size-only views would otherwise emit their own non-retail copies.
namespace _STL {
}
// Only the native0x90 stride is used by these algorithm instantiations.
// Native destruction and assignment are provided by their verified owners.
struct BfmeStringTailRecord144 { unsigned char body[0x90]; ~BfmeStringTailRecord144(); BfmeStringTailRecord144 &operator=(const BfmeStringTailRecord144 &); };
bool operator==(const BfmeStringTailRecord144 &x, const BfmeStringTailRecord144 &y);
// Native __destroy_aux at 0x4CC15D strides 156 bytes but calls the rowed
// owner-at-offset-zero destructor 0x10F149. Do not emit the implicit trailing
// AsciiString destructor from this historical copy/code-generation view.
struct BfmeStringTailRecord156 { int a[38]; AsciiString s; ~BfmeStringTailRecord156(); };
inline bool operator==(const BfmeStringTailRecord156 &x, const BfmeStringTailRecord156 &y) { return x.s == y.s; }
// _Construct<BfmeStringTailRecord156> is the rowed copy construct at 0x004CC095: declare it so this
// unit calls it rather than emitting the only other copy of that name.
namespace _STL { template <> void _Construct<BfmeStringTailRecord156, BfmeStringTailRecord156>(BfmeStringTailRecord156 *__p, const BfmeStringTailRecord156 &__val); }
struct BfmeStringTailRecord180 { int a[44]; AsciiString s; BfmeStringTailRecord180(); ~BfmeStringTailRecord180(); };
inline bool operator==(const BfmeStringTailRecord180 &x, const BfmeStringTailRecord180 &y) { return x.s == y.s; }
namespace _STL {
// Declared only: defined by their owning TUs. Declaring these explicit
// specializations before the member instantiations below suppresses
// emission here; this file's bodies keep calling them by the same names.
template <> void _Destroy<BfmeAssignRecord32 *>(BfmeAssignRecord32 *, BfmeAssignRecord32 *);
template <> void _Destroy<ScoredKillTracker *>(ScoredKillTracker *, ScoredKillTracker *);
template <> BfmeAssignRecord32 *vector<BfmeAssignRecord32, allocator<BfmeAssignRecord32> >::erase(BfmeAssignRecord32 *, BfmeAssignRecord32 *);
template <> BfmeAssignRecord172 *vector<BfmeAssignRecord172, allocator<BfmeAssignRecord172> >::erase(BfmeAssignRecord172 *, BfmeAssignRecord172 *);
}
// Retain native copy providers also used by other vector units.
namespace _STL {
template void _Construct<BfmeStringHeadRecord160, BfmeStringHeadRecord160>(BfmeStringHeadRecord160 *, const BfmeStringHeadRecord160 &);
template BfmeStringHeadRecord184 *__copy<BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *, int>(BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *, const random_access_iterator_tag &, int *);
template BfmeAssignRecord104 *__copy<BfmeAssignRecord104 *, BfmeAssignRecord104 *, int>(BfmeAssignRecord104 *, BfmeAssignRecord104 *, BfmeAssignRecord104 *, const random_access_iterator_tag &, int *);
template void _Destroy<BfmeAssignRecord172 *>(BfmeAssignRecord172 *, BfmeAssignRecord172 *);
}
// Instantiate only the recovered operations, avoiding unrelated class members.
namespace _STL {
template void _Construct<BfmeStringHeadRecord148, BfmeStringHeadRecord148>(BfmeStringHeadRecord148 *, const BfmeStringHeadRecord148 &);
template BfmeAssignRecord52 *__copy_backward<BfmeAssignRecord52 *, BfmeAssignRecord52 *, int>(BfmeAssignRecord52 *, BfmeAssignRecord52 *, BfmeAssignRecord52 *, const random_access_iterator_tag &, int *);
template BfmeAssignRecord24 *__copy_backward<BfmeAssignRecord24 *, BfmeAssignRecord24 *, int>(BfmeAssignRecord24 *, BfmeAssignRecord24 *, BfmeAssignRecord24 *, const random_access_iterator_tag &, int *);
template BfmeAssignRecord36 *__copy_backward<BfmeAssignRecord36 *, BfmeAssignRecord36 *, int>(BfmeAssignRecord36 *, BfmeAssignRecord36 *, BfmeAssignRecord36 *, const random_access_iterator_tag &, int *);
template void fill<BfmeAssignRecord52 *, BfmeAssignRecord52>(BfmeAssignRecord52 *, BfmeAssignRecord52 *, const BfmeAssignRecord52 &);
template void fill<BfmeAssignRecord28 *, BfmeAssignRecord28>(BfmeAssignRecord28 *, BfmeAssignRecord28 *, const BfmeAssignRecord28 &);
template void fill<BfmeAssignRecord32 *, BfmeAssignRecord32>(BfmeAssignRecord32 *, BfmeAssignRecord32 *, const BfmeAssignRecord32 &);
template void fill<BfmeAssignRecord36 *, BfmeAssignRecord36>(BfmeAssignRecord36 *, BfmeAssignRecord36 *, const BfmeAssignRecord36 &);
template BfmeStringHeadRecord184 *__copy_backward<BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *, int>(BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *, const random_access_iterator_tag &, int *);
template void __destroy_aux<BfmeStringHeadRecord184 *>(BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *, const __false_type &);
template BfmeAssignRecord172 *__copy_backward<BfmeAssignRecord172 *, BfmeAssignRecord172 *, int>(BfmeAssignRecord172 *, BfmeAssignRecord172 *, BfmeAssignRecord172 *, const random_access_iterator_tag &, int *);
template BfmeAssignRecord104 *__copy_backward<BfmeAssignRecord104 *, BfmeAssignRecord104 *, int>(BfmeAssignRecord104 *, BfmeAssignRecord104 *, BfmeAssignRecord104 *, const random_access_iterator_tag &, int *);
template Rva0054000B *__copy_backward<Rva0054000B *, Rva0054000B *, int>(Rva0054000B *, Rva0054000B *, Rva0054000B *, const random_access_iterator_tag &, int *);
template Rva0051FC54Element *__copy_backward<Rva0051FC54Element *, Rva0051FC54Element *, int>(Rva0051FC54Element *, Rva0051FC54Element *, Rva0051FC54Element *, const random_access_iterator_tag &, int *);
template void fill<BfmeAssignRecord172 *, BfmeAssignRecord172>(BfmeAssignRecord172 *, BfmeAssignRecord172 *, const BfmeAssignRecord172 &);
template void fill<BfmeAssignRecord104 *, BfmeAssignRecord104>(BfmeAssignRecord104 *, BfmeAssignRecord104 *, const BfmeAssignRecord104 &);
template void fill<Rva0051FC54Element *, Rva0051FC54Element>(Rva0051FC54Element *, Rva0051FC54Element *, const Rva0051FC54Element &);
template void __destroy_aux<BfmeStringTailRecord144 *>(BfmeStringTailRecord144 *, BfmeStringTailRecord144 *, const __false_type &);
template void __destroy_aux<BfmeStringTailRecord156 *>(BfmeStringTailRecord156 *, BfmeStringTailRecord156 *, const __false_type &);
template void __destroy_aux<BfmeStringTailRecord180 *>(BfmeStringTailRecord180 *, BfmeStringTailRecord180 *, const __false_type &);
template void vector<BfmeAssignRecord104, allocator<BfmeAssignRecord104> >::_M_clear();
template void _Destroy<BfmeStringTailRecord144 *>(BfmeStringTailRecord144 *, BfmeStringTailRecord144 *);
template void _Destroy<BfmeStringHeadRecord184 *>(BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *);
template void _Destroy<BfmeStringTailRecord180 *>(BfmeStringTailRecord180 *, BfmeStringTailRecord180 *);
template void _Destroy<BfmeStringHeadRecord160 *>(BfmeStringHeadRecord160 *, BfmeStringHeadRecord160 *);
template void _Destroy<BfmeStringTailRecord156 *>(BfmeStringTailRecord156 *, BfmeStringTailRecord156 *);
template void vector<BfmeStringTailRecord156, allocator<BfmeStringTailRecord156> >::_M_clear();
template BfmeAssignRecord36 *__copy_ptrs<BfmeAssignRecord36 *, BfmeAssignRecord36 *>(BfmeAssignRecord36 *, BfmeAssignRecord36 *, BfmeAssignRecord36 *, __false_type);
template BfmeAssignRecord32 *__copy_ptrs<BfmeAssignRecord32 *, BfmeAssignRecord32 *>(BfmeAssignRecord32 *, BfmeAssignRecord32 *, BfmeAssignRecord32 *, __false_type);
template BfmeAssignRecord172 *__copy_ptrs<BfmeAssignRecord172 *, BfmeAssignRecord172 *>(BfmeAssignRecord172 *, BfmeAssignRecord172 *, BfmeAssignRecord172 *, __false_type);
template BfmeAssignRecord52 *__copy_ptrs<BfmeAssignRecord52 *, BfmeAssignRecord52 *>(BfmeAssignRecord52 *, BfmeAssignRecord52 *, BfmeAssignRecord52 *, __false_type);
template Rva0051FC54Element *__copy_ptrs<Rva0051FC54Element *, Rva0051FC54Element *>(Rva0051FC54Element *, Rva0051FC54Element *, Rva0051FC54Element *, __false_type);
template BfmeAssignRecord84 *__copy_ptrs<BfmeAssignRecord84 *, BfmeAssignRecord84 *>(BfmeAssignRecord84 *, BfmeAssignRecord84 *, BfmeAssignRecord84 *, __false_type);
template BfmeStringTailRecord144 *__copy<BfmeStringTailRecord144 *, BfmeStringTailRecord144 *, int>(BfmeStringTailRecord144 *, BfmeStringTailRecord144 *, BfmeStringTailRecord144 *, const random_access_iterator_tag &, int *);
template void __destroy_aux<BfmeAssignRecord52 *>(BfmeAssignRecord52 *, BfmeAssignRecord52 *, const __false_type &);
template void vector<BfmeStringTailRecord156, allocator<BfmeStringTailRecord156> >::push_back(const BfmeStringTailRecord156 &);
template ScoredKillTracker *__copy<ScoredKillTracker *, ScoredKillTracker *, int>(ScoredKillTracker *, ScoredKillTracker *, ScoredKillTracker *, const random_access_iterator_tag &, int *);
template void _Destroy<BfmeStringTailRecord144>(BfmeStringTailRecord144 *);
template void vector<BfmeAssignRecord104, allocator<BfmeAssignRecord104> >::clear();
}

// Both assignment spellings designate the existing45B native body51C3F.
#pragma comment(linker, "/alternatename:??4BfmeStringTailRecord144@@QAEAAU0@ABU0@@Z=??4Rva00051C3F@@QAEAAV0@ABV0@@Z")

// Pinned spellings of helpers whose byte-verified retail bodies are rowed
// under other names; each alias names the row at the pinned address.
#pragma comment(linker, "/alternatename:??$_Construct@UBfmeStringTailRecord156@@U1@@_STL@@YAXPAUBfmeStringTailRecord156@@ABU1@@Z=??$_Construct@VRva003AD160@@V1@@_STL@@YAXPAVRva003AD160@@ABV1@@Z")
#pragma comment(linker, "/alternatename:??4BfmeAssignRecord104@@QAEAAU0@ABU0@@Z=??4ArmySummary@@QAEAAV0@ABV0@@Z")
#pragma comment(linker, "/alternatename:??4BfmeAssignRecord24@@QAEAAU0@ABU0@@Z=??4ProductionPrerequisite@@QAEAAV0@ABV0@@Z")
#pragma comment(linker, "/alternatename:??0BfmeStringHeadRecord148@@QAE@ABU0@@Z=??0Rva0036105B@@QAE@ABV0@@Z")

// Both ABI aliases preserve the existing native pin endpoints.
#pragma comment(linker, "/alternatename:??1BfmeStringHeadRecord184@@QAE@XZ=??1RunwayInfo@FlightDeckBehavior@@QAE@XZ")
#pragma comment(linker, "/alternatename:??4BfmeStringHeadRecord184@@QAEAAU0@ABU0@@Z=??4Rva003A35A0Element@@QAEAAU0@ABU0@@Z")

// StlportVectorDtorDeferred.cpp and StlportVectorEraseRangeDeferred.cpp declare
// _Destroy<Rva002BBB96Element *> only. Its retail body is the stride-0x34 loop
// over the BfmeAssignRecord52 dtor (0x002B707E) at 0x002BB6A5, so the element is
// that 52-byte record and this unit's flags supply the copy.
// The loop is __destroy_aux's own, over the record base: this unit's flags keep
// a derived element's destructor out of line, which retail's body never calls.
struct Rva002BBB96Element : BfmeAssignRecord52 {};
namespace _STL {
template <> void _Destroy<Rva002BBB96Element *>(Rva002BBB96Element *first, Rva002BBB96Element *last)
{
	for (; first != last; ++first)
		_Destroy(static_cast<BfmeAssignRecord52 *>(first));
}
}

// Native fill 001EB84E receives the live CarryoverUnit temporary made by
// copy 001EB79E in fill-insert 001EBEAB; assignment is the real 001EB20E.
template void _STL::fill<CarryoverUnit *, CarryoverUnit>(CarryoverUnit *, CarryoverUnit *, const CarryoverUnit &);

// Native backward loop 001EB262 assigns CarryoverUnit ranges through 001EB20E.
template CarryoverUnit *_STL::__copy_backward<CarryoverUnit *, CarryoverUnit *, int>(CarryoverUnit *, CarryoverUnit *, CarryoverUnit *, const _STL::random_access_iterator_tag &, int *);
