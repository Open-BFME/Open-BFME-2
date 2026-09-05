// ?do_put@?$money_put@DV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@_NAAVios_base@2@DO@Z
// partial score=0.907 date=2026-09-05
// ?do_put@?$money_put@DV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@2@V32@_NAAVios_base@2@DO@Z
// partial score=0.907 date=2026-09-05
//
// STLport 4.5.3 money_put<char>::do_put(iter, bool, ios_base&, char_type,
// long double), retail 0x0000BDA0, 174 bytes. First attempt on this address;
// it carried only the byte-dump row ?d_0000bda0@@YAXXZ in
// Code/gen_asm/d_0000b550.asm.
//
// IDENTITY IS SETTLED, and it came from the vtable rather than from the body's
// shape. tools/vtable_owner.py puts this address in a three-slot facet vtable
// bounded by the RTTI pointers at 0x008F3B58 and 0x008F3BA4:
//
//     slot 0  0x000072C0  the ICF-folded facet deleting destructor
//     slot 1  0x0000C410  2793 bytes, unclaimed
//     slot 2  0x0000BDA0  <== this body
//
// The vtable immediately before it in the image has exactly the same shape and
// BOTH its non-destructor slots are already claimed in reverse/functions.csv:
//
//     slot 1  0x00011230  money_get<char>::do_get(..., basic_string&)
//     slot 2  0x0000C000  money_get<char>::do_get(..., long double&)
//
// and 0x0000C000's own bank records that the long-double slot is the one that
// delegates to the string slot through the vtable. This body does the same
// thing in the same slot, so slot 1 here is the 2793-byte
// do_put(const string_type&) -- which is the long body at
// vendor/stlport/stl/_monetary.c:350 -- and this is the long-double overload.
//
// The upstream body is in vendor/stlport/stl/_monetary.h and it accounts for
// the two things that look like errors in the disassembly:
//
//     virtual iter_type do_put(iter_type __s, bool __intl, ios_base& __str,
//                              char_type __fill, long double /* __units */) const {
//       locale __loc = __str.getloc();
//       _CharT __buf[64];
//       return do_put(__s, __intl, __str, __fill, __buf + 0);
//     }
//
// __units is IGNORED -- upstream comments the parameter name out -- and the
// 64-byte buffer is never written before being handed to the string
// constructor. So the whole body is getloc at 0x00007EB0, the implicit
// basic_string(const char*, const allocator&) temporary at 0x00009100, the
// delegation through vtable slot 1, then the temporary's destructor and
// ~locale. `ret 0x20` is 4+8+4+4+4+8.
//
// 120 of 174 bytes exact, and everything up to the string temporary's
// destructor is byte-identical INCLUDING both REL32 displacements, which is
// what confirms the identification independently.
//
// TWO FLAGS ARE NEEDED AND ONLY ONE OF THEM IS REACHABLE:
//
//   1. _STLP_USE_MALLOC. Have it. It puts the temporary's destructor inline as
//      `if (p) free(p)`; without it _STLP_alloc_proxy reaches
//      __node_alloc::_M_deallocate and the tail diverges 25 bytes earlier, at
//      the first byte of the destructor. This is the same lever as the
//      0x0000EB60 bank, used in the opposite direction.
//
//   2. free with C++ LINKAGE. Do NOT have it, and this is the whole remaining
//      gap. reverse/symbols.csv pins ?free@@YAXPAX@Z at 0x00030830 and records
//      the mechanism: as extern "C" the call is nothrow, so MSVC reaches it
//      indirectly through the import and drops the unwind state store beside
//      it. Retail has the direct call and the store:
//
//        retail  85 c0  c6 44 24 5c 00  74 09  50  e8 0b 4a 02 00  83 c4 04
//        this    85 c0                  74 0a  50  ff 15 ....
//
// THE BLOCKER. Declaring `void __cdecl free(void *);` at global scope ahead of
// <locale> -- which is how the hand-rolled TUs such as
// stlport_narrow_string_base_dtor.cpp and stlport_locale_equal.cpp get the
// C++-linkage spelling -- fails here, because <locale> pulls in the vendor
// <stdlib.h>:
//
//   ...Vc7\include\stdlib.h(279) : error C2375: 'free' : redefinition;
//   different linkage
//
// No TU in the repo currently combines `#include <locale>` with a C++-linkage
// free, so this is unsolved rather than merely unattempted.
//
// NEXT PASS, in order of promise:
//   * suppress the vendor header by defining _INC_STDLIB before <locale> and
//     declare the handful of names STLport actually wants from it (free,
//     malloc, realloc, size_t, abort, exit). If the cascade is small this is
//     the clean answer and it unlocks every other <locale> TU that needs the
//     C++-linkage free.
//   * hand-roll the body in the stlport_wide_string_reserve.cpp style. It is
//     small -- getloc, a string constructor, one virtual call, two destructors
//     -- and every callee is already pinned or claimed, so this is far more
//     tractable here than for the bigger facet bodies.
//   * landing 0x0000C410 first (the 2793-byte string overload, still
//     unclaimed) would give this one a same-TU sibling and may settle the
//     linkage question on its own.

// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport

#include <locale>

template class _STL::money_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >;
