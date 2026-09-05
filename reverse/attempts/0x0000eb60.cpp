// ?do_put@?$num_put@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@AAVios_base@2@G_N@Z
// partial score=0.735 date=2026-09-05
// ?do_put@?$num_put@GV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$ostreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@AAVios_base@2@G_N@Z
// partial score=0.735 date=2026-09-05
//
// STLport 4.5.3 num_put<wchar_t>::do_put(iter, ios_base&, wchar_t, bool) --
// the boolalpha overload -- retail 0x0000EB60, 371 bytes.  Carried only the
// machine byte-dump row ?d_0000eb60@@YAXXZ in Code/gen_asm/d_0000b550.asm.
//
// IDENTITY IS SETTLED, do not re-derive it.  The decorated name above compiles
// and resolves; add_match accepted it and byte-compared against the right
// target.  The upstream body is vendor/stlport/stl/_num_put.c lines 422-447 and
// it maps onto the retail disassembly instruction for instruction:
//
//   if (!(__f.flags() & ios_base::boolalpha))          -> test ah,1 / jne  (+27)
//     return this->do_put(__s, __f, __fill, (long)__val);  -> call [eax+0x1c] (+49)
//   locale __loc = __f.getloc();                       -> call 0x00007EB0  (+68)
//   const numpunct<_CharT>& __np = *(const numpunct<_CharT>*)__f._M_numpunct_facet();
//                                                      -> mov ecx,[esi+0x44] (+73)
//   basic_string<_CharT> __str = __val ? __np.truename() : __np.falsename();
//                                                      -> call 0x0000EA30 / 0x0000EA50
//                                                         then copy ctor 0x0000EA90
//   ios_base::fmtflags __flags = __f.flags();
//   if ((__flags & adjustfield) == internal)           -> and cl,7 / cmp cl,4 (+240)
//     __flags = (__flags & ~adjustfield) | right;      -> and eax,~5 / or eax,2
//   return __copy_integer_and_fill(...)                -> call 0x0000ECE0  (+304)
//
// CALLEE MAP, decoded from this body's own REL32 displacements
// (target = 0xEB60 + offset + 5 + int32_le) and looked up in both ledgers:
//
//   +0x068 0x00007EB0  ios_base::getloc                        (functions.csv)
//   +0x085 0x0000EA30  numpunct<char>::truename                (ICF-folded; the
//   +0x09B 0x0000EA50  numpunct<char>::falsename                wide twins share
//                                                               the narrow bodies)
//   +0x0B2 0x0000EA90  basic_string<unsigned short> copy ctor  (wide -- this is
//                                                               what proves the
//                                                               G instantiation)
//   +0x0CF 0x0000B3C0  _String_base<char>::~_String_base       (ICF-folded, x2)
//   +0x0E6 0x0000B3C0  ditto
//   +0x130 0x0000ECE0  __copy_integer_and_fill<G, ostreambuf_iterator<G> >
//   +0x146 0x00030830  free  (C++-linkage spelling ?free@@YAXPAX@Z, symbols.csv)
//
// The element is wide (G / unsigned short, this build is /Zc:wchar_t-): 0x0000EA90
// and 0x0000ECE0 are both unambiguously the wide instantiations.
//
// WHAT THIS STASH IS.  Not a hand-rolled body -- the TU below is four lines.
// The whole-class explicit instantiation already emits a body with retail's
// exact control-flow graph; the entire remaining problem is a single MSVC
// inlining decision.  Two variants were measured against the retail bytes:
//
//   flags                                          exact prefix   similarity
//   /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC    97        0.654
//   /EHsc /MD /D_STLP_USE_STATIC_LIB   (this stash)       134        0.735
//
// DROPPING _STLP_USE_MALLOC IS THE FIND.  Under it, _STLP_alloc_proxy reaches
// __malloc_alloc::deallocate, which is `free((char*)p)` with free declared
// extern "C" -- nothrow, so the two temporaries need no unwind region, MSVC
// drops every EH state store, hoists free's import thunk into ebp and emits
// `ff d5` indirect calls.  That variant loses ebp to the hoist (retail pushes
// ebx only) and every subsequent esp displacement shifts by four, which is why
// it diverges at byte 97 and never re-converges.
//
// Without _STLP_USE_MALLOC the allocator is __node_alloc, whose _M_deallocate
// has C++ linkage and may throw.  That restores, byte for byte against retail:
//   * `push ebx` alone in the prologue of the boolalpha path (+0x60)
//   * the ebx live-temporary mask, 1 for truename and 2 for falsename
//   * every unwind state store: `c7 44 24 38 00 00 00 00` (+0x76),
//     `89 5c 24 38` (+0xA5), `c7 44 24 38 05 00 00 00` (+0xBA),
//     `c7 44 24 38 04 00 00 00` (+0xD7), and the `5b` pop at +0xDF
//   * the ebx spill `89 5c 24 08` at +0xCB
// so the first 134 bytes are exact and the frame layout is right throughout.
//
// THE ONE REMAINING GAP.  Retail CALLS ~_String_base out of line at 0x0000B3C0
// for both EH-tracked temporaries; this build still inlines the deallocation:
//
//   retail  +0xC2  74 10  83 e3 fd  8d 4c 24 18  89 5c 24 08  e8 8c c7 ff ff
//   this    +0xC2  74 35  8b 4c 24 18 8b 44 24 20 2b c1 83 e3 fd d1 f8 85 c9
//                  89 5c 24 08  74 1e  03 c0 3d 80 00 00 00 76 0b 51 e8 ...
//
// Same instruction, same ebx mask, same spill slot -- only inlined instead of
// called, and the widened branch displacement misaligns everything after it.
// Retail's 0x0000B3C0 is 63 bytes and carries its OWN /EHsc frame (see the note
// in Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string_base_dtor.cpp):
// that is the shape `if (_M_start) free(_M_start)` takes when free has C++
// linkage.  A destructor carrying its own unwind region is what MSVC 7.1
// refuses to inline, which is exactly why retail calls it.
//
// So the target configuration is _STLP_USE_MALLOC's deallocation shape (plain
// free, giving the 63-byte 0x0000B3C0 body) with free spelled as a C++-linkage
// function (giving the EH region that blocks the inline).  The vendored headers
// cannot express that combination: <cstdlib> brings free in as `using ::free`,
// so it keeps C linkage, and redeclaring it in this TU collides with that
// using-declaration.
//
// NEXT ATTEMPT SHOULD GO HAND-ROLLED, on the model of
// stlport_wide_string_reserve.cpp and stlport_narrow_string_base_dtor.cpp:
// declare `void __cdecl free(void *);` at global scope with C++ linkage (NOT
// extern "C" -- that is the whole point), hand-declare the minimum of
// ios_base (flags at +4, width at +0x1C, _M_numpunct_facet at +0x44 -- all
// three offsets are read straight out of the disassembly above), locale,
// numpunct, basic_string and ostreambuf_iterator (8 bytes: the ret 0x18 arity
// only closes at that width), and leave every callee in the map above
// DECLARED, NOT DEFINED, pinning each by address in reverse/symbols.csv so the
// REL32 displacements stay retail's.  Run tools/pin_consistency.py --symbol
// before pinning and --check after.
//
// FLAGS ALREADY RULED OUT, do not re-test:
//   /D_STLP_USE_TEMPLATE_EXPORT alone -- the header's own
//     `_STLP_EXPORT_TEMPLATE_CLASS num_put<wchar_t, ...>` becomes an extern
//     template (_STLP_EXPORT resolves to extern here), so nothing is emitted
//     and the symbol is absent from the object.
//   /D_STLP_USE_TEMPLATE_EXPORT with an explicit `template class num_put<...>`
//     -- C2949, duplicate explicit instantiation.
//   /D_STLP_USE_TEMPLATE_EXPORT /D_STLP_DESIGNATED_DLL -- flips _STLP_EXPORT
//     back to a real instantiation, but instantiating basic_ios that early
//     trips C2908 on the narrow/widen specialisations in stl/_ios.h:158,165.
//   An explicit `template class _STL::_String_base<wchar_t, ...>;` in this TU
//     -- forces the out-of-line COMDAT to exist but does not stop the inline.

// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <locale>

template class _STL::_String_base<wchar_t, _STL::allocator<wchar_t> >;
template class _STL::num_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
