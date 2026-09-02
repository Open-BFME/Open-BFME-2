// ?do_get@?$num_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@0AAVios_base@2@AAHAA_N@Z
// partial score=0.85 date=2026-09-02
// ?do_get@?$num_get@... (bool &), the wide twin
// partial score=0.85 date=2026-09-02
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
//
// Found by tools/vtable_gaps.py as the one slot of the wide num_get vtable
// with no ledger row - the bool overload, the last one left unclaimed once the
// other ten were named. Two things confirm it. The vendored instantiation
// compiles to exactly 631 bytes against 631, and the same holds for the
// other twin, which is not a coincidence twice. And decode_calls.py reads the
// REL32s as numpunct<wchar_t>::truename and falsename, which only the boolalpha
// path of do_get(bool &) calls; both are now pinned.
//
// What is left is one frame decision, and it is the first difference at 0x17:
// retail reserves 0x1C bytes of locals, cl 13.10 reserves 0x24 and pushes ebp
// as a fifth register. Downstream of that almost every byte shifts, which is
// why the diff count is high while the length is exact - retail also stores
// the zero straight to its stack slot where cl zeroes edi and spills it.
//
// Refuted: /Ob0 (624 bytes), /Ob1, /O2, /Os (506 bytes) and _STLP_USE_MALLOC
// all leave the frame at 0x24 or make it worse.

#include <locale>

template class _STL::num_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
